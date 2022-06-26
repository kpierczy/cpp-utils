/* ============================================================================================================================ *//**
 * @file       result.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 13th July 2021 9:00:51 am
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Implementation of inline methods and methods templates related to result class template
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_IMPL_RESULT_H__
#define __ESTD_RESULT_IMPL_RESULT_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/result.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Public constructors ===================================================== */

template<typename ResultType>
constexpr result<ResultType>::result(const ::estd::status &status) noexcept : 
    status(status), value()
{}


template<typename ResultType>
constexpr result<ResultType>::result(const ResultType &value, const ::estd::status &status) noexcept : 
    status(status), value(value)
{}

/* ======================================================= Public operators ======================================================= */

template<typename ResultType>
constexpr result<ResultType> &result<ResultType>::operator=(const ResultType &rvalue) noexcept {
    value = rvalue;
}


template<typename ResultType>
constexpr result<ResultType> &result<ResultType>::operator=(const ::estd::status &status) noexcept {
    this->status = status;
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
constexpr bool result<ResultType>::operator==(const ::estd::status &status) const noexcept {
    return this->status == status;
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result<ResultType>::operator==(const Enum &status) const noexcept {
    return this->status == status(status);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator!=(const ResultType &value) const noexcept {
    return !(*this == value);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator!=(const ::estd::status &status) const noexcept {
    return !(*this == status);
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result<ResultType>::operator!=(const Enum &status) const noexcept {
    return !(*this == status);
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
