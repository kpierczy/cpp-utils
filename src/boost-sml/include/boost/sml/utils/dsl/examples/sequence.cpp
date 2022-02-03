/** ==================================================================================================================================
 * @file     main.cpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 6:57:56 pm
 * @modified Thursday, 3rd February 2022 12:31:17 pm
 * @project  Winder
 * @brief
 * 
 *    Example of quasi-activity-diagram implementation of actions using UML state machine scheme implemented with boost::sml
 *    
 * @note Compilation environment is:
 * 
 *    FLAGS="  -I src/libraries/utils/miscellaneous/include"
 *    FLAGS+=" -I extern/boost"
 *    FLAGS+=" -I extern/boost-ext/sml/include"
 *    FLAGS+=" -I extern/static-stl/include"
 *    FLAGS+=" -I src/app/include"
 *    FLAGS+=" -I src/libraries/utils/sml/include"
 *    FLAGS+=" -I src/libraries/utils/result/include"
 *    FLAGS+=" -I src/libraries/utils/traits/include"
 *    SRC="       src/libraries/utils/result/src/default_domain_impl.cpp"
 *    function compile() { 
 *        g++ -std=c++2a $FLAGS $SRC main.cpp -o a.out; 
 *    }
 *    function preprocess() { 
 *        g++ -E -std=c++2a $FLAGS $SRC main.cpp > main.ii
 *    }
 * 
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

/* =========================================================== Includes =========================================================== */

#include <cstdio>
#include <concepts>
#include <iostream>
#include <queue>
#include "boost/sml.hpp"
#include "utils/sml/utils/states.hpp"
#include "utils/sml/utils/macros/states.hpp"
#include "utils/sml/utils/macros/transition_table.hpp"
#include "utils/sml/utils/macros/dsl/sequence.hpp"

/* ============================================================ Helpers =========================================================== */

void println(const char *str) {
    printf("%s", str);
    printf("\r\n");
}

/* ========================================================== Definitions ========================================================= */

// Some events
struct Ini {};
struct Fini {};
struct Error {};

/* ========================================================= State machine ======================================================== */

/**
 * @brief State machine
 */
template<typename Impl>
struct SM {
    
    /**
     * @brief Submachine implements actual activity flow. Every state performs some action 'on entry'. 'on exit' 
     *    action checks whether the transition action has succeeded. If so, flow is continued. Otherwise, the 'error'
     *    event is called that interrupts standard control flow. The 'error' condition is handled by the upper state machine
     */
    struct SubSub {

        // List of valid states
        EMPTY_STATE(InitLidar,  static init_lidar);
        EMPTY_STATE(InitDac,    static init_dac);
        EMPTY_STATE(InitTakeup, static init_takeup);
        EMPTY_STATE(InitGiveup, static init_giveup);
        EMPTY_STATE(InitPutup,  static init_putup);

        /**
         * @see https://github.com/boost-ext/sml/issues/400 : sml::back::process functor template queues
         *    events to be dispatched in the context of the current SM and not the parent SM.
         * 
         * @brief This functionality must be implemented like this due to #400. Otherwise it could be 
         *    implemented much simpler, like this
         * 
         *    @code
         * 
         *    template<bool(Impl::*action)()>
         *    static constexpr auto proceede_on_success_or_error = 
         *        [] (boost::sml::back::process<Proceede, Error> process, Impl &impl) {
         *            if((impl.*action)())
         *                process(Proceede{});
         *            else
         *                process(Error{});
         *        };
         *    
         *    * init_lidar  + event<Proceede> / proceede_on_success_or_error<&Impl::initializeLIDAR> = init_dac
         *    , init_dac    + event<Proceede> / proceede_on_success_or_error<&Impl::initializeDAC> = init_takeup
         *    , init_takeup + event<Proceede> / proceede_on_success_or_error<&Impl::initializeTakeup> = init_giveup
         *    , init_giveup + event<Proceede> / proceede_on_success_or_error<&Impl::initializeGiveup> = init_putup
         *    , init_putup  + event<Proceede> / proceede_on_success_or_error<&Impl::initializePutup> = X
         *    
         *    @endcode
         * 
         *    At the moment this will not even compile, as Error{} event is not used inside the submachine's transition table
         */

        using Proceede = boost::sml::ProceedeSequence<bool>;
        static constexpr auto is_success = boost::sml::is_sequence_action_success<bool>;
        
        TRANSITION_TABLE_NM(

            * ACTIONS_SEQUENCE_OR( Error,
                init_lidar,  &Impl::initializeLIDAR,
                init_dac,    &Impl::initializeDAC,
                init_takeup, &Impl::initializeTakeup,
                init_giveup, &Impl::initializeGiveup,
                init_putup,  &Impl::initializePutup,
                X,
            )

            // Equals to ...

            // /* --------------------- Transitions --------------------- */

            // * init_lidar  + event<Proceede>[ is_success ] = init_dac
            // , init_dac    + event<Proceede>[ is_success ] = init_takeup
            // , init_takeup + event<Proceede>[ is_success ] = init_giveup
            // , init_giveup + event<Proceede>[ is_success ] = init_putup
            // , init_putup  + event<Proceede>[ is_success ] = X

            // /* ------------------------ Errors ----------------------- */

            // , init_lidar  + event<Proceede>[ !is_success ] / ( &Impl::errorLIDAR,  process(Error{}) )
            // , init_dac    + event<Proceede>[ !is_success ] / ( &Impl::errorDAC,    process(Error{}) )
            // , init_takeup + event<Proceede>[ !is_success ] / ( &Impl::errorTakeup, process(Error{}) )
            // , init_giveup + event<Proceede>[ !is_success ] / ( &Impl::errorGiveup, process(Error{}) )
            // , init_putup  + event<Proceede>[ !is_success ] / ( &Impl::errorPutup,  process(Error{}) )

            // /* ---------------------- On-entries --------------------- */

            // , init_lidar  + on_entry<_> / proceede_on_success_or_event(&Impl::initializeLIDAR)
            // , init_dac    + on_entry<_> / proceede_on_success_or_event(&Impl::initializeDAC)
            // , init_takeup + on_entry<_> / proceede_on_success_or_event(&Impl::initializeTakeup)
            // , init_giveup + on_entry<_> / proceede_on_success_or_event(&Impl::initializeGiveup)
            // , init_putup  + on_entry<_> / proceede_on_success_or_event(&Impl::initializePutup)
        )

    };

    /**
     * @brief Intermediate composite state used to check whether Error will propagate to the top state
     */
    struct Sub {
        TRANSITION_TABLE_NM(
            * state<SubSub> = X
        )
    };

    /**
     * @brief Outer state machine. This one is needed for two purposes:
     *  
     *     1) Initialize activity flow implemented by the submachine
     *     2) Handle non-standrd activity flow ('error' in this case)
     * 
     */
    TRANSITION_TABLE_DEFS_NM(

        /* --------------------- Definitions --------------------- */
        SM_DEF(MAKE_STATE(Sub, sub));
        /* ------------------------ Table ------------------------ */ ,
        * "start"_s + event<Ini>   /  [] { println("ENTERING SUB"); } = sub        // Initialize activity flow
        , sub       + event<Error> /  [] { println("ERROR");        } = "error"_s  // Handle NON-standard control flow
        , sub                      /  [] { println("FINALIZING");   } = X          // Handle standard control flow
        
    );
};

/* ======================================================== Implementation ======================================================== */

struct Implementation {

    bool initializeLIDAR()  { println(" - Initializing LIDAR");  return true;  }
    bool initializeDAC()    { println(" - Initializing DAC");    return true;  }
    bool initializeTakeup() { println(" - Initializing takeup"); return false; }
    bool initializeGiveup() { println(" - Initializing giveup"); return true;  }
    bool initializePutup()  { println(" - Initializing putup");  return true;  }

    void errorLIDAR()  { println("   x Error on LIDAR initialization");  }
    void errorDAC()    { println("   x Error on DAC initialization");    }
    void errorTakeup() { println("   x Error on takeup initialization"); }
    void errorGiveup() { println("   x Error on giveup initialization"); }
    void errorPutup()  { println("   x Error on putup initialization");  }
};

/* ============================================================ Helpers =========================================================== */

using SMType = boost::sml::sm<SM<Implementation>, boost::sml::process_queue<std::queue>>;

// Helper routine
template<typename ev_type>
void process_event(SMType &sm, const ev_type &event) {
    sm.process_event(event);
    sm.visit_current_states                                                      ([](auto state) { std::cout << " -> Main state: " << state.c_str() << std::endl;              });
    sm.visit_current_states<decltype(boost::sml::state<SM<Implementation>::Sub>)>([](auto state) { std::cout << " -> Sub state:  " << state.c_str() << std::endl << std::endl; });
}

/* ============================================================= Main ============================================================= */

int main() {

    // State machine
    Implementation impl;
    SMType sm{impl};

    // Process events
    std::cout << "Processing Ini{}"   << std::endl; process_event(sm, Ini{});
    // std::cout << "Processing Error{}" << std::endl; process_event(sm, Error{});
    std::cout << "Processing Fini{}"  << std::endl; process_event(sm, Fini{});
    
}
