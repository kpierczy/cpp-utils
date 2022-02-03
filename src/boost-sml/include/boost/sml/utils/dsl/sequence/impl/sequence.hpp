/** ==================================================================================================================================
 * @file     sequence.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Saturday, 15th January 2022 1:44:31 pm
 * @modified Thursday, 3rd February 2022 12:31:08 pm
 * @project  Winder
 * @brief
 *    
 *    Helper DSL-type (Domain Specific Language) helpers modelling linear sequence of actions that may fail resuling
 *    in processing of the predefined event
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __BOOST_SML_UTILS_DSL_SEQUENCE_IMPL_SEQUENCE_H__
#define __BOOST_SML_UTILS_DSL_SEQUENCE_IMPL_SEQUENCE_H__

/* =========================================================== Includes =========================================================== */

#include "boost/sml/utils/dsl/sequence.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace boost::sml {

/* ============================================================ Actions =========================================================== */

template<ProceedeResult Result, typename ... T>
constexpr auto proceede_action(Result(*action)(T...), T... t) {
    return [action, &t...] (boost::sml::back::process<ProceedeSequence<Result>> process) {
        process(ProceedeSequence<Result>{ .result = action(std::forward<T>(t)...) });
    };
}


template<typename Impl, ProceedeResult Result, typename ... T>
constexpr auto proceede_action(Result(Impl::*action)(), T... t) {
    return [action, &t...] (boost::sml::back::process<ProceedeSequence<Result>> process, Impl &impl) {
        process(ProceedeSequence<Result>{ .result = (impl.*action)(std::forward<T>(t)...) });
    };
}



template<ProceedeResult Result, typename Callable, typename ... T>
    requires std::is_same_v<Result, std::invoke_result<Callable(T...)>>
constexpr auto proceede_action(Callable action, T... t) {
    return [action, &t...] (boost::sml::back::process<ProceedeSequence<Result>> process) {
        process(ProceedeSequence<Result>{ .result = action(std::forward<T>(t)...) });
    };
}


template<ProceedeResult Result>
constexpr auto is_sequence_action_success = [](const ProceedeSequence<Result> &proceede) {
    return bool(proceede.result);
};

/* ================================================================================================================================ */

} // End namespace boost::sml

#endif
