/** ==================================================================================================================================
 * @file     namedtuple.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 14th February 2022 11:27:10 pm
 * @modified Tuesday, 15th February 2022 1:40:34 am
 * @project  cpp-utils
 * @brief
 *    
 *    
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * @source https://godbolt.org/z/4889PqPGb
 * ================================================================================================================================ */

#ifndef __ESTD_NAMEDTUPLE_H__
#define __ESTD_NAMEDTUPLE_H__

/* =========================================================== Includes =========================================================== */

#include <algorithm>
#include <any>
#include <experimental/iterator>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>
#include <tuple>
#include <vector>
#include "estd/fixed_string.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ============================================================== Arg ============================================================= */

/**
 * @brief Helper typename representing named argument
 * 
 * @tparam Name 
 *     name of the tuple's element
 * @tparam TValue 
 *     value of the argument
 */
template <fixed_string Name, typename TValue>
struct arg {
public:

    // Name of the argument
    static constexpr auto name = Name;

public:

    /**
     * @brief Copying operator
     * @tparam T 
     *    type of the copied value
     * @param t 
     *    copied value
     * @returns 
     *    a NEW arg object
     */
    template <typename T>
    [[nodiscard]] constexpr auto operator=(const T& t) const;

public:

    // Value of the argument
    TValue value{};
    
};

/**
 * @brief Helper UDL creating @ref arg from string
 * 
 * @tparam Name 
 * @return constexpr auto 
 */
template <fixed_string Name>
constexpr auto operator""_t();

/* ========================================================== map-lookup ========================================================== */

namespace details {

    template <typename TDefault, fixed_string, template <fixed_string, typename> typename>
    auto map_lookup(...) -> TDefault;
    template <typename, fixed_string TKey, template <fixed_string, typename> typename TArg, typename TValue>
    auto map_lookup(TArg<TKey, TValue>*) -> TArg<TKey, TValue>;

    template <typename TDefault, typename, template <typename, typename> typename>
    auto map_lookup(...) -> TDefault;
    template <typename, typename TKey, template <typename, typename> typename TArg, typename TValue>
    auto map_lookup(TArg<TKey, TValue>*) -> TArg<TKey, TValue>;
    
}

/**
 * @brief Helper trait aiming targeted types-casting
 * 
 * @tparam T 
 * @tparam TKey 
 * @tparam TDefault 
 * @tparam TArg 
 */
template <typename T, fixed_string TKey, typename TDefault, template <fixed_string, typename> typename TArg>
using map_lookup = decltype(details::map_lookup<TDefault, TKey, TArg>( static_cast<T*>(nullptr) ));

/* =========================================================== inheriter ========================================================== */

/**
 * @brief Helper template inheriting it's arguments
 * 
 * @tparam Ts 
 *    list of types to be inherited
 */
template <typename... Ts> struct inherit : Ts... {};

static_assert(std::is_same_v<void,                 map_lookup<inherit<arg<"price", double>, arg<"size", int>>, "unknown", void, arg>>);
static_assert(std::is_same_v<arg<"price", double>, map_lookup<inherit<arg<"price", double>, arg<"size", int>>, "price",   void, arg>>);
static_assert(std::is_same_v<arg<"size", int>,     map_lookup<inherit<arg<"price", double>, arg<"size", int>>, "size",    void, arg>>);

/* ============================================================== any ============================================================= */

/**
 * @brief Helper typename representing any type with additional printing mechanism
 */
struct any : std::any {
public:

    /// @brief Default default constructor
    any() = default;

    /**
     * @brief Copy constructor
     * @tparam T 
     *    type of the value to be copied
     */
    template <typename T>
    explicit(false) any(const T& a);

    /**
     * @brief Casts the object into the underlying type
     * @tparam T 
     *    type to be casted to
     * @returns 
     *    object casted to the T type
     */
    template <typename T>
    constexpr explicit(false) operator T() const;

public:

    /// Printing function
    friend std::ostream& operator<<(std::ostream& os, const any& a);

public:

    /// Pointer to the printing function
    std::ostream& (*print)(std::ostream&, const std::any&){};

};
/* =========================================================== namedtupl ========================================================== */

namespace nt {

    /**
     * @brief Implementation of the named tuple
     * 
     * @tparam Name 
     * @tparam Ts 
     */
    template <fixed_string Name, typename... Ts>
    struct namedtuple : Ts... {
    public:

        // Name of the named tuple
        static constexpr auto name_v = Name;
        // Size of the tuple
        static constexpr auto size = sizeof...(Ts);

    public:

        /// @brief Constructs tuple from the list of contained elements
        constexpr explicit(true) namedtuple(Ts... ts);
        /// @brief Constructs tuple from the list of contained elements
        constexpr explicit(true) namedtuple(auto... ts);

    public:

        /**
         * @brief Indexing operator enabling element-specific access to the const tuple
         * 
         * @tparam T 
         *     type of the indexing value
         * @tparam TArg 
         *    helper argument enabling findin the required element of the tuple
         */
        template <typename T, typename TArg = map_lookup<namedtuple, T::name, void, arg>>
            requires(not std::is_void_v<TArg>)
        constexpr const auto& operator[](const T) const;

        /**
         * @brief Indexing operator enabling element-specific access to the tuple
         * 
         * @tparam T 
         *     type of the indexing value
         * @tparam TArg 
         *    helper argument enabling findin the required element of the tuple
         */
        template <typename T, typename TArg = map_lookup<namedtuple, T::name, void, arg>>
            requires(not std::is_void_v<TArg>)
        constexpr auto& operator[](const T);

    public:

        /**
         * @brief Helper method enabling tuple-wise assignements
         * 
         * @param ts 
         *    list of elements to be asigned to the tuple
         * @return auto& 
         */
        auto& assign(auto&&... ts);

        /**
         * @brief Method returning reference to the tuple's element
         * 
         * @tparam N 
         *    index of the element
         * @returns 
         *    reference to the element
         */
        template <std::size_t N>
        auto& get();

        /**
         * @brief Method returning reference to the const tuple's element
         * 
         * @tparam N 
         *    index of the element
         * @returns 
         *    reference to the const element
         */
        template <std::size_t N>
        const auto& get() const;

    public:

        /// Friend printing oeprator
        template <fixed_string, typename...>
        friend std::ostream& operator<<(std::ostream& os, const namedtuple& nt);
        
    };

    /**
     * @brief Deduction guide for the namedtuple
     */
    template <typename... Ts>
    namedtuple(Ts...) -> namedtuple<"", Ts...>;

}

/**
 * @brief Helper function creating the namedtuple
 * 
 * @tparam Name (optional, default: "")
 *    name of the tuple
 * @tparam Ts 
 *    types contained by the tuple
 * @param ts 
 *    argument to create tuple from
 * @returns 
 *    tuple object
 */
template <fixed_string Name = "", typename... Ts>
constexpr auto namedtuple(Ts... ts);

/* ============================================================ Extends =========================================================== */

/**
 * @brief Helper concept providing a compil-time way to check whether the tuple contains 
 *    given fields
 * 
 * @tparam T 
 *    type to be checked
 * @tparam Names 
 *    fields to be required
 */
template<typename T, fixed_string... Names>
concept extends = (requires(T t, arg<Names, any> name) { t[name]; } and ...);

/* ================================================================================================================================ */

} // End namespace estd

/* ========================================================= std namespace ======================================================== */

namespace std {

    /**
     * @brief Helper type holding the size of the estd::namedtuple
     * @tparam Name 
     *    name of the estd::namedtuple
     * @tparam Ts 
     *    list of types of elements hold by the namedtuple
     */
    template <estd::fixed_string Name, typename... Ts>
    struct tuple_size<estd::nt::namedtuple<Name, Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>  { };

    
    /**
     * @brief Helper trait holding type of the n'th element of the tuple
     * 
     * @tparam N 
     *    index off the element to be inspected
     * @tparam Name 
     *     name of the namedtuple
     * @tparam Ts 
     *    list of types of elements hold by the namedtuple
     */
    template <std::size_t N, estd::fixed_string Name, typename... Ts>
    struct tuple_element<N, estd::nt::namedtuple<Name, Ts...>> {

        /// Type of the n'th element of the tuple
        using type = decltype(std::declval<estd::nt::namedtuple<Name, Ts...>>().template get<N>());
        
    };

    /**
     * @brief Implementation of the std::get for estd::namedtuple
     * 
     * @tparam N 
     *    index off the element to be inspected
     * @tparam Name 
     *     name of the namedtuple
     * @tparam Ts 
     *    list of types of elements hold by the namedtuple
     * @param nt 
     *     namedtuple to be inspected
     * @returns 
     *     constant reference to the element
     */
    template<std::size_t N, estd::fixed_string Name, typename... Ts>
    const auto& get(estd::nt::namedtuple<Name, Ts...>&& nt) noexcept;
    
}

/* ================================================================================================================================ */

#endif
