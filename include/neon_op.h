#include "common.h"
#include <cassert>
#pragma once

/// @brief Adds two square matrices and stores the result.
/// @param a Matrix of size reference
/// @param b Second Matrix
/// @param r Matrix of sum of a and b
void neon_add(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R)
{
    assert(A.size() == B.size());
    // convert vectors<vec3> to a float*
    const float *a_ptr = reinterpret_cast<const float *>(A.data());
    const float *b_ptr = reinterpret_cast<const float *>(B.data());
    float *r_ptr = reinterpret_cast<float *>(R.data());

    // Shared in case of size % 4 > 0
    const size_t &size = A.size();
    size_t i = 0;

    for (i; i + 4 < size; i += 4)
    {
        // load 4 float32s of 3 diminsions from float*
        float32x4x3_t vec_a = vld3q_f32(a_ptr + i * 3);
        float32x4x3_t vec_b = vld3q_f32(b_ptr + i * 3);
        float32x4x3_t result;

        result.val[0] = vaddq_f32(vec_a.val[0], vec_b.val[0]);
        result.val[1] = vaddq_f32(vec_a.val[1], vec_b.val[1]);
        result.val[2] = vaddq_f32(vec_a.val[2], vec_b.val[2]);
        vst3q_f32(r_ptr + i * 3, result);
    }
    if (size % 4 > 0)
    {
        for (i; i < size; i++)
        {
            R[i].e[vec3::X] = A[i].x() + B[i].x();
            R[i].e[vec3::Y] = A[i].y() + B[i].y();
            R[i].e[vec3::Z] = A[i].z() + B[i].z();
        }
    }
}

std::vector<vec3> neon_add(const std::vector<vec3> &A, const std::vector<vec3> &B)
{
    assert(A.size() == B.size());
    
    const size_t &size = A.size();
    std::vector<vec3> C;
    C.reserve(size);

    // convert vectors<vec3> to a float*
    const float *a_ptr = reinterpret_cast<const float *>(A.data());
    const float *b_ptr = reinterpret_cast<const float *>(B.data());
    float *r_ptr = reinterpret_cast<float *>(C.data());

    // Shared in case of size % 4 > 0
    size_t i = 0;

    for (i; i + 4 < size; i += 4)
    {
        // load 4 float32s of 3 diminsions from float*
        float32x4x3_t vec_a = vld3q_f32(a_ptr + i * 3);
        float32x4x3_t vec_b = vld3q_f32(b_ptr + i * 3);
        float32x4x3_t result;

        result.val[0] = vaddq_f32(vec_a.val[0], vec_b.val[0]);
        result.val[1] = vaddq_f32(vec_a.val[1], vec_b.val[1]);
        result.val[2] = vaddq_f32(vec_a.val[2], vec_b.val[2]);
        vst3q_f32(r_ptr + i * 3, result);
    }
    if (size % 4 > 0)
    {
        for (i; i < size; i++)
        {
            C[i].e[vec3::X] = A[i].x() + B[i].x();
            C[i].e[vec3::Y] = A[i].y() + B[i].y();
            C[i].e[vec3::Z] = A[i].z() + B[i].z();
        }
    }
    return C;
}

void neon_add_test(const std::vector<vec3> &a, const std::vector<vec3> &b, std::vector<vec3> &r)
{
    // convert vectors<vec3> to a float*
    const float *a_ptr = reinterpret_cast<const float *>(a.data());
    const float *b_ptr = reinterpret_cast<const float *>(b.data());
    float *r_ptr = reinterpret_cast<float *>(r.data());

    // load 4 float32s of 3 diminsions from float*
    float32x4x3_t vec_a = vld3q_f32(a_ptr);
    float32x4x3_t vec_b = vld3q_f32(b_ptr);
    float32x4x3_t result;

    result.val[0] = vaddq_f32(vec_a.val[0], vec_b.val[0]);
    result.val[1] = vaddq_f32(vec_a.val[1], vec_b.val[1]);
    result.val[2] = vaddq_f32(vec_a.val[2], vec_b.val[2]);
    vst3q_f32(r_ptr, result);
}

void add_float_c(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    // 0.001341 seconds!
    for (size_t i = 0; i < A.size(); i++)
    {
        C[i].e[0] = A[i].e[0] + B[i].e[0];
        C[i].e[1] = A[i].e[1] + B[i].e[1];
        C[i].e[2] = A[i].e[2] + B[i].e[2];
    }
}