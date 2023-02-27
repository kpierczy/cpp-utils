/* ============================================================================================================================ *//**
 * @file       callback.hpp
 * @author     ARM Limited
 * @maintainer Krzysztof Pierczyk (kpierczyk@emka-project.com.pl)
 * @date       Tuesday, 30th August 2022 3:16:57 pm
 * @modified   Tuesday, 28th February 2023 12:25:09 am
 * @project    SHARK_KB
 * @brief      Modificationn of the mbed::callback class tempalte originally from ARM Mbed (details)
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

#ifndef __ESTD_CALLBACK_CALLBACK_H__
#define __ESTD_CALLBACK_CALLBACK_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#include <type_traits>
#include <cstring>
#include <functional>

/* ========================================================== Namespaces ========================================================== */

namespace estd::details::callback {

/* ======================================================= Auxiliary traits ======================================================= */

namespace details {

    template <typename T>
    struct member_type { };

    template <typename M, class C>
    struct member_type<M C::*> : std::type_identity<M> { };

}

/// Convert pointer-to-member type to member type
template <typename T>
using member_type_t =
    typename details::member_type<T>::type;


namespace details {

    template <typename T>
    struct unqualify_fn { };

    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...)> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) &> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const &> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) volatile> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) volatile &> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const volatile> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const volatile &> : std::type_identity<R(Args...)> { };

    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) & noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const & noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) volatile noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) volatile & noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const volatile noexcept> : std::type_identity<R(Args...)> { };
    template <typename R, typename... Args>
    struct unqualify_fn<R(Args...) const volatile & noexcept> : std::type_identity<R(Args...)> { };

}

/**
 * @brief Removes cv-qualifiers and lvalue ref-qualifiers
 * @note Not rvalue - we store the function object, so are always going
 *    to call it on an lvalue
 */
template <typename T>
using unqualify_fn_t =
    typename details::unqualify_fn<T>::type;

/**
 * @brief Wrapper around std::invoke enabled for non-void return callables
 */
template <typename R, typename F, typename... Args,
    typename std::enable_if_t<!std::is_void<R>::value, int> = 0>
R invoke_r(F&& f, Args&&... args) {
    return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
}

/**
 * @brief Wrapper around std::invoke enabled for void return callables
 */
template <typename R, typename F, typename... Args,
    typename std::enable_if_t<std::is_void<R>::value, int> = 0>
R invoke_r(F&& f, Args&&... args) {
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
}

/**
 * @brief Auxiliary trait checking whether type is callable
 */
template<typename F>
struct can_null_check :
    std::disjunction<
        std::is_function<std::remove_pointer_t<F>>,
        std::is_member_pointer<F>
    > {
};

/* ============================================================= Base ============================================================= */

/**
 * @brief Base class for the @ref callback type
 * 
 */
struct [[gnu::may_alias]] CallbackBase {
    
public: /* ---------------------------------------------------- Public types ----------------------------------------------------- */

    /**
     * @note Storage is sufficient to hold at least a pointer to member
     *    function, and an object pointer.
     */
    struct _model_function_object {
        struct _class;
        void (_class::*_methodfunc)(int);
        void *obj;
    };

    /* Notes on the [[gnu::may_alias]] attribute here.
     *
     * The CallbackBase::Store is subject to aliasing problems if ever copied via a trivial copy.
     * This issue is described here:
     *
     *    https://answers.launchpad.net/gcc-arm-embedded/+question/686870/+index
     *    http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0593r5.html
     *
     * The paper p0593 proposes to solve the problem via a language Defect Report, which would make this
     * code valid - it would become legal to copy a trivial object into char array storage. (But not
     * aligned_storage_t, as of version 5 - I've suggested a revision).
     *
     * Real-life problems have only been seen in GCC when the code used aligned_storage_t.
     *
     * The libstdc++ implementation of std::function uses the [[gnu::may_alias]] attribute itself to avoid
     * problems when it swaps locally-stored functors; we need it for copy-assignment too.
     *
     * It appears [[gnu::may_alias]] doesn't work through composition - it's not sufficent to mark just the
     * `Store` type, we have to mark the whole `callback` if we're going to let the compiler
     * implicitly define the trivial copy for it. This potentially could lead to an issue if a `callback`
     * was used in a trivially-copyable type itself, but this seems an unlikely use case. The p0593r5
     * change would, if correctly implemented, work in composition.
     *
     * Although, to further increase the confusion, it appears that using a character array does work
     * fine without may_alias, while aligned_storage_t does not. I've seen a suggestion that GCC 8
     * may have implicit "may_alias" on character arrays, rendering the attribute in std::function
     * and here redundant on current GCC:
     *
     *    https://gcc.gnu.org/ml/gcc-help/2017-06/msg00102.html
     *
     * For maximum safety, this version now avoids aligned_storage_t, and also has the possibly-redundant
     * attribute at each level.
     *
     * C++17 says that implementations ignore unrecognized attributes, and IAR+clang comply with this
     * even in C++14 mode, so we add [[gnu::may_alias]] unconditionally.
     */
    struct alignas(_model_function_object) [[gnu::may_alias]] Store {
        char data[sizeof(_model_function_object)];
    };

public: /* --------------------------------------------------- Public members ---------------------------------------------------- */

    // callback storage
    Store _storage;

    #if CONF_CALLBACK_NONTRIVIAL

    // Dynamically dispatched operations
    const struct ops {
        void (*call)(); // type-erased function pointer
        void (*copy)(Store &, const Store &);
        void (*dtor)(Store &);
    } *_ops;

    // Control
    using Control = const ops *;

    // Construct as empty
    CallbackBase(std::nullptr_t) noexcept : _ops(nullptr) { }

    #else

    // Type-erased function pointer
    void (*_call)();

    // Control
    using Control = void(*)();

    // Construct as empty
    CallbackBase(std::nullptr_t) noexcept : _call(nullptr) { }
    
    #endif

public: /* ---------------------------------------------------- Public ctors ----------------------------------------------------- */

    // Default constructor - no initialization
    CallbackBase() = default;

public: /* --------------------------------------------------- Public methods ---------------------------------------------------- */

    Control &control() {
        #if CONF_CALLBACK_NONTRIVIAL
        return _ops;
        #else
        return _call;
        #endif
    }

    const Control &control() const {
        #if CONF_CALLBACK_NONTRIVIAL
        return _ops;
        #else
        return _call;
        #endif
    }

    auto call_fn() const {
        #if CONF_CALLBACK_NONTRIVIAL
        return _ops->call;
        #else
        return _call;
        #endif
    }

    /**
     * @brief Clear to empty - does not destroy
     * @details For copy efficiency we only zero out the operation pointer
     *     Therefore storage is undefined when we are empty.
     *     callback-to-callback comparison operator has to deal with this,
     *     but such comparisons are rare. Comparisons to empty are efficient.
     */
    void clear() noexcept {
        control() = nullptr;
    }

    #if CONF_CALLBACK_NONTRIVIAL
    
    /**
     * @brief Copy from another CallbackBase - assumes we are uninitialised
     */
    void copy(const CallbackBase &other) {
        _ops = other._ops;
        if (_ops) {
            _ops->copy(_storage, other._storage);
        }
    }
    
    #else

    /// Swaps callback objects
    void swap(CallbackBase &other) noexcept {
        std::swap(_storage, other._storage);
        std::swap(_call, other._call);
    }
    
    #endif

    /**
     * @brief Destroy anything we hold - does not reset, so we are in undefined state afterwards.
     * @note Must be followed by copy, move, reset, or destruction of the CallbackBase
     */
    void destroy() {
        #if CONF_CALLBACK_NONTRIVIAL
        if (_ops) {
            _ops->dtor(_storage);
        }
        #endif
    }

    #if CONF_CALLBACK_NONTRIVIAL

    /// Copy construct F into storage
    template <typename F>
    static void target_copy(Store &d, const Store &p) {
        const F &f = reinterpret_cast<const F &>(p);
        new (&d) F(f);
    }

    /// Destroy F in storage
    template <typename F>
    static void target_dtor(Store &p) {
        F &f = reinterpret_cast<F &>(p);
        f.~F();
    }

    /// Trivial copy construction into storage
    static void trivial_target_copy(Store &d, const Store &p) noexcept {
        std::memcpy(&d, &p, sizeof d);
    }

    /// Trivial destruction in storage
    static void trivial_target_dtor(Store &p) noexcept { }
    
    #endif
};

/* ================================================================================================================================ */

} // End namespace estd::details::callback

/* ================================================================================================================================ */

#endif