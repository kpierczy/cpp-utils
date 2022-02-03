/** ==================================================================================================================================
 * @file     states.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 5:03:52 pm
 * @modified Thursday, 3rd February 2022 12:29:40 pm
 * @project  Winder
 * @brief
 *    
 *    Helpers concerning usage of the Boost::sml states
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __BOOST_SML_UTILS_STATES_H__
#define __BOOST_SML_UTILS_STATES_H__

/* =========================================================== Includes =========================================================== */

#include <type_traits>
#include "boost/sml.hpp"
#include "estd/traits.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace boost::sml {

/* ============================================================= Types ============================================================ */

/**
 * @brief Helper concept template aimed to define state concepts
 * @tparam T 
 *    type to be examined against the concept
 * @tparam States 
 *    valid states
 */
template<typename T, typename ... States>
concept AnyOfStates = requires {
    Traits::is_any_of_v<T, States...>;
};

/**
 * @brief Type of the instance of the state
 * @tparam T 
 *    type used to represent state
 */
template<typename T>
using state_instance = decltype(state<T>);

/**
 * @brief Helper concept template aimed to define state instance concepts
 * @tparam T 
 *    type to be examined against the concept
 * @tparam States 
 *    valid state instance types
 */
template<typename T, typename ... States>
concept InstanceOfAnyOfStates = requires {
    Traits::is_any_of_v<T, state_instance<States>...>;
};

/**
 * @brief Helper concept defining requirements for the choice-pseudostate
 * @tparam T 
 *    type to be examined against the concept
 */
template<typename T>
concept ChoicePsudostate = requires(T &t) {

    // Require T to define boolean @a ok member
    t.ok;
    std::is_same_v<decltype(t.ok), bool>;

};

/* =========================================================== Functions ========================================================== */

/**
 * @brief Template of the helper lambda checking whether given choice pseudostate is
 *    succesfull or not. Such a lambda can be used as a guard in the transition table
 * @tparam State 
 *    type of the state
 */
template<ChoicePsudostate State>
constexpr auto is_ok = [](State &state) { return state.ok; };

/* ================================================================================================================================ */

} // End namespace boost::sml

#endif
