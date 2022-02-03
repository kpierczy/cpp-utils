/** ==================================================================================================================================
 * @file     domain_descriptor.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 13th July 2021 7:57:43 am
 * @modified Thursday, 3rd February 2022 12:11:15 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of functions and of the DomainDescriptr class
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_IMPL_DOMAIN_DESCRIPTOR_H__
#define __ESTD_RESULT_IMPL_DOMAIN_DESCRIPTOR_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/domain_descriptor.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Public constructors ===================================================== */

constexpr DomainDescriptor::DomainDescriptor(
    std::span<const char *> success_description_table,
    std::span<const char *> warning_description_table,
    std::span<const char *> error_description_table
) : 
    success(success_description_table),
    warning(warning_description_table),
    error(error_description_table)
{}


/* ======================================================== Public methods ======================================================== */

constexpr std::span<const char *> DomainDescriptor::getTable(status_code::Category category) const {
    switch(category) {
        case status_code::Category::Success: return success;
        case status_code::Category::Warning: return warning;
        case status_code::Category::Error:   return error;
        case status_code::Category::Num:     return EmptyTable(); // To silence compiler's errors
        default:                        return EmptyTable();
    }
}


constexpr DomainID DomainDescriptor::getDomainID() const {
    return this;
}

/* ===================================================== Public static methods ==================================================== */

constexpr const DomainDescriptor & getDomainDescriptor(DomainID domain) {
    return *domain;
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
