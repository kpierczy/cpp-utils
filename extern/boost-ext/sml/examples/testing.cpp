/* ============================================================================================================================ *//**
 * @file     testing.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing testing facilities of the SML library
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>

namespace sml = boost::sml;

namespace {

    // Events
    struct e1 {};
    struct e2 {};
    struct e3 {};

    // Data type injected into guard/event routines 
    struct data { int value = 0; };

    // State machine
    struct testing {
        auto operator()() const noexcept {
            using namespace sml;

            // Guard functor taking injdected additional data as a parameter
            const auto guard = [](data& d) { return !d.value; };
            // Action functor taking injdected additional data as a parameter
            const auto action = [](data& d) { d.value = 42; };

            // Transition table
            return make_transition_table(
                *"idle"_s + event<e1>                  = "s1"_s
                ,  "s1"_s + event<e2>                  = "s2"_s
                // Transition under test
                ,  "s2"_s + event<e3> [guard] / action = X 
            );
        }
    };

}

int main() {
    using namespace sml;

    // Data injected into the SM
    data fake_data{0};

    // State machine with injected data
    sml::sm<::testing, sml::testing> sm{fake_data};

    // Set current state for debug purposes
    sm.set_current_states("s2"_s);
    // Process some event
    sm.process_event(e3{});

    assert(sm.is(X));
    assert(fake_data.value == 42);
}