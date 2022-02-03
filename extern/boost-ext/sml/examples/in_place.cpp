/** ==================================================================================================================================
 * @file     in_place.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Thursday, 23rd December 2021 3:47:33 pm
 * @brief 
 * 
 *    Example showing usage in-place defined SM (this example requires C++20 deduction guide and so needs to be compiled with
 *    -std=c++2a flag)
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>
#if defined(__cpp_deduction_guides)

int main() {
    
    namespace sml = boost::sml;

    // Example event
    struct start {};

    // In-place state machine
    sml::front::sm sm = [] {
        using namespace sml;
        return make_transition_table(
            *"idle"_s + event<start> / [] { std::cout << "action\n"; } = X
        );
    };

    // Processing of the state machine
    sm.process_event(start{});
    
    assert(sm.is(sml::X));
}

#else
int main() { std::cout << "In-place SM requires _cpp_deduction_guides to be defined" << "\n"; }
#endif
