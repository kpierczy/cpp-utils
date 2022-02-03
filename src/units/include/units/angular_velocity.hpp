/** ==================================================================================================================================
 * @file     angular_velocity.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 2nd December 2021 2:22:27 pm
 * @modified Thursday, 3rd February 2022 11:41:15 am
 * @project  Winder
 * @brief
 *    
 *    Definitions of units, dimensions and quantities (based on the mp-units library) describing angular velocity values (extends 
 *    mp-units nemspaces)
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_ANGULAR_VELOCITY_H__
#define __UNITS_ANGULAR_VELOCITY_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/angular_velocity.h"
#include "units/isq/si/prefixes.h"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/**
 * @brief Unit of angular velocity expressing number of revolutions per minute
 */
struct revolutions_per_minute : named_scaled_unit<revolutions_per_minute,
    basic_symbol_text{"RPM"},
    isq::si::prefix,
    ratio(2.0 * std::numbers::pi * 1'000'000'000, 60.0 * 1'000'000'000),
    radian_per_second
> {};

/**
 * @brief Unit of angular velocity expressing number of revolutions per second
 */
struct revolutions_per_second : named_scaled_unit<revolutions_per_second,
    basic_symbol_text{"RPS"},
    isq::si::prefix,
    ratio(2.0 * std::numbers::pi * 1'000'000'000, 1'000'000'000),
    radian_per_second
> {};

/// @brief Unit of angular velocity expressing number of tenths of revolution per minute
struct decirevolutions_per_minute : prefixed_unit<decirevolutions_per_minute, deci, revolutions_per_minute> {};
/// @brief Unit of angular velocity expressing number of thousanths of revolution per minute
struct millirevolutions_per_minute : prefixed_unit<millirevolutions_per_minute, milli, revolutions_per_minute> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with RPM units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_RPM(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angular_velocity<revolutions_per_minute, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with RPM units
     *     from long double
     */
    constexpr auto operator"" _q_RPM(long double l) { 
        return angular_velocity<revolutions_per_minute, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with RPS units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_RPS(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angular_velocity<revolutions_per_second, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with RPS units
     *     from long double
     */
    constexpr auto operator"" _q_RPS(long double l) { 
        return angular_velocity<revolutions_per_second, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with dRPM units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_dRPM(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angular_velocity<decirevolutions_per_minute, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with dRPM units
     *     from long double
     */
    constexpr auto operator"" _q_dRPM(long double l) { 
        return angular_velocity<decirevolutions_per_minute, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with mRPM units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_mRPM(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angular_velocity<millirevolutions_per_minute, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angular velocity quantity with mRPM units
     *     from long double
     */
    constexpr auto operator"" _q_mRPM(long double l) { 
        return angular_velocity<millirevolutions_per_minute, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace angular_velocity_references {

    /// @brief Reference for the angular velocity of one radian per second
    inline constexpr auto rad_per_s = reference<dim_angular_velocity, radian_per_second>{};
    /// @brief Reference for the angular velocity of one revolution per minute
    inline constexpr auto RPM = reference<dim_angular_velocity, revolutions_per_minute>{};
    /// @brief Reference for the angular velocity of one revolution per second
    inline constexpr auto RPS = reference<dim_angular_velocity, revolutions_per_second>{};
    /// @brief Reference for the angular velocity of one tenth revolution per minute
    inline constexpr auto dRPM = reference<dim_angular_velocity, decirevolutions_per_minute>{};
    /// @brief Reference for the angular velocity of one thousanth revolution per minute
    inline constexpr auto mRPM = reference<dim_angular_velocity, millirevolutions_per_minute>{};

}

namespace references {  
    using namespace angular_velocity_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline angular_velocity {

    /// @brief Alias for the quantity of angular velocity expressed in revolution per minute
    template<Representation Rep = double> using RPM = units::isq::si::angular_velocity<units::isq::si::revolutions_per_minute, Rep>;
    /// @brief Alias for the quantity of angular velocity expressed in revolution per second
    template<Representation Rep = double> using RPS = units::isq::si::angular_velocity<units::isq::si::revolutions_per_second, Rep>;
    /// @brief Alias for the quantity of angular velocity expressed in decirevolution per minute
    template<Representation Rep = double> using dRPM = units::isq::si::angular_velocity<units::isq::si::decirevolutions_per_minute, Rep>;
    /// @brief Alias for the quantity of angular velocity expressed in millirevolution per minute
    template<Representation Rep = double> using mRPM = units::isq::si::angular_velocity<units::isq::si::millirevolutions_per_minute, Rep>;

}

/* ================================================================================================================================ */

#endif
