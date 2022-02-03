/** ==================================================================================================================================
 * @file     states.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 4:42:02 pm
 * @modified Thursday, 3rd February 2022 12:31:42 pm
 * @project  Winder
 * @brief
 *    
 *    Header file defining helper macros related to dealing with SML states. This header does NOT include boost::sml module
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UTILS_SML_UTILS_MACROS_STATES_H__
#define __UTILS_SML_UTILS_MACROS_STATES_H__

/* =========================================================== Includes =========================================================== */

#include "utils/miscellaneous/macros/foreach.hpp"

/* ============================================================ General =========================================================== */

/**
 * @brief Creates instance of the @b boost::sml::state with the @p class_name as a template
 *    argument
 */
#define MAKE_STATE(class_name, instance_name) \
    const auto instance_name = ::boost::sml::state<class_name>

/* ========================================================== Empty state ========================================================= */

/**
 * @brief Helper macro defining a state class along with a sml::state
 *    wrapper variable around the defined class
 * @param state_class
 *    name of the class to be defined
 * @param state_var
 *    name of the variable to be defined
 */
#define EMPTY_STATE(state_class, state_var) \
    struct state_class {}; constexpr auto state_var = boost::sml::state<state_class>;

/**
 * @brief Callas EMPTY_STATE macro passing subsequent pairs of arguments from the
 *    given variadic list
 */
#define EMPTY_STATES(...) FOR_EACH_PAIR(EMPTY_STATE, __VA_ARGS__)

/* ===================================================== Printable empty state ==================================================== */

/**
 * @brief Helper macro defining a state class along with a sml::state
 *    wrapper variable around the defined class. Class has a c_str() method defined
 *    returning @p state_class as string
 * @param state_class
 *    name of the class to be defined
 * @param state_var
 *    name of the variable to be defined
 */
#define PRINTABLE_EMPTY_STATE(state_class, state_var) \
    struct state_class { static constexpr auto c_str() { return #state_class; }}; constexpr auto state_var = boost::sml::state<state_class>;

/**
 * @brief Callas PRINTABLE_EMPTY_STATE macro passing subsequent pairs of arguments from the
 *    given variadic list
 */
#define PRINTABLE_EMPTY_STATES(...) FOR_EACH_PAIR(PRINTABLE_EMPTY_STATE, __VA_ARGS__)

/* ========================================================= Complex state ======================================================== */

/// Helper macro adding semicolon at the end of the token
#define STATE_MEMBER(token) token;

/**
 * @brief Helper macro defining an state class along with also a sml::state
 *    wrapper variable around the defined class. The class may contain members
 *    passed in @p ... (every argument is ended with ';')
 * @param state_class
 *    name of the class to be defined
 * @param state_var
 *    name of the variable to be defined
 * @param ...
 *    statements to be put into the class definition
 */
#define COMPLEX_STATE(state_class, state_var, ...) \
    struct state_class { FOR_EACH(EVENT_MEMBER, __VA_ARGS__) }; constexpr auto state_var = boost::sml::event<state_class>;
    
/* =========================================================== OK state =========================================================== */

/**
 * @brief Helper macro defining a state class with a boolean flag 
 *    indicating internal state of the state. Defines also a sml::state
 *    wrapper wariable around the define class
 * @param state_class
 *    name of the class to be defined
 * @param state_var
 *    name of the variable to be defined
 */
#define OK_STATE(state_class, state_var) \
    struct state_class { bool ok = true; }; constexpr auto state_var = boost::sml::state<state_class>;

/**
 * @brief Callas OK_STATE macro passing subsequent pairs of arguments from the
 *    given variadic list
 */
#define OK_STATES(...) FOR_EACH_PAIR(OK_STATE, __VA_ARGS__)

/* ====================================================== Choice pseudostate ====================================================== */

/**
 * @brief Helper macro defining a state class with a boolean flag 
 *    indicating internal state of the state. Defines also a sml::state
 *    wrapper wariable around the define class
 * @param state_class
 *    name of the class to be defined
 * @param state_var
 *    name of the variable to be defined
 */
#define CHOICE_PSEUDOSTATE(state_class, state_var) \
    OK_STATE(state_class, state_var)

/**
 * @brief Callas CHOICE_PSEUDOSTATE macro passing subsequent pairs of arguments from the
 *    given variadic list
 */
#define CHOICE_PSEUDOSTATES(...) FOR_EACH_PAIR(CHOICE_PSEUDOSTATE, __VA_ARGS__)

/* ================================================================================================================================ */

#endif
