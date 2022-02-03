/** ==================================================================================================================================
 * @file     events.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 4:42:02 pm
 * @modified Thursday, 3rd February 2022 3:20:05 pm
 * @project  Winder
 * @brief
 *    
 *    Header file defining helper macros related to dealing with SML events. This header does NOT include boost::sml module
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UTILS_SML_UTILS_MACROS_EVENTS_H__
#define __UTILS_SML_UTILS_MACROS_EVENTS_H__

/* =========================================================== Includes =========================================================== */

#include "estd/preprocessor/foreach.hpp"

/* ========================================================= Empty events ========================================================= */

/**
 * @brief Helper macro defining an event class along with also a sml::event
 *    wrapper variable around the defined class
 * @param event_class
 *    name of the class to be defined
 * @param event_var
 *    name of the variable to be defined
 */
#define EMPTY_EVENT(event_class, event_var) \
    struct event_class {}; constexpr auto event_var = boost::sml::event<event_class>;

/**
 * @brief Callas EMPTY_EVENT macro passing subsequent pairs of arguments from the
 *    given variadic list
 */
#define EMPTY_EVENTS(...) FOR_EACH_PAIR(EMPTY_EVENT, __VA_ARGS__)

/* ======================================================== Complex events ======================================================== */

/// Helper macro adding semicolon at the end of the token
#define EVENT_MEMBER(token) token;

/**
 * @brief Helper macro defining an event class along with also a sml::event
 *    wrapper variable around the defined class. The class may contain members
 *    passed in @p ... (every argument is ended with ';')
 * @param event_class
 *    name of the class to be defined
 * @param event_var
 *    name of the variable to be defined
 * @param ...
 *    statements to be put into the class definition
 */
#define COMPLEX_EVENT(event_class, event_var, ...) \
    struct event_class { FOR_EACH(EVENT_MEMBER, __VA_ARGS__) }; constexpr auto event_var = boost::sml::event<event_class>;

/* ================================================================================================================================ */

#endif
