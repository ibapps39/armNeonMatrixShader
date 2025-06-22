# Results
```zsh
MAX THREADS per sysctl -n hw.ncpu: maxt = 8
MAX THREADS per std::thread::hardware_concurrency() = 8

N = 1000000

POPULATING A, B USING THREADS
Time to populate A with 1000000 elements: 0.010403s
Time to populate B with 1000000 elements: 0.010283s

ADD FLOAT C:
TIME: timeFunction(add_float_c, A, B, C): 0.000847s
Correct: 1000000/1000000

Time for neon_add (void) with 1000000 elements: 0.000733s
Correct: 1000000/1000000

Time for neon_add (returns std::vector<vec3>) with 1000000 elements: 0.002150s
Correct: 1000000/1000000

Time for neon_threads (void) with 1000000 elements: 0.000837s
Correct: 1000000/1000000
```