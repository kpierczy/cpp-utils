/** ==================================================================================================================================
 * @file     status.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:59:51 am
 * @modified Thursday, 3rd February 2022 12:29:18 pm
 * @project  Winder
 * @brief
 *    
 *    Header file of the class representing generic status of the operation composed of the status_code and domain pointer.
 *    Additional component (compared to the status_code) provides unique distinction between results produced by various domains
 *    of the project.
 * 
 *    As a unique domain identifier a pointer to the statically allocated array of strings is used. This way it is possible
 *    to simply assign human-readable representations of the status to the objects.
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_STATUS_H__
#define __ESTD_RESULT_STATUS_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/default_domain.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================= Declarations ========================================================= */

class status {

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */
    
    /**
     * @brief Construct a new status described by the @p code in the default domain
     * @param code
     *     code describing the status
     */
    inline constexpr status(status_code code = status_code::success()) noexcept;

    /**
     * @brief Construct a new status described by the @p code in the given @p domain
     * @param domain
     *     domain of the status
     * @param code
     *     code describing the status
     */
    inline constexpr status(DomainID domain, status_code code = status_code::success()) noexcept;

    /**
     * @brief Construct a new status with the @p code. 
     * @note To use this constructor, the @f construct_status(Enum code) function template
     *    must be specialized by the user in the global namespace
     * @param code 
     *    status code represented by enum constant
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>
    inline constexpr status(Enum code) noexcept;

    /**
     * @brief Constructs a status copying data from @p rstatus
     * @param rstatus 
     *    status to be copied to the created status code
     */
    inline constexpr status(const status &rstatus) noexcept = default;

public: /* --------------------------------------------------- Public operators --------------------------------------------------- */

    /**
     * @brief Assigns one status to another
     * @param rstatus 
     *    status to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr status &operator=(const status &rstatus) noexcept = default;

    /**
     * @brief Assigns enumerical value to the status object
     * @note To use this constructor, the @f construct_status(Enum code) function template
     *    must be specialized by the user in the global namespace
     * @param rstatus 
     *    status to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr status &operator=(const Enum &rstatus) noexcept;

    /**
     * @brief Conversion to the boolean category
     * @returns 
     *    @c true when status code category is @c Success \n
     *    @c false otherwise
     */
    inline constexpr explicit operator bool() const noexcept;

    /**
     * @brief Conversion to the arbitrary enumeration (looses information about code's category and domain)
     * @returns 
     *    status code converted to @tparam Enum
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>
    inline constexpr explicit operator Enum() const noexcept;

    /**
     * @brief Conversion to the status_code (looses information about code's category and domain)
     * @returns 
     *    status code converted to @ref status_code
     */
    inline constexpr explicit operator status_code() const noexcept;

    /**
     * @brief Comparison operator
     * @param rstatus 
     *    status to be compared with @p this
     * @returns 
     *    @c true when status have the same domain, category and code \n
     *    @c false otherwise
     */
    inline constexpr bool operator==(const status &rstatus) const noexcept = default;

    /**
     * @brief Comparison operator between status code and enumeration
     * @note To use this constructor, the @f construct_status(Enum code) function template
     *    must be specialized by the user in the estd:: namespace
     * @param rstatus 
     *    status enum code to be compared with @p this
     * @returns 
     *    @c true when status codes have the same domain, category and code \n
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
     *    @c false when status codes have not the same domain, category and code \n
     *    @c true otherwise
     */
    inline constexpr bool operator!=(const status &rstatus) const noexcept = default;

    /**
     * @brief Comparison operator between status code and enumeration
     * @note To use this constructor, the @f construct_status(Enum code) function template
     *    must be specialized by the user in the estd:: namespace
     * @param rstatus 
     *    status enum code to be compared with @p this
     * @returns 
     *    @c false when status codes have the same domain, category and code \n
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
    inline constexpr DomainID domain() const noexcept;

    /**
     * @returns 
     *    @category category of the status
     */
    inline constexpr status_code::Category category() const noexcept;

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
        requires std::is_enum_v<Enum>
    inline constexpr Enum code_enum() const noexcept;

    /**
     * @brief Converts status to string
     * @returns 
     *    string representation of the status code
     */
    inline constexpr std::string_view to_string() noexcept;

public: /* ------------------------------------------------ Static public methods ------------------------------------------------- */

    /**
     * @brief Creates status from the default domain with @c Success category and given code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status of the @c Success category
     */
    static inline constexpr status success(uint32_t code = 0) noexcept;

    /**
     * @brief Creates status from the given @p domain with @c Success category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status of the @c Success category
     */
    static inline constexpr status success(DomainID domain, uint32_t code = 0) noexcept;

    /**
     * @brief Creates status from the default with @c Success category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status code of the @c Success category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status success(Enum code) noexcept;

    /**
     * @brief Creates status from the given @p domain with @c Success category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status code of the @c Success category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status success(DomainID domain, Enum code) noexcept;

    /**
     * @brief Creates status from the default domain with @c Warning category and given code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status of the @c Warning category
     */
    static inline constexpr status warning(uint32_t code = 0) noexcept;

    /**
     * @brief Creates status from the given @p domain with @c Warning category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status of the @c Warning category
     */
    static inline constexpr status warning(DomainID domain, uint32_t code = 0) noexcept;

    /**
     * @brief Creates status from the default with @c Warning category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status code of the @c Warning category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status warning(Enum code) noexcept;

    /**
     * @brief Creates status from the given @p domain with @c Warning category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status code of the @c Warning category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status warning(DomainID domain, Enum code) noexcept;
    
    /**
     * @brief Creates status from the default domain with @c Error category and given code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status of the @c Error category
     */
    static inline constexpr status error(uint32_t code = 0) noexcept;

    /**
     * @brief Creates status from the given @p domain with @c Error category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status of the @c Error category
     */
    static inline constexpr status error(DomainID domain, uint32_t code = 0) noexcept;

    /**
     * @brief Creates status from the default with @c Error category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status code of the @c Error category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status error(Enum code) noexcept;

    /**
     * @brief Creates status from the given @p domain with @c Error category and given @p code
     * @param code 
     *    code to be set in the produces status code
     * @param domain
     *    domain of the status
     * @returns 
     *    status code of the @c Error category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr status error(DomainID domain, Enum code) noexcept;

private: /* -------------------------------------------------- Private variales --------------------------------------------------- */

    // Code of the status
    status_code current_code;
    
    // Domain of the status
    DomainID current_domain;
    
};

/* ======================================================= Helper functions ======================================================= */

/**
 * @brief Declaration of the function template that should be specialized by the user
 *    to use direct comparison between status and enumeration category as well as direct
 *    conversion from enumeration category to status
 * @tparam Enum 
 *    enumeration category directly convertible to status
 * @param code 
 *    code to be converted
 * @returns 
 *    @p code converted to status_code
 */
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status construct_status(Enum code);

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation Includes =================================================== */

#include "estd/result/impl/status.hpp"

/* ================================================================================================================================ */

#endif
