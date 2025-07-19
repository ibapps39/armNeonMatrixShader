#pragma once
#include <iomanip>
template <typename Func, typename... Args>
auto timeFunction(Func &&f, Args &&...args)
{
    auto begin = std::chrono::steady_clock::now();
    if constexpr (std::is_void_v<decltype(f(args...))>)
    {
        f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        return (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;
    }
    else
    {
        auto result = f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        return std::make_pair(result, (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0);
    }
}
void error_sum(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t i)
{
    std::cout << "Incorrect: C[" << i << "]:" << "[" << C[i] << "]" << std::endl;
    std::cout << "\t A[" << i << "]:" << A[i] << std::endl;
    std::cout << "\t B[" << i << "]:" << B[i] << std::endl;
    std::cout << "\t C[" << i << "] should be:[" << A[i].x() + B[i].x() << ", " << (A[i].y() + B[i].y()) << ", "
              << (A[i].z() + B[i].z()) << "]"
              << std::endl;
}
void validate_sum(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    size_t i = 0;
    for (; i < N; ++i)
    {
        correct += (C[i].x() == (A[i].x() + B[i].x()) &&
                    C[i].y() == (A[i].y() + B[i].y()) &&
                    C[i].z() == (A[i].z() + B[i].z()));
    }
    if (correct < i) { 
        error_sum(A, B, C, i); 
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}
void error_diff(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t i)
{
    std::cout << "Incorrect: C[" << i << "]:" << "[" << C[i] << "]" << std::endl;
    std::cout << "\t A[" << i << "]:" << A[i] << std::endl;
    std::cout << "\t B[" << i << "]:" << B[i] << std::endl;
    std::cout << "\t C[" << i << "] should be:[" << A[i].x() - B[i].x() << ", " << (A[i].y() - B[i].y()) << ", "
              << (A[i].z() - B[i].z()) << "]"
              << std::endl;
}
void validate_diff(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    size_t i = 0;
    for (; i < N; ++i)
    {
        correct += (C[i].x() == (A[i].x() - B[i].x()) &&
                    C[i].y() == (A[i].y() - B[i].y()) &&
                    C[i].z() == (A[i].z() - B[i].z()));
    }
    if (correct < i) { 
        error_sum(A, B, C, i); 
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}
void error_dot(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t i)
{
    std::cout << "Incorrect: C[" << i << "]:" << "[" << C[i] << "]" << std::endl;
    std::cout << "\t A[" << i << "]:" << A[i] << std::endl;
    std::cout << "\t B[" << i << "]:" << B[i] << std::endl;
    std::cout << "\t C[" << i << "] should be:[" << A[i].x() * B[i].x() << ", " << (A[i].y() * B[i].y()) << ", "
              << (A[i].z() * B[i].z()) << "]"
              << std::endl;
}
void validate_dot(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    size_t i = 0;
    for (; i < N; ++i)
    {
        correct += (C[i].x() == (A[i].x() * B[i].x()) &&
                    C[i].y() == (A[i].y() * B[i].y()) &&
                    C[i].z() == (A[i].z() * B[i].z()));
    }
    if (correct < i) { 
        error_dot(A, B, C, i); 
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}

void error_div(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t i)
{
    std::cout << "Incorrect: C[" << i << "]:" << "[" << C[i] << "]" << std::endl;
    std::cout << "\t A[" << i << "]:" << A[i] << std::endl;
    std::cout << "\t B[" << i << "]:" << B[i] << std::endl;
    std::cout << "\t C[" << i << "] should be:[" << A[i].x() / B[i].x() << ", " << (A[i].y() / B[i].y()) << ", "
              << (A[i].z() / B[i].z()) << "]"
              << std::endl;
}
void validate_div(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    size_t i = 0;
    for (; i < N; ++i)
    {
        correct += (C[i].x() == (A[i].x() / B[i].x()) &&
                    C[i].y() == (A[i].y() / B[i].y()) &&
                    C[i].z() == (A[i].z() / B[i].z()));
    }
    if (correct < i) { 
        error_dot(A, B, C, i); 
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}

void error_cross(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t i)
{

    // A[i].y() * B[i].z() - A[i].z() * B[i].y(),
    // A[i].z() * B[i].x() - A[i].x() * B[i].z(),
    // A[i].x() * B[i].y() - A[i].y() * B[i].x()

    std::cout << "Incorrect at C" << i << " -" << std::endl;
    std::printf("\t A%i[%.7f, %.7f, %.7f]\n", i, A[i].x(), A[i].y(), A[i].z());
    std::printf("\t B%i[%.7f, %.7f, %.7f]\n", i, B[i].x(), B[i].y(), B[i].z());
    std::printf("\t C%i[%.7f, %.7f, %.7f]\n", i, C[i].x(), C[i].y(), C[i].z());
    std::cout << std::fixed << std::setprecision(7) << "should be: [" << 
    ((A[i].y() * B[i].z()) - A[i].z() * B[i].y()) 
    << ", " << 
    A[i].z() * B[i].x() - A[i].x() * B[i].z() 
    << ", " << 
    (A[i].x() * B[i].y() - A[i].y() * B[i].x()) 
    << "]"
    << std::endl;
}
void validate_cross(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    auto first_error_index = 0;
    size_t i = 0;

    for (; i < N; ++i)
    {
        bool is_correct = ( 
            std::abs(C[i].x() - ( (A[i].y() * B[i].z()) - (A[i].z() * B[i].y()) ) ) <= 0.0009765625f // magic number I know
            && 
            std::abs(C[i].y() - ( (A[i].z() * B[i].x()) - (A[i].x() * B[i].z()) ) ) <= 0.0009765625f
            &&
            std::abs(C[i].z() - ( (A[i].x() * B[i].y()) - (A[i].y() * B[i].x()) ) ) <= 0.0009765625f
        );
        
        if (is_correct) {
            correct++;
        } else {
            // The first error is found, record its index
            first_error_index = i;
            std::cout << "Error at: " << first_error_index << std::endl;
            error_cross(A, B, C, first_error_index);
        }
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}

void validate_cross_epsilon(std::vector<vec3> &A, std::vector<vec3> &B, std::vector<vec3> &C, size_t N)
{
    size_t correct = 0;
    auto first_error_index = -1;
    float original_epsilon = 0.0006f;
    static float epsilon = original_epsilon;
    static float dec_amt = 0.0005000*.1;
    static float decs = 0;
    size_t i = 0;

    for (; i < N; ++i)
    {
        bool is_correct = ( 
            fabsf(C[i].x() - ( (A[i].y() * B[i].z()) - (A[i].z() * B[i].y()) ) ) <= epsilon // magic number I know
            && 
            fabsf(C[i].y() - ( (A[i].z() * B[i].x()) - (A[i].x() * B[i].z()) ) ) <= epsilon
            &&
            fabsf(C[i].z() - ( (A[i].x() * B[i].y()) - (A[i].y() * B[i].x()) ) ) <= epsilon
        );
        
        if (is_correct) {
            correct++;
            epsilon = epsilon+dec_amt;
            dec_amt = dec_amt/2.0f;
            decs++;
        } else {
            // The first error is found, record its index
            first_error_index = i;
            std::cout << "First error at: " << first_error_index << std::endl;
            error_cross(A, B, C, first_error_index);
            std::printf("Original Epsilon = %.7f\n", original_epsilon);
            std::printf("Epsilon = %.7f\n", epsilon);
            std::printf("Decrements = %.f\n", decs);
            std::printf("Dec_amt = %.32f\n", dec_amt);
            return;
        }
    }
    std::cout << "Correct: " << correct << "/" << N << std::endl;
}

// AI CODE

// Helper function to test if all cross products are within epsilon
bool test_all_with_epsilon(const std::vector<vec3>& A, const std::vector<vec3>& B, const std::vector<vec3>& C, size_t N, float epsilon) {
for (size_t i = 0; i < N; ++i) {
bool is_correct = (
fabsf(C[i].x() - ((A[i].y() * B[i].z()) - (A[i].z() * B[i].y()))) <= epsilon &&
fabsf(C[i].y() - ((A[i].z() * B[i].x()) - (A[i].x() * B[i].z()))) <= epsilon &&
fabsf(C[i].z() - ((A[i].x() * B[i].y()) - (A[i].y() * B[i].x()))) <= epsilon
);
    if (!is_correct) {
        return false;
    }
}
return true;
}

// Method 1: Binary search for the smallest epsilon
float find_smallest_epsilon_binary(const std::vector<vec3>& A, const std::vector<vec3>& B, const std::vector<vec3>& C, size_t N) {
float low = 0.0f;
float high = 0.01f; // Start with a reasonable upper bound
float epsilon = high;
const float precision = 1e-8f; // Desired precision

// First, find an upper bound that works
while (!test_all_with_epsilon(A, B, C, N, high)) {
    high *= 2.0f;
}

// Binary search for the smallest working epsilon
while (high - low > precision) {
    float mid = (low + high) / 2.0f;
    
    if (test_all_with_epsilon(A, B, C, N, mid)) {
        epsilon = mid;
        high = mid; // mid works, try smaller
    } else {
        low = mid;  // mid doesn't work, need larger
    }
}
return epsilon;
}

// Method 2: Incremental search with proper backtracking
float find_smallest_epsilon_incremental(const std::vector<vec3>& A, const std::vector<vec3>& B, const std::vector<vec3>& C, size_t N) {
float epsilon = 0.00001f; // Start very small
float increment = 0.00001f;


while (increment > 1e-8f) {
    if (test_all_with_epsilon(A, B, C, N, epsilon)) {
        // Current epsilon works, try smaller increment to refine
        increment /= 2.0f;
        epsilon -= increment; // Try going back
        if (epsilon < 0) epsilon = increment;
    } else {
        // Current epsilon doesn't work, increase it
        epsilon += increment;
    }
}

// Final verification - make sure our epsilon actually works
while (!test_all_with_epsilon(A, B, C, N, epsilon)) {
    epsilon += 1e-8f;
}
return epsilon;
}

// Method 3: Calculate exact epsilon needed for the specific failing case
float calculate_needed_epsilon_for_case(const std::vector<vec3>& A, const std::vector<vec3>& B, const std::vector<vec3>& C, size_t index) {
float expected_x = (A[index].y() * B[index].z()) - (A[index].z() * B[index].y());
float expected_y = (A[index].z() * B[index].x()) - (A[index].x() * B[index].z());
float expected_z = (A[index].x() * B[index].y()) - (A[index].y() * B[index].x());

float error_x = fabsf(C[index].x() - expected_x);
float error_y = fabsf(C[index].y() - expected_y);
float error_z = fabsf(C[index].z() - expected_z);

return fmaxf(fmaxf(error_x, error_y), error_z);
}

// Your corrected main function
void find_smallest_epsilon_corrected(const std::vector<vec3>& A, const std::vector<vec3>& B, const std::vector<vec3>& C, size_t N) {
// Method 1: Use binary search (recommended)
float optimal_epsilon = find_smallest_epsilon_binary(A, B, C, N);
std::printf("Smallest working epsilon (binary search): %.10f\n", optimal_epsilon);


// Method 3: Check all cases and find the maximum error
float max_epsilon_needed = 0.0f;
int worst_case_index = -1;

for (size_t i = 0; i < N; ++i) {
    float case_epsilon = calculate_needed_epsilon_for_case(A, B, C, i);
    if (case_epsilon > max_epsilon_needed) {
        max_epsilon_needed = case_epsilon;
        worst_case_index = i;
    }
}

std::printf("Maximum epsilon needed: %.10f (worst case at index %d)\n", 
            max_epsilon_needed, worst_case_index);

}