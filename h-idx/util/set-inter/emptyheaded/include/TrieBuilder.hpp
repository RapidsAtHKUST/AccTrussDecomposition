/******************************************************************************
*
* Author: Christopher R. Aberger
*
* The top level datastructure. This class holds the methods to create the 
* trie from a table. The TrieBlock class holds the more interesting methods.
******************************************************************************/
#ifndef _TRIEBUILDER_H_
#define _TRIEBUILDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <functional>
#include "util/set-inter/emptyheaded/include/utils/MemoryBuffer.hpp"
#include "util/set-inter/emptyheaded/include/trie/NextLevel.hpp"
#include "util/set-inter/emptyheaded/include/utils/utils.hpp"
#include "util/set-inter/emptyheaded/include/trie/set/Set.hpp"
#include "util/set-inter/emptyheaded/include/trie/TrieBlock.hpp"

template<class A, class M> struct Trie;

/*
* Very simple tree structure stores the trie. All that is needed is the 
* head and number of levels.  Methods are to build a trie from an encoded
* table.
*/
template<class A, class M>
struct TrieBuilder{
  Trie<A,M>* trie;
  std::vector<MemoryBuffer*> tmp_buffers;
  std::vector<NextLevel> next;
  std::vector<const Set<hybrid>*> aggregate_sets;
  TrieBuilder<A,M>(Trie<A,M>* t_in,const size_t num_attributes);
  uint32_t cur_level;
  uint32_t tmp_level;

  size_t build_aggregated_equality_selection_set(
    const TrieBlock<hybrid,M> *s1);

  size_t build_aggregated_set(
    const TrieBlock<hybrid,M> *s1);

  size_t build_aggregated_set(
    const TrieBlock<hybrid,M> *s1, 
    const TrieBlock<hybrid,M> *s2);

  size_t build_aggregated_set(
    std::vector<const TrieBlock<hybrid,M> *>* isets);

  size_t count_set(
    const TrieBlock<hybrid,M> *s1);

  size_t count_set(
    const TrieBlock<hybrid,M> *s1, 
    const TrieBlock<hybrid,M> *s2);

  size_t build_set(
    const size_t tid,
    const TrieBlock<hybrid,M> *s1);

  size_t build_set(
    const size_t tid,
    const TrieBlock<hybrid,M> *s1,
    const TrieBlock<hybrid,M> *s2);

  size_t build_set(
    const size_t tid,
    std::vector<const TrieBlock<hybrid,M> *>* isets);

  void set_level(
    const uint32_t index,
    const uint32_t data);

  void allocate_next(
    const size_t tid);

  void allocate_annotation(
    const size_t tid);

  void set_annotation(
    const A value,
    const uint32_t index,
    const uint32_t data);

  template<typename F>
  inline void foreach_aggregate(F f){
    const Set<hybrid> *s = aggregate_sets.at(tmp_level);
    auto buf = tmp_buffers.at(tmp_level);
    tmp_level++;
    s->foreach(sizeof(Set<hybrid>),buf,f);
    tmp_level--;
  }

  template<typename F>
  inline void foreach_builder(F f){
    const int cur_index = next.at(cur_level).index;
    if(cur_index == -1){
      return;
    }
    const size_t cur_offset = next.at(cur_level).offset;

    auto buf = trie->memoryBuffers->elements.at(cur_index);
    uint8_t* place = (uint8_t*)(buf->get_address(cur_offset)+sizeof(TrieBlock<hybrid,M>));

    Set<hybrid> *s = (Set<hybrid>*)place;

    cur_level++;
    s->foreach_index(
      (cur_offset+sizeof(TrieBlock<hybrid,M>)+sizeof(Set<hybrid>)),
      buf,
      f);
    cur_level--;
  }
};

template<class A, class M>
struct ParTrieBuilder{
  Trie<A,M>* trie;
  std::vector<TrieBuilder<A,M>*> builders;
  ParTrieBuilder<A,M>(Trie<A,M>* t_in,const size_t num_attributes);
  const TrieBlock<hybrid,M>* tmp_head;
  
  size_t build_aggregated_equality_selection_set(
    const uint32_t data,
    const TrieBlock<hybrid,M> *s1);

  size_t build_aggregated_set(
    const TrieBlock<hybrid,M> *s1);

  size_t build_aggregated_set(
    const TrieBlock<hybrid,M> *s1,
    const TrieBlock<hybrid,M> *s2);

  size_t build_aggregated_set(
    std::vector<const TrieBlock<hybrid,M> *>* isets);

  size_t build_set(
    const TrieBlock<hybrid,M> *s1);

  size_t build_set(
    const TrieBlock<hybrid,M> *tb1,
    const TrieBlock<hybrid,M> *tb2);

  size_t build_set(
    std::vector<const TrieBlock<hybrid,M> *>* isets);

  void allocate_next();

  void allocate_annotation();

  template<typename F>
  void par_foreach_aggregate(F f){
    const TrieBlock<hybrid,M>* block = tmp_head;
    Set<hybrid>* s = (Set<hybrid>*)((uint8_t*)block+sizeof(TrieBlock<hybrid,M>));
    s->par_foreach(f);
  }

  template<typename F>
  void par_foreach_builder(F f){
    const TrieBlock<hybrid,M>* block = trie->getHead();
    Set<hybrid>* s = (Set<hybrid>*)((uint8_t*)block+sizeof(TrieBlock<hybrid,M>));
    s->par_foreach_index(f);
  }
};

#endif
