/* ============================================================================================================================ *//**
 * @file       callback.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 16th June 2021 11:11:55 am
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Imlementation of the methods of the class template representing reference to an arbitrary callable object
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UTILITIES_CALLBACK_IMPL_CALLBACK_H__
#define __UTILITIES_CALLBACK_IMPL_CALLBACK_H__

/* =========================================================== Includes =========================================================== */

#include "callback.hpp"
#include "callback/impl/callback_priv.hpp"

/* ====================================================== Public constructors ===================================================== */

template<typename Return, typename... Args>
constexpr Callback<Return(Args...)>::Callback() noexcept : 
    self(nullptr), function(nullptr)
{ }


template<typename Return, typename... Args>
template<typename Class>
    requires Concepts::Functor<Class, Return, Args...>
constexpr Callback<Return(Args...)>::Callback(Class &&obj) noexcept {
    *this = obj;
}


template<typename Return, typename... Args>
constexpr Callback<Return(Args...)>::Callback(Return (*fun)(Args...)) noexcept { 
    *this = fun;
}


template<typename Return, typename... Args>
constexpr Callback<Return(Args...)>::Callback(const Callback &other) noexcept {
    *this = other;
}

/* ======================================================= Public operators ======================================================= */

template<typename Return, typename... Args>
constexpr Return Callback<Return(Args...)>::operator()(Args... args) const {
    return function(self, std::forward<Args>(args)...);
}


template<typename Return, typename... Args>
template<typename Class>
requires Concepts::Functor<Class, Return, Args...>
constexpr Callback<Return(Args...)> &Callback<Return(Args...)>::operator=(Class &obj) {
    self = &obj;
    function = expandFunctorCall<Class>(&Class::operator());
    return *this;
}


template<typename Return, typename... Args>
constexpr Callback<Return(Args...)> &Callback<Return(Args...)>::operator=(Return (*fun)(Args...)) {
    self = reinterpret_cast<void*>(fun);
    function = expandFunctionCall();
    return *this;
}


template<typename Return, typename... Args>
constexpr Callback<Return(Args...)> &Callback<Return(Args...)>::operator=(const Callback &other) {
    self = other.self;
    function = other.function;
    return *this;
}

/* ======================================================== Public methods ======================================================== */

template<typename Return, typename... Args>
constexpr bool Callback<Return(Args...)>::isSet() {
    return function != nullptr;
}

/* ================================================================================================================================ */

#endif
