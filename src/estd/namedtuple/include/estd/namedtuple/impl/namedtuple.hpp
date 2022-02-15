/** ==================================================================================================================================
 * @file     namedtuple.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 14th February 2022 11:27:10 pm
 * @modified Tuesday, 15th February 2022 1:38:53 am
 * @project  cpp-utils
 * @brief
 *    
 *    Implementation of the namedtuple
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * @source https://godbolt.org/z/4889PqPGb
 * ================================================================================================================================ */

#ifndef __ESTD_NAMEDTUPLE_IMPL_NAMEDTUPLE_H__
#define __ESTD_NAMEDTUPLE_IMPL_NAMEDTUPLE_H__

/* =========================================================== Includes =========================================================== */

#include "estd/namedtuple.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================== Arg ============================================================= */

template <fixed_string Name, typename TValue>
template <typename T>
constexpr auto arg<Name, TValue>::operator=(const T& t) const {
    return arg<Name, T>{ .value = t };
}

/* ============================================================== any ============================================================= */

template <typename T>
any::any(const T& a) :
    std::any{a},
    print{ 
        [](std::ostream& os, const std::any& a) -> std::ostream& {

            // If value can be any-casted, just use it
            if constexpr (requires { os << std::any_cast<T>(a); }) {
                os << std::any_cast<T>(a);

            // Else, if value is a range whose elements can be any-casted, just use it
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
constexpr any::operator T() const {
    return std::any_cast<T>(*this);
}

std::ostream& operator<<(std::ostream& os, const any& a) {
    return a.print(os, a);
}

template <fixed_string Name>
constexpr auto operator""_t() {
    return arg<Name, any>{};
}

/* =========================================================== namedtupl ========================================================== */

namespace nt {

    template <fixed_string Name, typename... Ts>
    constexpr namedtuple<Name, Ts...>::namedtuple(Ts... ts) : 
        Ts{ts}... 
    { }


    template <fixed_string Name, typename... Ts>
    constexpr namedtuple<Name, Ts...>::namedtuple(auto... ts) : 
        Ts{ts}... 
    { }
    

    template <fixed_string Name, typename... Ts>
    template <typename T, typename TArg>
        requires(not std::is_void_v<TArg>)
    constexpr const auto& namedtuple<Name, Ts...>::operator[](const T) const {
        return static_cast<const TArg&>(*this).value;
    }


    template <fixed_string Name, typename... Ts>
    template <typename T, typename TArg>
        requires(not std::is_void_v<TArg>)
    constexpr auto& namedtuple<Name, Ts...>::operator[](const T) {
        return static_cast<TArg&>(*this).value;
    }


    template <fixed_string Name, typename... Ts>
    auto& namedtuple<Name, Ts...>::assign(auto&&... ts) {

        // If all @p ts... are estd::arg, make advantage of it
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


    template <fixed_string Name, typename... Ts>
    template <std::size_t N>
    auto& namedtuple<Name, Ts...>::get() {

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


    template <fixed_string Name, typename... Ts>
    template <std::size_t N>
    const auto& namedtuple<Name, Ts...>::get() const {

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


    template <fixed_string Name, typename... Ts>
    std::ostream& operator<<(std::ostream& os, const namedtuple<Name, Ts...>& nt) {

        // Print name of the tuple to the ostream
        os << std::string_view{Name} << '{';
        
        // Print content of the tuple to the ostream using in-place lambda
        [&]<auto... Ns>(std::index_sequence<Ns...>) {
            ((os << (Ns ? "," : "") << std::string_view{Ts::name} << ':'
                 << static_cast<const map_lookup<namedtuple<Name, Ts...>, Ts::name, void, arg>&>(nt).value
            ), ...);
        } (std::make_index_sequence<sizeof...(Ts)>{});

        // Close printing
        os << '}';
        
        return os;
    }

}

template <fixed_string Name, typename... Ts>
constexpr auto namedtuple(Ts... ts) {
    return nt::namedtuple<Name, Ts...>(ts...);
}

/* ================================================================================================================================ */

} // End namespace estd

/* ========================================================= std namespace ======================================================== */

namespace std {

    template<std::size_t N, estd::fixed_string Name, typename... Ts>
    const auto& get(estd::nt::namedtuple<Name, Ts...>&& nt) noexcept {
        return nt.template get<N>();
    }
    
}

/* ================================================================================================================================ */

#endif
