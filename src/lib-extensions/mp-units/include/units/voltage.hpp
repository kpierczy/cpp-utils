/* ============================================================================================================================ *//**
 * @file       voltage.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 2:22:27 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing voltage values (extends 
 *             mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_VOLTAGE_H__
#define __UNITS_VOLTAGE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/voltage.h"
#include "units/isq/si/prefixes.h"
#include "units/prefixes.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/// @brief Unit representing tens of microvolts
struct tens_of_microvolts : prefixed_unit<tens_of_microvolts, tens_of_micros, volt> {};
/// @brief Unit representing hundreds of microvolts
struct hundreds_of_microvolts : prefixed_unit<hundreds_of_microvolts, hundreds_of_micros, volt> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating voltage quantity with tens of microvolts units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_ts_of_uV(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return voltage<tens_of_microvolts, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating voltage quantity with tens of microvolts units
     *     from long double
     */
    constexpr auto operator"" _q_ts_of_uV(long double l) { 
        return voltage<tens_of_microvolts, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating voltage quantity with hundreds of microvolts units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_hs_of_uV(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return voltage<hundreds_of_microvolts, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating voltage quantity with hundreds of microvolts units
     *     from long double
     */
    constexpr auto operator"" _q_hs_of_uV(long double l) { 
        return voltage<hundreds_of_microvolts, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace voltage_references {

    /// @brief Reference for the electric voltage in magnitude of tens of microvolts
    inline constexpr auto ts_of_uV = reference<dim_voltage, tens_of_microvolts>{};
    /// @brief Reference for the electric voltage in magnitude of hundreds of microvolts
    inline constexpr auto hs_of_uV = reference<dim_voltage, hundreds_of_microvolts>{};

}

namespace references {  
    using namespace voltage_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline power {

    /// @brief Alias for the quantity of voltage expressed in tens of microvolts
    template<Representation Rep = double> using ts_of_uV = units::isq::si::voltage<units::isq::si::tens_of_microvolts, Rep>;
    /// @brief Alias for the quantity of voltage expressed in hundreds of microvolts
    template<Representation Rep = double> using hs_of_uV = units::isq::si::voltage<units::isq::si::hundreds_of_microvolts, Rep>;

}

/* ================================================================================================================================ */

#endif
