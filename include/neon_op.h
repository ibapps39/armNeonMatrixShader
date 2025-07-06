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
void neon_sub_threaded(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R, int start, int end)
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

        result.val[0] = vsubq_f32(vec_a.val[0], vec_b.val[0]);
        result.val[1] = vsubq_f32(vec_a.val[1], vec_b.val[1]);
        result.val[2] = vsubq_f32(vec_a.val[2], vec_b.val[2]);
        vst3q_f32(r_ptr + i * 3, result);
    }
    // Would A-B be faster here??
    for (i; i < end; i++)
    {
        R[i].e[vec3::X] = A[i].x() - B[i].x();
        R[i].e[vec3::Y] = A[i].y() - B[i].y();
        R[i].e[vec3::Z] = A[i].z() - B[i].z();
    }
}
void neon_dot_threaded(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R, int start, int end)
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

        result.val[0] = vmulq_f32(vec_a.val[0], vec_b.val[0]);
        result.val[1] = vmulq_f32(vec_a.val[1], vec_b.val[1]);
        result.val[2] = vmulq_f32(vec_a.val[2], vec_b.val[2]);
        vst3q_f32(r_ptr + i * 3, result);
    }
    for (i; i < end; i++)
    {
        R[i].e[vec3::X] = A[i].x() * B[i].x();
        R[i].e[vec3::Y] = A[i].y() * B[i].y();
        R[i].e[vec3::Z] = A[i].z() * B[i].z();
    }
}
void neon_div_threaded(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R, int start, int end)
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

        result.val[0] = vdivq_f32(vec_a.val[0], vec_b.val[0]);
        result.val[1] = vdivq_f32(vec_a.val[1], vec_b.val[1]);
        result.val[2] = vdivq_f32(vec_a.val[2], vec_b.val[2]);
        vst3q_f32(r_ptr + i * 3, result);
    }
    for (i; i < end; i++)
    {
        R[i].e[vec3::X] = A[i].x() / B[i].x();
        R[i].e[vec3::Y] = A[i].y() / B[i].y();
        R[i].e[vec3::Z] = A[i].z() / B[i].z();
    }
}
void neon_cross_threaded(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R, int start, int end)
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

        result.val[0] = vmulq_f32(vec_a.val[1], vec_b.val[2]);
        result.val[0] = vmlsq_f32(result.val[0], vec_a.val[2], vec_b.val[1]);
        result.val[1] = vmulq_f32(vec_a.val[2], vec_b.val[0]);
        result.val[1] = vmlsq_f32(result.val[1], vec_a.val[0], vec_b.val[2]);
        result.val[2] = vmulq_f32(vec_a.val[0], vec_b.val[1]);
        result.val[2] = vmlsq_f32(result.val[2], vec_a.val[1], vec_b.val[0]);

        vst3q_f32(r_ptr + i * 3, result);
    }
    for (i; i < end; i++)
    {
        // A[i].y() * B[i].z() - A[i].z() * B[i].y(),
        // A[i].z() * B[i].x() - A[i].x() * B[i].z(),
        // A[i].x() * B[i].y() - A[i].y() * B[i].x()

        R[i].e[vec3::X] = (A[i].y() * B[i].z()) - (A[i].z() * B[i].y());
        R[i].e[vec3::Y] = (A[i].x() * B[i].z()) - (A[i].z() * B[i].x());
        R[i].e[vec3::Z] = (A[i].x() * B[i].y()) - (A[i].y() * B[i].x());

        // float32x2_t vec_a_1 = vld1_f32(a_ptr + 1); // D register = [ak, aj]
        // float32x2_t vec_a_2 = vld1_f32(a_ptr );     // D register = [aj, ai]
        // float32x2_t vec_b_1 = vld1_f32(b_ptr + 1); // D register = [bk, bj]
        // float32x2_t vec_b_2 = vld1_f32(b_ptr);     // D register = [bj, bi]

        // float32x4_t vec_a = vcombine_f32(vec_a_1, vec_a_2); // Q register = [aj, ai, ak, aj]
        // float32x4_t vec_b = vcombine_f32(vec_b_1, vec_b_2); // Q register = [bj, bi, bk, bj]
        // float32x4_t vec_a_rot = vextq_f32(vec_a, vec_a, 1);
        // float32x4_t vec_b_rot = vextq_f32(vec_b, vec_b, 1);

        // // vec_a     = [ aj, ai, ak, aj ]
        // // vec_b_rot = [ bj, bj, bi, bk ]
        // // vec_a_rot = [ aj, aj, ai, ak ]
        // // vec_b     = [ bj, bi, bk, bj ]

        // float32x4_t prod = vmulq_f32(vec_a, vec_b_rot);

        // // prod = [ ajbj, aibj, akbi, ajbk ]

        // prod = vmlsq_f32(prod, vec_a_rot, vec_b);
        // // prod = [ ajbj-ajbj, aibj-ajbi, akbi-aibk, ajbk-akbj ]

        // vst1_f32(r_ptr, vget_low_f32(prod));              // Store the lower two elements to address r
        // vst1_lane_f32(r_ptr + 2, vget_high_f32(prod), 0); // Store the 3rd element
    }
}

typedef void (*NeonFunc)(
    std::vector<std::thread> &threads,
    int start,
    int end,
    std::vector<vec3> &VEC_1,
    std::vector<vec3> &VEC_2,
    std::vector<vec3> &VEC_R);
// threads to vector that are prepopulated with tiles
void neon_add(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    threads_v.push_back(std::thread(&neon_add_threaded, std::ref(A), std::ref(B), std::ref(C), start, end));
}
void neon_sub(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    threads_v.push_back(std::thread(&neon_sub_threaded, std::ref(A), std::ref(B), std::ref(C), start, end));
}
void neon_dot(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    threads_v.push_back(std::thread(&neon_dot_threaded, std::ref(A), std::ref(B), std::ref(C), start, end));
}
void neon_div(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    threads_v.push_back(std::thread(&neon_div_threaded, std::ref(A), std::ref(B), std::ref(C), start, end));
}
void neon_cross(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    threads_v.push_back(std::thread(&neon_cross_threaded, std::ref(A), std::ref(B), std::ref(C), start, end));
}

void thread_neon(NeonFunc op, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    int max_threads = std::thread::hardware_concurrency();
    int chunk_size = A.size() / max_threads;
    int N = A.size();
    std::vector<std::thread> threads;

    for (int i = 0; i < max_threads; i++)
    {
        int start = i * chunk_size;
        int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
        op(threads, start, end, A, B, C);
    }
    for (auto &t : threads)
    {
        t.join();
    }
}

void thread_neon_switch(int N, char op, int max_threads, std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    std::vector<std::thread> threads;

    int chunk_size = N / max_threads; // 1000000 / 8 = 125000
    switch (op)
    {
    case '+':
        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            neon_add(threads, start, end, A, B, C);
        }
        break;
    case '-':
        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            neon_add(threads, start, end, A, B, C);
        }
        break;
    case '*':
        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            neon_dot(threads, start, end, A, B, C);
        }
        break;
    case '/':
        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            neon_dot(threads, start, end, A, B, C);
        }
        break;
    case 'c':
        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            neon_cross(threads, start, end, A, B, C);
        }
        break;
    default:
        break;
    }

    for (auto &t : threads)
    {
        t.join();
    }
}
