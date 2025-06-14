#include "common.h"

int main()
{
    srand(time(NULL));
    const int N = 1000000;

    std::vector<vec3> A(N);
    std::vector<vec3> B(N);
    std::vector<vec3> C(N);
    
    std::cout << "\n//START//START////START////START////START////START////START//\n";
    const char *command = "sysctl -n hw.ncpu";
    std::string max_t = exec(command);
    int max_threads = std::stoi(max_t);
    unsigned int m_threads = std::thread::hardware_concurrency();
    std::clog << "MAX THREADS per sysctl -n hw.ncpu: maxt = " << max_threads << std::endl;

    // double a_time = timeFunction(async_populate, A, 0, N - 1);
    double at_time = timeFunction(start_threads, N, max_threads, A);
    double b_time = timeFunction(start_threads, N, max_threads, B);
    read_vec(A, B, C);

    // std::cout << "A - linear, for loop time: " << a_time << "s" << std::endl;
    // std::cout << "B - threads, time: " << b_time << "s" << std::endl;
    // std::cout << std::endl;

    std::cout << "\n//////////////////////////////////////////////////\n";

    double add_float_neonc_t = timeFunction(add_float_neonc, A, B, C);
    std::cout << "\ntimeFunction(add_float_neonc, A, B, C): " << add_float_neonc_t << std::endl;
    std::cout << A.size() << std::endl;
    std::cout << B.size() << std::endl;
    std::cout << (A.size() == B.size()) << std::endl;
    read_vec(A, B, C);

    //double time_neon_add_test = timeFunction(neon_add_test, A, B);
    // std::cout << "\ntimeFunction(neon_add_test, A, B) " << time_neon_add_test << std::endl;
    
    std::cout << "\n//END////END////END////END////END////END////END//\n";
    return 0;
}
