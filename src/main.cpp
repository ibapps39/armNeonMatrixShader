#include "main.h"

int main()
{
    // time_t t = timelocal(NULL);
    srand(NULL);
    const int N = 1000000;
    int A[N];
    int B[N];
    int C[N];

    for (size_t i = 0; i < N; i++)
    {
        A[i] = rand() % 100;
    }

    

    

    const char* command = "sysctl -n hw.ncpu";
    std::string max_t = exec(command);
    int max_threads = std::stoi(max_t);

    std::clog << "maxt = " << max_threads;
    //std::clog << command << " << " << system(command) << std::endl;

    if (sizeof(A) > sizeof(int) && sizeof(A) != NULL && A != nullptr)
    {
        
    }

    return 0;
}