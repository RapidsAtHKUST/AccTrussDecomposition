/******************************************************************************
*
* Author: Christopher R. Aberger
*
* Some common utility functions.
******************************************************************************/

#ifndef UTILS_H
#define UTILS_H

#include "timer.hpp"
#include "io.hpp"
#include "parallel.hpp"
#include "thread_pool.hpp"
#include "debug.hpp"
#include "common.hpp"
#include "ParMMapBuffer.hpp"
#include "ParMemoryBuffer.hpp"

namespace utils {
  //Look for a key, pass in a pointer to an array and a start and end index.
  template<typename F>
  long binary_search(const uint32_t * const data, size_t first, size_t last, uint32_t search_key, F f){
   long index;
   if (first > last){
    index = -1;
   } else{
    size_t mid = (last+first)/2;
    if (search_key == data[f(mid)])
      index = mid;
    else{
      if (search_key < data[f(mid)]){
        if(mid == 0)
          index = -1;
        else
          index = binary_search(data,first,mid-1,search_key,f);
      }
      else
        index = binary_search(data,mid+1,last,search_key,f);
    }
   } // end if
   return index;
  }// end binarySearch

}

#endif
