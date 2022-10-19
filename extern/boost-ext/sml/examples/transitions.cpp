/* ============================================================================================================================ *//**
 * @file     transitions.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing way of functioning of various transition possible between states
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

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
    struct transitions {
        auto operator()() const noexcept {
            using namespace sml;
            
            // Transition table
            return make_transition_table(
                // Default state with unconditional transition
                *"idle"_s                    / [] { std::cout << "anonymous transition" << std::endl; } = "s1"_s
                // State with internal transition and action
                ,"s1"_s   + event<e1>        / [] { std::cout << "internal transition" << std::endl;  }
                // State with self transition and action
                ,"s1"_s   + event<e2>        / [] { std::cout << "self transition" << std::endl;      } = "s1"_s
                // State with external transition and 'on-entry'/'on-exit' behaviours
                ,"s1"_s   + sml::on_entry<_> / [] { std::cout << "s1 entry" << std::endl;             }
                ,"s1"_s   + sml::on_exit<_>  / [] { std::cout << "s1 exit" << std::endl;              }
                ,"s1"_s   + event<e3>        / [] { std::cout << "external transition" << std::endl;  }  = X
            );
        }
    };
}

int main() {

    // State machine without context
    sml::sm<transitions> sm;
    // Events loop
    sm.process_event(e1{});
    sm.process_event(e2{});
    sm.process_event(e3{});
    
    assert(sm.is(sml::X));
}