#include "common.h"

int main()
{
    // time_t t = timelocal(NULL);
    srand(time(NULL));
    const int N = 1000000;

    std::vector<vec3> A(N);
    std::vector<vec3> B(N);
    std::vector<vec3> C(N);

    const char* command = "sysctl -n hw.ncpu";
    std::string max_t = exec(command);
    int max_threads = std::stoi(max_t);
    std::clog << "maxt = " << max_threads << std::endl;

    std::vector<std::thread> threads;

    int chunk_size = N / max_threads; // 1000000 / 8 = 125000
    for (int i = 0; i < max_threads; i++)
    {
        int start = i*chunk_size;
        int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
        push_threads(threads, start, end, A);
    }
    
    for (auto& t : threads)
    {
        t.join();
    }
    for (size_t i = 0; i < 24; i++)
    {
        std::cout << "["<< A[i].x() << ", " << A[i].y() << ", " << A[i].z() << "]\n";
    }
    return 0;
}
