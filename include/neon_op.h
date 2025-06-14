#include "common.h"
#include <cassert>
#pragma once

// std::vector<vec3> neon_add(const std::vector<vec3>& a, const std::vector<vec3>& b)
// {
//     assert(a.size() == b.size() && !(a.empty()));
//     size_t size = a.size();
    
//     const float* a_ptr = reinterpret_cast<const float*>(a.data());
//     const float* b_ptr = reinterpret_cast<const float*>(b.data());
//     std::vector<vec3> c;
//     c.reserve(size);
//     size_t i = 0;
//     i < size;
//     for (; ; i+= 4)
//     {
//         float32x4x3_t a = vld3q_f32(a_ptr + i * 3);
//         float32x4x3_t b = vld3q_f32(b_ptr + i * 3);
//         float32x4x3_t result;
//         // x
//         result.val[0] = vaddq_f32(a.val[0], b.val[0]);
//         // y
//         result.val[1] = vaddq_f32(a.val[1], b.val[1]);
//         // z
//         result.val[2] = vaddq_f32(a.val[2], b.val[2]);

//         // c.at(i)[0] = result.val[0][0];
//         // c.at(i)[1] = result.val[1][1];
//         // c.at(i)[2] = result.val[2][2];
//     }
//     return c;
// }
void neon_add_test(const std::vector<vec3>& a, const std::vector<vec3>& b)
{
    assert(a.size() == b.size());
    size_t size = a.size();
    
    const float* a_ptr = reinterpret_cast<const float*>(a.data());
    const float* b_ptr = reinterpret_cast<const float*>(b.data());
    std::vector<vec3> c[1000000];
    // c.reserve(size);
    size_t i = 0;
    i < size;
    for (; ; i+= 4)
    {
        float32x4x3_t a = vld3q_f32(a_ptr + i * 3);
        float32x4x3_t b = vld3q_f32(b_ptr + i * 3);
        float32x4x3_t result;
        // x
        result.val[0] = vaddq_f32(a.val[0], b.val[0]);
        // y
        result.val[1] = vaddq_f32(a.val[1], b.val[1]);
        // z
        result.val[2] = vaddq_f32(a.val[2], b.val[2]);
    }

}

void neon_add(const std::vector<vec3>& a, const std::vector<vec3>& b, std::vector<vec3>& dst)
{
    // Safety check: make sure all vectors have the same size and aren't empty
    assert(a.size() == b.size() && a.size() == dst.size() && !a.empty());
    
    size_t num_vec3 = a.size();  // How many vec3 objects we need to process
    
    // Get raw pointers to the underlying float data
    // Each vec3 contains 3 floats (x, y, z), so the data is laid out like:
    // [x1, y1, z1, x2, y2, z2, x3, y3, z3, ...]
    const float* a_ptr = reinterpret_cast<const float*>(a.data());
    const float* b_ptr = reinterpret_cast<const float*>(b.data());
    float* dst_ptr = reinterpret_cast<float*>(dst.data());
    
    // NEON SIMD Processing: Handle 4 vec3s at once for maximum speed
    // Why 4? Because NEON can process 4 floats in parallel, and we have 3 components (x,y,z)
    // So we process 4 vec3s = 12 floats total per iteration
    for (size_t i = 0; i + 3 < num_vec3; i += 4) {
        
        // Load 12 consecutive floats and automatically separate them by component
        // vld3q_f32 is magic: it reads 12 floats but separates them into 3 groups:
        // - val[0] gets all the X components: [x1, x2, x3, x4]
        // - val[1] gets all the Y components: [y1, y2, y3, y4]  
        // - val[2] gets all the Z components: [z1, z2, z3, z4]
        float32x4x3_t a_data = vld3q_f32(a_ptr + i * 3);
        float32x4x3_t b_data = vld3q_f32(b_ptr + i * 3);
        
        // Perform vector addition on each component group
        // This adds 4 numbers at once in each operation!
        float32x4x3_t result;
        result.val[0] = vaddq_f32(a_data.val[0], b_data.val[0]); // Add all X components: [a.x1+b.x1, a.x2+b.x2, a.x3+b.x3, a.x4+b.x4]
        result.val[1] = vaddq_f32(a_data.val[1], b_data.val[1]); // Add all Y components: [a.y1+b.y1, a.y2+b.y2, a.y3+b.y3, a.y4+b.y4]
        result.val[2] = vaddq_f32(a_data.val[2], b_data.val[2]); // Add all Z components: [a.z1+b.z1, a.z2+b.z2, a.z3+b.z3, a.z4+b.z4]
        
        // Store the results back to memory
        // vst3q_f32 does the reverse of vld3q_f32: it takes our 3 component groups
        // and interleaves them back into the original format:
        // [x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4]
        vst3q_f32(dst_ptr + i * 3, result);
    }
    
    // Handle leftover vec3s that couldn't fit in groups of 4
    // This handles the "remainder" when the total count isn't divisible by 4
    // NOTE: There's a bug here - this processes ALL elements again!
    // It should start from where the NEON loop left off
    for (size_t i = 0; i < num_vec3; ++i) {
        dst[i].e[0] = a[i].e[0] + b[i].e[0];  // Add X components
        dst[i].e[1] = a[i].e[1] + b[i].e[1];  // Add Y components  
        dst[i].e[2] = a[i].e[2] + b[i].e[2];  // Add Z components
    }
}

/* 
PERFORMANCE EXPLANATION:
- Without NEON: To add 1000 vec3s, you'd do 3000 individual float additions
- With NEON: You do 750 NEON operations (each handling 4 floats) + 0 scalar operations
- This is roughly 4x faster because NEON processes 4 numbers simultaneously

MEMORY LAYOUT EXAMPLE:
If you have vec3s: {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}
Memory looks like: [1,2,3,4,5,6,7,8,9,10,11,12]
vld3q_f32 reads this and creates:
- val[0] = [1,4,7,10]   (X components)
- val[1] = [2,5,8,11]   (Y components) 
- val[2] = [3,6,9,12]   (Z components)
*/
void add_float_neonc(std::vector<vec3> A, std::vector<vec3> B, std::vector<vec3> C)
{
    //.004!
    for (size_t i = 0; i < A.size(); i+=3)
    {
        C[i].e[0] = A[i].e[0] + B[i].e[0];
        C[i].e[1] = A[i].e[1] + B[i].e[1];
        C[i].e[2] = A[i].e[2] + B[i].e[2];
    }
        for (size_t i = 0; i < A.size(); i+=3)
    {
        C[i].e[0] = A[i].e[0] + B[i].e[0];
        C[i].e[1] = A[i].e[1] + B[i].e[1];
        C[i].e[2] = A[i].e[2] + B[i].e[2];
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
inline void add_float_c(std::vector<vec3> dst, std::vector<vec3> src1, std::vector<vec3> src2, int count)

{
     for (size_t i = 0; i < count; i++)
     {
        dst[i] = src1[i] + src2[i];
     }
}