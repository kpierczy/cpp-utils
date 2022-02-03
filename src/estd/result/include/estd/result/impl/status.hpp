/** ==================================================================================================================================
 * @file     status.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 13th July 2021 7:57:43 am
 * @modified Thursday, 3rd February 2022 4:27:45 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of inline fucntions and function tempaltes related to the status class
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_IMPL_RESULT_STATUS_H__
#define __ESTD_IMPL_RESULT_STATUS_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/status.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Public constructors ===================================================== */

constexpr status::status(status_code code) noexcept :
    current_code(code), current_domain(DefaultDomain)
{}


constexpr status::status(domain_id domain, status_code code) noexcept :
    current_code(code), current_domain(domain)
{}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status::status(Enum code) noexcept : 
    status(construct_status(code))
{}

/* ======================================================= Public operators ======================================================= */

template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status &status::operator=(const Enum &rstatus) noexcept {
    *this = construct_status(rstatus);
    return *this;
}


constexpr status::operator bool() const noexcept {
    return bool(current_code);
}
    
    
template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status::operator Enum() const noexcept {
    return Enum(current_code);
}


constexpr status::operator status_code() const noexcept {
    return current_code;
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr bool status::operator==(const Enum &rstatus) const noexcept {
    return *this == construct_status(rstatus);
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr bool status::operator!=(const Enum &rstatus) const noexcept {
    return !(*this == rstatus);
}

/* ======================================================== Public methods ======================================================== */

constexpr domain_id status::domain() const noexcept {
    return current_domain;
}


constexpr status_code::Category status::category() const noexcept {
    return current_code.category();
}


constexpr uint32_t status::code() const noexcept {
    return current_code.code();
}


template<typename Enum>
        requires std::is_enum_v<Enum>
constexpr Enum status::code_enum() const noexcept {
    return current_code.code_enum<Enum>();
}


constexpr std::string_view status::to_string() noexcept {
    return (
        // Check whether table contains description of the code
        get_domain_descriptor(current_domain).getTable(current_code.category()).size() >= current_code.code()
    ) ?
        // If so, return it
        get_domain_descriptor(current_domain).getTable(current_code.category())[current_code.code()] : 
        // Else, return empty string
        std::string_view{};
}

/* ===================================================== Public static methods ==================================================== */

constexpr status status::success(uint32_t code) noexcept {
    return status(DefaultDomain, status_code::success(code));
}


constexpr status status::success(domain_id domain, uint32_t code) noexcept {
    return status(domain, status_code::success(code));
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status status::success(Enum code) noexcept {
    return status(DefaultDomain, status_code::success(enumToUnderlying(code)));
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status status::success(domain_id domain, Enum code) noexcept {
    return status(domain, status_code::success(enumToUnderlying(code)));
}


constexpr status status::warning(uint32_t code) noexcept {
    return status(DefaultDomain, status_code::warning(code));
}


constexpr status status::warning(domain_id domain, uint32_t code) noexcept {
    return status(domain, status_code::warning(code));
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status status::warning(Enum code) noexcept {
    return status(DefaultDomain, status_code::warning(enumToUnderlying(code)));
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status status::warning(domain_id domain, Enum code) noexcept {
    return status(domain, status_code::warning(enumToUnderlying(code)));
}


constexpr status status::error(uint32_t code) noexcept {
    return status(DefaultDomain, status_code::error(code));
}


constexpr status status::error(domain_id domain, uint32_t code) noexcept {
    return status(domain, status_code::error(code));
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status status::error(Enum code) noexcept {
    return status(DefaultDomain, status_code::error(enumToUnderlying(code)));
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status status::error(domain_id domain, Enum code) noexcept {
    return status(domain, status_code::error(enumToUnderlying(code)));
}

/* ================================================================================================================================ */

} // End namespace estd

/* ================================================================================================================================ */

#endif
