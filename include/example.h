#include <arm_neon.h>
#include <thread>
#include <vector>
#include <algorithm>

void add_arrays_neon_threaded(const float* a, const float* b, float* out, int size) {
    const int simd_width = 4; // NEON processes 4 floats at a time
    const int num_threads = std::thread::hardware_concurrency();
    const int chunk_size = (size + num_threads - 1) / num_threads;

    auto worker = [=](int start, int end) {
        int i = start;
        for (; i <= end - simd_width; i += simd_width) {
            float32x4_t va = vld1q_f32(&a[i]);
            float32x4_t vb = vld1q_f32(&b[i]);
            float32x4_t vsum = vaddq_f32(va, vb);
            vst1q_f32(&out[i], vsum);
        }
        for (; i < end; ++i) {
            out[i] = a[i] + b[i];
        }
    };

    std::vector<std::thread> threads;
    for (int t = 0; t < num_threads; ++t) {
        int start = t * chunk_size;
        int end = std::min(start + chunk_size, size);
        threads.emplace_back(worker, start, end);
    }

    for (auto& th : threads) {
        th.join();
    }
}