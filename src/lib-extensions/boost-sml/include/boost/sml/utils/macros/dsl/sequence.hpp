/* ============================================================================================================================ *//**
 * @file       sequence.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Saturday, 15th January 2022 1:44:31 pm
 * @modified   Sunday, 26th June 2022 3:23:02 pm
 * @project    cpp-utils
 * @brief      Helper DSL-type (Domain Specific Language) macros modelling linear sequence of actions that may fail resuling
 *             in processing of the predefined event
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UTILS_SML_DSL_MACROS_SEQUENCE_H__
#define __UTILS_SML_DSL_MACROS_SEQUENCE_H__

/* =========================================================== Includes =========================================================== */

#include "estd/traits.hpp"
#include "boost/sml/utils/dsl/sequence.hpp"
#include "estd/preprocessor/variadic.hpp"
#include "estd/preprocessor/foreach.hpp"
#include "boost/preprocessor/punctuation/comma_if.hpp"

/* ============================================================ Helpers =========================================================== */

/**
 * @brief Implements set of transitions associated with a single @p src state
 * @param error 
 *    error event generated on action failure
 * @param src 
 *    source state 
 * @param action 
 *    action associated with the @p src state
 * @param dst 
 *    destination state (on success) 
 */
#define ACTIONS_SEQUENCE_STATE_TRANSITIONS(error, src, action, dst)                                                                                       \
      src + event<ProceedeSequence<estd::result_t<decltype(action)>>>[  is_sequence_action_success<estd::result_t<decltype(action)>> ] = dst              \
    , src + event<ProceedeSequence<estd::result_t<decltype(action)>>>[ !is_sequence_action_success<estd::result_t<decltype(action)>> ] / process(error{}) \
    , src + on_entry<_> / proceede_action(action)

/* ============================================================ Macros ============================================================ */

/**
 * @brief Helper macro defining part of the transition table modelling linear flow of the
 *    sequence of actions that can fail
 * 
 * @example 
 * 
 *     // This one ... (note trailing ',' after "s5"_s)
 *     TRANSITION_TABLE_NM(
 *         * ACTIONS_SEQUENCE_OR( Error,
 *              "s1"_s, action1,
 *              "s2"_s, action2,
 *              "s3"_s, action3,
 *              "s4"_s, action4,
 *              "s5"_s,
 *         )
 *     )
 * 
 *     // ... is equal to this one
 *     TRANSITION_TABLE_NM(
 *         
 *         // --------------------- Transitions --------------------- //
 * 
 *         * "s1"_s + event<ProceedeSequence<decltype(action1())>>[ is_sequence_action_success<decltype(action1())> ] = "s2"_s
 *         , "s2"_s + event<ProceedeSequence<decltype(action2())>>[ is_sequence_action_success<decltype(action2())> ] = "s3"_s
 *         , "s3"_s + event<ProceedeSequence<decltype(action3())>>[ is_sequence_action_success<decltype(action3())> ] = "s4"_s
 *         , "s4"_s + event<ProceedeSequence<decltype(action4())>>[ is_sequence_action_success<decltype(action4())> ] = "s5"_s
 *         
 *         // ------------------------ Errors ----------------------- //
 *          
 *         , "s1"_s + event<ProceedeSequence<decltype(action1())>>[ !is_sequence_action_success<decltype(action1())> ] / process(Error{}) 
 *         , "s2"_s + event<ProceedeSequence<decltype(action2())>>[ !is_sequence_action_success<decltype(action2())> ] / process(Error{}) 
 *         , "s3"_s + event<ProceedeSequence<decltype(action3())>>[ !is_sequence_action_success<decltype(action3())> ] / process(Error{}) 
 *         , "s4"_s + event<ProceedeSequence<decltype(action4())>>[ !is_sequence_action_success<decltype(action4())> ] / process(Error{})
 *         
 *         // ---------------------- On-entries --------------------- //
 *          
 *         , "s1"_s + on_entry<_> / proceede_action(action1)
 *         , "s2"_s + on_entry<_> / proceede_action(action2)
 *         , "s3"_s + on_entry<_> / proceede_action(action3)
 *         , "s4"_s + on_entry<_> / proceede_action(action4)
 *         
 *     )
 */
#define ACTIONS_SEQUENCE_OR(error, ...) \
    __VA_OPT__(EXPAND5(ACTIONS_SEQUENCE_OR_IMPL(0, error, __VA_ARGS__, _)))

#define ACTIONS_SEQUENCE_OR_IMPL(comma, error, a, b, c, ...) \
    __VA_OPT__(BOOST_PP_COMMA_IF(comma)  ACTIONS_SEQUENCE_STATE_TRANSITIONS(error, a, b, c)) \
    __VA_OPT__(ACTIONS_SEQUENCE_OR_IMPL_AGAIN PARENS (1, error, c, __VA_ARGS__))

#define ACTIONS_SEQUENCE_OR_IMPL_AGAIN() ACTIONS_SEQUENCE_OR_IMPL

/* ================================================================================================================================ */

#endif
