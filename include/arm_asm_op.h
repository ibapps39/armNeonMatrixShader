#include "common.h"
void arm_asm_add(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &R)
{
    // Ensure vectors have the same size
    if (A.size() != B.size() || A.size() != R.size()) return;
    
    // Get raw pointers
    const float* a_ptr = reinterpret_cast<const float*>(A.data());
    const float* b_ptr = reinterpret_cast<const float*>(B.data());
    float* r_ptr = reinterpret_cast<float*>(R.data());
    int N = A.size();
    
    asm volatile (
        "mov w4, #3             \n\t"  // 3 floats per vec3
        "mul w4, %w3, w4        \n\t"  // Total float count = N * 3
        "1:                     \n\t"  // Loop label
        "ldr s0, [%0], #4       \n\t"  // Load A.x, increment pointer
        "ldr s1, [%1], #4       \n\t"  // Load B.x, increment pointer
        "fadd s2, s0, s1        \n\t"  // Add A.x + B.x
        "str s2, [%2], #4       \n\t"  // Store result, increment pointer
        "ldr s0, [%0], #4       \n\t"  // Load A.y
        "ldr s1, [%1], #4       \n\t"  // Load B.y
        "fadd s2, s0, s1        \n\t"  // Add A.y + B.y
        "str s2, [%2], #4       \n\t"  // Store result
        "ldr s0, [%0], #4       \n\t"  // Load A.z
        "ldr s1, [%1], #4       \n\t"  // Load B.z
        "fadd s2, s0, s1        \n\t"  // Add A.z + B.z
        "str s2, [%2], #4       \n\t"  // Store result
        "subs w4, w4, #3        \n\t"  // Decrement float counter by 3
        "b.gt 1b                \n\t"  // Branch if more floats to process
        : "+r" (a_ptr), "+r" (b_ptr), "+r" (r_ptr)
        : "r" (N)
        : "w4", "s0", "s1", "s2", "memory"
    );
}