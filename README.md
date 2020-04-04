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
Our simplified OPT-CPU with Large Data support `> 2G edges` | OPT-CPU-LD | [opt-cpu-large-data](opt-cpu-large-data) 
Wang et al.'s work (VLDB'12) | WC (sequential) | [opt-truss-decomp/related_work/wc_improved.cpp](opt-truss-decomp/related_work/wc_improved.cpp) 
Ross et al.'s work (PKDD'14) | ROSS (sequential) | [opt-truss-decomp/related_work/ros_improved.cpp](opt-truss-decomp/related_work/ros_improved.cpp)
Kabir et al.'s work (HiPC'17, HPEC'17) | PKT | [opt-truss-decomp/pkt_serial](opt-truss-decomp/pkt_serial), [opt-truss-decomp/pkt_parallel_org](opt-truss-decomp/pkt_parallel_org)
Smith el al.'s work (HPEC'17) | MSP | [msp](msp)
Sariyuce el al.'s work (VLDB'19) | H-IDX, H-IDX+ (our improved version) | [h-idx/pnd](h-idx/pnd)

## Datasets (Input) Pre-Processing 

* Real-World Graph 

We use the converter in [ppSCAN-release](https://github.com/RapidsAtHKUST/ppSCAN/tree/master/ppSCAN-release) 
to transform an `edge list txt file` into our format (two binary files `b_degree.bin` and `b_adj.bin` under a folder). 
These two binary files contain the information for the reconstruction of the Compressed Sparse Row (CSR) format.
Please see [Lijun's datasets format](https://github.com/LijunChang/Cohesive_subgraph_book/tree/master/datasets) for more details.

* Synthetic-Graph 

Please see [doc/RapidsSyntheticGraphGen.md](doc/RapidsSyntheticGraphGen.md) to install graph generators and 
format converters (GT Graph Generator (3 types), Random, RMAT, Clique; Kronecker Model (RMAT) Graph; Parallel Graph Pre-Processing and Conversion). 

* Statistics

The statistics (|V|, |E|, |TC|, avg-deg, max-deg, dodg-max-deg, max-core-val, core-histogram) 
can be collected using our tool in [KroneckerBinEdgeListToCSR](https://github.com/RapidsAtHKUST/KroneckerBinEdgeListToCSR)

## Build

We build the four cmake project [h-idx](h-idx), [msp](msp), [opt-truss-decomp](opt-truss-decomp) 
and [opt-truss-decomp-offload](opt-truss-decomp-offload) separately. 
In each build, 
we can give cmake options specified in the cmake list. For details, please see the corresponding project folder.

* build steps:

```
mkdir -p build
cd build
cmake .. ${cmake options}
make -j
```

* example cmake options for `OPT-CPU`: `-DBUILD_SERIAL=ON -DPLAYGROUND=OFF -DLEGACY_PKT_ALL=ON`

## Run

Suppose we already have two binary files `b_degree.bin` and `b_adj.bin` under a folder `folder_path` as our input. 
Then we run as follows

### WC/ROS/PKT/OPT-CPU/OPT-HPU

see [python_experiments/run_experiments/run_k_truss_reorderd_graph.py](python_experiments/run_experiments/run_k_truss_reorderd_graph.py)
, where `org` denotes the graph ordering. 

* WC (in [opt-truss-decomp](opt-truss-decomp))
* ROS (in [opt-truss-decomp](opt-truss-decomp))
* PKT (in [opt-truss-decomp](opt-truss-decomp))
* OPT-CPU (in [opt-truss-decomp](opt-truss-decomp))
* OPT-HPU (in [opt-truss-decomp-offload](opt-truss-decomp-offload))

```zsh
./wc /mnt/nvme-ssd/yche/datasets/snap_livejournal org
./ros /mnt/nvme-ssd/yche/datasets/snap_livejournal org
./pkt-inter-legacy /mnt/nvme-ssd/yche/datasets/snap_livejournal org
./pkt-inter-shrink /mnt/nvme-ssd/yche/datasets/snap_livejournal org
./cuda-pkt-offload-opt /mnt/nvme-ssd/yche/datasets/snap_livejournal org
```

### MSP

* MSP (in [msp](msp))

see [python_experiments/run_experiments/run_k_truss_karypis.py](python_experiments/run_experiments/run_k_truss_karypis.py)

```zsh
./ktruss -kttype msp -iftype bin /mnt/nvme-ssd/yche/datasets/snap_livejournal
```

### H-IDX and H-IDX+

* H-IDX, H-IDX+ (in [h-idx](h-idx))

see [python_experiments/run_experiments/run_necleus_decomposition.py](python_experiments/run_experiments/run_necleus_decomposition.py)

```zsh
./pnd /mnt/storage1/yche/datasets/snap_livejournal 2300
./hidx-org /mnt/storage1/yche/datasets/snap_livejournal 2300
```

### More Experiments

see [python_experiments/run_experiments](python_experiments/run_experiments)

## Dependencies

Folder | Comment
--- | ---
[dependencies/cub](dependencies/cub), [dependencies/moderngpu](dependencies/moderngpu) | GPU primitives
[dependencies/libpopcnt](dependencies/libpopcnt) | popcnt primitive
[dependencies/sparsepp](dependencies/sparsepp), [dependencies/sparsehash-yche](dependencies/sparsehash-yche) | sparse hash table implementation