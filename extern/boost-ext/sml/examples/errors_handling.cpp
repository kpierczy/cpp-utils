/* ============================================================================================================================ *//**
 * @file     error_handling.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Examples showing ways to handle errors (unexpected events and exceptions)
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace sml = boost::sml;

namespace {
    
    // Events
    struct some_event {};

    // State machine
    struct error_handling {
        auto operator()() const {
            using namespace sml;
            // Transition table
            return make_transition_table(

                /* --------------------------------------------------------- First region --------------------------------------------------------- */

                    // Event 'event1' trigger specific exception
                    *("idle"_s) + "event1"_e / [] { throw std::runtime_error{"error"}; }
                    // Event 'event2' trigger generic exception
                ,     "idle"_s  + "event2"_e / [] { throw 0;                           }

                /* --------------------------------------------------------- Second region -------------------------------------------------------- */

                // Specific exceptions are handled by the second region in a specialized way
                , *("exceptions handling"_s) + exception<std::runtime_error> / [] { std::cout << "- specific exception caught" << std::endl; }
                // Generic exceptions are handled by the second region in a common way
                ,   "exceptions handling"_s  + exception<_>                  / [] { std::cout << "- generic exception caught"  << std::endl; } = X

                /* --------------------------------------------------------- Third region --------------------------------------------------------- */

                // Specific unknown events are handled by the thirs region in a specialized way
                , *("unexpected events handling"_s) + unexpected_event<some_event> / [] { std::cout << "- unexpected event 'some_event'" << std::endl; }
                // Generic unknown events are handled by the thirs region in a common way
                ,   "unexpected events handling"_s  + unexpected_event<_>          / [] { std::cout << "- generic unexpected event"      << std::endl; } = X

            );
        }
    };
}

int main() {

    using namespace sml;

    // State machine
    sm<error_handling> sm;

    // Handle specific exception
    std::cout << "Processing 'event1'" << std::endl;
    sm.process_event("event1"_e());
    assert(sm.is("idle"_s, "exceptions handling"_s, "unexpected events handling"_s));

    // Handle generic exception
    std::cout << "Processing 'event2'" << std::endl;
    sm.process_event("event2"_e());
    assert(sm.is("idle"_s, X, "unexpected events handling"_s));

    // Handle specific unknown event
    std::cout << "Processing specific unknown event" << std::endl;
    sm.process_event(some_event{});
    assert(sm.is("idle"_s, X, "unexpected events handling"_s));

    // Handle generic unknown event
    std::cout << "Processing generic unknown event" << std::endl;
    sm.process_event(int{});
    assert(sm.is("idle"_s, X, X));
}