/* ============================================================================================================================ *//**
 * @file       power.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 6:45:04 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing power values (extends 
 *             mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_POWER_H__
#define __UNITS_POWER_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/power.h"
#include "units/isq/si/prefixes.h"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/**
 * @brief Unit representing hundreds of watts
 */
struct hectowatt : prefixed_unit<hectowatt, hecto, watt> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating power quantity with tens of microhenries units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_hW(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return power<hectowatt, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating power quantity with tens of microhenries units
     *     from long double
     */
    constexpr auto operator"" _q_hW(long double l) { 
        return power<hectowatt, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace power_references {

    /// @brief Reference for the power in magnitude of hundreds of watts
    inline constexpr auto hW = reference<dim_power, hectowatt>{};

}

namespace references {  
    using namespace power_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline power {

    /// @brief Alias for the quantity of power expressed in hectowatt
    template<Representation Rep = double> using hW = units::isq::si::power<units::isq::si::hectowatt, Rep>;

}

/* ================================================================================================================================ */

#endif
