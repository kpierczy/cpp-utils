/** ==================================================================================================================================
 * @file     status_code_priv.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 8:49:12 am
 * @modified Thursday, 3rd February 2022 12:11:06 pm
 * @project  Winder
 * @brief
 *    
 *    
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_IMPL_STATUS_CODE_PRIV_H__
#define __ESTD_RESULT_IMPL_STATUS_CODE_PRIV_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/status_code.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* =================================================== Inner types' constructors ================================================== */

constexpr status_code::SemanticalRepresentation::SemanticalRepresentation(Category category, uint32_t code) noexcept :
    category(category), code(code)
{}


constexpr status_code::Representation::Representation(Category category, uint32_t code) noexcept :
    semantical(category, code)
{}


constexpr status_code::Representation::Representation(uint32_t status) noexcept :
    numerical(status)
{}


constexpr status_code::Representation::Representation(const union Representation &rrep) noexcept :
    numerical(rrep.numerical)
{}

/* ==================================================== Inner types' operators ==================================================== */

constexpr bool status_code::Representation::operator==(const Representation &rrep) const noexcept {
    return numerical == rrep.numerical;
}


constexpr bool status_code::Representation::operator!=(const Representation &rrep) const noexcept {
    return !(*this == rrep);
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
