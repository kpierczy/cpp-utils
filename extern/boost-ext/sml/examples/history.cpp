/** ==================================================================================================================================
 * @file     history.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Wednesday, 22nd December 2021 6:02:52 pm
 * @brief 
 * 
 *    Example of the composite state machine utilizing 'history state'  feature of the UML SM
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>

namespace sml = boost::sml;

namespace {

    // Submachine
    struct sub {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                // Initial state declared with the (H) to indicate submachine with 'history' feature
                  "idle"_s(H) + "e1"_e / [] { std::cout << "- in sub"        << std::endl; } = "s1"_s
                // Next transition descibed with no additional elements
                , "s1"_s      + "e2"_e / [] { std::cout << "- finishing sub" << std::endl; } = X   
            );
        }
    };

    // State machine
    struct history {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                // Transition into the submachine
                  *"idle"_s  + "e1"_e / [] { std::cout << "- enter sub"       << std::endl; } = state<sub>
                // Transition out of and into the submachine (loop)
                , state<sub> + "e3"_e / [] { std::cout << "- exit sub"        << std::endl; } = "s1"_s 
                , "s1"_s     + "e4"_e / [] { std::cout << "- enter sub again" << std::endl; } = state<sub>
                // Finished submachine will be unconditionally result in finishing upper sm
                , state<sub>          / [] { std::cout << "- exit sm"         << std::endl; } = X
            );
        }
    };

}

int main() {

    using namespace sml;

    // Context-less state machine
    sml::sm<history> sm;

    // Processing e1 to enter the submachine
    std::cout << "Processing 'e1'" << std::endl;
    sm.process_event("e1"_e());

    // Processing e1 to make transition inside the submachine
    std::cout << "Processing 'e1 again'" << std::endl;
    sm.process_event("e1"_e());

    // Processing e3 that is handled by the upper machine and not by the sub (exiting submachine)
    std::cout << "Processing 'e3'" << std::endl;
    sm.process_event("e3"_e());

    // Processing e4 to enter the submachine again
    std::cout << "Processing 'e4'" << std::endl;
    sm.process_event("e4"_e());

    // Processing e2 to finalize submachine
    std::cout << "Processing 'e2'" << std::endl;
    sm.process_event("e2"_e());

    // Machine is in the finalized state (uncoonditional transition from the finished submachine)
    assert(sm.is(X));
    // When the submachine is finalized
    assert(sm.is<decltype(state<sub>)>(X));

}
