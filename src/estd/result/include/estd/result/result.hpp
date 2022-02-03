/** ==================================================================================================================================
 * @file     result.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 13th July 2021 9:47:10 am
 * @modified Thursday, 3rd February 2022 4:17:11 pm
 * @project  Winder
 * @brief
 *    
 *    Header file of the result class template representing an rabitrary pair {value, status}. status indicates
 *    status of the operation that returned result as well as whether value conains a valid value.
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_RESULT_H__
#define __ESTD_RESULT_RESULT_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/status.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================= Declarations ========================================================= */

/**
 * @class result
 * @brief Representation of the generic action's result holding additional informations about 
 *    it's status code
 * @tparam ResultType 
 *    category of the value associated with result
 */
template<typename ResultType>
class result  {

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */

    /**
     * @brief Constructs a result object with the given given @p status and value initialized to
     *    ResultType()
     * @param status 
     *    status code associated with result
     */
    inline constexpr result(const status &status = status::success()) noexcept;

    /**
     * @brief Constructs a new result object
     * @param value 
     *    value associated with the result
     * @param status 
     *    status associated with the result
     */
    inline constexpr result(const ResultType &value, const status &status = status::success()) noexcept;   

    /**
     * @brief Constructs a result copying data from @p rresult
     * @param rresult 
     *    result to be copied to the created status code
     */
    inline constexpr result(const result &rresult) noexcept = default;

public: /* --------------------------------------------------- Public operators --------------------------------------------------- */

    /**
     * @brief Assigns one result code to another
     * @param rresult 
     *    result to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr result &operator=(const result &rresult) noexcept = default;

    /**
     * @brief Assigns value to a result code
     * @param value 
     *    value to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr result &operator=(const ResultType &value) noexcept;

    /**
     * @brief Assigns status code to a result code
     * @param status 
     *    status code to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr result &operator=(const status &status) noexcept;

    /**
     * @brief Assigns enum-derived status code to the result object
     * @param status 
     *    status to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr result &operator=(const Enum &status) noexcept;

    /**
     * @brief Converts result o the boolean category
     * @returns 
     *    @c true when status associated with result is @c Success \n
     *    @c false otherwise
     */
    inline constexpr explicit operator bool() const noexcept;

    /**
     * @brief Comparison operator
     * @param rresult 
     *    result to be compared with @p this
     * @returns 
     *    @c true when results have the same value and status code \n
     *    @c false otherwise
     */
    inline constexpr bool operator==(const result &rresult) const noexcept = default;

    /**
     * @brief Comparison operator of result's value
     * @param rvalue 
     *    value to be compared with result's value
     * @returns 
     *    @c true when result's value is equal to @p value \n
     *    @c false otherwise
     */
    inline constexpr bool operator==(const ResultType &rvalue) const noexcept;

    /**
     * @brief Comparison operator between result code and and status code derived from enumeration
     * @param status 
     *    status to be compared with local status
     * @returns 
     *    @c true when result's status is equal to @p status \n
     *    @c false otherwise
     */
    inline constexpr bool operator==(const status &status) const noexcept;

    /**
     * @brief Comparison operator between result code and and status code derived from enumeration
     * @param status 
     *    status enum code to be compared with @p this
     * @returns 
     *    @c true when status codes have the same category and code \n
     *    @c false otherwise
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr bool operator==(const Enum &status) const noexcept;

    /**
     * @brief Comparison operator
     * @param rresult 
     *    result to be compared with @p this
     * @returns 
     *    @c false when results have the same value and status code \n
     *    @c true otherwise
     */
    inline constexpr bool operator!=(const result &rresult) const noexcept = default;

    /**
     * @brief Comparison operator of result's value
     * @param rresult 
     *    result to be compared with @p this
     * @returns 
     *    @c false when result's value is equal to @p value \n
     *    @c true otherwise
     */
    inline constexpr bool operator!=(const ResultType &value) const noexcept;

    /**
     * @brief Comparison operator between result code and and status code derived from enumeration
     * @param status 
     *    status to be compared with local status
     * @returns 
     *    @c false when result's status is equal to @p status \n
     *    @c true otherwise
     */
    inline constexpr bool operator!=(const status &status) const noexcept;

    /**
     * @brief Comparison operator between result code and and status code derived from enumeration
     * @param status 
     *    status enum code to be compared with @p this
     * @returns 
     *    @c false when status codes have the same category and code \n
     *    @c true otherwise
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr bool operator!=(const Enum &status) const noexcept;
    
public: /* ------------------------------------------------ Static public methods ------------------------------------------------- */

    /**
     * @brief Creates result with status code of @c Success category assigned to @c DefaultDomain with @p 0 code
     *    and value initialized to @p value
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Success category
     */
    static inline constexpr result success(const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of @c Success category assigned to @p domain with @p code code
     *    (casted to the numeric category) and value initialized to @p value
     * @param domain
     *    domain of the status
     * @param code 
     *    code to be set in the produces status code
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Success category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr result success(
        domain_id domain,
        Enum code,
        const ResultType &value = ResultType()
    ) noexcept;

    /**
     * @brief Creates result with status code of @c Warning category assigned to @c DefaultDomain with @p 0 code
     *    and value initialized to @p value
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Warning category
     */
    static inline constexpr result warning(const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of @c Warning category assigned to @p domain with @p code code
     *    (casted to the numeric category) and value initialized to @p value
     * @param domain
     *    domain of the status
     * @param code 
     *    code to be set in the produces status code
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Warning category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr result warning(
        domain_id domain,
        Enum code,
        const ResultType &value = ResultType()
    ) noexcept;

    /**
     * @brief Creates result with status code of @c Error category assigned to @c DefaultDomain with @p 0 code
     *    and value initialized to @p value
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Error category
     */
    static inline constexpr result error(const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of @c Error category assigned to @p domain with @p code code
     *    (casted to the numeric category) and value initialized to @p value
     * @param domain
     *    domain of the status
     * @param code 
     *    code to be set in the produces status code
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Error category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr result error(
        domain_id domain,
        Enum code,
        const ResultType &value = ResultType()
    ) noexcept;

public: /* --------------------------------------------------- Public variables --------------------------------------------------- */

    // status associated with the result
    status status;

    // Value associated with the result
    ResultType value;
     
};

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation Includes =================================================== */

#include "estd/result/impl/result.hpp"

/* ================================================================================================================================ */

#endif