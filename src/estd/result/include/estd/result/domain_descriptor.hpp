/** ==================================================================================================================================
 * @file     domain_descriptor.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Tuesday, 20th July 2021 10:39:30 pm
 * @modified Thursday, 3rd February 2022 4:27:45 pm
 * @project  Winder
 * @brief
 *    
 *    Class representing the domain_descriptor
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_RESULT_DOMAIN_DESCRIPTOR_H__
#define __ESTD_RESULT_DOMAIN_DESCRIPTOR_H__

/* =========================================================== Includes =========================================================== */

#include <span>
#include "estd/result/status_code.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================= Declarations ========================================================= */

// Forward declaration of domain_descriptor
class domain_descriptor;
// Category of the variables used to represent status domain
using domain_id = const domain_descriptor *;

/**
 * @brief Class representing a status domain's descriptor
 */
class domain_descriptor {
public:

    // Category of table containing descriptions of status codes
    using description_table = const char *[];
    // Category of the empty table
    using empty_table = std::span<const char *>;

public:

    /**
     * @brief Domain descriptor's constructor
     * @param success_description_table
     *    table of description strings for success status codes
     * @param warning_description_table
     *    table of description strings for warning status codes
     * @param error_description_table
     *    table of description strings for error status codes
     */
    inline constexpr domain_descriptor(
        std::span<const char *> success_description_table,
        std::span<const char *> warning_description_table,
        std::span<const char *> error_description_table
    );

    /**
     * @param category 
     *    table of the table to be returned
     * @returns 
     *    requested table containing descriptions of error codes
     */
    inline constexpr std::span<const char *> getTable(status_code::Category category) const;

    /**
     * @brief Converts domain_descriptor into domain_id
     * 
     * @param descriptor 
     *    descriptor to be converted
     * @returns 
     *    domain's ID
     */
    inline constexpr domain_id getDomainID() const;

private:

    // Table of descriptions for success status codes
    std::span<const char *> success;
    // Table of descriptions for warning status codes
    std::span<const char *> warning;
    // Table of descriptions for error status codes
    std::span<const char *> error;

};

/**
 * @brief Converts domain_descriptor into domain_id
 * 
 * @param descriptor 
 *    descriptor to be converted
 * @returns 
 *    domain's ID
 */
static inline constexpr const domain_descriptor & get_domain_descriptor(domain_id domain);

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation Includes =================================================== */

#include "estd/result/impl/domain_descriptor.hpp"

/* ================================================================================================================================ */

#endif