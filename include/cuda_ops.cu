#pragma once
#include "cuda_runtime.h"
#include "vec3.h"

__global__
void add_float_cuda_test(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    const float* a_ptr = reinterpret_cast<const float*>(A.data());
    const float* b_ptr = reinterpret_cast<const float*>(B.data());
    float* c_ptr = reinterpret_cast<float*>(C.data());

    const float *a_ptr = reinterpret_cast<const float *>(A.data());
    const float *b_ptr = reinterpret_cast<const float *>(B.data());
    float *r_ptr = reinterpret_cast<float *>(R.data());

    for (size_t i = 0; i < A.size(); i++)
    {
        C[i].e[0] = A[i].e[0] + B[i].e[0];
        C[i].e[1] = A[i].e[1] + B[i].e[1];
        C[i].e[2] = A[i].e[2] + B[i].e[2];
    }
}