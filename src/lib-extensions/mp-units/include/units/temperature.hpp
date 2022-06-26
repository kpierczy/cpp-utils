/* ============================================================================================================================ *//**
 * @file       temperature.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 2:22:27 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing temperature values (extends 
 *             mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_TEMPERATURE_H__
#define __UNITS_TEMPERATURE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/thermodynamic_temperature.h"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/**
 * @brief Alias of the default temperature unit (Kelvin)
 */
struct degree_celsius : alias_unit<kelvin, basic_symbol_text{"°C", "deg_C"}, no_prefix> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating temperature quantity with degrees of celsius
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_deg_C(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return thermodynamic_temperature<degree_celsius, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating temperature quantity with degrees of celsius
     *     from long double
     */
    constexpr auto operator"" _q_deg_C(long double l) { 
        return thermodynamic_temperature<degree_celsius, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace thermodynamic_temperature_references {

    /// @brief Reference for temperature quantity with degrees of celsius units
    inline constexpr auto deg_C = reference<dim_thermodynamic_temperature, degree_celsius>{};

}

namespace references {  
    using namespace thermodynamic_temperature_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline thermodynamic_temperature {

    /// @brief Alias for the quantity of temperature quantity with degrees of celsius units
    template<Representation Rep = double> using deg_C = units::isq::si::thermodynamic_temperature<units::isq::si::degree_celsius, Rep>;

}

/* ================================================================================================================================ */

#endif
