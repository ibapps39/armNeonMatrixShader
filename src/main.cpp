#include "common.h"

int main()
{
    srand(time(NULL));
    const int N = 1000000;

    std::vector<vec3> A(N);
    std::vector<vec3> B(N);
    std::vector<vec3> C(N);
    
    std::cout << "\n//////////////////////////////////////////////////\n";
    const char *command = "sysctl -n hw.ncpu";
    std::string max_t = exec(command);
    int max_threads = std::stoi(max_t);
    std::clog << "MAX THREADS per sysctl -n hw.ncpu: maxt = " << max_threads << std::endl;

    double a_time = timeFunction(async_populate, A, 0, N - 1);
    double b_time = timeFunction(start_threads, N, max_threads, B);

    std::cout << "A - linear, for loop time: " << a_time << "s" << std::endl;
    std::cout << "B - threads, time: " << b_time << "s" << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < 10; i++)
    {
        std::cout << "A" << i << "[" << A[i] << "]" << std::endl;
    }
    std::cout << "\n";
    float* flatx = flatten_vec3(A, vec3::X);
    float* flaty = flatten_vec3(A, vec3::Y);
    float* flatz = flatten_vec3(A, vec3::Z);
    std::cout << "ax[";
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << flatx[i] << ", ";
    }
    std::cout << "...]\n";
    std::cout << "ay[";
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << flaty[i] << ", ";
    }
    std::cout << "...]\n";
    std::cout << "az[";
    for (size_t i = 0; i < 10; i++)
    {
        std::cout << flatz[i] << ", ";
    }
    std::cout << "...]\n";

    std::cout << "\n//////////////////////////////////////////////////\n";
    return 0;
}
