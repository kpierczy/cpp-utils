/* ============================================================================================================================ *//**
 * @file       test.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 28th December 2022 10:17:27 pm
 * @modified   Wednesday, 28th December 2022 11:56:17 pm
 * @project    cpp-utils
 * @brief      
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

/* =========================================================== Includes =========================================================== */

#include <iostream>
#include <vector>
#include "sstl/vector.h"

/* ============================================================= Main ============================================================= */

int main() {

    std::cout << "Hello SSTL World!" << std::endl;
    
    auto print_array = [](const auto &array, auto name) {
        std::cout << " - " << name << " array: [ ";
        for(auto elem : array) { std::cout << elem << " "; }
        std::cout << "] (at " << array.data() << ")" << std::endl;
    };

    sstl::vector<int, 4> static_vector  { 1, 2, 3, 4 };
    std::vector<int>     dynamic_vector { 1, 2, 3, 4 };

    print_array(static_vector,  "static ");
    print_array(dynamic_vector, "dynamic");
}

/* ================================================================================================================================ */