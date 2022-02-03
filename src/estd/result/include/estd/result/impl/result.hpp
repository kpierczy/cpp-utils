/** ==================================================================================================================================
 * @file     result.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 13th July 2021 9:00:51 am
 * @modified Thursday, 3rd February 2022 4:17:11 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline methods and methods templates related to result class template
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_IMPL_RESULT_H__
#define __ESTD_RESULT_IMPL_RESULT_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/result.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Public constructors ===================================================== */

template<typename ResultType>
constexpr result<ResultType>::result(const status &status) noexcept : 
    status(status), value()
{}


template<typename ResultType>
constexpr result<ResultType>::result(const ResultType &value, const status &status) noexcept : 
    status(status), value(value)
{}

/* ======================================================= Public operators ======================================================= */

template<typename ResultType>
constexpr result<ResultType> &result<ResultType>::operator=(const ResultType &rvalue) noexcept {
    value = rvalue;
}


template<typename ResultType>
constexpr result<ResultType> &result<ResultType>::operator=(const status &status_code) noexcept {
    status = status_code;
}


template<typename ResultType>
constexpr result<ResultType>::operator bool() const noexcept {
    return bool(status);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator==(const ResultType &rvalue) const noexcept {
    return value == rvalue;
}


template<typename ResultType>
constexpr bool result<ResultType>::operator==(const status &status_code) const noexcept {
    return status == status_code;
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result<ResultType>::operator==(const Enum &status_code) const noexcept {
    return status == status(status_code);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator!=(const ResultType &value) const noexcept {
    return !(*this == value);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator!=(const status &status_code) const noexcept {
    return !(*this == status_code);
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result<ResultType>::operator!=(const Enum &status_code) const noexcept {
    return !(*this == status_code);
}

/* ===================================================== Public static methods ==================================================== */

template<typename ResultType>
constexpr result<ResultType> result<ResultType>::success(
    const ResultType &value
) noexcept {
    return result(value, status::success(DefaultDomain, 0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result<ResultType> result<ResultType>::success(
    domain_id domain,
    Enum code,
    const ResultType &value
) noexcept {
    return result(value, status::success(domain, code));
}


template<typename ResultType>
constexpr result<ResultType> result<ResultType>::warning(
    const ResultType &value
) noexcept {
    return result(value, status::warning(DefaultDomain, 0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result<ResultType> result<ResultType>::warning(
    domain_id domain,
    Enum code,
    const ResultType &value
) noexcept {
    return result(value, status::warning(domain, code));
}


template<typename ResultType>
constexpr result<ResultType> result<ResultType>::error(
    const ResultType &value
) noexcept {
    return result(value, status::error(DefaultDomain, 0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result<ResultType> result<ResultType>::error(
    domain_id domain,
    Enum code,
    const ResultType &value
) noexcept {
    return result(value, status::error(domain, code));
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
