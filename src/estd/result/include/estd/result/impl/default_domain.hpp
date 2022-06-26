/* ============================================================================================================================ *//**
 * @file       default_domain.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 24th June 2021 4:41:31 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Definitions of helper functions related to default status domain
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_IMPL_DOMAIN_H__
#define __ESTD_RESULT_IMPL_DOMAIN_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/status.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Definitions ========================================================= */

// Specification of the construct_status_code() functions
template<> constexpr estd::status_code construct_status_code(Warning code) {
    return status_code::warning(code);
}


// Specification of the construct_status_code() functions
template<> constexpr status construct_status(Warning code) {
    return status::warning(DefaultDomain, code);
}

// Specification of the construct_status_code() functions
template<> constexpr estd::status_code construct_status_code(Error code) {
    return status_code::error(code);
}


// Specification of the construct_status_code() functions
template<> constexpr status construct_status(Error code) {
    return status::error(DefaultDomain, code);
}


// StatucCode's `to_string` function
constexpr std::string_view to_string(const estd::status_code &status) {
    return status.to_string(get_domain_descriptor(DefaultDomain).getTable(status.category()));
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
