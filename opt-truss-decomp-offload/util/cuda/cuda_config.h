//
// Created by Bryan on 22/7/2019.
//

#pragma once

/*CUDA configuration*/
#define WARP_BITS   (5)
#define WARP_SIZE   (1<<WARP_BITS)
#define WARP_MASK   (WARP_SIZE-1)
#define BLOCK_SIZE  (256)  /*default block size*/
#define WARPS_PER_BLOCK (BLOCK_SIZE/WARP_SIZE)
#define GRID_SIZE   (1024) /*default grid size*/
