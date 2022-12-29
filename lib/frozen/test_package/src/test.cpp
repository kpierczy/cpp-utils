/* ============================================================================================================================ *//**
 * @file       test.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 28th December 2022 10:17:27 pm
 * @modified   Thursday, 29th December 2022 12:41:00 am
 * @project    cpp-utils
 * @brief      
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

/* =========================================================== Includes =========================================================== */

#include <iostream>
#include "frozen/map.h"

/* ============================================================= Main ============================================================= */

int main() {

    std::cout << "Hello Frozen World!" << std::endl;
    
    constexpr frozen::map<char, int, 3> map{
        {'F', 0},
        {'S', 1},
        {'T', 2},
    };

    std::cout
        << " - " << map.at('F') << std::endl
        << " - " << map.at('S') << std::endl
        << " - " << map.at('T') << std::endl;

}

/* ================================================================================================================================ */