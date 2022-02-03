/** ==================================================================================================================================
 * @file     nested.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Wednesday, 22nd December 2021 6:02:52 pm
 * @brief 
 * 
 *    Example showing usage of the state machine nested into the class object
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>

namespace sml = boost::sml;

namespace {

    // State machine (use a dummy template to delay POI and support nested SM)
    template <class = class Dummy>
    class top {
    private:

        // Events
        struct e1 {};

        // Nested state machine
        struct nested {
            auto operator()() const noexcept {
                using namespace sml;
                // Transition table
                return make_transition_table(
                    *"idle"_s + event<e1> / []() { std::cout << "Transition" << std::endl; }  = X
                );
            }
        };

    public:

        // Processing of the nested SM
        void process() {
            sm.process_event(e1{});
            assert(sm.is(sml::X));
        }

    private:
    
        // Instance of the state machine
        sml::sm<nested> sm{};
    
    };

}

int main() {
    top<> sm{};
    sm.process();
}