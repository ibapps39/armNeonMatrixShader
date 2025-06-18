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
    std::clog << "MAX THREADS per sysctl -n hw.ncpu: maxt = " << m_threads << std::endl;
    assert(m_threads == max_threads);

    std::cout << "POPULATING A, B USING THREADS" << std::endl;
    double a_populated_by_threads = timeFunction(start_threads, N, m_threads, A);
    double b__populated_by_threads = timeFunction(start_threads, N, m_threads, B);
    
    std::cout << "ADD FLOAT NEONC:" << std::endl;
    double add_float_neonc_t = timeFunction(add_float_neonc, A, B, C);
    std::cout << "TIME: timeFunction(add_float_neonc, A, B, C): " << add_float_neonc_t << std::endl;
    std::cout << "VECTORS CURRENTLY:" << std::endl;
    read_vec(A, B, C);
    
    std::cout << "\n//END////END////END////END////END////END////END//\n";
    return 0;
}
