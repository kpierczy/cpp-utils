/** ==================================================================================================================================
 * @file     logging.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Wednesday, 22nd December 2021 6:02:52 pm
 * @brief 
 * 
 *    Example showing usage of the logger policy of the state machines
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <cstdio>
#include <iostream>

namespace sml = boost::sml;

namespace {

    // Logger object
    struct my_logger {

        // Logging mechanism for events
        template <class SM, class TEvent>
        void log_process_event(const TEvent&) {
                printf("[%s][process_event] %s\n", sml::aux::get_type_name<SM>(), sml::aux::get_type_name<TEvent>());
        }

        // Logging mechanism for guards
        template <class SM, class TGuard, class TEvent>
        void log_guard(const TGuard&, const TEvent&, bool result) {
            printf("[%s][guard        ] %s %s %s\n", sml::aux::get_type_name<SM>(), sml::aux::get_type_name<TGuard>(),
                sml::aux::get_type_name<TEvent>(), (result ? "[OK]" : "[Reject]"));
        }

        // Logging mechanism for actions
        template <class SM, class TAction, class TEvent>
        void log_action(const TAction&, const TEvent&) {
            printf("[%s][action       ] %s %s\n", sml::aux::get_type_name<SM>(), sml::aux::get_type_name<TAction>(),
                sml::aux::get_type_name<TEvent>());
        }

        // Logging mechanism for transitions
        template <class SM, class TSrcState, class TDstState>
        void log_state_change(const TSrcState& src, const TDstState& dst) {
            printf("[%s][transition   ] %s -> %s\n", sml::aux::get_type_name<SM>(), src.c_str(), dst.c_str());
        }

    };

    // Events
    struct e1 {};
    struct e2 {};

    // Guard functor
    struct guard {
        bool operator()() const { return true; }
    } guard;

    // Actions functor
    struct action {
        void operator()() {}
    } action;

    // State machine
    struct logging {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                *"idle"_s + event<e1> [ guard && guard ] / action = "s1"_s
            );
        }
    };
}

int main() {

    // State machine with logging policy
    my_logger logger;
    sml::sm<logging, sml::logger<my_logger>> sm{logger};

    printf("\n");

    // Example logg
    printf("----------------------------- Event e1 -----------------------------\n");
    sm.process_event(e1{});
    // Lack of log on unknown event
    printf("----------------------------- Event e2 -----------------------------\n");
    sm.process_event(e2{});

    printf("\n");
    
}
