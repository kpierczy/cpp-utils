/** ==================================================================================================================================
 * @file     action_guards.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Wednesday, 22nd December 2021 5:37:35 pm
 * @brief 
 * 
 *    Example showing various ways to utilize action guards in the state machine
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>
#include <typeinfo>

namespace sml = boost::sml;

namespace {

    // Events
    struct e1 {};
    struct e2 {};
    struct e3 {};
    struct e4 {};
    struct e5 {};

    // Guard's forward declaration
    bool guard2_impl(int i);

    // State machine
    struct actions_guards {

        using self = actions_guards;

        // Transition table maker
        auto operator()() {
            using namespace sml;

            // Guard lambda
            auto guard1 = [] {
                std::cout << "guard1" << std::endl;
                return true;
            };
            // Functor wrapper for as a gaurd object
            auto guard2 = wrap(&guard2_impl);

            // Action lambda
            auto action1 = [](auto e) { std::cout << "action1: " << typeid(e).name() << std::endl; };
            // Action functor
            struct action2 {
                void operator()(int i) {
                    assert(42 == i);
                    std::cout << "action2" << std::endl;
                }
            };

            // Transition table
            return make_transition_table(
                // No guard
                *"idle"_s + event<e1>                                                                                                            = "s1"_s
                // Lambda object as guard (single action)
                , "s1"_s  + event<e2> [ guard1                         ] / action1                                                               = "s2"_s
                // Boolean combination of lambda objects' results as guard (list of actions)
                , "s2"_s  + event<e3> [ guard1 && ![] { return false;} ] / (action1, action2{})                                                  = "s3"_s
                // Boolean combination of functor objects' results as guard (free function wrapped in functor obejct with sml::wrap) (list of actions)
                , "s3"_s  + event<e4> [ !guard1 || guard2              ] / (action1, [] { std::cout << "action3" << std::endl; })                = "s4"_s
                // Object used as a context for action lambda functor
                , "s3"_s  + event<e4> [ guard1                         ] / ([] { std::cout << "action4" << std::endl; }, [this] { action4(); } ) = "s5"_s
                // Object's method as a guard as an action
                , "s5"_s  + event<e5> [ &self::guard3                  ] / &self::action5                                                        = X
            );
        }

        // Guard definition (class method)
        bool guard3(int i) const noexcept {
            assert(42 == i);
            std::cout << "guard3" << std::endl;
            return true;
        }

        // Action definition (class method)
        void action4() const { std::cout << "action4" << std::endl; }
        // Action definition (const class method)
        void action5(int i, const e5&) {
            assert(42 == i);
            std::cout << "action5" << std::endl;
        }

    };

    // Postponed definition of the guard function
    bool guard2_impl(int i) {
        assert(42 == i);
        std::cout << "guard2" << std::endl;
        return false;
    }

}

int main() {

    // State machine constructed with class' instantiation as a context
    actions_guards ag{};
    sml::sm<actions_guards> sm{ag, 42};
    
    // State machine constructed with class' instantiation as a context
    sm.process_event(e1{});
    sm.process_event(e2{});
    sm.process_event(e3{});
    sm.process_event(e4{});
    sm.process_event(e5{});
    
    assert(sm.is(sml::X));
}
