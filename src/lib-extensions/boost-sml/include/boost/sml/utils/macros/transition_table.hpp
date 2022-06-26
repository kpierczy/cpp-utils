/* ============================================================================================================================ *//**
 * @file       transition_table.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Sunday, 9th January 2022 5:35:19 pm
 * @modified   Sunday, 26th June 2022 11:57:43 am
 * @project    cpp-utils
 * @brief      Header file defining helper macros related to dealing with SML transition tables. This header does NOT include boost::sml 
 *             module
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UTILS_SML_UTILS_MACROS_TRANSITION_TABLE_H__
#define __UTILS_SML_UTILS_MACROS_TRANSITION_TABLE_H__

/* ======================================================= Transition tables ====================================================== */

/**
 * @brief Helper macro defining common elements of the transition tables' 
 *    definition
 */
#define TRANSITION_TABLE(...)                      \
    auto operator()() const noexcept {             \
        return make_transition_table(__VA_ARGS__); \
    }

/**
 * @brief Defines transition table with enabled @b boost::sml namespace
 * @see TRANSITION_TABLE
 */
#define TRANSITION_TABLE_NM(...)                   \
    auto operator()() const noexcept {             \
        using namespace boost::sml;                \
        return make_transition_table(__VA_ARGS__); \
    }

/**
 * @brief Helper macro desired to be used with @ref TRANSITION_TABLE_DEFS* as a wrapper around
 *    subsequent definitions passed as @p defs. Delays expansion of commas in the deinition statement
 */
#define SM_DEF(...) __VA_ARGS__

/**
 * @brief Helper macro desired to be used with @ref TRANSITION_TABLE_DEFS* as a wrapper around
 *    subsequent definitions passed as @p defs. Delays expansion of commas in the deinition statement
 */
#define SM_DEFS(...) EXPAND5(__VA_ARGS__)

/**
 * @brief Helper macro defining common elements of the transition tables' 
 *    definition. Inserts @p defs into the body of the @b operator()
 */
#define TRANSITION_TABLE_DEFS(defs, ...)           \
    auto operator()() const noexcept {             \
        defs;                                      \
        return make_transition_table(__VA_ARGS__); \
    }

/**
 * @brief Defines transition table with enabled @b boost::sml namespace
 * @see TRANSITION_TABLE
 */
#define TRANSITION_TABLE_DEFS_NM(defs, ...)        \
    auto operator()() const noexcept {             \
        using namespace boost::sml;                \
        defs;                                      \
        return make_transition_table(__VA_ARGS__); \
    }

/* ======================================================== State machines ======================================================== */

/**
 * @brief Helper macro defining a structure named @p name with the
 *    transition table defined int @p ...
 * @param name 
 *    name of the class wrapping transition table
 * @param ...
 *    definiton of the transition table
 */
#define STATE_MACHINE(name, ...) \
    struct name { TRANSITION_TABLE(__VA_ARGS__) }

/**
 * @brief Defines state machine with enabled @b boost::sml namespace
 * @see STATE_MACHINE
 * 
 */
#define STATE_MACHINE_NM(name, ...) \
    struct name { TRANSITION_TABLE_NM(__VA_ARGS__) }

/**
 * @brief Helper macro defining common elements of the transition tables' 
 *    definition. Inserts @p defs into the body of the @b operator()
 */
#define STATE_MACHINE_DEFS(name, defs, ...) \
    struct name { TRANSITION_TABLE_DEFS(DEFER(defs), __VA_ARGS__) }

/**
 * @brief Defines transition table with enabled @b boost::sml namespace
 * @see TRANSITION_TABLE
 */
#define STATE_MACHINE_DEFS_NM(name, defs, ...) \
    struct name { TRANSITION_TABLE_DEFS_NM(DEFER(defs), __VA_ARGS__) }
    
/* ========================================================== Submachines ========================================================= */

/**
 * @brief Helper macro defining a structure named @p name with the
 *    transition table defined int @p ... . Defines boost::sml::state<_>
 *    wrapper around defined class named @p instance
 * @param name 
 *    name of the class wrapping transition table
 * @param instance 
 *    name of the boost::sml::state<_> wrapper around @p name class
 * @param ...
 *    definiton of the transition table
 * 
 * @bug Defining @a boost::sml::state<name> as an independent object results in premature
 *    instantiation of the @ref boost::sml::front::state_sm<T>::type for the @p name class.
 *    This results in invalid behaviour of the whole state machine.
 *    To enable using short name for the @b boost::sml::state<name> one need to define 
 *    @b instance=boost::sml::state<name> in the local scope of the transition-table maker
 *    (i.e. operator()(...)) as an automatic constance
 */
#define STATE_SUBMACHINE(name, instance, ...) \
    STATE_MACHINE(name, __VA_ARGS__); static constexpr auto instance = boost::sml::state<name>

/**
 * @brief Defines submachine with enabled @b boost::sml namespace
 * @see STATE_SUBMACHINE
 */
#define STATE_SUBMACHINE_NM(name, instance, ...) \
    STATE_MACHINE_NM(name, __VA_ARGS__); static constexpr auto instance = boost::sml::state<name>

/* ================================================================================================================================ */

#endif
