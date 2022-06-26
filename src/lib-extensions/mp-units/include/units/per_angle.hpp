/* ============================================================================================================================ *//**
 * @file       per_angle.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 2:22:27 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing units of some quantity per 
 *             angle (extends mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_PER_ANGLE_H__
#define __UNITS_PER_ANGLE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/generic/angle.h"
#include "units/angle.hpp"

/* =========================================================== Namespace ========================================================== */

namespace units {

/* ================================================================================================================================ */
/*----------------------------------------------------------- Dimension------------------------------------------------------------ */
/* ================================================================================================================================ */

/**
 * @brief Base of the units per angle dimension
 * @tparam Child 
 *    downacting target
 * @tparam U 
 *    unit of the dimension
 * @tparam ...
 *    dimension's recipi
 */
template<typename Child, Unit U, typename...>
struct dim_per_angle_;

/// @brief Definition of the recipie for 'per angle' dimension on the 'angle' dimension
template<typename Child, Unit U, DimensionOfT<dim_angle> A>
struct dim_per_angle_<Child, U, A> : derived_dimension<Child, U, exponent<A, -1>> {};

/**
 * @brief Concept of the quantity of units per angle
 * @tparam T 
 *    type to be tested against the concept
 */
template<typename T>
concept PerAngle_ = QuantityOfT<T, dim_per_angle_>;

/* ================================================================================================================================ */
/* ----------------------------------------------------------- System ------------------------------------------------------------- */
/* ================================================================================================================================ */

/* =========================================================== Base Unit ========================================================== */

/// @brief Base unit of the 'per angle' dimension
struct one_per_radian : unit<one_per_radian> {};

/* =========================================================== Dimension ========================================================== */

/// @brief Definition of the 'per angle' dimension based on the 'radian' unit
struct dim_per_angle : dim_per_angle_<dim_per_angle, one_per_radian, dim_angle<>> {};

/* ========================================================= Derived Units ======================================================== */

/// @brief Derived unit of the 'per angle' dimension expressing number of units per revolution
struct one_per_revolution : derived_unit<one_per_revolution, dim_per_angle, revolution> {};

/* ========================================================== Quantities ========================================================== */

/**
 * @brief Concept representing quantity of 'per angle'
 * @tparam T 
 *    quantity to be tested against concept
 */
template<typename T>
concept PerAngle =  QuantityOf<T, dim_per_angle>;

/**
 * @brief Alias name for quantity of 'per angle'
 * @tparam U 
 *    unit representing the quantity
 * @tparam Rep 
 *    numerical representation of the quantity
 */
template<UnitOf<dim_per_angle> U, Representation Rep = double>
using per_angle = quantity<dim_per_angle, U, Rep>;

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating 'per revolution' quantity with 'per radian' units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_per_rad(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return per_angle<one_per_radian, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'per revolution' quantity with 'per radian' units
     *     from long double
     */
    constexpr auto operator"" _q_per_rad(long double l) { 
        return per_angle<one_per_radian, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating 'per revolution' quantity with base units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_per_rev(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return per_angle<one_per_revolution, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'per revolution' quantity with base units
     *     from long double
     */
    constexpr auto operator"" _q_per_rev(long double l) { 
        return per_angle<one_per_revolution, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace references {

    /// @brief Reference for the 'per revolution' unit expressed in units per revolution
    inline constexpr auto per_rev = reference<dim_per_angle, one_per_revolution>{};
    /// @brief Reference for the 'per revolution' unit expressed in units per radian
    inline constexpr auto per_rad = reference<dim_per_angle, one_per_radian>{};
    
}

/* ================================================================================================================================ */

} // End namespace units

/* =========================================================== Aliases ============================================================ */

namespace units::aliases {

    /// @brief Quantity alias for the 'per revolution' quantity expressed in units per revolution
    template<Representation Rep = double> using per_rev = units::per_angle<units::one_per_revolution, Rep>;
    /// @brief Quantity alias for the 'per revolution' quantity expressed in units per radian
    template<Representation Rep = double> using per_rad = units::per_angle<units::one_per_radian, Rep>;
    
}

/* ================================================================================================================================ */

#endif
