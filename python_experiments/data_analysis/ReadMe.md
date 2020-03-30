# Experimental History

## 2019/03/25 Add Improve BMP-HY, BMP-OP

platform | algo |results
--- | --- | ---
gpu23 | tri-cnt | [data-md/gpu23/03-25-study-tri-cnt.md](data-md/gpu23/03-25-study-tri-cnt.md)
gpu23 | all-edge-cnt | [data-md/gpu23/03-21-gro-exp.md](data-md/gpu23/03-21-gro-exp.md)

## 2019/03/15 Selected Tri-Cnt, All-Edge-Cnt

platform | algo |results
--- | --- | ---
gpu23 | tri-cnt | [data-md/gpu23/03-15-tri-cnt-reorder.md](data-md/gpu23/03-15-tri-cnt-reorder.md)
gpu23 | all-edge-cnt | [data-md/gpu23/03-13-gro-exp.md](data-md/gpu23/03-13-gro-exp.md)

## 2019/03/02 Triangle Counting Overview (GPU23-Synthetic)

platform | results
--- | ---
gpu23 | [data-md/gpu23/03-10-tri-cnt.md](data-md/gpu23/03-10-tri-cnt.md)

## 2019/03/02 Triangle Counting Overview (GPU23)

platform | results
--- | ---
gpu23 | [data-md/gpu23/03-01-tri-cnt.md](data-md/gpu23/03-01-tri-cnt.md)

## 2019/01/22 Experimental Overview (CPU/KNL)

* add reordering
* gro lack twitter/friendster
* metis not correct yet (segment fault), cache not working yet (performance degradation)

platform | results
--- | ---
gpu-other | [data-md/gpu-other/01-22-gro-exp.md](data-md/gpu-other/01-22-gro-exp.md)
gpu23 | [data-md/gpu23/01-22-gro-exp.md](data-md/gpu23/01-22-gro-exp.md)
lccpu12 (not accurate) | [data-md/lccpu12/01-22-gro-exp.md](data-md/lccpu12/01-22-gro-exp.md)
knl | [data-md/knl/01-22-gro-exp.md](data-md/knl/01-22-gro-exp.md)

## 2019/01/09-2019/01/14 Experimental Overview (CPU/KNL)

* add emptyheaded, lemire, roaring, han's qfilter and bsr, bmiss/bmiss+sttni, tetzanks
* not remove the construct time yet

platform | results
--- | ---
gpu23 | [data-md/gpu23/01-10-exp.md](data-md/gpu23/01-10-exp.md)
lccpu12 (not accurate) | [data-md/lccpu12/01-10-exp.md](data-md/lccpu12/01-10-exp.md)
knl | [data-md/knl/01-10-exp-non-hbw.md](data-md/knl/01-10-exp-non-hbw.md)

## 2018/09/29 Effectiveness of Symmetric Assignment

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-29-non-sym.md](data-md/lccpu12/09-29-non-sym.md)
knl | [data-md/knl/09-29-non-sym.md](data-md/knl/09-29-non-sym.md)

## 2018/09/25 Bitmap 1D vs 2D

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09_25_bitmap_1D.md](data-md/lccpu12/09_25_bitmap_1D.md)

## 2018/09/23 CPU/KNL Scalability to number of Threads

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-23-cpu-knl-best-varying-threads.md](data-md/lccpu12/09-23-cpu-knl-best-varying-threads.md)
knl | [data-md/knl/09-23-cpu-knl-best-varying-threads.md](data-md/knl/09-23-cpu-knl-best-varying-threads.md)

## 2018/09/23 KNL Experiments 

enable-hbw | results
--- | ---
no | [data-md/knl/09-23-knl-non-hbw.md](data-md/knl/09-23-knl-non-hbw.md)
yes | ...

## 2018/09/20, 2018/09/23 CUDA Scalability 

results: [data-md/lccpu12/09-23-lb-gpu-wildcard.md](data-md/lccpu12/09-23-lb-gpu-wildcard.md)

## 2018/09/20 CUDA Load Balance Dynamic (Config: 8x)

num-of-gpus | results
--- | ---
1 | [data-md/lccpu12/09-20-lb-gpu-1.md](data-md/lccpu12/09-20-lb-gpu-1.md)
2 | [data-md/lccpu12/09-20-lb-gpu-2.md](data-md/lccpu12/09-20-lb-gpu-2.md)
3 | [data-md/lccpu12/09-20-lb-gpu-3.md](data-md/lccpu12/09-20-lb-gpu-3.md)
4 | [data-md/lccpu12/09-20-lb-gpu-4.md](data-md/lccpu12/09-20-lb-gpu-4.md)
8 | [data-md/lccpu12/09-20-lb-gpu-8.md](data-md/lccpu12/09-20-lb-gpu-8.md)

## 2018/09/18 Performance Study On CPU and KNL

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-18-cpu-knl-overview.md](data-md/lccpu12/09-18-cpu-knl-overview.md)
knl | [data-md/knl/09-18-cpu-knl-overview.md](data-md/knl/09-18-cpu-knl-overview.md)

## 2018/09/17 CUDA Dedicated Performance Study (Hybrid Kernels / Hybird Computation per Thread / Bitmap) on Single-GPU

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-17-multi-pass-general-num-gpu-single.md](data-md/lccpu12/09-17-multi-pass-general-num-gpu-single.md)

## 2018/09/13 CUDA With Co-Processing For Bin-Search on CPU All

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-13-co-processing-bin-search.md](data-md/lccpu12/09-13-co-processing-bin-search.md)

## 2018/09/11 CUDA Multi-Pass To Process Snap-Friendster

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-11-multi-pass-general.md](data-md/lccpu12/09-11-multi-pass-general.md)

## 2018/09/10 CUDA Multi-GPU

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-10-multi-gpu.md](data-md/lccpu12/09-10-multi-gpu.md)

## 2018/09/08 CUDA Unified-Memory Bitmap (With 4x Index Range Size)

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-08-cuda-large-bitmap-index-scale.md](data-md/lccpu12/09-08-cuda-large-bitmap-index-scale.md)

## 2018/09/08 CUDA Unified-Memory To Support Larger Dataset

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-08-cuda-unified-mem.md](data-md/lccpu12/09-08-cuda-unified-mem.md)

## 2018/09/06 CUDA-Naive Implementation Time

exec | description
--- | ---
cuda-baseline-hybrid | one edge `intersect(u,v)` per cuda-thread
cuda-baseline | one edge `intersect(u,v)` per cuda-thread
cuda | global memory, each warp per edge `intersect(u,v)`

platform | results
--- | ---
lccpu12 | [data-md/lccpu12/09-06-cuda-naive_fixed_eps_0.8_mu_5.md](data-md/lccpu12/09-06-cuda-naive_fixed_eps_0.8_mu_5.md)

## 2018/09/03 Pre-Processing Edge-List to CSR Time

To show this time is trivial compared to the intensive set-intersections for our application.

platform | results
--- | ---
knl | [data-md/knl/09_03_edge-list-to-csr-performance.md](data-md/knl/09_03_edge-list-to-csr-performance.md)
lccpu12 | [data-md/lccpu12/09_03_edge-list-to-csr-performance.md](data-md/lccpu12/09_03_edge-list-to-csr-performance.md)

## 2018/09/01 Removing `edge_src`, Adopting BitVec

* Attention: optimal workload in bitvec requires degree-descending traversal, with partial computation contraint `u < v`

* BitVec Cost: `num of threads * (number of vertices / 8)`  bytes

platform | results
--- | ---
knl | [data-md/knl/09_01_fixed_eps_0.8_mu_5.md](data-md/knl/09_01_fixed_eps_0.8_mu_5.md)
lccpu12 | [data-md/lccpu12/09_01_fixed_eps_0.8_mu_5.md](data-md/lccpu12/09_01_fixed_eps_0.8_mu_5.md)

## 2018/08/28 Reordering with IPDPS `rabbit_order`, Not-Useful

platform | results
--- | ---
knl | [data-md/knl/08_28_rabbit_order_fixed_eps_0.8_mu_5.md](data-md/knl/08_28_rabbit_order_fixed_eps_0.8_mu_5.md)

## 2018/08/25 Initial

platform | results
--- | ---
knl | [data-md/knl/08_25_fixed_eps_0.8_mu_5.md](data-md/knl/08_25_fixed_eps_0.8_mu_5.md)
lccpu12 | [data-md/lccpu12/08_25_fixed_eps_0.8_mu_5.md](data-md/lccpu12/08_25_fixed_eps_0.8_mu_5.md)



