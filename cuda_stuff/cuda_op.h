#ifdef __CUDACC__
//#include "cuda_driver.h"
#include "cuda_runtime.h"
#include "vec3.h"
void add_float_cuda_kernel(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &C, size_t N);
void add_float_cuda(const std::vector<vec3> &A, const std::vector<vec3> &B, std::vector<vec3> &C, size_t N);
void add_float_cuda(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N);
void add_float_cuda_test(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N);
#endif