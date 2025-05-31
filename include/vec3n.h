#pragma once
#include <arm_neon.h>
#include <cmath>
#include <cstdio>

class vec3n {
public:
    float32x4_t x;
    float32x4_t y;
    float32x4_t z;

    vec3n() = default;

    vec3n(float32x4_t vx, float32x4_t vy, float32x4_t vz) : x(vx), y(vy), z(vz) {}

    // Load 4 vec3s from array
    static vec3n load(const float* data) {
        // Layout: x0 y0 z0  | x1 y1 z1  | ...
        float32x4_t vx, vy, vz;
        float tmpx[4], tmpy[4], tmpz[4];
        for (int i = 0; i < 4; ++i) {
            tmpx[i] = data[i*3 + 0];
            tmpy[i] = data[i*3 + 1];
            tmpz[i] = data[i*3 + 2];
        }
        vx = vld1q_f32(tmpx);
        vy = vld1q_f32(tmpy);
        vz = vld1q_f32(tmpz);
        return vec3n(vx, vy, vz);
    }

    // Store back to array
    void store(float* out) const {
        float tmpx[4], tmpy[4], tmpz[4];
        vst1q_f32(tmpx, x);
        vst1q_f32(tmpy, y);
        vst1q_f32(tmpz, z);
        for (int i = 0; i < 4; ++i) {
            out[i*3 + 0] = tmpx[i];
            out[i*3 + 1] = tmpy[i];
            out[i*3 + 2] = tmpz[i];
        }
    }

    // Addition
    vec3n operator+(const vec3n& other) const {
        return vec3n(
            vaddq_f32(x, other.x),
            vaddq_f32(y, other.y),
            vaddq_f32(z, other.z)
        );
    }

    // Subtraction
    vec3n operator-(const vec3n& other) const {
        return vec3n(
            vsubq_f32(x, other.x),
            vsubq_f32(y, other.y),
            vsubq_f32(z, other.z)
        );
    }

    // Element-wise multiplication
    vec3n operator*(const vec3n& other) const {
        return vec3n(
            vmulq_f32(x, other.x),
            vmulq_f32(y, other.y),
            vmulq_f32(z, other.z)
        );
    }

    // Scalar multiplication
    vec3n operator*(float scalar) const {
        float32x4_t s = vdupq_n_f32(scalar);
        return vec3n(
            vmulq_f32(x, s),
            vmulq_f32(y, s),
            vmulq_f32(z, s)
        );
    }

    // Length squared
    float32x4_t len_sqf() const {
        return vaddq_f32(
            vaddq_f32(vmulq_f32(x, x), vmulq_f32(y, y)),
            vmulq_f32(z, z)
        );
    }

    // Length (slow)
    float32x4_t len() const {
        return vsqrtq_f32(len_sqf());
    }

    void debug_print(const char* label = "") const {
        float out[12];
        store(out);
        printf("%s:\n", label);
        for (int i = 0; i < 4; ++i)
            printf("  [%f %f %f]\n", out[i*3], out[i*3+1], out[i*3+2]);
    }
};