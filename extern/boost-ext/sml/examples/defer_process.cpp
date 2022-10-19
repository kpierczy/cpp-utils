/* ============================================================================================================================ *//**
 * @file     defer_process.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing way to deffer transition of the state machine between 'process_event()' calls and trigger events from
 *    actions associated with transitions
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>
#include <deque>
#include <queue>

namespace sml = boost::sml;

namespace {

    // Events
    struct e1 {};
    struct e2 {};
    struct e3 {};
    struct e4 {};

    // State machine
    struct defer_and_process {
        // Trnasition table maker
        auto operator()() const noexcept {
            using namespace sml;

            // Trnasition table 
            return make_transition_table(
                *"idle"_s  + event<e1> / sml::defer
                , "idle"_s + event<e2>                      = "s1"_s
                , "s1"_s   + event<e1>                      = "s2"_s
                , "s2"_s   + event<e3> / sml::process(e4{})
                , "s2"_s   + event<e4>                      = X
            );
        }
    };
}

int main() {

    using namespace sml;
    
    // State machine (defer_queue policy to enable deferred events using std::queue)
    sm<defer_and_process, sml::defer_queue<std::deque>, sml::process_queue<std::queue>> sm;

    // Initial state
    assert(sm.is("idle"_s));
    // 'e1' event does not result in transition as it is deferred to the later execution
    sm.process_event(e1{});
    assert(sm.is("idle"_s));
    // On the next event, deferred transition is executed (triggers idle -> s1 and s1 -> s2)
    sm.process_event(e2{});
    assert(sm.is("s2"_s));
    // Transition triggerred by 'e3' result in action generating 'e4' event that is automatically processed by the call (triggers s2.process(e4) -> X (via processed e4))
    sm.process_event(e3{});
    assert(sm.is(sml::X));
}