/** ==================================================================================================================================
 * @file     pulses.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 2nd December 2021 2:22:27 pm
 * @modified Thursday, 3rd February 2022 11:42:00 am
 * @project  Winder
 * @brief
 *    
 *    Definitions of units, dimensions and quantities (based on the mp-units library) describing pulses values
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_PULSES_H__
#define __UNITS_PULSES_H__

/* =========================================================== Includes =========================================================== */

#include "units/per_angle.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace units {

/* ============================================================ Units ============================================================= */

/// @brief Alias name for the number of pulses per radian
struct pulse_per_radian : alias_unit<one_per_radian, "P/rad", no_prefix> {};

/// @brief Alias name for the number of pulses per revolution
struct pulse_per_revolution : alias_unit<one_per_revolution, "P/rev", no_prefix> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating 'per radian' quantity with pulses per radian units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_pulses_per_rad(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return per_angle<pulse_per_radian, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'per radian' quantity with pulses per radian units
     *     from long double
     */
    constexpr auto operator"" _q_pulses_per_rad(long double l) { 
        return per_angle<pulse_per_radian, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating 'per revolution' quantity with pulses per revolution units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_pulses_per_rev(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return per_angle<pulse_per_revolution, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'per revolution' quantity with pulses per revolution units
     *     from long double
     */
    constexpr auto operator"" _q_pulses_per_rev(long double l) { 
        return per_angle<pulse_per_revolution, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace references {

    /// @brief Reference for the 'per radian' unit expressed in units of pulses per radian
    inline constexpr auto pulse_per_rad = reference<dim_per_angle, pulse_per_radian>{};
    /// @brief Reference for the 'per revolution' unit expressed in units of pulses per revolution
    inline constexpr auto pulse_per_rev = reference<dim_per_angle, pulse_per_revolution>{};
    
}

/* ================================================================================================================================ */

} // End namespace units

/* =========================================================== Aliases ============================================================ */

namespace units::aliases {

    /// @brief Quantity alias for the 'per radian' unit expressed in units of pulses per radian
    template<Representation Rep = double> using pulse_per_rad = units::per_angle<units::pulse_per_radian, Rep>;
    /// @brief Quantity alias for the 'per revolution' unit expressed in units of pulses per revolution
    template<Representation Rep = double> using pulse_per_rev = units::per_angle<units::pulse_per_revolution, Rep>;
    
}

/* ================================================================================================================================ */

#endif
