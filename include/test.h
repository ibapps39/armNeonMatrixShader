#pragma once
template<typename Func, typename... Args>
auto timeFunction(Func&& f, Args&&... args) {
    auto begin = std::chrono::steady_clock::now();
    if constexpr (std::is_void_v<decltype(f(args...))>) {
        f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        return (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;
    } else {
        auto result = f(std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        return std::make_pair(result, (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0);
    }
}