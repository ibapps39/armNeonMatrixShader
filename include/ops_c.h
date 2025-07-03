#pragma once
#include "common.h"

// async, give an array random floats
void async_populate(std::vector<vec3> &v, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        v[i] = rand_vecf();
    }
}
// threads to vector that are prepopulated with tiles
void push_threads(std::vector<std::thread> &threads_v, int start, int end, std::vector<vec3> &v)
{
    threads_v.push_back(std::thread(&async_populate, std::ref(v), start, end));
}

void start_threads(int N, int max_threads, std::vector<vec3>& arr)
{
        std::vector<std::thread> threads;

        int chunk_size = N / max_threads; // 1000000 / 8 = 125000

        for (int i = 0; i < max_threads; i++)
        {
            int start = i * chunk_size;
            int end = (i == max_threads - 1) ? N : (i + 1) * chunk_size;
            push_threads(threads, start, end, arr);
        }
        for (auto &t : threads)
        {
            t.join();
        }
}
void add_float_c(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C)
{
    for (size_t i = 0; i < A.size(); i++)
    {
        C[i].e[0] = A[i].e[0] + B[i].e[0];
        C[i].e[1] = A[i].e[1] + B[i].e[1];
        C[i].e[2] = A[i].e[2] + B[i].e[2];
    }
}