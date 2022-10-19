/* ============================================================================================================================ *//**
 * @file     dependencies.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing data injection into the statemachine's guards and actions
 * 
 * @todo fixme 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>
#include <queue>

namespace sml = boost::sml;

namespace {

    // Events        
    struct e1 { int i = 0; };
    // Dependent data        
    struct dependency { int i = 0;};

    // State machine
    struct dependencies {
        auto operator()() const noexcept {
            using namespace sml;

            // Guard with dependency (more dependencies might be passed [?])
            const auto guard = [](const dependency& d) { return !d.i; };

            // Guard with dependency (event is deduced, order of arguments is not important [?])
            const auto action = [](dependency& d, const auto& event) { d.i = event.i + 42; };

            // Transition table
            return make_transition_table(
                *"idle"_s + event<e1> [ guard                                                                   ] / action = "s1"_s
                ,  "s1"_s + event<e1> [ ([](const auto& event, const dependency& d) { return d.i == event.i; }) ]          = X
            );
        }
    };
}  

int main() {

    using namespace sml;

    /**
     * @brief State machine with dependencies injected pass all dependencies (from guards, actions) via
     *    constructor (order is not important)
     */
    dependency d;
    sm<dependencies> sm{d};
    
    assert(sm.is("idle"_s));

    /// Action sets dependency.i to 42
    sm.process_event(e1{0});
    assert(sm.is("s1"_s));

    /// Guard not satisfied, dependency.i(42) != event.i(0)
    sm.process_event(e1{0});
    assert(sm.is("s1"_s));  

    /// Transition to X
    sm.process_event(e1{42});
    assert(sm.is(X));
}
