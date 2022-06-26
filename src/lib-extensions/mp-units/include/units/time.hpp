/* ============================================================================================================================ *//**
 * @file       time.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 6:41:31 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing time values (extends 
 *             mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_TIME_H__
#define __UNITS_TIME_H__

/* =========================================================== Includes =========================================================== */

#include <chrono>
#include <numbers>
#include "estd/traits.hpp"
#include "units/unit.h"
#include "units/isq/si/time.h"
#include "units/isq/si/prefixes.h"
#include "units/prefixes.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/// @brief Unit representing tens of milliseconds (hundreths of seconds / centiseconds)
struct centisecond : prefixed_unit<centisecond, centi, second> {};
/// @brief Unit representing hundreds of milliseconds (tenths of seconds / deciseconds)
struct decisecond : prefixed_unit<decisecond, deci, second> {};
/// @brief Unit representing tens of microseconds
struct tens_of_microseconds : prefixed_unit<tens_of_microseconds, tens_of_micros, second> {};
/// @brief Unit representing hundreds of microseconds
struct hundreds_of_microseconds : prefixed_unit<tens_of_microseconds, hundreds_of_micros, second> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating time quantity with centiseconds units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_cs(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return time<centisecond, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating time quantity with centiseconds units
     *     from long double
     */
    constexpr auto operator"" _q_cs(long double l) { 
        return time<centisecond, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating time quantity with deciseconds units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_ds(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return time<decisecond, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating time quantity with deciseconds units
     *     from long double
     */
    constexpr auto operator"" _q_ds(long double l) { 
        return time<decisecond, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating time quantity with tens of microseconds
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_ts_of_us(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return time<tens_of_microseconds, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating time quantity with tens of microseconds
     *     from long double
     */
    constexpr auto operator"" _q_ts_of_us(long double l) { 
        return time<tens_of_microseconds, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating time quantity with hundreds of microseconds
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_hs_of_us(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return time<hundreds_of_microseconds, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating time quantity with hundreds of microseconds
     *     from long double
     */
    constexpr auto operator"" _q_hs_of_us(long double l) { 
        return time<hundreds_of_microseconds, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace time_references {

    /// @brief Reference for the time in magnitude of centisecond
    inline constexpr auto cs = reference<dim_time, centisecond>{};
    /// @brief Reference for the time in magnitude of decisecond
    inline constexpr auto ds = reference<dim_time, decisecond>{};
    /// @brief Reference for the time in magnitude of tens of microseconds
    inline constexpr auto ts_of_us = reference<dim_time, tens_of_microseconds>{};
    /// @brief Reference for the time in magnitude of hundreds of microseconds
    inline constexpr auto hs_of_us = reference<dim_time, hundreds_of_microseconds>{};

}

namespace references {  
    using namespace time_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline time {

    /// @brief Alias for the quantity of time in magnitude of centisecond
    template<Representation Rep = double> using cs = units::isq::si::time<units::isq::si::centisecond, Rep>;
    /// @brief Alias for the quantity of time in magnitude of decisecond
    template<Representation Rep = double> using ds = units::isq::si::time<units::isq::si::decisecond, Rep>;
    /// @brief Alias for the quantity of time in magnitude of tens of microseconds
    template<Representation Rep = double> using ts_of_us = units::isq::si::time<units::isq::si::tens_of_microseconds, Rep>;
    /// @brief Alias for the quantity of time in magnitude of hundreds of microseconds
    template<Representation Rep = double> using hs_of_us = units::isq::si::time<units::isq::si::hundreds_of_microseconds, Rep>;

}

/* ============================================================ Helpers =========================================================== */

namespace units::isq::si {

    /**
     * @brief Coverts time expressed by the mp-units-style structure to the corresponding
     *    std::chrono::duration
     * @tparam T 
     *    type of the time to be convrted
     * @param time 
     *    time to be converted
     * @returns 
     *    @p time converted to the corresponding specialization of @ref std::chrono::duration
     */
    template<typename T> requires
        Time<T>
    constexpr auto time_to_chrono(const T &time);

    /**
     * @brief Coverts time expressed as std::chrono::duration to the corresponding
     *    mp-units-style structure
     * @tparam T 
     *    type of the time to be convrted
     * @param time 
     *    time to be converted
     * @returns 
     *    @p time converted to the corresponding mp-units-style structure
     */
    template<typename T> requires
        estd::is_specialization_of<T, std::chrono::duration>::value
    constexpr auto chrono_to_time(const T &time);

    /**
     * @brief Calculates difference between two times taking overflow of the @p late into account
     * 
     * @tparam Early 
     *    type of the earlier timepoint
     * @tparam Late 
     *     type of the later timepoint
     * @param early 
     *     earlier timepoint
     * @param late 
     *     laters timepoint
     * @returns 
     *     time difference between two timepoints
     * 
     * @note Return type is the wider of arguments types
     */
    template<isq::Time Early, isq::Time Late>
    constexpr auto time_diff(Early early, Late late) -> decltype(early - late);

}

/* ==================================================== Implementation includes =================================================== */

#include "units/time/impl/time.hpp"

/* ================================================================================================================================ */

#endif
