/* ============================================================================================================================ *//**
 * @file       callback.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 16th June 2021 11:11:55 am
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Header of the generic class template representing a reference to an arbitrary callable object
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UTILITIES_CALLBACK_H__
#define __UTILITIES_CALLBACK_H__

/* =========================================================== Includes =========================================================== */

#include "estd/concepts.hpp"

/* ========================================================== Declarations ======================================================== */

/**
 * @brief Declaration of the Callback template
 * @note It is used to instantiate template as Callback<ret(args...)>, instead Callback<ret, args...>
 */
template<typename>
class Callback;

/**
 * @brief Generic callback class template representing a reference to a functor or function
 * @tparam Return 
 *    callable's return type
 * @tparam Args 
 *    callable's arguments
 */
template<typename Return, typename... Args>
class Callback<Return(Args...)> {
    
public: /* ---------------------------------------------------- Public types ----------------------------------------------------- */

    // Signature of the callable
    using Type = Return(Args...);
    
private: /* --------------------------------------------------- Private types ---------------------------------------------------- */

    // Internal pointer type used to call an arbitrary callable
    using Ptr = Return(*)(void*, Args...);

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */
    
    /**
     * @brief Constructs an empty Callback with an empty reference
     */
    inline constexpr Callback() noexcept;

    /**
     * @brief Constructs a new Callback referencing a functor
     * @tparam Class 
     *    class of the object
     * @param obj 
     *    object to be referenced
     */
    template<typename Class>
        requires Concepts::Functor<Class, Return, Args...>
    inline constexpr Callback(Class &&obj) noexcept;

    /**
     * @brief Construct a new Callback referencing a function
     * @param fun 
     *    function to be referenced
     */
    inline constexpr Callback(Return (*fun)(Args...)) noexcept;

    /**
     * @brief Construct a new Callback copying reference from another object
     * @param other 
     *    reference to be copied
     */
    inline constexpr Callback(const Callback &other) noexcept;

public: /* -------------------------------------------------- Public operators ---------------------------------------------------- */

    /**
     * @brief Call operator of the Callback
     * @param args 
     *    arguments of the call
     * @returns 
     *    return value of the referenced callable
     */
    inline constexpr Return operator()(Args... args) const;

    /**
     * @brief Copies reference to a functor object to the Callback
     * @tparam Class 
     *    class of the object
     * @param obj 
     *    object to be referenced
     */
    template<typename Class>
    requires Concepts::Functor<Class, Return, Args...>
    inline constexpr Callback &operator=(Class &obj);

    /**
     * @brief Copies reference to a function to the Callback
     * @param fun 
     *    function to be referenced
     */
    inline constexpr Callback &operator=(Return (*fun)(Args...));

    /**
     * @brief Copies reference from another Callback
     * @param other 
     *    callback to be copied
     */
    inline constexpr Callback &operator=(const Callback &other);

public: /* --------------------------------------------------- Public methods ----------------------------------------------------- */

    /**
     * @returns 
     *   @c true if callback is set
     *   @c false if callback isn't set
     */
    inline constexpr bool isSet();

private: /* -------------------------------------------------- Private methods ---------------------------------------------------- */

    /**
     * @brief Expands functor's non-const operator() to the pointer to Result(void *, Args...) 
     *    function that can be internally called by the object with an object's pointer as argument
     * @tparam Class 
     *    class to be expapnded
     * @returns 
     *    pointer to Result(void *, Args...) function that casts first argument to the @tparam 
     *    Class and calls result with arguments
     */
    template<Concepts::Functor<Return, Args...> Class>
    static inline constexpr Ptr expandFunctorCall(Return (Class::*)(Args...));

    /**
     * @brief Expands functor's const operator() to the pointer to Result(void *, Args...) function
     *    that can be internally called by the object with an object's pointer as argument
     * @tparam Class 
     *    class to be expapnded
     * @returns 
     *    pointer to Result(void *, Args...) function that casts first argument to the @tparam 
     *    Class and calls result with arguments
     */
    template<Concepts::Functor<Return, Args...> Class>
    static inline constexpr Ptr expandFunctorCall(Return (Class::*)(Args...) const);

    /**
     * @brief Expands pointer to the function to the pointer to Result(void *, Args...) function
     *    that can be internally called by the object with a nullpointer as the first argument
     * @tparam Class 
     *    class to be expapnded
     * @returns 
     *    pointer to Result(void *, Args...) function that ignores the first argument and calls
     *    expanded function with given arguments
     */
    static inline constexpr Ptr expandFunctionCall();

private: /* ------------------------------------------------- Private variables --------------------------------------------------- */

    // Pointer to the functor object
    void* self;
    // Pointer to the actual callable function/method
    Ptr function;

};

/* ================================================================================================================================ */

#endif

/* ==================================================== Implementation includes =================================================== */

#include "callback/impl/callback.hpp"

/* ================================================================================================================================ */