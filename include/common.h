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

void read_arr(const std::vector<vec3> &A, const std::vector<vec3> &B, const std::vector<vec3> &C)
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
    if (C[0].x() == 0 && C[0].x() == 0 && C[0].x() == 0) {return;}
    
        std::cout << "First 10 elements: B" << std::endl;
        for (size_t i = 0; i < 11; i++)
        {
            std::cout << "C" << i << "[" << C[i].x() << ", " << C[i].y() << ", " << C[i].z() << "]\n";
        }
    std::cout << std::endl;
}

inline double chrono(void(*func))
{
    std::chrono::steady_clock::time_point begin;
    func;
    std::chrono::steady_clock::time_point end;
    return (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;
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