#include "common.h"
#pragma once

float* flatten_vec3(const std::vector<vec3>& arr)
{
    float* flat_arr = new float[arr.size() * 3];  // Allocate dynamic memory
    for (int i = 0; i < arr.size(); ++i)
    {
        flat_arr[i*3]       = arr[i].x();
        flat_arr[i*3 + 1]   = arr[i].y();
        flat_arr[i*3 + 2]   = arr[i].z();
    }
    return flat_arr;
}
std::vector<float> flatten_vec3_vec(const std::vector<vec3>& arr) {
    std::vector<float> flat;
    flat.reserve(arr.size() * 3);
    for (const auto& v : arr) {
        flat.push_back(v.x());
        flat.push_back(v.y());
        flat.push_back(v.z());
    }
    return flat;
}

inline void add_float_c(std::vector<vec3> dst, std::vector<vec3> src1, std::vector<vec3> src2, int count)

{
     for (size_t i = 0; i < count; i++)
     {
        dst[i] = src1[i] + src2[i];
     }
}

void example_SIMD()
{
    float a[4] = {rand_vec().x(), rand_vec().y(), rand_vec().z(), 1.0f};
    float b[4] = {rand_vec().x(), rand_vec().y(), rand_vec().z(), 1.0f};
    float result[4];

    float32x4_t vec_a = vld1q_f32(a);
    float32x4_t vec_b = vld1q_f32(b);

    float32x4_t vec_result = vaddq_f32(vec_a, vec_b);
    vst1q_f32(result, vec_result);

    for (auto& e : result)
    {
        std::cout << " " << e; 
    }
}
void vec3_SIMD_add(const std::vector<vec3>& dst, const std::vector<vec3>& A, const std::vector<vec3>& B, size_t N)
{
    float* A_flat = flatten_vec3(A);
    float* B_flat = flatten_vec3(B);
    float* result[N*3];
    size_t i = 0;
    for (; i + 4 <= N; i += 4) {
        // Load 4 vec3s = 12 floats
        float32x4x3_t va = vld3q_f32(A_flat + i * 3);
        float32x4x3_t vb = vld3q_f32(B_flat + i * 3);

        float32x4x3_t vc;
        vc.val[0] = vaddq_f32(va.val[0], vb.val[0]);  // x components
        vc.val[1] = vaddq_f32(va.val[1], vb.val[1]);  // y components
        vc.val[2] = vaddq_f32(va.val[2], vb.val[2]);  // z components

        vst3q_f32(result + i * 3, vc);
    }

    // Fallback for remaining (less than 4)
    for (; i < N; ++i) {
        result[i * 3 + 0] = A_flat[i * 3 + 0] + B_flat[i * 3 + 0];
        result[i * 3 + 1] = A[i * 3 + 1] + B[i * 3 + 1];
        result[i * 3 + 2] = A[i * 3 + 2] + B[i * 3 + 2];
    }

}