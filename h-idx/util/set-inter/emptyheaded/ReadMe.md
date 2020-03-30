### Set Representation

```
template<typename T>
const Set<T> *NewSet(Graph *g, uint32_t offset_beg, uint32_t size) {
    static thread_local Set<T> *buffer = (Set<T> *) malloc(2048 * 1024 * 4);
    T tmp;

    Set<T> *set_u;

    buffer->from_array((uint8_t *) buffer + sizeof(Set<T>),
                       reinterpret_cast<uint32_t *>(g->edge_dst + offset_beg), size);
    assert(buffer->number_of_bytes + sizeof(Set<T>) < 2048 * 1024 * 4);
    set_u = (Set<T> *) malloc(buffer->number_of_bytes + sizeof(Set<T>));
    mempcpy(set_u, buffer, buffer->number_of_bytes + sizeof(Set<T>));
    return set_u;
}
```


#### Join

* builder: computed trie results, using thread local buffers each block start recorded with `(tid, offset)`
* iterator: temporary set the current path, space complexity: `#of columns`

attention: set-sevel links to a previous tri-blk (level `i`) at the offset `d`.

```
template<class A,class M>
void TrieIterator<A,M>::get_next_block(const size_t level, const uint32_t data){
  levels.at(level+1) = (const TrieBlock<hybrid,M>*)
    levels.at(level)->get_next_block(data,trie->memoryBuffers);
}

template<class A,class M>
const TrieBlock<hybrid,M>* TrieIterator<A,M>::get_block(const size_t level) const {
  return levels.at(level);
}
```


```
     Iterator_Edge_a_b->get_next_block(0, a_d);
            Iterator_Edge_a_c->get_next_block(0, a_d);
            const size_t count_b =
                    Builder->build_set(tid, Iterator_Edge_a_b->get_block(1),
                                       Iterator_Edge_b_c->get_block(0));
```

#### `NextLevel`

```
struct NextLevel{
  int index; //# of threads
  size_t offset;
};
```

```
//sets the pointers in the previous level to point to
//the current level
template<class A,class M>
void TrieBuilder<A,M>::set_level(
```

#### `Set<T>*`

meta | following
--- | ---
Set-meta-properties, e.g. four fields | raw buffer to hold array or sparse bitmap

* four fields (used by tri-block, `return is_sparse ? set->cardinality:(set->range+1)`)

```cpp
 uint32_t cardinality;
 uint32_t range;
 size_t number_of_bytes;
 type::layout type;
```

#### `TrieBlock`

meta | following | | |
--- | --- | --- | ---
tri-block property, `is_sparse` | Set<hybrid> (`cardinality`, `range`, `number_of_bytes`, `layout`) | raw array or sparse bitmap | next-levels (next-attribute)

each tri-block is a set, e.g (attr0, attr1, xxx) xxx is a set.

```
  inline const Set<T>* get_const_set() const {
    const Set<T>* const result = (const Set<T>*)((uint8_t*)this + sizeof(TrieBlock<T,M>));
    return result;
  }

  inline NextLevel* getNext(const size_t index) const {
    const Set<hybrid>* const set = this->get_const_set();
    return (NextLevel*)(
      ((uint8_t*)set)+
      sizeof(Set<hybrid>) +
      (set->number_of_bytes) +
      (sizeof(NextLevel)*index) );
  }
```

#### `build_set(tb1)`

simply copy

#### `build_set(tb1, tb2)`

set intersection

```
template<class A,class M>
size_t TrieBuilder<A,M>::build_set(
  const size_t tid,
  const TrieBlock<hybrid,M>* tb1,
  const TrieBlock<hybrid,M>* tb2){

  M* data_allocator = trie->memoryBuffers;
  if(tb1 == NULL || tb2 == NULL){
    next.at(cur_level).index = -1;

    //clear the memory and move on (will set num bytes and cardinality to 0)
    const size_t alloc_size = sizeof(Set<hybrid>)+sizeof(TrieBlock<hybrid,M>);
    uint8_t* place = (uint8_t*)data_allocator->get_next(tid,alloc_size);
    const size_t offset = place-data_allocator->get_address(tid);
    next.at(cur_level).offset = offset;
    memset(place,(uint8_t)0,sizeof(alloc_size));
    return 0;
  }

  const Set<hybrid>* s1 = (const Set<hybrid>*)((uint8_t*)tb1+sizeof(TrieBlock<hybrid,M>));
  const Set<hybrid>* s2 = (const Set<hybrid>*)((uint8_t*)tb2+sizeof(TrieBlock<hybrid,M>));

  const size_t alloc_size = get_alloc_size(s1->number_of_bytes,s2->number_of_bytes,(s1->type == s2->type));

  uint8_t* start_block = (uint8_t*)data_allocator->get_next(tid,
    (sizeof(TrieBlock<hybrid,M>)+
    sizeof(Set<hybrid>)+
    alloc_size));

  const size_t offset = start_block-data_allocator->get_address(tid);
  Set<hybrid>* myset =  (Set<hybrid>*)(start_block+sizeof(TrieBlock<hybrid,M>));
  myset = ops::set_intersect(
            myset,
            s1,
            s2);
  assert(alloc_size >= myset->number_of_bytes);
  data_allocator->roll_back(tid,alloc_size - (myset->number_of_bytes) );

  //(3) set the offset and index of the trie block in a vector
  next.at(cur_level).index = (myset->cardinality > 0) ? tid: -1;
  next.at(cur_level).offset = offset;

  return myset->cardinality;
  //aside: when you call set block it will just pull the values and set with (data,index) value
  //(4) allocated space for the next blocks
  //return the set
}
```

#### `TriIterator`

* `Builders.par_foreach_builder([&](const size_t tid, const uint32_t a_i, const uint32_t a_d)`

a_i | a_d
--- | ---
index | data