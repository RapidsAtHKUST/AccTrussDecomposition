//
// Created by Bryan on 22/7/2019.
//

#include <cassert>
#include <cooperative_groups.h>
#include <cuda_occupancy.h>

#include "cuda_util.h"

/*memory statistics*/
ZLCUDAMemStat::ZLCUDAMemStat() {
    cur_use = 0;
    max_use = 0;
    acc_use = 0;
    valid = true;
}

void ZLCUDAMemStat::malloc_mem_stat(unsigned long addr, long add_bytes) {
    if (!valid) return;

    cur_use += add_bytes;
    acc_use += add_bytes;
    if (cur_use > max_use) {
        max_use = cur_use;
    }

    /*record the allocated address and memory size*/
    addr_bytes.insert(std::make_pair(addr, add_bytes));
}

void ZLCUDAMemStat::delete_mem_stat(unsigned long addr) {
    if (!valid) return;

    auto iter = addr_bytes.find(addr);
    if (iter == addr_bytes.end()) {
        log_warn("MemStat does not match. The Mem stat becomes invalid.");
        valid = false;
        return;
    }

    long delete_bytes = iter->second;
    addr_bytes.erase(iter); //remove the address
    cur_use -= delete_bytes;
    assert(cur_use >= 0);
}

long ZLCUDAMemStat::get_max_use() {
    return max_use;
}

long ZLCUDAMemStat::get_acc_use() {
    return acc_use;
}

long ZLCUDAMemStat::get_cur_use() {
    return cur_use;
}

void ZLCUDAMemStat::reset() {
    cur_use = 0;
    max_use = 0;
    acc_use = 0;

    addr_bytes.clear();
    valid = true;
}

uint32_t ZLCUDAMemStat::get_num_obj() {
    return (uint32_t)addr_bytes.size();
}

void ZLCUDAMemStat::displaceMap() {
    if (!valid) return;
    log_info("Display the memory map.");
    for(auto i : addr_bytes)
        log_info("%p %ld.", i.first, i.second);
}

/*time statistics*/
ZLCUDATimer::ZLCUDATimer() {
    idx = 0;
}

void ZLCUDATimer::reset() {
    idx = (uint32_t)kernel_time.size();
}

float ZLCUDATimer::elapsed() {
    uint32_t end = (uint32_t)kernel_time.size();
    float res = 0.0;
    for(auto i = idx; i < end; i++)
        res += this->kernel_time[i];
    return res;
}

void ZLCUDATimer::insert_record( std::string file,
                    std::string host_func,
                    std::string kernel,
                    float ker_time) {
    file_name.emplace_back(file);
    host_func_name.emplace_back(host_func);
    kernel_name.emplace_back(kernel);
    kernel_time.emplace_back(ker_time);
}

void check(cudaError_t code, char const *const func, const char *const file,
           int const line, bool abort)
{
    if (code != cudaSuccess)
    {
        if (abort)
        {
            log_fatal("CUDA error at %s:%d code=%d(%s) \"%s\" \n", file, line,
                      static_cast<unsigned int>(code), cudaGetErrorString(code), func);
            // Make sure we call CUDA Device Reset before exiting
            cudaDeviceReset();
            exit(static_cast<unsigned int>(code));
        }
        else
        {
            log_warn("CUDA error at %s:%d code=%d(%s) \"%s\" \n", file, line,
                     static_cast<unsigned int>(code), cudaGetErrorString(code), func);
        }
    }
}

//void ZLCudaMalloc(void *addr, size_t malloc_bytes, ZLCUDAMemStat *stat)
//{
//    checkCudaErrors(cudaMallocManaged((void**)addr, malloc_bytes));
//    checkCudaErrors(cudaMemset(*addr, 0, malloc_bytes));
//    if (stat)
//        stat->malloc_mem_stat((unsigned long)*addr, malloc_bytes);
//}
//
//void ZLCudaFree(void *addr, ZLCUDAMemStat *stat)
//{
//    checkCudaErrors(cudaFree(addr));
//    if (stat)
//        stat->delete_mem_stat((unsigned long)addr);
//}

