/* ============================================================================================================================ *//**
 * @file       domain.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th June 2021 8:53:35 pm
 * @modified   Tuesday, 28th February 2023 8:58:14 pm
 * @project    cpp-utils
 * @brief      Declarations of default domain symbol's
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_RESULT_DOMAIN_H__
#define __ESTD_RESULT_DOMAIN_H__

/* =========================================================== Includes =========================================================== */

#include <cstdint>
#include <string_view>
#include "estd/result/domain_descriptor.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================= Declarations ========================================================= */

// Commonly occurring error codes
enum class Error : uint32_t {
    Timeout,        // Access timeout indicator
    Unknown,        // Unknown error indicator
    Config,         // General configuration error indicator
    Nullptr,        // Indicator of error due to nullptr being illegally passed as argument to method
    Arg,            // Indicator of error due to invalid value of one or more of arguments
    ZeroArg,        // Indicator of error due to zero value of one or more of arguments required to be non-zero
    ZeroDiv,        // Indicator of error due to zero value division
    Empty,          // Indicator of error due to passing an empty object
    Size,           // Error associated with object's size
    Index,          // Index'es exciding error
    Uninitialized,  // Object uninitialized
    WrongConfig,    // Wrong configuration
    Unsupported,    // Unsupported feature
    Unprivileged,   // Unprivileged access to resources
    Value,          // Wrong value given (e.g. wrong flag)
    Alignment,      // Wrong alignment (e.g. wrong configuration of DMA's address in the burst mode)
    Busy,           // Called context is busy and cannot serve a request
    BufferOverflow, // Generic buffer overflow error
    NotFound,       // Generic 'not found'' error
    Inactive,       // Generic 'inactive' error
    Num
};

// Commonly occurring warning codes
enum class Warning : uint32_t {
    TooLate         // Action could not be finalized as some condition was stolen in the meanwhile
};

// Object used as a domain's reference point
extern const domain_descriptor DefaultDomainDescriptor;
// Global namespace's domain ID
constexpr domain_id DefaultDomain = DefaultDomainDescriptor.getDomainID();

/**
 * @brief Converts error code from default namespace to a human-readable string
 * @param code 
 *    code to be converted
 * @returns 
 *    human-readable representation of @p code if found in table
 *    @p std::string_view() if @p key is unknown
 */
inline constexpr std::string_view to_string(const status_code &status);

/* ======================================================== Static objects ======================================================== */

// Descriptor of status codes from the global namespace
constexpr domain_descriptor DefaultDomainDescriptor(
    
    /* ------ Success codes ------ */
    domain_descriptor::empty_table(),

    /* ------ Warning codes ------ */
    (domain_descriptor::description_table) {

        /* TooLate */ "Action could not be finalized as some condition was stolen in the meanwhile"

    },

    /* ------- Error codes ------- */
    (domain_descriptor::description_table) {

        /* Timeout        */ "Access timeout",
        /* Unknown        */ "Unknown error",
        /* Config         */ "Configuration error",
        /* Nullptr        */ "Null pointer error",
        /* Arg            */ "Invalid value of one or more of arguments",
        /* ZeroArg        */ "Zero-argument error (non-zero value expected)" ,
        /* ZeroDiv        */ "Indicator of error due to zero value division",
        /* Empty          */ "Empty object passed (non-empty object expected)" ,
        /* Size           */ "Invalid size",
        /* Index          */ "Invalid index",
        /* Uninitialized  */ "Object uninitialized",
        /* WrongConfig    */ "Wrong configuration",
        /* Unsupported    */ "Unsupported feature",
        /* Unprivileged   */ "Unprivileged access to resource",
        /* Value          */ "Wrong value given",
        /* Alignment      */ "Wrong alignment",
        /* Busy           */ "Called context is busy and cannot serve a request",
        /* BufferOverflow */ "Buffer overflow error",
        /* NotFound       */ "Element not found",
        /* Inactive       */ "Functionality inactive"

    }
);

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation Includes =================================================== */

#include "estd/result/impl/default_domain.hpp"

/* ================================================================================================================================ */

#endif