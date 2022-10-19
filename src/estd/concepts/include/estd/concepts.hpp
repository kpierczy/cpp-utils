/* ============================================================================================================================ *//**
 * @file       concepts.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 3rd February 2022 10:22:20 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief
 *    
 *    
 *    
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_CONCEPTS_H__
#define __ESTD_CONCEPTS_H__

/* =========================================================== Includes =========================================================== */

#include <utility>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* =========================================================== Functors =========================================================== */

/**
 * @brief Concept of the class defining an operator() method with given return
 *    type and arguments types
 * @tparam T 
 *    class to be tested
 * @tparam Return 
 *    operator's result typ to be sested
 * @tparam Args 
 *    operator's arguments typ to be sested
 * 
 * @deprecated Use @ref std::invocable instead
 * @note In C++20 [[deprecated]] attribute cannot be used along with concepts
 */
template<typename T, typename Return, typename ... Args>
concept functor = requires (T obj, Args ... args) {
    { obj(std::forward<Args>(args)...) } -> std::same_as<Return>;
};

/**
 * @brief Concept of the function returning a particular type
 * @tparam T 
 *    type to be tested
 * @tparam Return 
 *    operator's result typ to be sested
 * @tparam Args 
 *    operator's arguments typ to be sested
 */
template<typename T, typename Return, typename ... Args>
concept returning_function = requires (T fun, Args ... args) {
    std::is_function_v<T>;
    functor<T, Return, Args...>;
};

/* ========================================================== Inheritance ========================================================= */

namespace details
{
    template<template<typename...> typename Type, typename... Params>
    void to_base_specialization_of(const volatile Type<Params...>*);
}

/**
 * @brief Concept of the class derived from a specialization of the given template
 * @tparam T 
 *    class to be verified
 * @tparam Template 
 *    template to be compared against
 */
template<typename T, template<typename...> typename Template>
concept derived_from_specialization_of = 
    requires(T* t) { details::to_base_specialization_of<Template>(t); };

/* ====================================================== Types manipulation ====================================================== */

/**
 * @brief Concept of the type being any of the given list
 * @tparam T 
 *    class to be tested
 * @tparam Args 
 *    types to be tested against
 */
template<typename T, typename ... Args>
concept any_of = (std::same_as<T, Args> || ...);

/* ================================================================================================================================ */

} // End namespace estd

#endif
