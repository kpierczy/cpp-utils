/** ==================================================================================================================================
 * @file     states.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Wednesday, 22nd December 2021 5:47:51 pm
 * @brief 
 * 
 *    Example showing various ways of creating and utilizing states
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>

namespace sml = boost::sml;

namespace {
  
    // Events
    struct e1 {};
    struct e2 {};
    struct e3 {};

    // State machine
    struct states {
        auto operator()() const noexcept {
            using namespace sml;

            // Sate instance
            const auto idle = state<class idle>;

            // Transition table
            return make_transition_table(
                // Initial state
                *idle           + event<e1>                                                            = "s1"_s,
                // On-the-fly-defined state with 'on-entry' and 'on-exit' behaviours
                "s1"_s          + sml::on_entry<_> / [] { std::cout << "s1 on entry" << std::endl; },  
                "s1"_s          + sml::on_exit<_>  / [] { std::cout << "s1 on exit" << std::endl; },   
                "s1"_s          + event<e2>                                                            = state<class s2>,
                // Second to last state
                state<class s2> + event<e3>                                                            = X
            );
        }
    };
} 

int main() {

    // Context-less state machine
    sml::sm<states> sm;
    // Events loop
    sm.process_event(e1{});
    sm.process_event(e2{});
    sm.process_event(e3{});
    
    assert(sm.is(sml::X));
}