//
// Created by yche on 2/1/18.
//

#ifndef CUDA_SCAN_FAKE_ATOMIC_H
#define CUDA_SCAN_FAKE_ATOMIC_H

// Atomic Functions: http://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html#atomic-functions
//.......................... arithmetic operations
// 1st: add
int atomicAdd(int *address, int val);

unsigned int atomicAdd(unsigned int *address, unsigned int val);

unsigned long long int atomicAdd(unsigned long long int *address, unsigned long long int val);

float atomicAdd(float *address, float val);

double atomicAdd(double *address, double val);

// 2nd: sub
int atomicSub(int *address, int val);

unsigned int atomicSub(unsigned int *address, unsigned int val);

// 3rd: exch
int atomicExch(int *address, int val);

unsigned int atomicExch(unsigned int *address, unsigned int val);

unsigned long long int atomicExch(unsigned long long int *address, unsigned long long int val);

float atomicExch(float *address, float val);

// 4th: min
int atomicMin(int *address, int val);

unsigned int atomicMin(unsigned int *address, unsigned int val);

unsigned long long int atomicMin(unsigned long long int *address, unsigned long long int val);

// 5th: inc, dec
unsigned int atomicInc(unsigned int *address, unsigned int val);

unsigned int atomicDec(unsigned int *address, unsigned int val);

// 6th: cas
int atomicCAS(int *address, int compare, int val);

unsigned int atomicCAS(unsigned int *address, unsigned int compare, unsigned int val);

unsigned long long int
atomicCAS(unsigned long long int *address, unsigned long long int compare, unsigned long long int val);

//.......................... logical operations
// 1st: and
int atomicAnd(int *address, int val);

unsigned int atomicAnd(unsigned int *address, unsigned int val);

unsigned long long int atomicAnd(unsigned long long int *address, unsigned long long int val);

// 2nd: or
int atomicOr(int *address, int val);

unsigned int atomicOr(unsigned int *address, unsigned int val);

unsigned long long int atomicOr(unsigned long long int *address, unsigned long long int val);

// 3rd: xor
int atomicXor(int *address, int val);

unsigned int atomicXor(unsigned int *address, unsigned int val);

unsigned long long int atomicXor(unsigned long long int *address, unsigned long long int val);

#endif //CUDA_SCAN_FAKE_ATOMIC_H
