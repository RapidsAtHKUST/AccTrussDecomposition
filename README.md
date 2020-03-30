# AccTD

This repository contains the source code of the paper "Accelerating Truss Decomposition on Heterogeneous Processors" by 
Yulin Che, Zhuohang Lai, Dr. Shixuan Sun, Dr. Yue Wang and Prof.Qiong Luo. 

## Overview

We provide source codes of `OPT-CPU`, `OPT-HPU`, `WC`, `ROSS`, `PKT`, `MSP`, `H-IDX`, `H-IDX+` for truss decomposition, 
and [experimental scripts](python_experiments). 
The codes are organized in four cmake projects - 
[h-idx](h-idx), [msp](msp), [opt-truss-decomp](opt-truss-decomp) and [opt-truss-decomp-offload](opt-truss-decomp-offload). 
We give the code organization in the following "Algorithms" section. 

## Algorithms

Algorithm | Abbreviation | Code Folder |
--- | --- | --- 
Our Optimized TD | OPT-CPU | [opt-truss-decomp](opt-truss-decomp)
Our Optimized TD with GPU | OPT-HPU | [opt-truss-decomp-offload](opt-truss-decomp-offload)
Wang et al.'s work (VLDB'12) | WC (sequential) | [opt-truss-decomp/related_work/wc_improved.cpp](opt-truss-decomp/related_work/wc_improved.cpp) 
Ross et al.'s work (PKDD'14) | ROSS (sequential) | [opt-truss-decomp/related_work/ros_improved.cpp](opt-truss-decomp/related_work/ros_improved.cpp)
Kabir et al.'s work (HiPC'17, HPEC'17) | PKT | [opt-truss-decomp/pkt_serial](opt-truss-decomp/pkt_serial), [opt-truss-decomp/pkt_parallel_org](opt-truss-decomp/pkt_parallel_org)
Smith el al.'s work (HPEC'17) | MSP | [opt-truss-decomp/msp](opt-truss-decomp/msp)
Sariyuce el al.'s work (VLDB'19) | H-IDX, H-IDX+ (our improved version) | [h-idx/pnd](h-idx/pnd)

## Dependencies

Folder | Comment
--- | ---
[dependencies/cub](dependencies/cub), [dependencies/moderngpu](dependencies/moderngpu) | GPU primitives
[dependencies/libpopcnt](dependencies/libpopcnt) | popcnt primitive
[dependencies/sparsepp](dependencies/sparsepp), [dependencies/sparsehash-yche](dependencies/sparsehash-yche) | sparse hash table implementation