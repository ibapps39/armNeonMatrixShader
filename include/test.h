#pragma once
#include "common.h"
#include <cassert>
using namespace std;


void thread_vec3(std::vector<vec3>& a, std::vector<vec3>& b, std::vector<vec3>& result, int start, int end)
{
    for (int i = start; i < end; i += 4)
    {
        // Load 4 vec3s at once (interleaved SoA style recommended for real SIMD benefit)
        float32x4_t ax = {a[i].x(), a[i+1].x(), a[i+2].x(), a[i+3].x()};
        float32x4_t ay = {a[i].y(), a[i+1].y(), a[i+2].y(), a[i+3].y()};
        float32x4_t az = {a[i].z(), a[i+1].z(), a[i+2].z(), a[i+3].z()};

        float32x4_t bx = {b[i].x(), b[i+1].x(), b[i+2].x(), b[i+3].x()};
        float32x4_t by = {b[i].y(), b[i+1].y(), b[i+2].y(), b[i+3].y()};
        float32x4_t bz = {b[i].z(), b[i+1].z(), b[i+2].z(), b[i+3].z()};

        float32x4_t rx = vaddq_f32(ax, bx);
        float32x4_t ry = vaddq_f32(ay, by);
        float32x4_t rz = vaddq_f32(az, bz);

        // Store results
        for (int j = 0; j < 4; ++j)
        {
            result[i + j][vec3::X] = vgetq_lane_f32(rx, j);
            result[i + j][vec3::Y] = vgetq_lane_f32(ry, j);
            result[i + j][vec3::Z] = vgetq_lane_f32(rz, j);
        }
    }
}
void start_neon_threads_test(std::vector<vec3>& a, std::vector<vec3>& b, std::vector<vec3>& result, int max_threads)
{
    int N = a.size();
    int chunk_size = N / max_threads;

    std::vector<std::thread> threads;
    for (int i = 0; i < max_threads; ++i)
    {
        int start = i * chunk_size;
        int end = (i == max_threads - 1) ? N : start + chunk_size;

        threads.emplace_back(thread_vec3, std::ref(a), std::ref(b), std::ref(result), start, end);
    }

    for (auto& t : threads)
        t.join();
}