/******************************************************************************
*
* Author: Christopher R. Aberger
*
* The top level datastructure. This class holds the methods to create the 
* trie from a table. The TrieBlock class holds the more interesting methods.
******************************************************************************/
#include "TrieIterator.hpp"
#include "Trie.hpp"
#include "trie/TrieBlock.hpp"
#include "utils/common.hpp"

template<class A,class M>
TrieIterator<A,M>::TrieIterator(Trie<A,M>* t_in){
  trie = t_in;
  levels.resize(trie->num_columns);
  if(trie->num_columns > 0){
    levels.at(0) = trie->getHead();
  }
  num_rows = 0;
}

template<class A,class M>
void TrieIterator<A,M>::get_next_block(const size_t level, const uint32_t data){
  levels.at(level+1) = (const TrieBlock<hybrid,M>*)
    levels.at(level)->get_next_block(data,trie->memoryBuffers);
}

template<class A,class M>
void TrieIterator<A,M>::get_next_block(
  const size_t level, 
  const uint32_t index, 
  const uint32_t data){
  
  levels.at(level+1) = (const TrieBlock<hybrid,M>*)
    levels.at(level)->get_next_block(index,data,trie->memoryBuffers);
}

template<class A,class M>
const TrieBlock<hybrid,M>* TrieIterator<A,M>::get_block(const size_t level) const {
  return levels.at(level);
}

template<class A,class M>
A TrieIterator<A,M>::get_annotation(
  const size_t level,
  const uint32_t data){
  const TrieBlock<hybrid,M>* block = levels.at(level);
  const Set<hybrid>* s1 = block->get_const_set();
  long index = s1->find(data);
  if(index != -1){
    A* annotation = (A*)( ((uint8_t*)block)+
      (sizeof(TrieBlock<hybrid,M>)+
      sizeof(Set<hybrid>) +
      s1->number_of_bytes) );
    return annotation[block->get_index(index,data)];
  }
  return (A)0;
}

template<class A, class M>
ParTrieIterator<A,M>::ParTrieIterator(Trie<A,M> *t_in){
  head = t_in->getHead();
  annotation = t_in->annotation;
  iterators.resize(NUM_THREADS);
  trie = t_in;
  for(size_t i = 0; i < NUM_THREADS; i++){
    iterators.at(i) = new TrieIterator<A,M>(t_in);
  }
}

template<class A,class M>
void ParTrieIterator<A,M>::get_next_block(const uint32_t data){
  head =  head->get_next_block(data,trie->memoryBuffers);
  for(size_t i = 0; i < NUM_THREADS; i++){
    iterators.at(i)->levels.at(0) = head;
  }
}

template struct ParTrieIterator<void*,ParMemoryBuffer>;
template struct ParTrieIterator<long,ParMemoryBuffer>;
template struct ParTrieIterator<int,ParMemoryBuffer>;
template struct ParTrieIterator<float,ParMemoryBuffer>;
template struct ParTrieIterator<double,ParMemoryBuffer>;

template struct ParTrieIterator<void*,ParMMapBuffer>;
template struct ParTrieIterator<long,ParMMapBuffer>;
template struct ParTrieIterator<int,ParMMapBuffer>;
template struct ParTrieIterator<float,ParMMapBuffer>;
template struct ParTrieIterator<double,ParMMapBuffer>;

template struct TrieIterator<void*,ParMemoryBuffer>;
template struct TrieIterator<long,ParMemoryBuffer>;
template struct TrieIterator<int,ParMemoryBuffer>;
template struct TrieIterator<float,ParMemoryBuffer>;
template struct TrieIterator<double,ParMemoryBuffer>;

template struct TrieIterator<void*,ParMMapBuffer>;
template struct TrieIterator<long,ParMMapBuffer>;
template struct TrieIterator<int,ParMMapBuffer>;
template struct TrieIterator<float,ParMMapBuffer>;
template struct TrieIterator<double,ParMMapBuffer>;
