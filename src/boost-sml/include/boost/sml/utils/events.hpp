/** ==================================================================================================================================
 * @file     events.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 5:03:52 pm
 * @modified Thursday, 3rd February 2022 6:58:12 pm
 * @project  Winder
 * @brief
 *    
 *    Helpers concerning usage of the Boost::sml events
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __BOOST_SML_UTILS_EVENTS_H__
#define __BOOST_SML_UTILS_EVENTS_H__

/* =========================================================== Includes =========================================================== */

#include "boost/sml.hpp"
#include "estd/traits.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace boost::sml {

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Helper concept template aimed to define event concepts
 * @tparam T 
 *    type to be examined against the concept
 * @tparam Events 
 *    valid events
 */
template<typename T, typename ... Events>
constexpr bool AnyOfEvents = estd::is_any_of_v<T, Events...>;

/* ================================================================================================================================ */

} // End namespace boost::sml

#endif
