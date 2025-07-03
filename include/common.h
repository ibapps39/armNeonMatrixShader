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
#include "ops_c.h"

void read_vec(const std::vector<vec3> &A, const std::vector<vec3> &B, const std::vector<vec3> &C)
{

    std::cout << "First 5 elements: A" << std::endl;
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << "A" << i << "[" << A[i].x() << ", " << A[i].y() << ", " << A[i].z() << "]\n";
    }
    std::cout << std::endl;
    std::cout << "First 5 elements: B" << std::endl;
    for (size_t i = 0; i < 5; i++)
    {
        std::cout << "B" << i << "[" << B[i].x() << ", " << B[i].y() << ", " << B[i].z() << "]\n";
    }
    std::cout << std::endl;
    std::cout << "First 5 elements: C" << std::endl;
    for (size_t i = 0; i < 5; i++)
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