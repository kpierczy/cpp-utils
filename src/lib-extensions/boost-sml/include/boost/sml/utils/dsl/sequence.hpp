/* ============================================================================================================================ *//**
 * @file       sequence.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Saturday, 15th January 2022 1:44:31 pm
 * @modified   Tuesday, 28th February 2023 9:03:18 pm
 * @project    cpp-utils
 * @brief      Helper DSL-type (Domain Specific Language) helpers modelling linear sequence of actions that may fail resuling
 *             in processing of the predefined event
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __BOOST_SML_UTILS_DSL_SEQUENCE_H__
#define __BOOST_SML_UTILS_DSL_SEQUENCE_H__

/* =========================================================== Includes =========================================================== */

#include <concepts>
#include "estd/traits.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace boost::sml {

/* ============================================================ Helpers =========================================================== */

/**
 * @brief Helper concept descibing type being convertible to bool
 */
template<typename T>
concept ProceedeResult = requires {
    estd::is_explicitly_convertible_v<T, bool> || std::is_convertible_v<T, bool>;
};

/* ============================================================ Events ============================================================ */

/**
 * @brief Helper event type holding a single boolean flag indicating
 *    whether the last action has been sucesfully finalized
 * 
 * @tparam Result
 *    result of the actions run in the sequence
 */
template<ProceedeResult Result>
struct ProceedeSequence {
    Result result = Result{};
};

// Definition of the ProceedeSequence-base event
template<ProceedeResult Result>
constexpr auto proceede_sequence = ::boost::sml::event<ProceedeSequence<Result>>;

/* ============================================================ Actions =========================================================== */

/**
 * @brief Helper function generating a lambda-expression-action that executes @p action
 *    and queues @ref ProceedeSequence event depending on the action's result
 * 
 * @tparam Result 
 *    result type of the action (must be convertible to boolean)
 * @tparam T...
 *    type of arguments to call @p action with
 * @param action 
 *    action to be run
 */
template<ProceedeResult Result, typename ... T>
constexpr auto proceede_action(Result(*action)(T...), T... t) ;

/**
 * @brief Helper function generating a lambda-expression-action that executes @p action
 *    and queues @ref ProceedeSequence event depending on the action's result
 * 
 * @tparam Impl 
 *    class implementing the action to be run
 * @tparam Result 
 *    result type of the action (must be convertible to boolean)
 * @tparam T...
 *    type of arguments to call @p action with
 * @param action 
 *    action to be run
 */
template<typename Impl, ProceedeResult Result, typename ... T>
constexpr auto proceede_action(Result(Impl::*action)(), T... t);

/**
 * @brief Helper function generating a lambda-expression-action that executes @p action
 *    and queues @ref ProceedeSequence event depending on the action's result
 * 
 * @tparam Result 
 *    result type of the action (must be convertible to boolean)
 * @tparam Callable 
 *    type of the callable object
 * @tparam T...
 *    type of arguments to call @p action with
 * @param action 
 *    action to be run (callacble objecct)
 */
template<ProceedeResult Result, typename Callable, typename ... T>
    requires std::is_same_v<Result, std::invoke_result<Callable(T...)>>
constexpr auto proceede_action(Callable action, T... t);

/**
 * @brief Helper lambda-expresion-guard verifying whether the last action in sequence
 *    has been sucesfully executed
 * @tparam Result 
 *    type returned by the action
 */
template<ProceedeResult Result>
constexpr auto is_sequence_action_success = [](const ProceedeSequence<Result> &proceede) {
    return bool(proceede.result);
};

/* ================================================================================================================================ */

} // End namespace boost::sml

/* ==================================================== Implementation includes =================================================== */

#include "boost/sml/utils/dsl/sequence/impl/sequence.hpp"

/* ================================================================================================================================ */

#endif
