/** ==================================================================================================================================
 * @file     dependency_injection.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Thursday, 23rd December 2021 7:14:26 pm
 * @brief 
 * 
 *    Example showing usage of DI (dependency-injection) boost library along with SML
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <boost/di.hpp>
#include <cassert>
#include <typeinfo>
#include <iostream>

namespace sml = boost::sml;
namespace di = boost::di;

namespace {

    // Events
    struct e1 {};
    struct e2 {};
    struct e3 {};

    // Guard
    auto guard = [](int i, double d) {

        // Some assertions concerning arguments
        assert(42   == i);
        assert(87.0 == d);
        // Visualize guard's call
        std::cout << "- guard" << std::endl;
        
        return true;
    };

    // Action
    auto action = [](int i, auto e) {
    
        // Some assertions concerning arguments
        assert(42 == i);
        // Visualize guard's call
        std::cout << "- action: " << typeid(e).name() << std::endl;
        
    };

    // State machine
    struct example {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                *"idle"_s + event<e1>                                                                   = "s1"_s
                ,  "s1"_s + event<e2> [ guard ] / action                                                = "s2"_s
                ,  "s2"_s + event<e3>           / [] { std::cout << "- in place action" << std::endl; } = X
            );
        }
    };

    /**
     * @brief Controller class that the SM is injected into
     */
    class controller {
    public:

        // Explicit constructor
        explicit controller(sml::sm<example>& sm) : sm(sm) {}

        // Processing loop
        void start() {
            sm.process_event(e1{});
            sm.process_event(e2{});
            sm.process_event(e3{});
            assert(sm.is(sml::X));
        }

    private:
    
        // Reference to the state machine
        sml::sm<example>& sm;
        
    };
}


int main() {
    
    // Bind injected arguments
    const auto injector = di::make_injector(

        /// Bind all 'int's requred to construct @ref controller to @c 42
        di::bind<>.to(42), 
        /// Bind all 'double's requred to construct @ref controller to @c 87.0
        di::bind<>.to(87.0)
    );

    /**
     * @note @ref action lambda takes an 'auto' parameter 'e'. SML will assume (I guess so) that a template
     *    type passed to the action/guard routine should be an associated event
     */
    
    // Process SM
    injector.create<controller>().start();
}
