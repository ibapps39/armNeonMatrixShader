#include "common.h"
#include <cassert>
#pragma once

/// @brief Adds two square matrices and stores the result.
/// @param A Matrix of size reference
/// @param B Second Matrix
/// @param R Matrix of sum of a and b
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
    for (i; i < size; i++)
    {
        R[i].e[vec3::X] = A[i].x() + B[i].x();
        R[i].e[vec3::Y] = A[i].y() + B[i].y();
        R[i].e[vec3::Z] = A[i].z() + B[i].z();
    }
}

std::vector<vec3> neon_add(const std::vector<vec3> &A, const std::vector<vec3> &B)
{
    assert(A.size() == B.size());

    const size_t size = A.size();
    std::vector<vec3> C(size);

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
    for (i; i < size; i++)
    {
        C[i].e[vec3::X] = A[i].x() + B[i].x();
        C[i].e[vec3::Y] = A[i].y() + B[i].y();
        C[i].e[vec3::Z] = A[i].z() + B[i].z();
    }
    return C;
}

void neon_add_threaded(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R, int start, int end)
{
    assert(A.size() == B.size());
    // convert vectors<vec3> to a float*
    const float *a_ptr = reinterpret_cast<const float *>(A.data());
    const float *b_ptr = reinterpret_cast<const float *>(B.data());
    float *r_ptr = reinterpret_cast<float *>(R.data());

    // Shared in case of size % 4 > 0
    size_t i = start;

    for (i; i + 4 < end; i += 4)
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
    for (i; i < end; i++)
        {
            R[i].e[vec3::X] = A[i].x() + B[i].x();
            R[i].e[vec3::Y] = A[i].y() + B[i].y();
            R[i].e[vec3::Z] = A[i].z() + B[i].z();
        }
}


// threads to vector that are prepopulated with tiles
void push_threads_neon(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    threads_v.push_back(std::thread(&neon_add_threaded, std::ref(A), std::ref(B), std::ref(C), start, end));
}

void start_threads_neon(int N, int max_threads, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    std::vector<std::thread> threads;

    int chunk_size = N / max_threads; // 1000000 / 8 = 125000

    for (int i = 0; i < max_threads; i++)
    {
        int start = i * chunk_size;
        int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
        push_threads_neon(threads, start, end, A, B, C);
    }
    for (auto &t : threads)
    {
        t.join();
    }
}