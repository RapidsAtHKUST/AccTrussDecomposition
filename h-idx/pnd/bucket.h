#ifndef __BUCKET__H
#define __BUCKET__H

#include <vector>
#include <unordered_map>

typedef long long lol;

//typedef uint32_t item;
//typedef lol item; // for big graph runs

struct Naive_Bucket_element {
    Naive_Bucket_element *prev;
    Naive_Bucket_element *next;

    Naive_Bucket_element();
};

template<typename item>
struct Naive_Bucket {
    Naive_Bucket_element **buckets; /* actual pointers to bucket heads */
    Naive_Bucket_element *elements; /* for direct access to bucket elements elements[id] is the id-th element */
    item nb_elements;
    item max_value;
    item *values; /* needed for update, in case bucket head changed. */
    item current_min_value;

    Naive_Bucket();

    ~Naive_Bucket();

    void Initialize(item max_value, item nb_element);

    void Free(); /* value == INT_MAX means not present in bucket */
    void Insert(item id, item value);

    void Update(item id, item new_value);

    void DecVal(item id);

    item PopMin(item *ret_id, item *ret_value); /* returns -1 if empty */
    item CurrentValue(item id);
};

template<typename item>
Naive_Bucket<item>::Naive_Bucket()
        : max_value(0), current_min_value(1), elements(NULL), buckets(NULL), values(NULL), nb_elements(0) {}

template<typename item>
Naive_Bucket<item>::~Naive_Bucket() {
    if (buckets != NULL)
        free(buckets);
    if (elements != NULL)
        free(elements);
    if (values != NULL)
        free(values);
}

template<typename item>
void Naive_Bucket<item>::Free() {
    free(buckets);
    buckets = NULL;
    free(elements);
    elements = NULL;
    free(values);
    values = NULL;
}

template<typename item>
void Naive_Bucket<item>::Initialize(item max_v, item nb_element) {
    item i;
    max_value = max_v;
    buckets = (Naive_Bucket_element **) malloc(sizeof(Naive_Bucket_element *) * (max_value + 1));
    elements = (Naive_Bucket_element *) malloc(sizeof(Naive_Bucket_element) * nb_element);
    values = (item *) malloc(sizeof(item) * nb_element);
    nb_elements = nb_element;
    if (buckets == NULL || elements == NULL || values == NULL) {
        free(values);
        free(buckets);
        free(elements);
    } else {
        for (i = 0; i <= max_value; i++)
            buckets[i] = NULL;
        for (i = 0; i < nb_element; i++) {
            elements[i].prev = NULL;
            elements[i].next = NULL;
        }
    }
    current_min_value = max_value + 1;
}

template<typename item>
void Naive_Bucket<item>::Insert(item id, item value) {
    values[id] = value;
    elements[id].prev = NULL;
    elements[id].next = buckets[value];
    if (buckets[value] != NULL)
        buckets[value]->prev = &(elements[id]);
    else if (current_min_value > value)
        current_min_value = value;
    buckets[value] = &(elements[id]);
}

template<typename item>
item Naive_Bucket<item>::PopMin(item *id, item *ret_value) {
    for (; current_min_value <= max_value; current_min_value++) {
        if (buckets[current_min_value] != NULL) {
            *id = buckets[current_min_value] -
                  elements; // pointer arithmetic. finds the index of element that buckets[current_min_value] points to
            buckets[current_min_value] = buckets[current_min_value]->next; // adjust the pointer to the new head of the list that has same degree elements
            if (buckets[current_min_value] != NULL)
                buckets[current_min_value]->prev = NULL;
            *ret_value = values[*id];
            values[*id] = -1;
            return 0;
        }
    }
    return -1; // if the bucket is empty
}

template<typename item>
item Naive_Bucket<item>::CurrentValue(item id) {
    return values[id];
}

template<typename item>
void Naive_Bucket<item>::DecVal(item id) {
    item old_value = values[id];
    // adjust the prev and next pointers
    if (elements[id].prev == NULL)
        buckets[old_value] = elements[id].next;
    else
        elements[id].prev->next = elements[id].next;
    if (elements[id].next != NULL)
        elements[id].next->prev = elements[id].prev;
    Naive_Bucket::Insert(id, values[id] - 1);
    return;
}


#endif
