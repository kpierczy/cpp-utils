/* ============================================================================================================================ *//**
 * @file       test.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 28th December 2022 10:17:27 pm
 * @modified   Wednesday, 1st March 2023 3:44:40 am
 * @project    cpp-utils
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

/* =========================================================== Includes =========================================================== */

#include <iostream>
#include <iomanip>
#include "utils/numeric/solvers.hpp"

/* ============================================================= Main ============================================================= */

int main() {
    
    auto result_1 = numeric::solvers::quadratic(1.0,  -4.0,   2.0);
    auto result_2 = numeric::solvers::quadratic(2.0, -15.0,  20.0);
    auto result_3 = numeric::solvers::quadratic(3.0,   1.0, - 8.0);

    std::cout << "Hello world from quadratic solver!"                                                                    << std::endl
        << " -  x^2 -  4x + 2  => (" << std::setw(8) << result_1.first << ", " << std::setw(7) << result_1.second << ")" << std::endl
        << " - 2x^2 - 15x + 20 => (" << std::setw(8) << result_2.first << ", " << std::setw(7) << result_2.second << ")" << std::endl
        << " - 3x^2 +   x - 8  => (" << std::setw(8) << result_3.first << ", " << std::setw(7) << result_3.second << ")" << std::endl;
}

/* ================================================================================================================================ */