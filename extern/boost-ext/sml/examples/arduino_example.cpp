/** ==================================================================================================================================
 * @file     arduino_example.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Thursday, 23rd December 2021 7:29:03 pm
 * @brief 
 * 
 *    Example showing usage of the SML in Arduino environment
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#if __has_include(<Arduino.h>)
#include <Arduino.h>

/**
 * @brief Concept representing 'component' type that can be configred, turned-on and turned-off
 *    (e.g. LED)
 */
template<class T>
concept component = requires {
    T::setup;
    T::on;
    T::off;
};

/**
 * @brief Class template representing GPIO pin of the arduino configured in the OUTPUT mode
 * @tparam Pin 
 *    ID of the pin
 */
template<auto Pin>
struct led final {
    static constexpr auto setup = [] { pinMode(uint8_t(Pin), OUTPUT); };
    static constexpr auto on    = [] { digitalWrite(uint8_t(Pin), HIGH); }; 
    static constexpr auto off   = [] { digitalWrite(uint8_t(Pin), LOW); }; 
};

/**
 * @brief Class template representing GPIO pin of the arduino configured in the INPUT mode
 * @tparam Pin 
 *    ID of the pin
 */
template<auto Pin>
struct button final {
    static constexpr auto setup   = [] { pinMode(uint8_t(Pin), INPUT); };
    static constexpr auto on      = [] (const auto& event) { return event() == HIGH; };
    static constexpr auto off     = [] (const auto& event) { return event() == LOW; };
    static constexpr auto pressed = [] { return digitalRead(uint8_t(Pin)); }; 
};

/**
 * Implementation: https://godbolt.org/z/55z858
 * Simulation: https://www.tinkercad.com/things/9epUrFrzKP3
 */
template<component Btn, component Led>
struct switcher {

    /**
     * @brief Constructor using C++17 fold expressions to call ::setup() methods of all types
     *    passed as the templace argument
     * 
     */
    constexpr switcher() {

        // Generic lambda called in place of the definition. Utilized C++17 fold expressions to deduce types
        // of @ref switcher template's arguments
        []<class... Ts>(switcher<Ts...>) { (Ts::setup(), ...); }(*this);
        
    }


    constexpr auto operator()() const {

        /**
         * @brief Functor providing a wrapper around an arbitrary type to produce an sml::event instance
         */
        const auto event = []<class TEvent>(TEvent) { return boost::sml::event<TEvent>; };

        /**
         * Initial state: *initial_state
         * Transition DSL: src_state + event [ guard ] / action = dst_state
         */
        using namespace boost::sml;
        return make_transition_table(
            *"off"_s + event(Btn::pressed) [ Btn::on  ] / Led::on  = "on"_s,
              "on"_s + event(Btn::pressed) [ Btn::off ] / Led::off = "off"_s
        );
    }
};

int main() {

    /**
     * @brief Begin infinite loop creating SM based on the D2 (button) and D11 (LED) pins
     *    of the Arduino
     */
    for (boost::sml::sm<switcher<button<2>, led<11>>> sm;;) {

        /**
         * @brief In every iteration process list of all events registered in the SM (use C++17 folding 
         *   expressions to automatically deduce types of these events). Note that the only event registered
         *   in the SM is an event build around @ref button::pressed() member which is a lambda object
         *   (body of this lambda, when called, reads and returns state of the button pin). Such an event
         *   is passed to the guard condition where it is called to inspect state of the button and return state
         *   of the guard
         */
        [&sm]<template<class...> class TList, class... TEvents>(TList<TEvents...>) {
            (sm.process_event(TEvents{}), ...);
        }(decltype(sm)::events{});
    }
}

#else
#include <iostream>
int main() { std::cout << "No <Arduino.h> header has been found" << std::endl; }
#endif
