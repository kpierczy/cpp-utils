/** ==================================================================================================================================
 * @file     callback_priv.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Wednesday, 16th June 2021 11:11:55 am
 * @modified Thursday, 3rd February 2022 11:50:22 am
 * @project  Winder
 * @brief
 *    
 *    Imlementation of the private functions related to the class template representing reference to an arbitrary callable object
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UTILITIES_CALLBACK_CALLBACK_PRIV_IMPL_H__
#define __UTILITIES_CALLBACK_CALLBACK_PRIV_IMPL_H__

/* =========================================================== Includes =========================================================== */

#include "callback.hpp"
#include <utility>

/* ========================================================== Definitions ========================================================= */

template<typename Return, typename... Args>
template<Concepts::Functor<Return, Args...> Class>
constexpr typename Callback<Return(Args...)>::Ptr 
Callback<Return(Args...)>::expandFunctorCall(Return (Class::*)(Args...)) {
    return [](void* object, Args... args) { 
        return (*reinterpret_cast<Class*>(object))(std::forward<Args>(args)...); 
    };
}

template<typename Return, typename... Args>
template<Concepts::Functor<Return, Args...> Class>
constexpr typename Callback<Return(Args...)>::Ptr 
Callback<Return(Args...)>::expandFunctorCall(Return (Class::*)(Args...) const) {
    return [](void* object, Args... args) { 
        return (*reinterpret_cast<Class*>(object))(std::forward<Args>(args)...); 
    };
}

template<typename Return, typename... Args>
constexpr typename Callback<Return(Args...)>::Ptr 
Callback<Return(Args...)>::expandFunctionCall() {
    return [](void* function, Args... args) { 
        return (*reinterpret_cast<Return(*)(Args...)>(function))(std::forward<Args>(args)...); 
    };
}

/* ================================================================================================================================ */

#endif
