/** ==================================================================================================================================
 * @file       namedtuple.hpp
 * @author     Krzysztof Jusiak
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 14th February 2022 11:27:10 pm
 * @modified   Tuesday, 15th February 2022 11:34:03 pm
 * @project    cpp-utils
 * @brief       Implementation of the namedtuple
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * @source https://godbolt.org/z/4889PqPGb
 * ================================================================================================================================ */

#ifndef __ESTD_NAMEDTUPLE_IMPL_NAMEDTUPLE_H__
#define __ESTD_NAMEDTUPLE_IMPL_NAMEDTUPLE_H__

/* =========================================================== Includes =========================================================== */

#include <sstream>
#include "estl/namedtuple.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estl {

/* ============================================================== Arg ============================================================= */

template <estd::fixed_string Name, typename TValue>
template <typename T>
constexpr auto named_arg<Name, TValue>::operator=(const T& t) const {
    return named_arg<Name, T>{ .value = t };
}


template<estd::fixed_string Name, class TValue>
constexpr decltype(auto) get(named_arg<Name, TValue>& t) {
    return (t.value);    
}


template<estd::fixed_string Name, class TValue>
constexpr decltype(auto) get(const named_arg<Name, TValue>& t) {
    return (t.value);    
}


template <estd::fixed_string Name>
constexpr auto operator""_t() {
    return named_arg<Name, named_any>{};
}

/* ============================================================== named_any ============================================================= */

template <typename T>
named_any::named_any(const T& a) :
    std::any{a},
    print{ 
        [](std::ostream& os, const std::any& a) -> std::ostream& {

            // If value can be named_any-casted, just use it
            if constexpr (requires { os << std::any_cast<T>(a); }) {
                os << std::any_cast<T>(a);

            // Else, if value is a range whose elements can be named_any-casted, just use it
            } else if constexpr (
                requires {
                    std::begin(std::any_cast<T>(a));
                    std::end(std::any_cast<T>(a));
            }) {
                auto obj = std::any_cast<T>(a);
                std::copy(std::begin(obj), std::end(obj), std::experimental::make_ostream_joiner(os, ','));
            
            // Otherwise, use name of the value
            } else {
                os << a.type().name();
            }
            
            return os;
        }
    }
{}

template <typename T>
constexpr named_any::operator T() const {
    return std::any_cast<T>(*this);
}


std::string named_any::to_string() const {
    std::stringstream stream;
    print(stream, *this);
    return stream.str();
}


std::ostream& operator<<(std::ostream& os, const named_any& a) {
    return a.print(os, a);
}

/* =========================================================== namedtupl ========================================================== */

namespace nt {

    template <estd::fixed_string Name, typename... Ts>
    constexpr namedtuple<Name, Ts...>::namedtuple(Ts... ts) : 
        Ts{ts}... 
    { }


    template <estd::fixed_string Name, typename... Ts>
    constexpr namedtuple<Name, Ts...>::namedtuple(auto... ts) : 
        Ts{ts}... 
    { }
    

    template <estd::fixed_string Name, typename... Ts>
    template <typename T, typename TArg>
        requires(not std::is_void_v<TArg>)
    constexpr const auto& namedtuple<Name, Ts...>::operator[](const T) const {
        return static_cast<const TArg&>(*this).value;
    }


    template <estd::fixed_string Name, typename... Ts>
    template <typename T, typename TArg>
        requires(not std::is_void_v<TArg>)
    constexpr auto& namedtuple<Name, Ts...>::operator[](const T) {
        return static_cast<TArg&>(*this).value;
    }


    template <estd::fixed_string Name, typename... Ts>
    auto& namedtuple<Name, Ts...>::assign(auto&&... ts) {

        // If all @p ts... are estl::named_arg, make advantage of it
        if constexpr ((
            requires {
                ts.name;
                ts.value;
            } and ...
        )) {
        
            ((static_cast<decltype(ts)&>(*this) = ts), ...);
        
        // Else, assign raw value
        } else {

            ((static_cast<Ts&>(*this).value = ts), ...);
            
        }

        return *this;
    }


    template <estd::fixed_string Name, typename... Ts>
    template <estd::fixed_string Name_>
    constexpr auto namedtuple<Name, Ts...>::get() -> decltype(estl::get<Name_>(*this)) {
        return estl::get<Name_>(*this);
    }


    template <estd::fixed_string Name, typename... Ts>
    template <estd::fixed_string Name_>
    constexpr const auto namedtuple<Name, Ts...>::get() const -> decltype(estl::get<Name_>(*this)) {
        return estl::get<Name_>(*this);
    }

    
    template <estd::fixed_string Name, typename... Ts>
    template <std::size_t N>
    constexpr auto& namedtuple<Name, Ts...>::get() {

        // Use in-place lambda to get IDs of the types hold by the tuple
        auto id_type = []<auto... Ns>(std::index_sequence<Ns...>) {
            return inherit<std::pair<std::integral_constant<std::size_t, Ns>, Ts>...>{ };
        } (std::make_index_sequence<sizeof...(Ts)>{});

        // Cast the tuple to the requested type
        return static_cast<
            typename decltype(
                details::map_lookup<void, std::integral_constant<std::size_t, N>, std::pair>(&id_type)
            )::second_type&
        >(*this);
    }


    template <estd::fixed_string Name, typename... Ts>
    template <std::size_t N>
    constexpr const auto& namedtuple<Name, Ts...>::get() const {

        // Use in-place lambda to get IDs of the types hold by the tuple
        auto id_type = []<auto... Ns>(std::index_sequence<Ns...>) {
            return inherit<std::pair<std::integral_constant<std::size_t, Ns>, Ts>...>{};
        } (std::make_index_sequence<sizeof...(Ts)>{});

        // Cast the tuple to the requested type
        return static_cast<
            const typename decltype(
                details::map_lookup<void, std::integral_constant<std::size_t, N>, std::pair>(&id_type)
            )::second_type&
        >(*this);
    }


    template <estd::fixed_string Name, typename... Ts>
    std::string namedtuple<Name, Ts...>::to_string() const {
        std::stringstream stream;
        stream << *this;
        return stream.str();
    }


    template <estd::fixed_string Name, typename... Ts>
    std::ostream& operator<<(std::ostream& os, const namedtuple<Name, Ts...>& nt) {

        // Print name of the tuple to the ostream
        os << std::string_view{Name} << '{';
        
        // Print content of the tuple to the ostream using in-place lambda
        [&]<auto... Ns>(std::index_sequence<Ns...>) {
            ((os << (Ns ? "," : "") << std::string_view{Ts::name} << ':'
                 << static_cast<const map_lookup<namedtuple<Name, Ts...>, Ts::name, void, named_arg>&>(nt).value
            ), ...);
        } (std::make_index_sequence<sizeof...(Ts)>{});

        // Close printing
        os << '}';
        
        return os;
    }

}

template <estd::fixed_string Name, typename... Ts>
constexpr auto namedtuple(Ts... ts) {
    return nt::namedtuple<Name, Ts...>(ts...);
}

namespace details  {

    /**
     * @brief Declaration of the helper meta-function testing whether the @tparam T type
     *    is brace-constructible with @tparam TArgs... parameters (uses SFINAE)
     * 
     * @tparam T 
     *    type to be examined
     * @tparam TArgs 
     *    types of construction arguments
     * @returns 
     *    @c std::true_type{} on match
     */
    template <class T, class... TArgs>
    decltype(void(T{std::declval<TArgs>()...}), std::true_type{}) test_is_braces_constructible(int);
        
    /**
     * @brief Declaration of the helper meta-function testing whether the @tparam T type
     *    is brace-constructible with @tparam TArgs... parameters (uses SFINAE)
     * 
     * @tparam T 
     *    type to be examined
     * @tparam TArgs 
     *    types of construction arguments
     * @returns 
     *    @c std::false_type{} on lack of match
     */
    template <class, class...>
    std::false_type test_is_braces_constructible(...);

    /**
     * @brief Helper alias template checking whether @tparam T is brac-constructible
     * 
     * @tparam T 
     *    type to be examined
     * @tparam TArgs 
     *    types of construction arguments 
     */
    template <class T, class... TArgs>
    using is_braces_constructible = decltype(test_is_braces_constructible<T, TArgs...>(0));

    /**
     * @brief @brief Helper type used to represent an arbitrary type
     */
    struct any_type {

        /**
         * @brief Non explicit conversion operator
         */
        template <class T>
        constexpr operator T();
        
    };
}


template <class T>
constexpr auto to_tuple(T object) noexcept {

    using any_type = details::any_type;

    // Helper alias for decayed version of @tparam T
    using type = std::decay_t<T>;

    // Convert 10-elements tuple
    if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4, p5, p6, p7, p8, p9, p10] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    // Convert 9-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4, p5, p6, p7, p8, p9] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9);
    // Convert 8-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4, p5, p6, p7, p8] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4, p5, p6, p7, p8);
    // Convert 7-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4, p5, p6, p7] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4, p5, p6, p7);
    // Convert 6-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4, p5, p6] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4, p5, p6);
    // Convert 5-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4, p5] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4, p5);
    // Convert 4-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3, p4] = std::forward<T>(object);
        return std::tuple(p1, p2, p3, p4);
    // Convert 3-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type, any_type>{}) {
        auto [p1, p2, p3] = std::forward<T>(object);
        return std::tuple(p1, p2, p3);
    // Convert 2-elements tuple
    } else if constexpr (details::is_braces_constructible<type, any_type, any_type>{}) {
        auto [p1, p2] = std::forward<T>(object);
        return std::tuple(p1, p2);
    // Convert 1-element tuple
    } else if constexpr (details::is_braces_constructible<type, any_type>{}) {
        auto [p1] = std::forward<T>(object);
        return std::tuple(p1);
    // Convert 0-element tuple
    } else {
        return std::tuple{};
    }
}

/* ================================================================================================================================ */

} // End namespace estl

/* ========================================================= std namespace ======================================================== */

namespace std {

    template<std::size_t N, estd::fixed_string Name, typename... Ts>
    const auto& get(estl::nt::namedtuple<Name, Ts...>&& nt) noexcept {
        return nt.template get<N>();
    }
    
}

/* ================================================================================================================================ */

#endif
