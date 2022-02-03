/** ==================================================================================================================================
 * @file     runtime_dispatcher.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Wednesday, 22nd December 2021 6:02:52 pm
 * @brief 
 * 
 *    Example showing usage of the built-in runtime dispatcher (this also explains some aspects of the dispatche mechanism
 *    that are not exaplined in the documentation of the SML)
 * 
 * @todo fixme 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include "boost/sml/utility/dispatch_table.hpp"
#include <boost/sml.hpp>
#include <cassert>

namespace sml = boost::sml;

namespace {

    /**
     * @brief Event type used to dispatch events at tuntime. Types used for events need to meet two requirements
     *    (according to boost::sml::utility::concepts::dispatchable_impl):
     * 
     *      - contain static constexpr member EventType::id (formally, typename(EventType::id) expression needs 
     *        to be valid ); this field is a numeric identifier of the event dispatched by the SM (and so I \b assume
     *        that these fields needs to be kept unique between event classes)
     *      - be constructible in at least one of following ways:
     *         * be default-constructible
     *         * be constructible-from @ref runtime_event
     *         * be constructible-from ( @ref runtime_event, EventType::id ) pair
     * 
     *    In this example @ref id field of the @ref runtime_event is in fact unused. One may confirm this by using
     *    default constructor of this objects inside the @ref main() function (final assertion will still hold as long
     *    as appropriate indeces range is given in the call to make_dispatch_table)
     */
    struct runtime_event { int id = 0; };

    /**
     * @brief Example of runtime_event-constructible event class. Needs to define @ref id field
     */
    struct event1 {
        static constexpr auto id = 1;
        event1(const runtime_event &) {}
    };
    
    /**
     * @brief Example of default-constructible event class. Needs to define @ref id field
     */
    struct event2 {
        static constexpr auto id = 2;
    };
    
    /**
     * @brief Example of default-constructible event class. Needs to define @ref id field
     */
    struct event3 {
        static constexpr auto id = 3;
    };

    // State machine
    struct dispatch_table {
        auto operator()() noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                *"idle"_s + event<event1> = "s1"_s
                ,  "s1"_s + event<event2> = "s2"_s
                ,  "s3"_s + event<event3> = X
            );
        }
    };
}

int main() {

    // State machine
    sml::sm<dispatch_table> sm;

    // Event dispatcher
    auto dispatch_event = sml::utility::make_dispatch_table<runtime_event, 1 /*min*/, 5 /*max*/>(sm);

    {
        runtime_event event{1};
        // runtime_event event; // Also works (?)
        dispatch_event(event, event.id);
    }

    {
        runtime_event event{2};
        // runtime_event event; // Also works (?)
        dispatch_event(event, event.id);
    }

    {
        runtime_event event{3};
        // runtime_event event; // Also works (?)
        dispatch_event(event, event.id);
    }

    assert(sm.is(sml::X));
}