/** ==================================================================================================================================
 * @file     status_code.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 14th June 2021 7:39:49 pm
 * @modified Thursday, 3rd February 2022 12:19:12 pm
 * @project  Winder
 * @brief
 *    
 *    Header of the status_code class representing a generic status code
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_STATUS_CODE_H__
#define __ESTD_RESULT_STATUS_CODE_H__

/* =========================================================== Includes =========================================================== */

#include <string_view>
#include <cstdint>
#include <utility>
#include <span>

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ======================================================= Class declaration ====================================================== */

/**
 * @class status_code
 * @brief Objective representation of the generic status code consisting of pair {category, code}.
 * @details Class implements three types: Success, Warning and Error
 * @note status_code code used along with the status_code class are 30-bit integer values
 */
class status_code {

public: /* ------------------------------------------------ Public symbolic names ------------------------------------------------- */

    /**
     * @typedef status_code::Category
     * @brief Categories of status codes
     * @note As GCC 10.2 does not support C++20 `using enum`, cat-codes cannot be named like
     *     `status_code::Success` from the outside
     */
    enum class Category : uint32_t {
        Success,
        Warning,
        Error,
        Num
    };

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */

    /**
     * @brief Constructs a status code of the given @p category and with given @p code
     * @param category 
     *    category of the status code
     * @param code 
     *    code of the resulting status_code object
     */
    inline constexpr status_code(Category category = Category::Success, uint32_t code = 0) noexcept;

    /**
     * @brief Construct a new status code with the given @p category and @p code
     * @param category 
     *    status code's category
     * @param code 
     *    status code
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>
    inline constexpr status_code(Category category, Enum code) noexcept;

    /**
     * @brief Construct a new status code with the @p code. 
     * @note To use this constructor, the @f construct_status_code(Enum code) function template
     *    must be specialized by the user in the estd:: namespace
     * @param code 
     *    status code represented by enum constant
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>
    inline constexpr status_code(Enum code) noexcept;

    /**
     * @brief Constructs a status code copying data from @p rstatus
     * @param rstatus 
     *    status to be copied to the created status code
     */
    inline constexpr status_code(const status_code &rstatus) noexcept = default;

public: /* --------------------------------------------------- Public operators --------------------------------------------------- */

    /**
     * @brief Assigns one status code to another
     * @param rstatus 
     *    status to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr status_code &operator=(const status_code &rstatus) noexcept = default;

    /**
     * @brief Assigns enumerical value to the status_code object
     * @note To use this constructor, the @f construct_status_code(Enum code) function template
     *    must be specialized by the user in the estd:: namespace
     * @param rstatus 
     *    status to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr status_code &operator=(const Enum &rstatus) noexcept;

    /**
     * @brief Conversion to the boolean type
     * @returns 
     *    @c true when status is @c Success \n
     *    @c false otherwise
     */
    inline constexpr explicit operator bool() const noexcept;


    /**
     * @brief Conversion to the unsigned integer type
     * @returns 
     *    numerical representation of the status code
     */
    inline constexpr operator uint32_t() const noexcept;

    /**
     * @brief Conversion to the arbitrary enumeration (looses information about code's category)
     * @returns 
     *    status code converted to @tparam Enum
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>
    inline constexpr explicit operator Enum() const noexcept;

    /**
     * @brief Comparison operator
     * @param rstatus 
     *    status code to be compared with @p this
     * @returns 
     *    @c true when status codes have the same category and code \n
     *    @c false otherwise
     */
    inline constexpr bool operator==(const status_code &rstatus) const noexcept = default;

    /**
     * @brief Comparison operator between status code and enumeration
     * @note To use this constructor, the @f construct_status_code(Enum code) function template
     *    must be specialized by the user in the estd:: namespace
     * @param rstatus 
     *    status enum code to be compared with @p this
     * @returns 
     *    @c true when status codes have the same category and code \n
     *    @c false otherwise
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr bool operator==(const Enum &rstatus) const noexcept;

    /**
     * @brief Comparison operator
     * @param rstatus 
     *    status code to be compared with @p this
     * @returns 
     *    @c false when status codes have not the same category or code \n
     *    @c true otherwise
     */
    inline constexpr bool operator!=(const status_code &rstatus) const noexcept = default;

    /**
     * @brief Comparison operator between status code and enumeration
     * @note To use this constructor, the @f construct_status_code(Enum code) function template
     *    must be specialized by the user in the estd:: namespace
     * @param rstatus 
     *    status enum code to be compared with @p this
     * @returns 
     *    @c false when status codes have the same category and code \n
     *    @c true otherwise
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr bool operator!=(const Enum &rstatus) const noexcept;

public: /* ---------------------------------------------------- Public methods ---------------------------------------------------- */

    /**
     * @returns 
     *    @category category of the status
     */
    inline constexpr Category category() const noexcept;

    /**
     * @returns 
     *    code of the status
     */
    inline constexpr uint32_t code() const noexcept;

    /**
     * @returns 
     *    code of the status converted to the given enum
     */
    template<typename Enum>
        requires std::is_enum_v<Enum> &&
                 std::is_convertible_v<std::underlying_type_t<Enum>, uint32_t>
    inline constexpr Enum code_enum() const noexcept;

    /**
     * @brief Converts status code to string according to a @p context table containing
     *    descriptions of codes (context[code] is a description)
     * @param context
     *    table with descriptions
     * @returns 
     *    string representation of the status code on succes
     *    @c empty string_view if context does not hold description of the current code
     */
    inline constexpr std::string_view to_string(const std::span<const char*> &context) const noexcept;

public: /* ------------------------------------------------ Static public methods ------------------------------------------------- */

    /**
     * @brief Creates status code with @c Success category and given code
     * @param code 
     *    code to be set in the produces status code
     * @returns 
     *    status code of the @c Success category
     */
    static inline constexpr status_code success(uint32_t code = 0) noexcept;

    /**
     * @brief Creates status code with @c Success category and given code
     * @param code 
     *    code to be set in the produces status code
     * @returns 
     *    status code of the @c Success category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status_code success(Enum code) noexcept;    

    /**
     * @brief Creates status code with Category::Warning category and given code
     * @param code 
     *    code to be set in the produces status code
     * @returns 
     *    status code of the Category::Warning category
     */
    static inline constexpr status_code warning(uint32_t code = 0) noexcept;

    /**
     * @brief Creates status code with Category::Warning category and given code
     * @param code 
     *    code to be set in the produces status code
     * @returns 
     *    status code of the Category::Warning category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status_code warning(Enum code) noexcept;

    /**
     * @brief Creates status code with Category::Error category and given code
     * @param code 
     *    code to be set in the produces status code
     * @returns 
     *    status code of the Category::Error category
     */
    static inline constexpr status_code error(uint32_t code = 0) noexcept;

    /**
     * @brief Creates status code with Category::Error category and given code
     * @param code 
     *    code to be set in the produces status code
     * @returns 
     *    status code of the Category::Error category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>
    static inline constexpr status_code error(Enum code) noexcept;

private: /* ---------------------------------------------------- Private types ---------------------------------------------------- */

    // Semantical representation of the status code
    class SemanticalRepresentation {
    public: 

        /**
         * @brief Construct a new Semantical Representation of the status
         * @param category 
         *    stauts category
         * @param code 
         *    status code
         */
        inline constexpr SemanticalRepresentation(Category category, uint32_t code) noexcept;
        
    public: 

        // Category of the status code
        Category category : 2;

        // Code's identifier
        uint32_t code : 30;

    };

    // Unified representation of the status
    union Representation {
    public:

        /**
         * @brief Construct a new semantical representation of the status
         * @param category 
         *    stauts category
         * @param code 
         *    status code
         */
        inline constexpr Representation(Category category, uint32_t code) noexcept;

        /**
         * @brief Construct a new numerical representation of the status
         * @param status 
         *    numerical value
         */        
        inline constexpr Representation(uint32_t status) noexcept;

        /**
         * @brief Construct a new numerical representation of the status
         * @param status 
         *    numerical value
         */        
        inline constexpr Representation(const union Representation &rrep) noexcept;

    public:

        /**
         * @brief Default comparison operator
         * @param rrep 
         *    rightvalue to be compared
         * @returns 
         *    @c true of representations are identical
         *    @c false otherwise
         */
        inline constexpr bool operator==(const Representation &rrep) const noexcept;

        /**
         * @brief Default comparison operator
         * @param rrep 
         *    rightvalue to be assigned
         * @returns 
         *    @c true of representations are identical
         *    @c false otherwise
         */
        inline constexpr bool operator!=(const Representation &rrep) const noexcept;

    public: 
    
        // Semantical representation
        SemanticalRepresentation semantical;

        // Numerical representation
        uint32_t numerical;

    };

private: /* -------------------------------------------------- Private variales --------------------------------------------------- */

    // Representation of the status
    Representation representation;

};

/* ======================================================= Helper functions ======================================================= */

/**
 * @brief Declaration of the function template that should be specialized by the user
 *    to use direct comparison between status_code and enumeration category as well as direct
 *    conversion from enumeration category to status_code
 * @tparam Enum 
 *    enumeration category directly convertible to status_code
 * @param code 
 *    code to be converted
 * @returns 
 *    @p code converted to status_code
 */
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status_code construct_status_code(Enum code);

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation Headers ==================================================== */

#include "estd/result/impl/status_code.hpp"
#include "estd/result/impl/status_code_priv.hpp"

/* ================================================================================================================================ */

#endif