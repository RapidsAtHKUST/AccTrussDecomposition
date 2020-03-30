#include "bucket.h"

/******* HASH_MAPPED BUCKET ********/

Bucket_element::Bucket_element(int mid, int mvalue)
: id(mid), value(mvalue), next(NULL), prev(NULL)
{}

Bucket::Bucket()
: max_value(0), current_min_value(1), elements(NULL, INT_MAX)
{}

Bucket::~Bucket() {
	for (int i=0; i<=max_value; ++i) {
		Bucket_element * head = buckets[i];
		if (head==NULL)
			continue;
		while(head!=NULL) {
			Bucket_element * todelete = head;
			head = head->next;
			delete todelete;
		}
	}
}

void Bucket::Initialize(int mmax_value) {
	max_value = mmax_value;
	current_min_value = max_value+1;

	elements.reset(NULL);

	buckets = std::vector<Bucket_element*>(max_value+1, NULL);
}

void Bucket::Insert(int id, int value)
{
	Bucket_element * & newHead = elements[id];
	if (newHead!=NULL) {
		Update(id, value);
		return;
	}
	Bucket_element * oldHead = buckets[value];
	newHead = new Bucket_element (id, value);
	newHead->next = oldHead;
	if (oldHead != NULL)
		oldHead->prev = newHead;
	buckets[value] = newHead;

	if (current_min_value > value)
		current_min_value = value;
}

void Bucket::Update(int id, int new_value)
{
	Bucket_element * elem = elements[id];
	if (elem==NULL) { // rare case
		elements.erase(id);
		return;
	}
	int old_value = elem->value;
	if (old_value == new_value)
		return;
	if (elem->prev == NULL)
		buckets[old_value] = elem->next;
	else
		elem->prev->next = elem->next;
	if (elem->next != NULL)
		elem->next->prev = elem->prev;

	Bucket_element * oldHead = buckets[new_value];
	elem->next = oldHead;
	if (oldHead != NULL)
		oldHead->prev = elem;
	buckets[new_value] = elem;
	elem->prev = NULL;
	elem->value = new_value;

	if(new_value<old_value) {
		if (current_min_value > new_value)
			current_min_value = new_value;
	}
	else if (current_min_value == old_value) {
		while (buckets[current_min_value] == NULL)
			current_min_value++;
	}
}

void Bucket::DecVal(int id) {
	Bucket_element * elem = elements[id];
	if (elem==NULL) { // rare case
		elements.erase(id);
		return;
	}
	if (elem->value > 0)
		Update(id, elem->value-1);
}

void Bucket::IncVal(int id) {
	Bucket_element * elem = elements[id];
	if (elem==NULL) { // rare case
		elements.erase(id);
		return;
	}
	if (elem->value > 0)
		Update(id, elem->value+1);
}

int Bucket::CurrentValue(int id) {
	Bucket_element * elem = elements[id];
	if (elem==NULL) { // rare case
		elements.erase(id);
		return -1;
	}
	return elem->value;
}

int Bucket::PopMin(int* ret_id, int* ret_value) {
	if (current_min_value>max_value)
		return -1;
	Bucket_element * elem = buckets[current_min_value];
	buckets[current_min_value] = elem->next;
	if (elem->next != NULL) {
		elem->next->prev = NULL;
	}
	while ((current_min_value <= max_value) &&
			(buckets[current_min_value] == NULL))
		current_min_value++;

	(*ret_id) = elem->id;
	(*ret_value) = elem->value;

	elements.erase(elem->id);
	delete elem;

	return 19;
}




/******* ARRAY BUCKET ********/

Naive_Bucket_element::Naive_Bucket_element()
: next(NULL), prev(NULL)
{}

Naive_Bucket::Naive_Bucket()
: max_value(0), current_min_value(1), elements(NULL), buckets(NULL), values(NULL), nb_elements(0)
{}

Naive_Bucket::~Naive_Bucket() {
	free (buckets);
	free (elements);
	free(values);
}

void Naive_Bucket::Initialize(int max_v, int nb_element) {
	int i;

	max_value = max_v;
	buckets = (Naive_Bucket_element **) malloc(sizeof(Naive_Bucket_element *) * (max_value+1));
	elements = (Naive_Bucket_element *) malloc(sizeof(Naive_Bucket_element) * nb_element);
	values = (int *) malloc(sizeof(int) * nb_element);
	nb_elements = nb_element;

	if (buckets == NULL || elements == NULL || values == NULL) {
		free(values);
		free(buckets);
		free(elements);
	}
	else {
		for (i = 0; i <= max_value; i++)
			buckets[i] = NULL;

		for (i = 0; i < nb_element; i++) {
			elements[i].prev = NULL;
			elements[i].next = NULL;
		}
	}

	current_min_value = max_value + 1;
}

void Naive_Bucket::Insert (int id, int value) {
	values[id] = value;

	elements[id].prev = NULL;
	elements[id].next = buckets[value];

	if (buckets[value] != NULL)
		buckets[value]->prev = &(elements[id]);
	else if (current_min_value > value)
		current_min_value = value;

	buckets[value] = &(elements[id]);
}

void Naive_Bucket::Update(int id, int new_value) {
	int old_value = values[id];

	if (old_value == INT_MAX)
		return;

	values[id] = new_value;

	if (elements[id].prev == NULL)
		buckets[old_value] = elements[id].next;
	else
		elements[id].prev->next = elements[id].next;

	if (elements[id].next != NULL)
		elements[id].next->prev = elements[id].prev;

	Naive_Bucket::Insert(id, new_value);
}

int Naive_Bucket::PopMin(int* id, int* ret_value) {

	for (; current_min_value < max_value; current_min_value++) {
		if (buckets[current_min_value] != NULL) {
			*id = buckets[current_min_value] - elements;
			buckets[current_min_value] = buckets[current_min_value]->next;
			if (buckets[current_min_value] != NULL) {
				buckets[current_min_value]->prev = NULL;
			}
			*ret_value = values[*id];
			values[*id] = INT_MAX;
			return 19;
		}
	}

	return -1;
}

int Naive_Bucket::CurrentValue(int id) {
	return values[id];
}


void Naive_Bucket::DecVal(int id) {
	Naive_Bucket::Update(id, values[id]-1);
	return;
}

