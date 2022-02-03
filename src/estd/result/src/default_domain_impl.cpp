/** ==================================================================================================================================
 * @file     domain_impl.cpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 24th June 2021 4:41:31 pm
 * @modified Thursday, 3rd February 2022 12:06:16 pm
 * @project  Winder
 * @brief
 *    
 *    Definitions of symbols of the default domain
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

/* =========================================================== Includes =========================================================== */

#include "estd/result/default_domain.hpp"
#include <array>
#include <utility>
#include <type_traits>

/* ======================================================== Static objects ======================================================== */

// Descriptor of status codes from the global namespace
const DomainDescriptor DefaultDomainDescriptor(
    
    /* ------ Success codes ------ */
    DomainDescriptor::EmptyTable(),

    /* ------ Warning codes ------ */
    (DomainDescriptor::DescriptionTable) {

        /* TooLate */ "Action could not be finalized as some condition was stolen in the meanwhile"

    },

    /* ------- Error codes ------- */
    (DomainDescriptor::DescriptionTable) {

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
