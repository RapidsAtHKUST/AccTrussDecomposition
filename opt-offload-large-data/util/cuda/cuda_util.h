//
// Created by Bryan on 19/11/2018.
//

#ifndef CUDA_UTIL_H
#define CUDA_UTIL_H

#ifdef __JETBRAINS_IDE__

#include "../../cuda_fake/fake.h"

#endif

#include <map>
#include <vector>

#include "../log.h"
#include "cuda_config.h"

/*---- 1. CUDA kernel check functions ----*/
#define checkCudaErrors(val) check((val), #val, __FILE__, __LINE__)

/*
 * cudaPeekAtLastError(): get the code of last error, no resetting
 * udaGetLastError(): get the code of last error, resetting to cudaSuccess
 * */
#define CHECK_KERNEL(func)          if (cudaSuccess != cudaPeekAtLastError()) { \
                                        cudaError_t error = cudaGetLastError(); \
                                        log_fatal("Kernel %s: %s.", func, \
                                        cudaGetErrorString(error)); \
                                        exit(1); \
                                    }

void check(cudaError_t code, char const *const func, const char *const file,
           int const line, bool abort = true);

/*---- 1. CUDA kernel check functions end ----*/

/*---- 2. CUDA kernel execution wrapper ----*/
/*normal execution without dynamic shared memory allocation*/
#define execKernel(kernel, gridSize, blockSize, timing, verbose, ...) \
{ \
    float singleKernelTime;\
    cudaEvent_t start, end; \
    checkCudaErrors(cudaEventCreate(&start)); \
    checkCudaErrors(cudaEventCreate(&end)); \
    dim3 grid(gridSize); \
    dim3 block(blockSize); \
    \
    checkCudaErrors(cudaEventRecord(start)); \
    kernel<<<grid,block>>>(__VA_ARGS__); \
    CHECK_KERNEL(#kernel)\
    checkCudaErrors(cudaPeekAtLastError());\
    checkCudaErrors(cudaEventRecord(end));\
    \
    checkCudaErrors(cudaEventSynchronize(start)); \
    checkCudaErrors(cudaEventSynchronize(end)); \
    checkCudaErrors(cudaDeviceSynchronize()); \
    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end)); \
    \
    if (timing != nullptr)\
    {\
        if(verbose) log_info("Kernel: %s, time: %.2f ms.",#kernel, singleKernelTime); \
        timing->insert_record(__FILE__,__FUNCTION__,#kernel,singleKernelTime);\
    }\
}

/*execution with dynamic shared memory allocation*/
#define execKernelDynamicAllocation(kernel, gridSize, blockSize, sharedSize, timing, verbose, ...) \
{ \
    float singleKernelTime;\
    cudaEvent_t start, end; \
    checkCudaErrors(cudaEventCreate(&start)); \
    checkCudaErrors(cudaEventCreate(&end)); \
    dim3 grid(gridSize); \
    dim3 block(blockSize); \
    \
    checkCudaErrors(cudaEventRecord(start)); \
    kernel<<<grid,block,sharedSize>>>(__VA_ARGS__); \
    CHECK_KERNEL(#kernel)\
    checkCudaErrors(cudaPeekAtLastError());\
    checkCudaErrors(cudaEventRecord(end));\
    \
    checkCudaErrors(cudaEventSynchronize(start)); \
    checkCudaErrors(cudaEventSynchronize(end)); \
    checkCudaErrors(cudaDeviceSynchronize()); \
    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end)); \
    \
    if (timing != nullptr)\
    {\
        if(verbose) log_info("Kernel: %s, time: %.2f ms.",#kernel, singleKernelTime); \
        timing->insert_record(__FILE__,__FUNCTION__,#kernel,singleKernelTime);\
    }\
}
/*---- 2. CUDA kernel execution wrapper end ----*/

/*---- 3. CUDA function macros ---- */

#define WARP_REDUCE(var)    { \
                                var += __shfl_down_sync(0xFFFFFFFF, var, 16);\
                                var += __shfl_down_sync(0xFFFFFFFF, var, 8);\
                                var += __shfl_down_sync(0xFFFFFFFF, var, 4);\
                                var += __shfl_down_sync(0xFFFFFFFF, var, 2);\
                                var += __shfl_down_sync(0xFFFFFFFF, var, 1);\
                            }

/*---- 3. CUDA function macros end ---- */

/*---- 4. CUDA memory allocation and statistics----*/
class ZLCUDAMemStat {
private:
    long cur_use; //current use of memory in bytes
    long max_use; //maximum use of memory in bytes
    long acc_use; //accumulated memory used in bytes
    bool valid;   //whether the MemStat is valid

    std::map<unsigned long, long> addr_bytes; //store the allocated address and sizes
public:
    ZLCUDAMemStat();

    void malloc_mem_stat(unsigned long addr, long add_bytes);

    void delete_mem_stat(unsigned long addr);

    long get_max_use();

    long get_acc_use();

    long get_cur_use();

    void reset();

    void displaceMap();

    uint32_t get_num_obj();
};

template<typename T>
void ZLCudaMalloc(T **addr, size_t malloc_bytes, ZLCUDAMemStat *stat = nullptr) {
    if (malloc_bytes == 0) {
        malloc_bytes = 1;
    }
    checkCudaErrors(cudaMallocManaged((void **) addr, malloc_bytes));
//    checkCudaErrors(cudaMemset(*addr, 0, malloc_bytes));
    checkCudaErrors(cudaMemPrefetchAsync(*addr, malloc_bytes, 0));
    if (stat)
        stat->malloc_mem_stat((unsigned long) *addr, malloc_bytes);
}

template<typename T>
void ZLCudaFree(T *addr, ZLCUDAMemStat *stat = nullptr) {
    if (addr == nullptr)
        return;
    checkCudaErrors(cudaFree(addr));
    if (stat)
        stat->delete_mem_stat((unsigned long) addr);
}

/*---- 4. CUDA memory statistics end ----*/

/*---- 5. CUDA timing functions ----*/
struct ZLCUDATimer {
private:
    uint32_t idx;                        //current start idx of the kernel interested
    std::vector <std::string> file_name;         //name of the file the kernel is invoked in
    std::vector <std::string> host_func_name;   //name of the host function the kernel is invoked in
    std::vector <std::string> kernel_name;   //name of the kernel invoked
    std::vector<float> kernel_time;              //kernel time

public:
    ZLCUDATimer();

    void reset();

    float elapsed();

    void insert_record(std::string file,
                       std::string host_func,
                       std::string kernel,
                       float ker_time);
};

/*---- 5. CUDA timing functions end ----*/

#endif

