/** ==================================================================================================================================
 * @file     namedtuple.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 14th February 2022 11:27:10 pm
 * @modified Tuesday, 15th February 2022 11:34:43 pm
 * @project  cpp-utils
 * @brief
 *    
 *    Implementation of the python-like named tuple in c++ 20 (does not work in GCC < 11.2)
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * @source https://gist.github.com/GuillaumeDua/b354dd4c46df160dbfd04c31b2a51c80 (https://godbolt.org/z/4889PqPGb)
 * @source https://twitter.com/krisjusiak/status/1455843968361586690 (https://t.co/fGBE43xnZy)
 * ================================================================================================================================ */

#ifndef __ESTD_NAMEDTUPLE_H__
#define __ESTD_NAMEDTUPLE_H__

/* =========================================================== Warnings =========================================================== */

#if defined(__GNUC__) or defined(__GNUG__)
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if ( GCC_VERSION < 11'02'00 )
#error "estl::namedtupl does not work with GCC < 11.2"
#endif
#endif

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

namespace estl {

/* ============================================================== Arg ============================================================= */

/**
 * @brief Helper typename representing named argument
 * 
 * @tparam Name 
 *     name of the tuple's element
 * @tparam TValue 
 *     value of the argument
 */
template <estd::fixed_string Name, typename TValue>
struct named_arg {
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
     *    a NEW named_arg object
     */
    template <typename T>
    [[nodiscard]] constexpr auto operator=(const T& t) const;

public:

    // Value of the argument
    TValue value{};
    
};


/**
 * @brief Helper function returning value of the named argument
 * 
 * @tparam Name 
 *    name of the argument
 * @tparam TValue 
 *    type of the arguments value
 * @param t 
 *    argument obejct
 * @returns 
 *    reference to the argument's value
 */
template<estd::fixed_string Name, class TValue>
[[nodiscard]] constexpr decltype(auto) get(named_arg<Name, TValue>& t);


/**
 * @brief Helper function returning value of the const named argument
 * 
 * @tparam Name 
 *    name of the argument
 * @tparam TValue 
 *    type of the arguments value
 * @param t 
 *    const argument obejct
 * @returns 
 *    const reference to the argument's value
 */
template<estd::fixed_string Name, class TValue>
[[nodiscard]] constexpr decltype(auto) get(const named_arg<Name, TValue>& t);


/**
 * @brief Helper UDL creating @ref named_arg from string
 * 
 * @tparam Name 
 *    name of the argument
 * @returns 
 *    a temporary, named argument
 * 
 * @note the value of the returned argument is of @c estl::named_any type. This issue makes the returned
 *    object non-trivially-destructible and - in result - non-literal. In the result, the @ref ""_t
 *    UDL cannot be used in constexpr expressions
 */
template <estd::fixed_string Name>
constexpr auto operator""_t();

/* ============================================================== named_any ============================================================= */

/**
 * @brief Helper typename representing named_any type with additional printing mechanism
 */
struct named_any : std::any {
public:

    /// @brief Default default constructor
    constexpr named_any() = default;

    /**
     * @brief Copy constructor
     * @tparam T 
     *    type of the value to be copied
     */
    template <typename T>
    explicit(false) named_any(const T& a);

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

    /**
     * @brief Converts object to the human-readible string
     */
    std::string to_string() const;

public:

    /// Printing function
    friend std::ostream& operator<<(std::ostream& os, const named_any& a);

public:

    /// Pointer to the printing function
    std::ostream& (*print)(std::ostream&, const std::any&){};

};

/* ========================================================== map-lookup ========================================================== */

namespace details {

    /// @brief Helper meta-function resolving list of template parameters to the TDefault type
    template <typename TDefault, estd::fixed_string, template <estd::fixed_string, typename> typename>
    auto map_lookup(...) -> TDefault;
    /// @brief Helper meta-function resolving list of template parameters to the TArg element type (key of the element represented by estd::fixed_string)
    template <typename, estd::fixed_string TKey, template <estd::fixed_string, typename> typename TArg, typename TValue>
    auto map_lookup(TArg<TKey, TValue>*) -> TArg<TKey, TValue>;

    /// @brief Helper meta-function resolving list of template parameters to the TDefault type
    template <typename TDefault, typename, template <typename, typename> typename>
    auto map_lookup(...) -> TDefault;
    /// @brief Helper meta-function resolving list of template parameters to the TArg element type (key of the element represented by type)
    template <typename, typename TKey, template <typename, typename> typename TArg, typename TValue>
    auto map_lookup(TArg<TKey, TValue>*) -> TArg<TKey, TValue>;
    
}

/**
 * @brief Helper meta-function (template alias) resolving @tparam T into either TDefault or TArg<TKey, TValue>
 *    depending on whether @tparam T is convertible to @tp TArg<TKey, _value_type_> ( i.e. if is convertible to
 *    @tparam TArg with the match @tparam TKey )
 * 
 * @tparam T 
 *    type to be resolved
 * @tparam TKey 
 *    key of the named argument
 * @tparam TDefault 
 *    default type to be resolved
 * @tparam TArg 
 *    named argument type to be resolved on match
 */
template <typename T, estd::fixed_string TKey, typename TDefault, template <estd::fixed_string, typename> typename TArg>
using map_lookup = decltype(details::map_lookup<TDefault, TKey, TArg>( static_cast<T*>(nullptr) ));

/* =========================================================== inheriter ========================================================== */

/**
 * @brief Helper template inheriting it's arguments
 * 
 * @tparam Ts 
 *    list of types to be inherited
 */
template <typename... Ts> struct inherit : Ts... {};

/* =========================================================== namedtupl ========================================================== */

namespace nt {

    /**
     * @brief Implementation of the named tuple
     * 
     * @tparam Name 
     *    name of the tuple 
     * @tparam Ts 
     *    other elements of the tuple
     */
    template <estd::fixed_string Name, typename... Ts>
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
        /// @brief Constructs tuple from the other namedtuple
        constexpr explicit(true) namedtuple(const namedtuple& other) = default;

    public:

        /**
         * @brief Indexing operator enabling element-specific access to the const tuple
         * 
         * @tparam T 
         *     type of the indexing value
         * @tparam TArg 
         *    helper argument enabling findin the required element of the tuple
         */
        template <typename T, typename TArg = map_lookup<namedtuple, T::name, void, named_arg>>
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
        template <typename T, typename TArg = map_lookup<namedtuple, T::name, void, named_arg>>
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
         * @tparam Name 
         *    name of the field
         * @tparam TValue 
         *    type of the field's value
         * @returns 
         *    reference to the element
         */
        template <estd::fixed_string Name_>
        [[nodiscard]] constexpr auto get() -> decltype(estl::get<Name_>(*this));

        /**
         * @brief Method returning reference to the const tuple's element
         * 
         * @tparam Name 
         *    name of the field
         * @tparam TValue 
         *    type of the field's value
         * @returns 
         *    reference to the const element
         */
        template <estd::fixed_string Name_>
        [[nodiscard]] constexpr const auto get() const -> decltype(estl::get<Name_>(*this));

        /**
         * @brief Method returning reference to the tuple's element
         * 
         * @tparam N 
         *    index of the element
         * @returns 
         *    reference to the element
         */
        template <std::size_t N>
        [[nodiscard]] constexpr auto& get();

        /**
         * @brief Method returning reference to the const tuple's element
         * 
         * @tparam N 
         *    index of the element
         * @returns 
         *    reference to the const element
         */
        template <std::size_t N>
        [[nodiscard]] constexpr const auto& get() const;

    public:

        /**
         * @brief Converts tuple to the human-readable string
         */
        std::string to_string() const;

    public:

        /// Friend printing operator (non-empty tuples)
        template <estd::fixed_string, typename...>
        friend std::ostream& operator<<(std::ostream& os, const namedtuple& nt);
        
    };

    /**
     * @brief Deduction guide for the namedtuple
     */
    template <typename... Ts>
    namedtuple(Ts...) -> namedtuple<estd::basic_fixed_string{""}, Ts...>;

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
template <estd::fixed_string Name = "", typename... Ts>
constexpr auto namedtuple(Ts... ts);

/**
 * @brief Helper function coverting object that can be structure-bind with up-to @c 10 elements
 *    into a std::tuple
 * 
 * @tparam T 
 *    type of the structure-bindable object
 * @param object 
 *    object to be converted
 * @returns 
 *    @p object converted to std::tuple 
 */
template <class T>
constexpr auto to_tuple(T object) noexcept;

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
template<typename T, estd::fixed_string... Names>
#if defined(__clang__)
concept extends = ((requires(T t, named_arg<Names, named_any> name) { t[name]; }) and ...) ;
#elif defined(__GNUC__) || defined(__GNUG__)
concept extends = requires(T t, named_arg<Names, named_any> ... name) { (t[name], ...); };
#endif

/* ================================================================================================================================ */

} // End namespace estl

/* ========================================================= std namespace ======================================================== */

namespace std {

    /**
     * @brief Helper type holding the size of the estl::namedtuple
     * @tparam Name 
     *    name of the estl::namedtuple
     * @tparam Ts 
     *    list of types of elements hold by the namedtuple
     */
    template <estd::fixed_string Name, typename... Ts>
    struct tuple_size<estl::nt::namedtuple<Name, Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>  { };

    
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
    struct tuple_element<N, estl::nt::namedtuple<Name, Ts...>> {

        /// Type of the n'th element of the tuple
        using type = decltype(std::declval<estl::nt::namedtuple<Name, Ts...>>().template get<N>());
        
    };

    /**
     * @brief Implementation of the std::get for estl::namedtuple
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
    const auto& get(estl::nt::namedtuple<Name, Ts...>&& nt) noexcept;
    
}

/* ==================================================== Implementation includes =================================================== */

#include "estl/namedtuple/impl/namedtuple.hpp"

/* ================================================================================================================================ */

#endif
