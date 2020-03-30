

#include "kt_hmap.h"


kt_hmap_t * alloc_hmap(
    ssize_t max_elems)
{
  kt_hmap_t * hmap = gk_malloc(sizeof(*hmap), "hmap");


  int32_t l;
  for (l=1; max_elems > (1<<l); l++);
  hmap->hmsize = (1<<(l+3))-1;
  hmap->map = gk_i32smalloc(hmap->hmsize+1, -1, "hmap");

  return hmap;
}


void free_hmap(
    kt_hmap_t * hmap)
{
  gk_free((void **) &(hmap->map), LTERM);
  gk_free((void **) &hmap, LTERM);
}


