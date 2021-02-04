//Constexpr can be execute during compile time, so in run time we have only the results
//when running in debug mode you can see results like
// constexpr factorial time: 7 microseconds
// factorial time: 58690 microseconds

#include <array>
#include <string_view>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <map>
#include <cassert>
#include <windows.h>

const int ITERATIONS = 100;

//constexpr fib function
constexpr int fib(int n)
{
    return (n <= 1) ? n : fib(n - 1) + fib(n - 2);
}

int main()
{
    auto factorialStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        //in run time we have only the return value
        constexpr int f = fib(20);
    }
    auto factorialEnd = std::chrono::high_resolution_clock::now();
    std::cout << "constexpr factorial time: " << std::chrono::duration_cast<std::chrono::microseconds>(factorialEnd - factorialStart).count() << " microseconds" << '\n';

    factorialStart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        //the return value is not const
        //the fib function will need to execute
        auto f = fib(20);
        //static_assert(fib(10)); //one way to check if the function can be evoluted during compile time
    }
    factorialEnd = std::chrono::high_resolution_clock::now();
    std::cout << "factorial time: " << std::chrono::duration_cast<std::chrono::microseconds>(factorialEnd - factorialStart).count() << " microseconds" << '\n';

    return 0;
}
