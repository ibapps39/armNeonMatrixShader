#pragma once
#include <thread>
#include <vector>
#include <memory>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
#include <stdlib.h>



inline std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;

    // Open a pipe to the command
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output into the result string
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result;
}