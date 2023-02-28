/* ============================================================================================================================ *//**
 * @file       result.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 13th July 2021 9:00:51 am
 * @modified   Tuesday, 28th February 2023 9:01:39 pm
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
constexpr result<ResultType>::result(const status &status_p) noexcept : 
    _status(status_p), _value()
{}


template<typename ResultType>
constexpr result<ResultType>::result(const ResultType &value_p, const status &status_p) noexcept : 
    _status(status_p), _value(value_p)
{}

/* ======================================================= Public operators ======================================================= */

template<typename ResultType>
constexpr result<ResultType> &result<ResultType>::operator=(const ResultType &rvalue) noexcept {
    _value = rvalue;
}


template<typename ResultType>
constexpr result<ResultType> &result<ResultType>::operator=(const status &status_p) noexcept {
    this->_status = status_p;
}


template<typename ResultType>
constexpr result<ResultType>::operator bool() const noexcept {
    return bool(_status);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator==(const ResultType &rvalue) const noexcept {
    return _value == rvalue;
}


template<typename ResultType>
constexpr bool result<ResultType>::operator==(const status &status_p) const noexcept {
    return this->_status == status_p;
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result<ResultType>::operator==(const Enum &status_p) const noexcept {
    return this->_status == _status(status_p);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator!=(const ResultType &value_p) const noexcept {
    return !(*this == value_p);
}


template<typename ResultType>
constexpr bool result<ResultType>::operator!=(const status &status_p) const noexcept {
    return !(*this == status_p);
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result<ResultType>::operator!=(const Enum &status_p) const noexcept {
    return !(*this == status_p);
}

/* ===================================================== Public static methods ==================================================== */

template<typename ResultType>
constexpr result<ResultType> result<ResultType>::success(
    const ResultType &value_p
) noexcept {
    return result(value_p, status::success(DefaultDomain, 0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result<ResultType> result<ResultType>::success(
    domain_id domain,
    Enum code,
    const ResultType &value_p
) noexcept {
    return result(value_p, status::success(domain, code));
}


template<typename ResultType>
constexpr result<ResultType> result<ResultType>::warning(
    const ResultType &value_p
) noexcept {
    return result(value_p, status::warning(DefaultDomain, 0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result<ResultType> result<ResultType>::warning(
    domain_id domain,
    Enum code,
    const ResultType &value_p
) noexcept {
    return result(value_p, status::warning(domain, code));
}


template<typename ResultType>
constexpr result<ResultType> result<ResultType>::error(
    const ResultType &value_p
) noexcept {
    return result(value_p, status::error(DefaultDomain, 0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result<ResultType> result<ResultType>::error(
    domain_id domain,
    Enum code,
    const ResultType &value_p
) noexcept {
    return result(value_p, status::error(domain, code));
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
