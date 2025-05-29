#include "common.h"

int main()
{
    // time_t t = timelocal(NULL);
    srand(time(NULL));
    const int N = 1000000;

    std::vector<vec3> A(N);
    std::vector<vec3> B(N);
    std::vector<vec3> C(N);

    const char *command = "sysctl -n hw.ncpu";
    std::string max_t = exec(command);
    int max_threads = std::stoi(max_t);
    std::clog << "maxt = " << max_threads << std::endl;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    {
        begin = std::chrono::steady_clock::now();
        async_populate(A, 0, N - 1);
        end = std::chrono::steady_clock::now();
    }
    double a_time = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;

    {
        begin = std::chrono::steady_clock::now();
        std::vector<std::thread> threads;
        int chunk_size = N / max_threads; // 1000000 / 8 = 125000
        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            push_threads(threads, start, end, B);
        }

        for (auto &t : threads)
        {
            t.join();
        }
        end = std::chrono::steady_clock::now();
    }
    double b_time = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;

    for (size_t i = 0; i < 24; i++)
    {
        std::cout << "A" << i << "[" << A[i].x() << ", " << A[i].y() << ", " << A[i].z() << "]\n";
    }
    std::cout << std::endl;
    for (size_t i = 0; i < 24; i++)
    {
        std::cout << "B" << i << "[" << B[i].x() << ", " << B[i].y() << ", " << B[i].z() << "]\n";
    }

    std::cout << "A - linear, for loop time: " << a_time << "s" << std::endl;
    std::cout << "B - threads, time: " << b_time << "s" << std::endl;

    return 0;
}
