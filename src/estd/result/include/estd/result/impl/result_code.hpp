/* ============================================================================================================================ *//**
 * @file       result_code.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 13th July 2021 9:00:51 am
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Implementation of inline methods and methods templates related to result_code class template
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_IMPL_RESULT_CODE_H__
#define __ESTD_RESULT_IMPL_RESULT_CODE_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/result_code.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Public constructors ===================================================== */

template<typename ResultType>
constexpr result_code<ResultType>::result_code(const estd::status_code &status) noexcept : 
    status(status), value()
{}


template<typename ResultType>
constexpr result_code<ResultType>::result_code(const ResultType &value, const estd::status_code &status) noexcept : 
    status(status), value(value)
{}

/* ======================================================= Public operators ======================================================= */

template<typename ResultType>
constexpr result_code<ResultType> &result_code<ResultType>::operator=(const ResultType &rvalue) noexcept {
    value = rvalue;
}


template<typename ResultType>
constexpr result_code<ResultType> &result_code<ResultType>::operator=(const estd::status_code &status_code) noexcept {
    status = status_code;
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result_code<ResultType> &result_code<ResultType>::operator=(const Enum &status_code) noexcept {
    status = status_code;
}


template<typename ResultType>
constexpr result_code<ResultType>::operator bool() const noexcept {
    return bool(status);
}


template<typename ResultType>
constexpr bool result_code<ResultType>::operator==(const ResultType &rvalue) const noexcept {
    return value == rvalue;
}


template<typename ResultType>
constexpr bool result_code<ResultType>::operator==(const estd::status_code &status_code) const noexcept {
    return status == status_code;
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool result_code<ResultType>::operator==(const Enum &status_code) const noexcept {
    return status == status_code(status_code);
}


template<typename ResultType>
constexpr bool result_code<ResultType>::operator!=(const ResultType &value) const noexcept {
    return !(*this == value);
}


template<typename ResultType>
constexpr bool result_code<ResultType>::operator!=(const estd::status_code &status_code) const noexcept {
    return !(*this == status_code);
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>   
constexpr bool result_code<ResultType>::operator!=(const Enum &status_code) const noexcept {
    return !(*this == status_code);
}

/* ===================================================== Public static methods ==================================================== */

template<typename ResultType>
constexpr result_code<ResultType> result_code<ResultType>::success(const ResultType &value) noexcept {
    return result_code(value, status_code::success(0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result_code<ResultType> result_code<ResultType>::success(Enum code, const ResultType &value) noexcept {
    return result_code(value, status_code::success(code));
}


template<typename ResultType>
constexpr result_code<ResultType> result_code<ResultType>::warning(const ResultType &value) noexcept {
    return result_code(value, status_code::warning(0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result_code<ResultType> result_code<ResultType>::warning(Enum code, const ResultType &value) noexcept {
    return result_code(value, status_code::warning(code));
}


template<typename ResultType>
constexpr result_code<ResultType> result_code<ResultType>::error(const ResultType &value) noexcept {
    return result_code(value, status_code::error(0));
}


template<typename ResultType>
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr result_code<ResultType> result_code<ResultType>::error(Enum code, const ResultType &value) noexcept {
    return result_code(value, status_code::error(code));
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
