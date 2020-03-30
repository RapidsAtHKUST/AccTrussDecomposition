//
// Created by Bryan on 22/7/2019.
//

#ifndef TRUSS_DECOMP_CUBWRAPPERS_H
#define TRUSS_DECOMP_CUBWRAPPERS_H

#include "cuda_util.h"
#include <cub/cub.cuh>
#include <moderngpu/kernel_sortedsearch.hxx>  //Modern GPU set insersection
using namespace std;

template<typename InputType, typename OutputType>
OutputType CUBScanExclusive(
        InputType *input,
        OutputType *output,
        const int count,
        ZLCUDATimer *timer,
        ZLCUDAMemStat *mem_stat = nullptr)
{
    float singleKernelTime, elaspedTime = 0;
    cudaEvent_t start, end;
    void *d_temp_storage = nullptr;
    size_t temp_storage_bytes = 0;

    /*record the last input item in case it is an in-place scan*/
    auto last_input = input[count-1];

    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&end));

    checkCudaErrors(cudaEventRecord(start));
    cub::DeviceScan::ExclusiveSum(d_temp_storage, temp_storage_bytes, input, output, count);
    checkCudaErrors(cudaEventRecord(end));
    checkCudaErrors(cudaEventSynchronize(start));
    checkCudaErrors(cudaEventSynchronize(end));
    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end));
    elaspedTime += singleKernelTime;
    CHECK_KERNEL("CUB 1st scan");

    ZLCudaMalloc(&d_temp_storage, temp_storage_bytes, mem_stat);

    /*Run exclusive prefix sum*/
    checkCudaErrors(cudaEventRecord(start));
    cub::DeviceScan::ExclusiveSum(d_temp_storage, temp_storage_bytes, input, output, count);
    checkCudaErrors(cudaEventRecord(end));
    checkCudaErrors(cudaEventSynchronize(start));
    checkCudaErrors(cudaEventSynchronize(end));
    checkCudaErrors(cudaDeviceSynchronize());

    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end));
    elaspedTime += singleKernelTime;

    CHECK_KERNEL("CUB 2nd scan");
    ZLCudaFree(d_temp_storage, mem_stat);

    if (timer != nullptr) {
#ifdef VERBOSE
        log_info("Kernel: %s, count: %d, time: %.2f ms.","CUB scan", count, elaspedTime);
#endif
        timer->insert_record(__FILE__,__FUNCTION__,"CUB scan",elaspedTime);
    }

    return output[count-1] + (OutputType)last_input;
}

template<typename DataType, typename SumType, typename CntType>
SumType CUBSum(
        DataType *input,
        CntType count,
        ZLCUDATimer *timer,
        ZLCUDAMemStat *mem_stat = nullptr)
{
    cudaEvent_t start, end;
    float elaspedTime=0, singleKernelTime=0;

    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&end));

    SumType *sum_value = nullptr;
    ZLCudaMalloc(&sum_value, sizeof(SumType), mem_stat);

    void *d_temp_storage = nullptr;
    size_t temp_storage_bytes = 0;

    checkCudaErrors(cudaEventRecord(start));
    cub::DeviceReduce::Sum(d_temp_storage, temp_storage_bytes, input, sum_value, count);
    checkCudaErrors(cudaEventRecord(end));
    checkCudaErrors(cudaEventSynchronize(start));
    checkCudaErrors(cudaEventSynchronize(end));
    checkCudaErrors(cudaDeviceSynchronize());

    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end));
    elaspedTime += singleKernelTime;

    CHECK_KERNEL("CUB 1st sum");

    ZLCudaMalloc(&d_temp_storage, temp_storage_bytes, mem_stat);

    checkCudaErrors(cudaEventRecord(start));
    cub::DeviceReduce::Sum(d_temp_storage, temp_storage_bytes, input, sum_value, count);
    checkCudaErrors(cudaEventRecord(end));
    checkCudaErrors(cudaEventSynchronize(start));
    checkCudaErrors(cudaEventSynchronize(end));
    checkCudaErrors(cudaDeviceSynchronize());

    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end));
    elaspedTime += singleKernelTime;

    CHECK_KERNEL("CUB 2nd sum");

    if (timer != nullptr) {
#ifdef VERBOSE
        log_info("Kernel: %s, count: %d, time: %.2f ms.","CUB sum", count, singleKernelTime);
#endif
        timer->insert_record(__FILE__,__FUNCTION__,"CUB sum",elaspedTime);
    }

    SumType res = *sum_value;
    ZLCudaFree(d_temp_storage, mem_stat);
    ZLCudaFree(sum_value, mem_stat);

    return res;
}

template<typename InputType, typename OutputType, typename CountType, typename FlagIterator>
uint32_t CUBSelect(
        InputType input, OutputType output,
        FlagIterator flags,
        const CountType countInput,
        ZLCUDATimer *timer,
        ZLCUDAMemStat *mem_stat = nullptr)
{
    cudaEvent_t start, end;
    float elaspedTime=0, singleKernelTime=0;

    uint32_t *countOutput = nullptr;
    ZLCudaMalloc(&countOutput, sizeof(uint32_t), mem_stat);

    checkCudaErrors(cudaEventCreate(&start));
    checkCudaErrors(cudaEventCreate(&end));

    void *d_temp_storage = nullptr;
    size_t temp_storage_bytes = 0;

    checkCudaErrors(cudaEventRecord(start));
    cub::DeviceSelect::Flagged(d_temp_storage, temp_storage_bytes, input, flags, output, countOutput, countInput);
    checkCudaErrors(cudaEventRecord(end));
    checkCudaErrors(cudaEventSynchronize(start));
    checkCudaErrors(cudaEventSynchronize(end));
    checkCudaErrors(cudaDeviceSynchronize());

    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end));
    elaspedTime += singleKernelTime;

    CHECK_KERNEL("CUB 1st select");

    ZLCudaMalloc(&d_temp_storage, temp_storage_bytes, mem_stat);

    checkCudaErrors(cudaEventRecord(start));
    cub::DeviceSelect::Flagged(d_temp_storage, temp_storage_bytes, input, flags, output, countOutput, countInput);
    checkCudaErrors(cudaEventRecord(end));
    checkCudaErrors(cudaEventSynchronize(start));
    checkCudaErrors(cudaEventSynchronize(end));
    checkCudaErrors(cudaDeviceSynchronize());

    checkCudaErrors(cudaEventElapsedTime(&singleKernelTime, start, end));
    elaspedTime += singleKernelTime;

    CHECK_KERNEL("CUB 2nd select");

    if (timer != nullptr) {
#ifdef VERBOSE
        log_info("Kernel: %s, count: %d, time: %.2f ms.","CUB select", count, elaspedTime);
#endif
        timer->insert_record(__FILE__,__FUNCTION__,"CUB select",elaspedTime);
    }

    ZLCudaFree(d_temp_storage, mem_stat);

    uint32_t res = *countOutput;
    ZLCudaFree(countOutput, mem_stat);

    return res;
}

#endif //TRUSS_DECOMP_CUBWRAPPERS_H
