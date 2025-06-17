#pragma once
#include <thread>
#include <vector>
#include <memory>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <arm_neon.h>
#include "vec3.h"
#include "neon_op.h"
#include "vec3n.h"
#include "test.h"

void read_vec(const std::vector<vec3> &A, const std::vector<vec3> &B, const std::vector<vec3> &C)
{

    std::cout << "First 10 elements: A" << std::endl;
    for (size_t i = 0; i < 11; i++)
    {
        std::cout << "A" << i << "[" << A[i].x() << ", " << A[i].y() << ", " << A[i].z() << "]\n";
    }
    std::cout << std::endl;
    std::cout << "First 10 elements: B" << std::endl;
    for (size_t i = 0; i < 11; i++)
    {
        std::cout << "B" << i << "[" << B[i].x() << ", " << B[i].y() << ", " << B[i].z() << "]\n";
    }
    std::cout << std::endl;
    std::cout << "First 10 elements: C" << std::endl;
    for (size_t i = 0; i < 11; i++)
    {
        std::cout << "C" << i << "[" << C[i].x() << ", " << C[i].y() << ", " << C[i].z() << "]\n";
    }
    
    std::cout << std::endl;
}
void read_arr(float*& flat, int start, int end, vec3::dim dim)
{
    char d;
    switch (dim)
    {
    case vec3::X :
        d = 'x';
        break;
    case vec3::Y :
        d = 'y';
        break;
    case vec3::Z :
        d = 'z';
        break;
    default:
        d = '?';
        break;
    }
std::cout << "flat_" << d << "[";
    for (size_t i = start; i < end; i++)
    {
        std::cout << flat[i] << ", ";
    }
    std::cout << "...]\n";
}

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

inline std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output into the result string
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    return result;
}