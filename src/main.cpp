#include "common.h"

int main()
{
    // time_t t = timelocal(NULL);
    srand(NULL);
    const int N = 1000000;
    vec3 A[N];
    vec3 B[N];
    vec3 C[N];

    const char* command = "sysctl -n hw.ncpu";
    std::string max_t = exec(command);
    int max_threads = std::stoi(max_t);
    std::clog << "maxt = " << max_threads;

    // Linear, sync
    for (size_t i = 0; i < N; i++)
    {
        A[i] = rand_vecf();
    }
    // Concurrent
    std::vector<std::thread> threads;
    std::vector<TILE> tiles;
    
    return 0;
}