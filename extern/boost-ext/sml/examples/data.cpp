/* ============================================================================================================================ *//**
 * @file     data.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing usage of SML with respect to data associated with states and events
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 */// ============================================================================================================================= */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>

namespace sml = boost::sml;

namespace {

    // Events
    struct connect { int id{}; };
    struct disconnect {};
    struct interrupt {};

    // States
    struct Disconnected {};           // State with no data
    struct Connected   { int id{}; }; // Per-state data ( default-initialized to 0 )
    struct Interrupted { int id{}; }; // Per-state data ( default-initialized to 0 )

    // State machine
    class data {

        using Self = data;

    public:
    
        // Explicit constructor initializing data members
        explicit data(const std::string& address) : address{address} {}

        auto operator()() {

            using namespace boost::sml;

            // Action setting per-state data based on the data associated with an even
            const auto set = [](const auto& event, Connected& state) { state.id = event.id; };
            // Action setting per-state data of the destination state base on the data of the source state
            const auto update = [](Connected& src_state, Interrupted& dst_state) { dst_state.id = src_state.id; };

            // Transition table
            return make_transition_table(
                * state<Disconnected> + event<connect>    / (&Self::printIn, &Self::printCn, set,    &Self::printCn                ) = state<Connected>
                , state<Connected>    + event<interrupt>  / (&Self::printIn,                 update, &Self::printCn, &Self::printIn) = state<Interrupted>
                , state<Interrupted>  + event<connect>    / (                                set,    &Self::printCn                ) = state<Connected>
                , state<Connected>    + event<disconnect> / (                                        &Self::printCn                ) = X
            );
            
        }

    private:
    
        // Actions implemented as a private method
        void printCn(Connected& state)   { std::cout << "- " << address << ':' << state.id << "(connected)"   << '\n'; };
        void printIn(Interrupted& state) { std::cout << "- " << address << ':' << state.id << "(interrupted)" << '\n'; };

    private:

        /// Data shared between states
        std::string address{};
        
    };
}


int main() {

    // Initialize context common for all states
    data d{std::string{"127.0.0.1"}};
    
    /**
     * @brief Create state machine with context data. @var d will be passed to each action/guard
     *    taking @ref data object (or it's pointer/reference) as an argument (mainly actions/guards
     *    implemented as methods of the @ref data class)
     * 
     *    @ref Connected state will be initialized with @var id = 1. @ref Interrupts state will be
     *    default-initialized ( with @var id = 0 )
     */
    sml::sm<data> sm{d, Connected{1}};

    /**
     * @brief Transit from Disconnected to Connected. At this transition:
     *    
     *     - printIn() action will NOT be called as it requires an argument (reference to the Interrupted state)
     *       that is not associated with the transition
     *     - printCn() action will be called with a pointer to the @var d structure passed to the SM at construction
     *       and with reference to the Connected state (which is destination state of the transition)
     *     - set() action will be called with the @ref connect event that is processed and the reference to the destination
     *       state
     *     - printCn() action will be called again to visualize change of data associated with destination state 
     *       that has been introduced by the set() action
     */
    sm.process_event(connect{1024});

    /**
     * @brief Transit from Connected to Interrupted state. At this transition:
     *    
     *     - printIn() action will be called as with required arguments to visualize data associated with Interrupted
     *       state before call to the update() action
     *     - action() action will be called the with references to the source (Connected) and destination (Interrupted)
     *       state
     *     - printCn() action will be called to visualize that the contecte of the source state has NOT been changed
     *     - printIn() action will be called again to visualize change of data associated with destination state 
     *       that has been introduced by the update() action
     */
    sm.process_event(interrupt{});

    /**
     * @brief Transit from Interrupted to Connected state. Data associated with the Connected state will be one
     *    more time modified by the set() action
     */ 
    sm.process_event(connect{1025});

    /**
     * @brief Transit from Connected to termination state.
     */ 
    sm.process_event(disconnect{});

    assert(sm.is(sml::X));
}
