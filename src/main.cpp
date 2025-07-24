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
    std::clog << "MAX THREADS per std::thread::hardware_concurrency() = " << m_threads << std::endl;
    assert(m_threads == max_threads);
    std::cout << std::endl;

    std::cout << "N = " << N << std::endl;
    std::cout << std::endl;

    std::__1::chrono::steady_clock::time_point begin;
    std::__1::chrono::steady_clock::time_point end;
    double time = 0.0;

    std::cout << "POPULATING A, B USING THREADS" << std::endl;
    double a_populated_by_threads = timeFunction(populate_threads_random_vectors, N, m_threads, A);
    std::printf("Time to populate A with %i elements: %fs\n", N, a_populated_by_threads);
    double b_populated_by_threads = timeFunction(populate_threads_random_vectors, N, m_threads, B);
    std::printf("Time to populate B with %i elements: %fs\n", N, b_populated_by_threads);
    std::cout << std::endl;

    std::cout << "ADD FLOAT C:" << std::endl;
    double add_float_c_t = timeFunction(add_float_c, A, B, C);
    std::cout << "TIME: timeFunction(add_float_c, A, B, C): " << add_float_c_t << "s" << std::endl;
    validate_sum(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    double neon_add_time = timeFunction(
        static_cast<void (*)(const std::vector<vec3> &, const std::vector<vec3> &, std::vector<vec3> &)>(neon_add), A, B, C);
    std::printf("Time for neon_add (void), non-threaded+stack+neon, with %i elements: %fs\n", N, neon_add_time);
    validate_sum(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    auto [result, neon_add_t_returned] = timeFunction(
        static_cast<std::vector<vec3> (*)(const std::vector<vec3> &, const std::vector<vec3> &)>(neon_add), A, B);
    std::printf("Time for neon_add (returns std::vector<vec3>) with %i elements: %fs\n", N, neon_add_t_returned);
    C = result;
    validate_sum(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    double neon_threads = timeFunction(thread_neon_switch, N, '+', m_threads, A, B, C);
    std::printf("Time for neon_threads operation with '+' switch (void), threaded, with %i elements: %fs\n", N, neon_threads);
    validate_sum(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    thread_neon(neon_add, std::ref(A), std::ref(B), std::ref(C));
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_add, threaded, with %i elements: %fs\n", N, time);
    validate_sum(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    neon_sub_threaded(std::ref(A), std::ref(B), std::ref(C), 0, N);
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_sub (subtraction), non-threaded, with %i elements: %fs\n", N, time);
    validate_diff(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    thread_neon(neon_sub, std::ref(A), std::ref(B), std::ref(C));
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_sub (subtraction), threaded, with %i elements: %fs\n", N, time);
    validate_diff(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    thread_neon(neon_dot, std::ref(A), std::ref(B), std::ref(C));
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_dot, threaded, with %i elements: %fs\n", N, time);
    validate_dot(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    neon_div_threaded(std::ref(A), std::ref(B), std::ref(C), 0, N);
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_divide, non-threaded, with %i elements: %fs\n", N, time);
    validate_div(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    thread_neon(neon_div, std::ref(A), std::ref(B), std::ref(C));
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_divide, threaded, with %i elements: %fs\n", N, time);
    validate_div(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    neon_cross_threaded(A, B, C, 0, N);
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_cross (void), non-threaded, with %i elements: %fs\n", N, time);
    validate_cross(A, B, C, N);
    // validate_cross_epsilon(A, B, C, N);
    // find_smallest_epsilon_corrected(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    thread_neon(neon_cross, std::ref(A), std::ref(B), std::ref(C));
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for neon_cross (void), threaded, with %i elements: %fs\n", N, time);
    validate_cross(A, B, C, N);
    // validate_cross_epsilon(A, B, C, N);
    // find_smallest_epsilon_corrected(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    arm_asm_add(std::ref(A), std::ref(B), std::ref(C));
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for arm_asm_add (void), with %i elements: %fs\n", N, time);
    validate_sum(A, B, C, N);
    std::cout << std::endl;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < 10; i++)
    {
        vec3 C = A[i] + B[i];
    }
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));

    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++)
    {
        C[i] = A[i] + B[i];
    }
    end = std::chrono::steady_clock::now();
    time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    std::printf("Time for for loop of 'C[i] = A[i]+B[i]' with %i elements: %fs\n", N, time);
    validate_sum(std::ref(A), std::ref(B), std::ref(C), N);
    std::fill(C.begin(), C.end(), vec3(0.00, 0.00, 0.00f));
    std::cout << std::endl;

    
    std::cout << "\n//END////END////END////END////END////END////END//\n";
    return 0;
}
