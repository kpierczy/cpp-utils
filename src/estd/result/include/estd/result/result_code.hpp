/* ============================================================================================================================ *//**
 * @file       result_code.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 13th July 2021 8:29:14 am
 * @modified   Tuesday, 28th February 2023 8:57:59 pm
 * @project    cpp-utils
 * @brief      Header file of the result_code class template representing an rabitrary pair {value, status_code}. status_code indicates
 *             status of the operation that returned result_code as well as whether value conains a valid value.
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_RESULT_CODE_H__
#define __ESTD_RESULT_RESULT_CODE_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/status_code.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================= Declarations ========================================================= */

/**
 * @class result_code
 * @brief Representation of the generic action's result holding additional informations about 
 *    it's status code
 * @tparam ResultType 
 *    category of the value associated with result
 */
template<typename ResultType>
class result_code  {

public: /* ------------------------------------------------- Public constructors -------------------------------------------------- */

    /**
     * @brief Constructs a result_code object with the given given @p status and value initialized to
     *    ResultType()
     * @param status 
     *    status code associated with result
     */
    inline constexpr result_code(const status_code &status = status_code::success()) noexcept;

    /**
     * @brief Constructs a new result object with the given @p value and given @p status
     * @param value 
     *    value associated with the result
     * @param status 
     *    status associated with the result
     */
    inline constexpr result_code(const ResultType &value, const status_code &status = status_code::success()) noexcept; 

    /**
     * @brief Constructs a result copying data from @p rresult
     * @param rresult 
     *    result to be copied to the created status code
     */
    inline constexpr result_code(const result_code &rresult) noexcept = default;

public: /* --------------------------------------------------- Public operators --------------------------------------------------- */

    /**
     * @brief Assigns one result code to another
     * @param rresult 
     *    result to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr result_code &operator=(const result_code &rresult) noexcept = default;

    /**
     * @brief Assigns value to a result code
     * @param value 
     *    value to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr result_code &operator=(const ResultType &value) noexcept;

    /**
     * @brief Assigns status code to a result code
     * @param status 
     *    status code to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    inline constexpr result_code &operator=(const status_code &status) noexcept;

    /**
     * @brief Assigns enum-derived status code to the result_code object
     * @param status 
     *    status to be assigned
     * @returns 
     *    reference to assignment's left value
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    inline constexpr result_code &operator=(const Enum &status) noexcept;

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
    inline constexpr bool operator==(const result_code &rresult) const noexcept = default;

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
    inline constexpr bool operator==(const status_code &status) const noexcept;

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
    inline constexpr bool operator!=(const result_code &rresult) const noexcept = default;

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
    inline constexpr bool operator!=(const status_code &status) const noexcept;

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
     * @brief Creates result with status code of  @c Success category with @p 0 code and @p value
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Success category
     */
    static inline constexpr result_code success(const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of  @c Success with @p code code (casted to numeric
     *    category) and @p value
     * @param code 
     *    code to be set in the produces status code
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Success category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr result_code success(Enum code, const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of  @c Warning category with @p 0 code and @p value
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Warning category
     */
    static inline constexpr result_code warning(const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of  @c Warning with @p code code (casted to numeric
     *    category) and @p value
     * @param code 
     *    code to be set in the produces status code
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Warning category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr result_code warning(Enum code, const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of  @c Error category with @p 0 code and @p value
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Error category
     */
    static inline constexpr result_code error(const ResultType &value = ResultType()) noexcept;

    /**
     * @brief Creates result with status code of  @c Error with @p code code (casted to numeric
     *    category) and @p value
     * @param code 
     *    code to be set in the produces status code
     * @param value
     *    result's value
     * @returns 
     *    result of the @c Error category
     */
    template<typename Enum>
        requires std::is_enum_v<Enum>    
    static inline constexpr result_code error(Enum code, const ResultType &value = ResultType()) noexcept;        
       
public: /* --------------------------------------------------- Public variables --------------------------------------------------- */

    // status associated with the result
    status_code status;

    // Value associated with the result
    ResultType value;
     
};

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation Includes =================================================== */

#include "estd/result/impl/result_code.hpp"

/* ================================================================================================================================ */

#endif