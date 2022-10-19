/* ============================================================================================================================ *//**
 * @file     orthogonal_regions.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing usage of orthogonal regions
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

    // State machgine
    struct orthogonal_regions {
    auto operator()() const noexcept {
        using namespace sml;
        // Transition table
        return make_transition_table(

            /* --------- First region --------- */

            *"idle"_s + event<e1> = "s1"_s
            , "s1"_s  + event<e2> = X

            /* -------- Second region --------- */

            ,*"idle2"_s + event<e2> = "s2"_s
            , "s2"_s    + event<e3> = X
        );
    }
    };
}

int main() {

    // Context-less state machine
    sml::sm<orthogonal_regions> sm;
    using namespace sml;
    
    // State machine in combination of two states at the same time
    assert(sm.is("idle"_s, "idle2"_s));
    // Only the first region is influenced by the 'e1' event
    sm.process_event(e1{});
    assert(sm.is("s1"_s, "idle2"_s));
    // Both region are influenced by the 'e2' event
    sm.process_event(e2{});
    assert(sm.is(X, "s2"_s));
    // Only the second region is influenced by the 'e4' event
    sm.process_event(e3{});
    assert(sm.is(X, X));
}