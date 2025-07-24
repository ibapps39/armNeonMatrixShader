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
# Results so far...
```zsh
//START//START////START////START////START////START////START//
MAX THREADS per sysctl -n hw.ncpu: maxt = 8
MAX THREADS per std::thread::hardware_concurrency() = 8

N = 1000000

POPULATING A, B USING THREADS
Time to populate A with 1000000 elements: 0.006001s
Time to populate B with 1000000 elements: 0.005831s

ADD FLOAT C:
TIME: timeFunction(add_float_c, A, B, C): 0.001593s
Correct: 1000000/1000000

Time for neon_add (void), non-threaded+stack+neon, with 1000000 elements: 0.000848s
Correct: 1000000/1000000

Time for neon_add (returns std::vector<vec3>) with 1000000 elements: 0.001961s
Correct: 1000000/1000000

Time for neon_threads operation with '+' switch (void), threaded, with 1000000 elements: 0.000891s
Correct: 1000000/1000000

Time for neon_add, threaded, with 1000000 elements: 0.000900s
Correct: 1000000/1000000

Time for neon_sub (subtraction), non-threaded, with 1000000 elements: 0.000853s
Correct: 1000000/1000000

Time for neon_sub (subtraction), threaded, with 1000000 elements: 0.000863s
Correct: 1000000/1000000

Time for neon_dot, threaded, with 1000000 elements: 0.000931s
Correct: 1000000/1000000

Time for neon_divide, non-threaded, with 1000000 elements: 0.001178s
Correct: 1000000/1000000

Time for neon_divide, threaded, with 1000000 elements: 0.000898s
Correct: 1000000/1000000

Time for neon_cross (void), non-threaded, with 1000000 elements: 0.000868s
Correct: 1000000/1000000

Time for neon_cross (void), threaded, with 1000000 elements: 0.000906s
Correct: 1000000/1000000

Time for arm_asm_add (void), with 1000000 elements: 0.001043s
Correct: 1000000/1000000

Time for for loop of 'C[i] = A[i]+B[i]' with 1000000 elements: 0.001422s
Correct: 1000000/1000000

Time for to create, populate, and add 1000 vectors of 1M vec3s, threaded_pop+linear+neon_add: 14.975543s
Time for to create, populate, and add 1000 vectors of 1M vec3s, threaded: 15.492284s
Time for to create, populate, and add 1000 vectors of 1M vec3s, linear: 46.048497s
Time adding 1000 vectors of 1M vec3s with neon_add 154.972602s
Time adding 1000 vectors of 1M vec3s with add_float_c 191.205802s
Time thread_neon(neon_add, vec_of_vec_of_vec3[i], vec_of_vec_of_vec3_threaded[i], vec_of_vec_of_vec3_linear[i]); 83.112341s

//END////END////END////END////END////END////END//
```