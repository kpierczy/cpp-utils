/* ============================================================================================================================ *//**
 * @file     error_watcher.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>
#include <queue>
#include <iostream>

namespace sml = boost::sml;

namespace {
  
    // Events
    struct tick {};
    struct error {};
    struct finished {};

    
    static bool err = false;
    auto is_error = []() -> bool { return err; };
    
    static int counter = 0;
    auto tguard = []() -> bool {return counter >= 3; };
    auto update = []() -> void { 
        ++counter; 
        std::cout << "Counter: " << counter << std::endl; 
        if(counter == 4) 
            err = true; 
    };

    // State submachine
    struct submachine {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                // Driver
                *"acc"_s + event<tick> [!tguard] / update
              ,  "acc"_s + event<tick> [ tguard] / ([]() { std::cout << "Finishing driver..." << std::endl; }, process(finished{})) = X
                // Watcher
              , *"watcher"_s + event<tick> [is_error] / ([]() { std::cout << "Finishing watcher..." << std::endl; }, process(error{})) = X
            );
        }
    };

    // State machine
    struct states {
        auto operator()() const noexcept {
            using namespace sml;
            auto sub = state<submachine>;
            return make_transition_table(
              * "start"_s                                                               = sub
              , sub + event<error>    / []() { std::cout << "Error!"    << std::endl; } = "err"_s
              , sub + event<finished> / []() { std::cout << "Ending..." << std::endl; } = X
            );
        }
    };
} 

int main() {

    // Context-less state machine
    sml::sm<states, sml::defer_queue<std::deque>, sml::process_queue<std::queue>> sm;
    // Events loop
    sm.process_event(tick{});
    sm.process_event(tick{});
    sm.process_event(tick{});
    sm.process_event(tick{});
    sm.process_event(tick{});
    
}