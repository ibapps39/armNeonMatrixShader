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


typedef struct TILE
{
    int start;
    int end;
} TILE;

// async
void async_populate(vec3 arr[], TILE tile)
{
    for (int i = tile.start; i < tile.end; i++)
    {
        arr[i] = rand_vecf();
    }
}

void create_threads(std::vector<std::thread>& threads_v, TILE tile, vec3 arr[])
{
    for (size_t i = tile.start; i < tile.end; i++)
    {
        threads_v.push_back(std::thread(&async_populate, arr, tile));
    }
}
void create_tile(std::vector<TILE>& tile_v, int start, int tile_size, int max_threads, int N, int tile_idx = 0) {
    if (start >= N || tile_idx >= max_threads) return;
    
    TILE tile;
    tile.start = start;
    tile.end = std::min(start + tile_size - 1 + (tile_idx < N % max_threads ? 1 : 0), N - 1);
    tile_v.push_back(tile);
    
    create_tile(tile_v, tile.end + 1, tile_size, max_threads, N, tile_idx + 1);
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