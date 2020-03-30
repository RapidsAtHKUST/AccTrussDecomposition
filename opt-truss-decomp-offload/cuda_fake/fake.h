//
// Created by yche on 1/31/18.
//

#ifndef CUDA_SCAN_FAKE_H
#define CUDA_SCAN_FAKE_H

#ifdef __JETBRAINS_IDE__

#ifdef __GNUC__
#define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif

#include <climits>
#include "math.h"
#include <cstdint>

// 1st: macros
#define __CUDACC__ 1
#define __host__
#define __device__
#define __global__
#define __noinline__
#define __forceinline__
#define __shared__
#define __constant__
#define __managed__
#define __restrict__


// 2nd: CUDA Synchronization
inline void __syncthreads() {};
inline void __threadfence_block() {};
inline void __threadfence() {};
inline void __threadfence_system();
inline int __syncthreads_count(int predicate) { return predicate; }
inline int __syncthreads_and(int predicate) { return predicate; }
inline int __syncthreads_or(int predicate) { return predicate; }


// 3rd: CUDA TYPES
typedef unsigned short uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;
typedef long long longlong;
typedef int * cudaEvent_t;

struct dim3
{
    int x;
    int y;
    int z;

    dim3(int x1, int y1, int z1): x(x1),y(y1),z(z1) {}
    dim3(int x1, int y1): x(x1),y(y1),z(1) {}
    dim3(int x1): x(x1),y(1),z(1) {}
};

enum cudaError_t
{
    cudaSuccess = 0,
    cudaNotSuccess = 1
};

enum cudaMemcpyKind
{
    cudaMemcpyHostToHost, cudaMemcpyHostToDevice, cudaMemcpyDeviceToHost, cudaMemcpyDeviceToDevice, cudaMemcpyDefault
};

struct cudaDeviceProp {
    char name[256];
    size_t totalGlobalMem;
    size_t sharedMemPerBlock;
    int regsPerBlock;
    int warpSize;
    size_t memPitch;
    int maxThreadsPerBlock;
    int maxThreadsDim[3];
    int maxGridSize[3];
    int clockRate;
    size_t totalConstMem;
    int major;
    int minor;
    size_t textureAlignment;
    size_t texturePitchAlignment;
    int deviceOverlap;
    int multiProcessorCount;
    int kernelExecTimeoutEnabled;
    int integrated;
    int canMapHostMemory;
    int computeMode;
    int maxTexture1D;
    int maxTexture1DMipmap;
    int maxTexture1DLinear;
    int maxTexture2D[2];
    int maxTexture2DMipmap[2];
    int maxTexture2DLinear[3];
    int maxTexture2DGather[2];
    int maxTexture3D[3];
    int maxTexture3DAlt[3];
    int maxTextureCubemap;
    int maxTexture1DLayered[2];
    int maxTexture2DLayered[3];
    int maxTextureCubemapLayered[2];
    int maxSurface1D;
    int maxSurface2D[2];
    int maxSurface3D[3];
    int maxSurface1DLayered[2];
    int maxSurface2DLayered[3];
    int maxSurfaceCubemap;
    int maxSurfaceCubemapLayered[2];
    size_t surfaceAlignment;
    int concurrentKernels;
    int ECCEnabled;
    int pciBusID;
    int pciDeviceID;
    int pciDomainID;
    int tccDriver;
    int asyncEngineCount;
    int unifiedAddressing;
    int memoryClockRate;
    int memoryBusWidth;
    int l2CacheSize;
    int maxThreadsPerMultiProcessor;
    int streamPrioritiesSupported;
    int globalL1CacheSupported;
    int localL1CacheSupported;
    size_t sharedMemPerMultiprocessor;
    int regsPerMultiprocessor;
    int managedMemory;
    int isMultiGpuBoard;
    int multiGpuBoardGroupID;
    int singleToDoublePrecisionPerfRatio;
    int pageableMemoryAccess;
    int concurrentManagedAccess;
    int computePreemptionSupported;
    int canUseHostPointerForRegisteredMem;
    int cooperativeLaunch;
    int cooperativeMultiDeviceLaunch;
    int pageableMemoryAccessUsesHostPageTables;
    int directManagedMemAccessFromHost;
};

enum cudaLimit
{
    cudaLimitStackSize,
    cudaLimitPrintfFifoSize,
    cudaLimitMallocHeapSize
};

typedef dim3 uint3;
extern uint3 gridDim;
extern uint3 blockIdx;
extern uint3 blockDim;
extern uint3 threadIdx;
extern int warpsize;
extern int warpSize;

// 4th: Warp-Functions
// old:
int __any(int predicate);
uint32_t __ballot(int predicate);
uint32_t __popc(int predicate);

template<class T>
T __shfl_down(T var, unsigned int delta, int width = warpSize);

template<class T>
T __shfl(T var, unsigned int delta, int width = warpSize);

// new:
int __all_sync(unsigned mask, int predicate);

int __any_sync(unsigned mask, int predicate);

unsigned __ballot_sync(unsigned mask, int predicate);

unsigned __activemask();
__device__ ​ int __ffs ( int  x );

// 5th: Warp-Match Functions
template<class T>
unsigned int __match_any_sync(unsigned mask, T value);

template<class T>
unsigned int __match_all_sync(unsigned mask, T value, int *pred);

// Warp-Shuffle Functions
template<class T>
T __shfl_sync(unsigned mask, T var, int srcLane, int width = warpSize);

template<class T>
T __shfl_up_sync(unsigned mask, T var, unsigned int delta, int width = warpSize);

template<class T>
T __shfl_down_sync(unsigned mask, T var, unsigned int delta, int width = warpSize);

template<class T>
T __shfl_xor_sync(unsigned mask, T var, int laneMask, int width = warpSize);

// 5th: memory functions

template<class T>
T cudaMallocManaged(void** devPtr, size_t size, unsigned int flags = cudaMemAttachGlobal);
cudaError_t cudaMalloc ( void** devPtr, size_t size );
cudaError_t cudaMemcpy ( void* dst, const void* src, size_t count, cudaMemcpyKind kind );

template<class T>
T cudaFree ( void* devPtr );


cudaError_t cudaMemset(void *devPtr, int value, size_t count);

// 6th: others
​const char* cudaGetErrorString ( cudaError_t error );
cudaError_t cudaGetLastError ( void );
​cudaError_t cudaPeekAtLastError ( void );
cudaError_t cudaGetDeviceProperties ( cudaDeviceProp* prop, int  device );
cudaError_t cudaEventCreate ( cudaEvent_t* event );
cudaError_t cudaEventRecord ( cudaEvent_t event);
cudaError_t cudaEventSynchronize(cudaEvent_t event );
cudaError_t cudaEventElapsedTime(float *time, cudaEvent_t event1, cudaEvent_t event2);
cudaError_t cudaDeviceGetLimit	(size_t * pValue, cudaLimit limit);
​cudaError_t cudaDeviceSetLimit ( cudaLimit limit, size_t value );
cudaError_t cudaSetDevice ( int  device );
void __syncwarp(unsigned mask=0xffffffff);
​cudaError_t cudaMemPrefetchAsync ( const void* devPtr, size_t count, int dstDevice, cudaStream_t stream = 0 );
cudaError_t cudaDeviceReset ( void );
cudaError_t cudaDeviceSynchronize ( void );

/*coalesced group*/
struct coalesced_group {
public:
    void sync(){}
    unsigned size(){}
    unsigned thread_rank(){}
    bool is_valid(){}
};
coalesced_group coalesced_threads();

template<typename T>
__host__ ​cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessor ( int* numBlocks, T func, int  blockSize, size_t dynamicSMemSize );

#include "fake_atomic.h"
#include "fake_math.h"

#endif

#endif //CUDA_SCAN_FAKE_H
