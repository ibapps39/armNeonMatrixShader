#pragma once
#include "cuda_op.h"

__global__ 
void add_float_cuda_kernel(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t i = blockIdx.x * blockDim.x + threadIdx.x;
    // Calculate chunks, but for now just finish the sum?
    if (i < N)
    {
        C[i] = A[i] + B[i];
    }
}

void add_float_cuda(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    const float* a_ptr = reinterpret_cast<const float*>(A.data());
    const float* b_ptr = reinterpret_cast<const float*>(B.data());
    float* c_ptr = reinterpret_cast<float*>(C.data());

    cudaMalloc(&a_ptr, );

    for (size_t i = 0; i < A.size(); i++)
    {
        C[i].e[0] = A[i].e[0] + B[i].e[0];
        C[i].e[1] = A[i].e[1] + B[i].e[1];
        C[i].e[2] = A[i].e[2] + B[i].e[2];
    }
}