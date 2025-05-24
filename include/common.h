#pragma once
#include <thread>
#include <vector>
#include <memory>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>
#include "vec3.h"


// typedef struct TILE
// {
//     int start;
//     int end;
// } TILE;



// async, give an array random floats
void async_populate(std::vector<vec3>& v, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        v[i] = rand_vecf();
    }
}
// threads to vector that are prepopulated with tiles
void push_threads(std::vector<std::thread>& threads_v, int start, int end, std::vector<vec3>& v)
{
    threads_v.push_back( std::thread(&async_populate, std::ref(v), start, end) );
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