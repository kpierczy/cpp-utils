/* ============================================================================================================================ *//**
 * @file     composite_with_unconditional_exit_from_sub_sm.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Extension of the 'composite.cpp' example showing automatic transition of the upper machine when the composed (sub-) state
 *    machine reaches final state
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
    struct e4 {};
    struct e5 {};

    // State submachine
    struct sub {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                *"idle"_s + event<e3> / [] { std::cout << "- in sub sm"     << std::endl; } = "s1"_s
                , "s1"_s  + event<e4> / [] { std::cout << "- finish sub sm" << std::endl; } = X
            );
        }
    };

    // State machine
    struct composite {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                // On-the-fly-instantiated states
                *"idle"_s    + event<e1> / [] { std::cout << "- in upper sm"  << std::endl; } = "s1"_s
                , "s1"_s     + event<e2> / [] { std::cout << "- enter sub sm" << std::endl; } = state<sub>
                // Composite state
                , state<sub>             / [] { std::cout << "- exit sub sm"  << std::endl; } = X
            );
        }
    };
}  

int main() {

    using namespace sml;

    // State machine
    sml::sm<composite> sm;

    /* ------------- Transitions inside 'upper' machine ------------- */

    // Default 'is' method's specialization inspects 'sm' itself
    assert(sm.is("idle"_s));
    // Specialization with the state type drivern from submachine inspects state of the submachine
    assert(sm.is<decltype(state<sub>)>("idle"_s));

    std::cout << "Processing e1"  << std::endl;
    sm.process_event(e1{});
    assert(sm.is("s1"_s));
    assert(sm.is<decltype(state<sub>)>("idle"_s));

    // Enters submachine ()
    std::cout << "Processing e2"  << std::endl;
    sm.process_event(e2{});
    assert(sm.is(state<sub>));
    assert(sm.is<decltype(state<sub>)>("idle"_s));

    /* ------------- Transitions inside 'lower' machine ------------- */
    
    // Processes first transition in the submachine
    std::cout << "Processing e3"  << std::endl;
    sm.process_event(e3{});
    assert(sm.is(state<sub>));
    assert(sm.is<decltype(state<sub>)>("s1"_s));

    // Finish sub sm. Finished state of the machine will trigger unconditional transition in the upper sm
    std::cout << "Processing e4"  << std::endl;
    sm.process_event(e4{});
    assert(sm.is(X));
    assert(sm.is<decltype(state<sub>)>(X));

}