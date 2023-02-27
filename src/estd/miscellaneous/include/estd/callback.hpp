/* ============================================================================================================================ *//**
 * @file       callback.hpp
 * @author     ARM Limited
 * @maintainer Krzysztof Pierczyk (kpierczyk@emka-project.com.pl)
 * @date       Tuesday, 30th August 2022 3:16:57 pm
 * @modified   Tuesday, 28th February 2023 12:24:29 am
 * @project    SHARK_KB
 * @brief      Modificationn of the mbed::callback class tempalte originally from ARM Mbed
 * @details 
 * 
 *   Configuration of the module:
 * 
 *       CONF_CALLBACK_NONTRIVIAL - support storing non-trivial function objects
 *       CONF_CALLBACK_COMPARABLE - support memcmp comparing stored objects (requires zero padding)
 * 
 * @copyright Copyright (c) 2006-2019 ARM Limited
 * @license
 * 
 *     mbed Microcontroller Library
 *     Copyright (c) 2006-2019 ARM Limited
 *     SPDX-License-Identifier: Apache-2.0
 *     
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *     
 *         http://www.apache.org/licenses/LICENSE-2.0
 *     
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 * 
 */// ============================================================================================================================= */

#ifndef __ESTD_CALLBACK_H__
#define __ESTD_CALLBACK_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#include <cstring>
#include <type_traits>
#include <cstdint>
// Private includes
#include "estd/callback/callback.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ========================================================== Definitions ========================================================= */

/** 
 * @brief Callback class based on template specialization
 */
template <typename Signature>
class callback;

/**
 * @brief callback class based on template specialization
 */
template <typename R, typename... ArgTs>
class callback<R(ArgTs...)> : private estd::details::callback::CallbackBase {

public: /* ---------------------------------------------------- Public types ----------------------------------------------------- */

    /// Result type of the callback
    using result_type = R;

public: /* ---------------------------------------------------- Public ctors ----------------------------------------------------- */

    /** 
     * @brief Create an empty callback
     */
    callback() noexcept : CallbackBase(nullptr) { }

    /** 
     * @brief Create an empty callback
     */
    callback(std::nullptr_t) noexcept : callback() { }

    #if CONF_CALLBACK_NONTRIVIAL

    /** 
     * @brief Copy a callback
     * @param other 
     *     The callback to copy
     */
    callback(const callback &other) : CallbackBase() {
        copy(other);
    }

    /** 
     * @brief Move a callback
     * @details Move constructor exists to ensure that it gets selected in 
     *    preference to the universal constructor form.
     * 
     * @param other 
     *    The callback to move
     */
    callback(callback &&other) : CallbackBase() {
        copy(other);
    }

    #else

    // Use default copy-constructor
    callback(const callback &other) = default;
    // Use default move-constructor
    callback(callback &&other) = default;

    #endif

    /** 
     * @brief Create a callback with a member function
     * 
     * @param obj
     *    Pointer to object to invoke member function on
     * @param method
     *    Member function to attach
     */
    template<typename Obj, typename Method,
        typename std::enable_if_t<std::is_invocable_r<R, Method, Obj, ArgTs...>::value, int> = 0>
    callback(Obj obj, Method method) : CallbackBase() {
        generate([obj, method](ArgTs... args) {
            return estd::details::callback::invoke_r<R>(method, obj, std::forward<ArgTs>(args)...);
        });
    }

    /** 
     * @brief Create a callback with a static function and bound pointer 
     * 
     * @param func 
     *    Static function to attach
     * @param arg 
     *    Pointer argument to function
     */
    template<typename Fn, typename BoundArg,
        typename std::enable_if_t<std::is_invocable_r<R, Fn, BoundArg, ArgTs...>::value, int> = 0>
    callback(Fn func, BoundArg arg) : CallbackBase()
    {
        generate([func, arg](ArgTs... args) {
            return estd::details::callback::invoke_r<R>(func, arg, std::forward<ArgTs>(args)...);
        });
    }

    /** 
     * @brief Create a callback with a function object 
     * 
     * @param f 
     *    Function object to attach
     * 
     * @note The function object is limited to a a few words of storage
     */
    template <typename F,
        typename std::enable_if_t<
            !estd::details::callback::can_null_check<F>::value &&
            std::is_invocable_r<R, F, ArgTs...>::value, int> = 0>
    callback(F f) : CallbackBase() {
        static_assert(std::is_copy_constructible<F>::value, "callback F must be CopyConstructible");
        generate(std::move(f));
    }

    /** 
     * @brief Create a callback with a function pointer 
     * 
     * @param f 
     *    Function pointer to attach
     */
    template <typename F,
        typename std::enable_if_t<
            estd::details::callback::can_null_check<F>::value &&
            std::is_invocable_r<R, F, ArgTs...>::value, int> = 0>
    callback(F f) : CallbackBase() {
        static_assert(std::is_copy_constructible<F>::value, "callback F must be CopyConstructible");
        if (!f) {
            clear();
        } else {
            generate(std::move(f));
        }
    }

    #if CONF_CALLBACK_NONTRIVIAL

    /// Destroys a callback
    ~callback() {
        destroy();
    }

    #else

    /// Destroys a callback
    ~callback() = default;
    
    #endif

public: /* --------------------------------------------------- Public methods ---------------------------------------------------- */

    /// Swap a callback
    void swap(callback &that) noexcept {
        #if CONF_CALLBACK_NONTRIVIAL
        if (this != &that) {
            callback temp(std::move(*this));
            *this = std::move(that);
            that = std::move(temp);
        }
        #else
        CallbackBase::swap(that);
        #endif
    }

    #if CONF_CALLBACK_NONTRIVIAL

    /// Assign a callback
    callback &operator=(const callback &that) {
        
        /**
         * @note C++ standard says to use swap, but that's overkill with no exceptions
         */
        
        if (this != &that) {
            destroy();
            copy(that);
        }

        return *this;
    }

    /// Assign a callback
    callback &operator=(callback &&that) {
        if (this != &that) {
            destroy();
            copy(that);
        }
        return *this;
    }
    
    #else

    // Use default copy-asignment
    callback &operator=(const callback &that) = default;
    // Use default move-asignment
    callback &operator=(callback &&that) = default;

    #endif

    /**
     * @brief Assign a callback
     * 
     * @note C++ std::function lacks the is_same restriction here, which would mean non-const lvalue references hit this,
     *    rather than the normal copy assignment (`F &&` is a better match for `callback &` than `const callback &`).
     *    Wouldn't matter if both used the swap form, but having cut it down, for code size want to ensure we don't use this
     *    instead of copy assignment. (If nontrivial disabled, definitely want to use the default copy assignment, and
     *    if nontrivial enabled, we know this doesn't handle self-assignment).
     *    *INDENT-OFF*
     */
    template <typename F,
        typename = std::enable_if_t<
            std::is_invocable_r<R, F, ArgTs...>::value &&
            !std::is_same<std::remove_cvref_t<F>, callback>::value>>
    callback &operator=(F &&f) {
        
        /**
         * @note C++ standard says to use swap, but that's overkill with no exceptions
         */
        
        this->~callback();
        new (this) callback(std::forward<F>(f));
        return *this;
    }

    /// Assigns callback
    template <typename F>
    callback &operator=(std::reference_wrapper<F> f) noexcept {
        
        /**
         * @note C++ standard says to use swap, but that's overkill with no exceptions
         */

        this->~callback();
        new (this) callback(f);
        return *this;
    }

    /// Empty a callback
    callback &operator=(std::nullptr_t) noexcept {
        destroy();
        clear();
        return *this;
    }

    /// Call the attached function
    R call(ArgTs... args) const {
        assert_param(bool(*this));
        auto op_call = reinterpret_cast<call_type *>(call_fn());
        return op_call(this, args...);
    }

    /// Call the attached function
    R operator()(ArgTs... args) const {
        return call(args...);
    }

    /// Test if function has been assigned
    explicit operator bool() const noexcept {
        return control();
    }

    #if CONF_CALLBACK_COMPARABLE

    /**
     * @brief Test for equality
     *
     * @note This only compares stored objects byte-wise using memcmp
     *       after checking that they're the same type. It does *not* use
     *       any equality operator defined for the class.
     *
     * @note This is an extension compared to std::function, and supporting
     *       it requires extra code even if the comparison is never used.
     *       Avoid using this operator if possible, so that the option
     *       `platform.callback-comparable` can be turned off to save ROM.
     */
    friend bool operator==(const callback &l, const callback &r) noexcept {
        
        // Type of stored object differs
        if (l.control() != r.control()) {
            return false;
        }

        /* Both must be empty, as we checked the types match. Do not
         * check storage in this case - this simplifies clear(), and
         * clears are far more estd than callback comparison.
         */
        if (!l)
            return true;

        return memcmp(&l._storage, &r._storage, sizeof(Store)) == 0;
    }
    
    #endif

    /// Test for emptiness
    friend bool operator==(const callback &f, std::nullptr_t) noexcept {
        return !f;
    }

    /// Test for emptiness
    friend bool operator==(std::nullptr_t, const callback &f) noexcept {
        return !f;
    }

    #if CONF_CALLBACK_COMPARABLE

    /** 
     * @brief Test for inequality
     * @see operator==(const callback &l, const callback &r)
     */
    friend bool operator!=(const callback &l, const callback &r) noexcept {
        return !(l == r);
    }

    #endif

    /// Test for non-emptiness
    friend bool operator!=(const callback &f, std::nullptr_t) noexcept {
        return bool(f);
    }

    /// Test for non-emptiness
    friend bool operator!=(std::nullptr_t, const callback &f) noexcept {
        return bool(f);
    }

    /** 
     * @brief Static thunk for passing as C-style function
     * 
     * @param func
     *    callback to call passed as void pointer
     * @param args
     *    Arguments to be called with function func
     * 
     * @returns the value as determined by func which is of type and determined
     *    by the signature of func
     */
    static R thunk(void *func, ArgTs... args) {
        return static_cast<callback *>(func)->call(args...);
    }

public: /* --------------------------------------------------- Private types ----------------------------------------------------- */

    // Signature of the callback
    using call_type = R(const CallbackBase *, ArgTs...);

public: /* -------------------------------------------------- Private methods ---------------------------------------------------- */

    /**
     * @brief Generate operations for function object
     * @details Storage assumed to be uninitialised - destructor should have already been called if it 
     *    was previously used. When generating, function object should always be moved
     */
    template <typename F, typename = std::enable_if_t<!std::is_lvalue_reference<F>::value>>
    void generate(F &&f) {

        #ifndef __ICCARM__ /* This assert fails on IAR for unknown reason */
        static_assert(std::is_same<decltype(target_call<F>), call_type>::value, "Call type mismatch");
        #endif
        static_assert(sizeof(callback) == sizeof(CallbackBase), "callback should be same size as CallbackBase");
        static_assert(std::is_trivially_copyable<CallbackBase>::value, "CallbackBase expected to be TriviallyCopyable");

        // Set the control pointer
        #if CONF_CALLBACK_NONTRIVIAL
        // Generates one static ops for each <F,R,ArgTs...> tuple
        // But the functions used for copy/move/dtor depend only on F, and even then only if non-trivial.
        // `call` is type-erased - we cast from our call_type to the void (*)(void) in CallbackBase
        // This should be a ROMmed constant table, but formally it can't be constexpr because of the reinterpret_cast :(
        static const ops ops = {
            reinterpret_cast<void (*)()>(target_call<F>),
            std::is_trivially_copy_constructible<F>::value ? trivial_target_copy : target_copy<F>,
            std::is_trivially_destructible<F>::value ? trivial_target_dtor : target_dtor<F>,
        };
        _ops = &ops;
        #else
        // Avoid the need for the const ops table - just one function pointer in the callback itself
        _call = reinterpret_cast<void (*)()>(target_call<F>);
        static_assert(std::is_trivially_copyable<F>::value, "F must be TriviallyCopyable. Turn on Mbed configuration option 'platform.callback-nontrivial' to use more complex function objects");
        static_assert(std::is_trivially_copyable<callback>::value, "callback expected to be TriviallyCopyable");
        #endif

        // Move the functor into storage
        static_assert(sizeof(F) <= sizeof(Store) && alignof(F) <= alignof(Store),
                      "Type F must not exceed the size of the callback class");
        new (&_storage) F(std::move(f));

        #if CONF_CALLBACK_COMPARABLE
        // Zero out any padding - required for callback-to-callback comparisons.
        if (sizeof(F) < sizeof(Store)) {
            std::memset(reinterpret_cast<char *>(&_storage) + sizeof(F), 0, sizeof(Store) - sizeof(F));
        }
        #endif
    }

    /// Target call routine - custom needed for each <F,R,ArgTs...> tuple
    template <typename F>
    static R target_call(const CallbackBase *p, ArgTs... args) {
        // Need for const_cast here correlates to a std::function bug - see P0045 and N4159
        F &f = const_cast<F &>(reinterpret_cast<const F &>(p->_storage));
        return estd::details::callback::invoke_r<R>(f, std::forward<ArgTs>(args)...);
    }
};

/* ====================================================== Auxiliary functions ===================================================== */

/// Swaps callbacks
template <typename R, typename... ArgTs>
void swap(callback<R(ArgTs...)> &lhs, callback<R(ArgTs...)> &rhs) noexcept {
    lhs.swap(rhs);
}

/** 
 * @brief Create a callback class with type inferred from the arguments
 *
 * @param func 
 *    Static function to attach
 * @returns 
 *    callback with inferred type
 */
template <typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(R(*func)(ArgTs...) = nullptr) noexcept {
    return callback<R(ArgTs...)>(func);
}

/** 
 * @brief Create a callback class with type inferred from the arguments
 * 
 * @param func 
 *    Static function to attach
 * @returns 
 *    callback with inferred type
 */
template <typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(const callback<R(ArgTs...)> &func) {
    return callback<R(ArgTs...)>(func);
}

/** 
 * @brief Create a callback class with type inferred from the arguments
 * 
 * @param func 
 *    Static function to attach
 * @return 
 *    callback with inferred type
 */
template <typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(callback<R(ArgTs...)> &&func) noexcept {
    return callback<R(ArgTs...)>(std::move(func));
}

/** 
 * @brief Create a callback class with type inferred from the arguments
 * 
 * @param obj 
 *    Optional pointer to object to bind to function
 * @param method 
 *    Member function to attach
 * @return 
 *    callback with inferred type
 */
template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(U *obj, R(T::*method)(ArgTs...)) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(U *obj, R(T::*method)(ArgTs...) &) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(const U *obj, R(T::*method)(ArgTs...) const) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(const U *obj, R(T::*method)(ArgTs...) const &) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(volatile U *obj, R(T::*method)(ArgTs...) volatile) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(volatile U *obj, R(T::*method)(ArgTs...) volatile &) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(const volatile U *obj, R(T::*method)(ArgTs...) const volatile) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

template<typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(const volatile U *obj, R(T::*method)(ArgTs...) const volatile &) noexcept {
    return callback<R(ArgTs...)>(obj, method);
}

/** 
 * @brief Create a callback class with type inferred from the arguments
 * 
 * @param func 
 *    Static function to attach
 * @param arg 
 *    Pointer argument to function
 * @return 
 *    callback with inferred type
 */
template <typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(R(*func)(T *, ArgTs...), U *arg) noexcept {
    return callback<R(ArgTs...)>(func, arg);
}

template <typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(R(*func)(const T *, ArgTs...), const U *arg) noexcept {
    return callback<R(ArgTs...)>(func, arg);
}

template <typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(R(*func)(volatile T *, ArgTs...), volatile U *arg) noexcept {
    return callback<R(ArgTs...)>(func, arg);
}

template <typename T, typename U, typename R, typename... ArgTs>
callback<R(ArgTs...)> callback(R(*func)(const volatile T *, ArgTs...), const volatile U *arg) noexcept {
    return callback<R(ArgTs...)>(func, arg);
}

/** 
 * @brief Create a Create a callback class with type inferred from the arguments
 * 
 * @param f
 *    Function object to attach
 * 
 * @note The function object is limited to a single word of storage
 */
template <typename F>
callback<estd::details::callback::unqualify_fn_t<estd::details::callback::member_type_t<decltype(&std::remove_cvref_t<F>::operator())>>>
callback(F &&f) {
    return callback<estd::details::callback::unqualify_fn_t<estd::details::callback::member_type_t<decltype(&std::remove_cvref_t<F>::operator())>>>(std::forward<F>(f));
}

/* ======================================================= Deduction guides ======================================================= */

#if __cplusplus >= 201703 || __cpp_deduction_guides >= 201703

template <typename R, typename... Args>
callback(R(*)(Args...)) -> callback<R(Args...)>;
template <typename F>
callback(F) -> callback<estd::details::callback::unqualify_fn_t<estd::details::callback::member_type_t<decltype(&F::operator())>>>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(U *obj, R(T::*method)(ArgTs...)) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(U *obj, R(T::*method)(ArgTs...) &) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(const U *obj, R(T::*method)(ArgTs...) const) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(const U *obj, R(T::*method)(ArgTs...) const &) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(volatile U *obj, R(T::*method)(ArgTs...) volatile) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(volatile U *obj, R(T::*method)(ArgTs...) volatile &) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(const volatile U *obj, R(T::*method)(ArgTs...) const volatile) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(const volatile U *obj, R(T::*method)(ArgTs...) const volatile &) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(R(*func)(T *, ArgTs...), U *arg) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(R(*func)(const T *, ArgTs...), const U *arg) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(R(*func)(volatile T *, ArgTs...), volatile U *arg) -> callback<R(ArgTs...)>;
template <typename T, typename U, typename R, typename... ArgTs>
callback(R(*func)(const volatile T *, ArgTs...), const volatile U *arg) -> callback<R(ArgTs...)>;

#endif

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif