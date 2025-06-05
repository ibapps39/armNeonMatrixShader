#include "common.h"
#include <cassert>
#pragma once

inline float* flatten_vec3(const std::vector<vec3>& vec3_vector, vec3::dim dim)
{
    float* arr = new float[vec3_vector.size()];
    
    for (size_t i = 0; i < vec3_vector.size(); i++)
    {
        arr[i] = vec3_vector[i][dim];
    }
    return arr;
}
// std::vector<float> flatten_vec3_vec(const std::vector<vec3>& arr) {
//     std::vector<float> flat;
//     flat.reserve(arr.size() * 3);
//     for (const auto& v : arr) {
//         flat.push_back(v.x());
//         flat.push_back(v.y());
//         flat.push_back(v.z());
//     }
//     return flat;
// }

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
