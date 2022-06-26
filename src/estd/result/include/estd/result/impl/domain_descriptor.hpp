/* ============================================================================================================================ *//**
 * @file       domain_descriptor.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 13th July 2021 7:57:43 am
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Implementation of functions and of the DomainDescriptr class
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_IMPL_DOMAIN_DESCRIPTOR_H__
#define __ESTD_RESULT_IMPL_DOMAIN_DESCRIPTOR_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/domain_descriptor.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Public constructors ===================================================== */

constexpr domain_descriptor::domain_descriptor(
    std::span<const char *> success_description_table,
    std::span<const char *> warning_description_table,
    std::span<const char *> error_description_table
) : 
    success(success_description_table),
    warning(warning_description_table),
    error(error_description_table)
{}


/* ======================================================== Public methods ======================================================== */

constexpr std::span<const char *> domain_descriptor::getTable(status_code::Category category) const {
    switch(category) {
        case status_code::Category::Success: return success;
        case status_code::Category::Warning: return warning;
        case status_code::Category::Error:   return error;
        case status_code::Category::Num:     return empty_table(); // To silence compiler's errors
        default:                        return empty_table();
    }
}


constexpr domain_id domain_descriptor::getDomainID() const {
    return this;
}

/* ===================================================== Public static methods ==================================================== */

constexpr const domain_descriptor & get_domain_descriptor(domain_id domain) {
    return *domain;
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
