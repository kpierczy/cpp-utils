/** ==================================================================================================================================
 * @file     dimensionless.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 2nd December 2021 2:22:27 pm
 * @modified Thursday, 3rd February 2022 11:41:15 am
 * @project  Winder
 * @brief
 *    
 *    Definitions of units, dimensions and quantities (based on the mp-units library) describing dimensionless values (extends 
 *    mp-units nemspaces)
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_DIMENSIONLESS_H__
#define __UNITS_DIMENSIONLESS_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/generic/dimensionless.h"

/* ========================================================== Namespaces ========================================================== */

namespace units {

/* ============================================================= Units ============================================================ */

/**
 * @brief Dimensionless unit representing thousanth part of quantity (10^(-3))
 */
struct per_mille : named_scaled_unit<per_mille,
    basic_symbol_text{"\u2030", "per mille"},
    no_prefix,
    ratio(1, 1, -1),
    percent
> {};

/**
 * @brief Dimensionless unit representing hundret thousanth part of quantity (10^(-5))
 */
struct per_cent_mille : named_scaled_unit<per_cent_mille,
    basic_symbol_text{"pcm"},
    no_prefix,
    ratio(1, 1, -3),
    percent
> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with no units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_one(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return dimensionless<one, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with no units
     *     from long double
     */
    constexpr auto operator"" _q_one(long double l) { 
        return dimensionless<one, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with percent units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_prc(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return dimensionless<percent, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with percent units
     *     from long double
     */
    constexpr auto operator"" _q_prc(long double l) { 
        return dimensionless<percent, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with per mille units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_prm(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return dimensionless<per_mille, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with per mille units
     *     from long double
     */
    constexpr auto operator"" _q_prm(long double l) { 
        return dimensionless<per_mille, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with per cent mille units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_prcm(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return dimensionless<per_cent_mille, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating dimensionless quantity with per cent mille units
     *     from long double
     */
    constexpr auto operator"" _q_prcm(long double l) { 
        return dimensionless<per_cent_mille, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace references {

    /// @brief Reference for the dimensionless quantity expressed in ones
    inline constexpr auto one = reference<dim_one, units::one>{};
    /// @brief Reference for the dimensionless quantity expressed in percents
    inline constexpr auto prc = reference<dim_one, units::percent>{};
    /// @brief Reference for the dimensionless quantity expressed in per milles
    inline constexpr auto prm = reference<dim_one, units::per_mille>{};
    /// @brief Reference for the dimensionless quantity expressed in per cent milles
    inline constexpr auto prcm = reference<dim_one, units::per_cent_mille>{};

}

/* ================================================================================================================================ */

} // End namespace units

/* ========================================================== Aliases ========================================================== */

namespace units::aliases {

    /// @brief Alias for the for the dimensionless quantity expressed in ones
    template<Representation Rep = double> using one = units::dimensionless<units::one, Rep>;
    /// @brief Alias for the for the dimensionless quantity expressed in percents
    template<Representation Rep = double> using prc = units::dimensionless<units::percent, Rep>;
    /// @brief Alias for the for the dimensionless quantity expressed in per milles
    template<Representation Rep = double> using prm = units::dimensionless<units::per_mille, Rep>;
    /// @brief Alias for the for the dimensionless quantity expressed in per cent milles
    template<Representation Rep = double> using prcm = units::dimensionless<units::per_cent_mille, Rep>;

}

/* ================================================================================================================================ */

#endif
