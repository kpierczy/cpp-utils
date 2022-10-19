/* ============================================================================================================================ *//**
 * @file     events.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Examples showing various ways of creating and utilizing events
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>

namespace sml = boost::sml;

namespace {

    // Event 1
    struct e1 {};
    // Event 2
    struct e2 { bool value = true; };
    auto event2 = sml::event<e2>;
    // Event 3 (created on the fly with UDL)
    // Event 4
    struct e4 { int value = 0; };

    // State machine
    struct events {
        auto operator()() const noexcept {
            using namespace sml;

            // Custom guard
            auto guard = [](const e2& e) { return e.value; };

            // Transition table
            return make_transition_table(
                // Event instance created on the fly
                * "idle"_s + event<e1>                                                       = "s1"_s,
                // Predefined event instance with guard condition
                "s1"_s     + event2 [guard]                                                  = "s2"_s,
                // Event type and instance created on the fly
                "s2"_s     + "e3"_e                                                          = "s3"_s,
                // Event instance created on the fly, additional action
                "s3"_s     + event<e4>       / [] (const auto& e) { assert(42 == e.value); } = X
            );
        }
    };

}

int main() {

    using namespace sml;

    // State machine without a context
    sml::sm<events> sm;

    // Events loop
    sm.process_event(e1{});
    sm.process_event(e2{});
    sm.process_event("e3"_e());
    sm.process_event(e4{42});
    
    assert(sm.is(X));
}
