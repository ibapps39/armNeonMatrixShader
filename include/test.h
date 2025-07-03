#pragma once
template <typename Func, typename... Args>
auto timeFunction(Func &&f, Args &&...args)
{
    auto begin = std::chrono::steady_clock::now();
    if constexpr (std::is_void_v<decltype(f(args...))>)
    {
        f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        return (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;
    }
    else
    {
        auto result = f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        return std::make_pair(result, (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0);
    }
}
void error_sum(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t i)
{
    std::cout << "Incorrect: C[" << i << "]:" << "[" << C[i] << "]" << std::endl;
    std::cout << "\t A[" << i << "]:" << A[i] << std::endl;
    std::cout << "\t B[" << i << "]:" << B[i] << std::endl;
    std::cout << "\t C[" << i << "] should be:[" << A[i].x() + B[i].x() << ", " << (A[i].y() + B[i].y()) << ", "
              << (A[i].z() + B[i].z()) << "]"
              << std::endl;
}
void validate_sum(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    size_t i = 0;
    for (; i < N; ++i)
    {
        correct += (C[i].x() == (A[i].x() + B[i].x()) &&
                    C[i].y() == (A[i].y() + B[i].y()) &&
                    C[i].z() == (A[i].z() + B[i].z()));
    }
    if (correct < i) { 
        error_sum(A, B, C, i); 
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}