/* ============================================================================================================================ *//**
 * @file       status_code.cpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 12th July 2021 8:25:41 am
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Implementation of status_code class 'es methods
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_IMPL_STATUS_CODE_H__
#define __ESTD_RESULT_IMPL_STATUS_CODE_H__

/* =========================================================== Includes =========================================================== */

#include "estd/result/status_code.hpp"
#include "estd/enum.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================= Constructors ========================================================= */

constexpr status_code::status_code(Category category, uint32_t code) noexcept :
    representation(category, code)
{}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status_code::status_code(Category category, Enum code) noexcept :
    status_code(category, to_underlying(code))
{}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status_code::status_code(Enum code) noexcept :
    status_code(construct_status_code(code))
{}

/* =========================================================== Operators ========================================================== */

template<typename Enum>
    requires std::is_enum_v<Enum> 
constexpr status_code &status_code::operator=(const Enum &rstatus) noexcept {
    *this = construct_status_code(rstatus);
    return *this;
}


constexpr status_code::operator bool() const noexcept {
    return representation.semantical.category == Category::Success;
}


constexpr status_code::operator uint32_t() const noexcept {
    return representation.numerical;
}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr status_code::operator Enum() const noexcept {
    return to_enum<Enum>(representation.semantical.code);
}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool status_code::operator==(const Enum &rstatus) const noexcept {
    return representation.numerical == construct_status_code(rstatus);
}


template<typename Enum>
    requires std::is_enum_v<Enum>
constexpr bool status_code::operator!=(const Enum &rstatus) const noexcept {
    return !(*this == rstatus);
}

/* ============================================================ Methods =========================================================== */

constexpr status_code::Category status_code::category() const noexcept {
    return representation.semantical.category;
};


constexpr uint32_t status_code::code() const noexcept {
    return representation.semantical.code;
}


template<typename Enum>
    requires std::is_enum_v<Enum> &&
             std::is_convertible_v<std::underlying_type_t<Enum>, uint32_t>
constexpr Enum status_code::code_enum() const noexcept {
    return to_enum<Enum>(static_cast<std::underlying_type_t<Enum>>(representation.semantical.code));
}


constexpr std::string_view status_code::to_string(const std::span<const char*> &context) const noexcept {
    return (
        // Check whether current code is represented in the array
        context.size() >= representation.semantical.code
    ) ?
        // If so, return description
        context[representation.semantical.code] :
        // Else, return empty string
        std::string_view{};
}

/* ======================================================== Static methods ======================================================== */

constexpr status_code status_code::success(uint32_t code) noexcept {
    return status_code(Category::Success, code);
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status_code status_code::success(Enum code) noexcept {
    return status_code(Category::Success, to_underlying(code));
}


constexpr status_code status_code::warning(uint32_t code) noexcept {
    return status_code(Category::Warning, code);
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status_code status_code::warning(Enum code) noexcept {
    return status_code(Category::Warning, to_underlying(code));
}


constexpr status_code status_code::error(uint32_t code) noexcept {
    return status_code(Category::Error, code);
}


template<typename Enum>
    requires std::is_enum_v<Enum>    
constexpr status_code status_code::error(Enum code) noexcept {
    return status_code(Category::Error, to_underlying(code));
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
