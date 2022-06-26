/* ============================================================================================================================ *//**
 * @file       angle.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 2:22:27 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing angle values (extends mp-units 
 *             nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_ANGLE_H__
#define __UNITS_ANGLE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/generic/angle.h"
#include "units/kind.h"
#include "units/quantity_kind.h"
#include "units/isq/si/prefixes.h"

/* ========================================================== Namespaces ========================================================== */

namespace units {

/* ============================================================= Units ============================================================ */

/**
 * @brief Degree unit of the angular dimension. Derivd from the @ref units::radian
 *    using @c π/180 scaling factor. @ref degree can prefixed with standard SI 
 *    prefixes
 */
struct degree : named_scaled_unit<degree,
    basic_symbol_text{"\u00B0", "deg"},
    isq::si::prefix,
    ratio(std::numbers::pi * 1'000'000'000, 180.0 * 1'000'000'000),
    radian
> {};

/**
 * @brief Revolution unit of the angular dimension. Derivd from the @ref units::radian
 *    using @c 2π scaling factor. @ref revolution unit can prefixed with standard SI 
 *    prefixes
 */
struct revolution : named_scaled_unit<revolution,
    basic_symbol_text{"rev"},
    isq::si::prefix,
    ratio(std::numbers::pi * 1'000'000'000, 500'000'000),
    radian
> {};

/* ========================================================== Dimensions ========================================================== */

/**
 * @brief Dimension kind representing electric angle dimension. Although when it comes
 *    to dimensional analysis, the electric cangle is the same dimension as an angle,
 *    it has different meaning and is used in different contexts
 */
struct electric_angle_kind : kind<electric_angle_kind, dim_angle<>> {};

/* ========================================================= Derived units ======================================================== */

/// @brief Tenth part of the degree
struct decidegree : prefixed_unit<decidegree, units::isq::si::deci, degree> {};

/* ========================================================== Quantities ========================================================== */

/**
 * @brief Concept representing an electrical angle quantity kind
 * @tparam T 
 *    quantity to be tested against concept
 */
template<typename T>
concept ElectricalAngle = 
    QuantityKindOf<T, electric_angle_kind>;

/**
 * @brief Alias name for the quantity kind of electric angle
 * @tparam U 
 *    unit used to represent the electric angle (must be derived from @ref units::radian)
 * @tparam Rep 
 *    type of the representation
 */
template<UnitOf<electric_angle_kind::dimension> U, Representation Rep = double>
using electric_angle = quantity_kind<electric_angle_kind, U, Rep>;

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating angle quantity with degree units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_deg(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angle<degree, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angle quantity with degree units
     *     from long double
     */
    constexpr auto operator"" _q_deg(long double l) { 
        return angle<degree, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating angle quantity with decidegree units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_ddeg(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angle<decidegree, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angle quantity with decidegree units
     *     from long double
     */
    constexpr auto operator"" _q_ddeg(long double l) { 
        return angle<decidegree, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating angle quantity with revolutions units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_rev(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return angle<revolution, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating angle quantity with revolutions units
     *     from long double
     */
    constexpr auto operator"" _q_rev(long double l) { 
        return angle<revolution, long double>(l); 
    }

}


inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating electirc angle quantity with radian units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_e_rad(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l));
        return electric_angle<radian, std::int64_t>(
            angle<radian, std::int64_t>(static_cast<std::int64_t>(l))
        ); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating electirc angle quantity with radian units
     *     from long double
     */
    constexpr auto operator"" _q_e_rad(long double l) { 
        return electric_angle<radian, long double>(
            angle<radian, long double>(l)
        ); 
    }

    /**
     * @brief UDL (User-Define Literal) creating electirc angle quantity with decidegree units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_e_ddeg(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return electric_angle<decidegree, std::int64_t>(
            angle<decidegree, std::int64_t>(static_cast<std::int64_t>(l))
        );
    }
    
    /**
     * @brief UDL (User-Define Literal) creating electirc angle quantity with decidegree units
     *     from long double
     */
    constexpr auto operator"" _q_e_ddeg(long double l) { 
        return electric_angle<decidegree, long double>(
            angle<decidegree, long double>(l)
        );
    }

    /**
     * @brief UDL (User-Define Literal) creating electirc angle quantity with degree units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_e_deg(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return electric_angle<degree, std::int64_t>(
            angle<degree, std::int64_t>(static_cast<std::int64_t>(l))
        ); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating electirc angle quantity with degree units
     *     from long double
     */
    constexpr auto operator"" _q_e_deg(long double l) { 
        return electric_angle<degree, long double>(
            angle<degree, long double>(l)
        ); 
    }
    
}

/* ========================================================== References ========================================================== */

namespace references {

    /// @brief Reference for the angle of single degree unit
    inline constexpr auto deg = reference<dim_angle<>, degree>{};
    /// @brief Reference for the angle of single decidegree unit
    inline constexpr auto ddeg = reference<dim_angle<>, decidegree>{};
    /// @brief Reference for the angle of single revolution unit
    inline constexpr auto rev = reference<dim_angle<>, revolution>{};
    /// @brief Reference for the electric angle of single radian unit
    inline constexpr auto e_rad = reference<dim_angle<>, radian>{};
    /// @brief Reference for the electric angle of single degree unit
    inline constexpr auto e_deg = reference<dim_angle<>, degree>{};
    /// @brief Reference for the electric angle of single decidegree unit
    inline constexpr auto e_ddeg = reference<dim_angle<>, decidegree>{};
    
}

/* ========================================================== Aliases ========================================================== */

namespace aliases {

    /// @brief Quantity alias for the angle of single radian unit
    template<Representation Rep = double> using rad = units::angle<radian, Rep>;
    /// @brief Quantity alias for the angle of single degree unit
    template<Representation Rep = double> using deg = units::angle<degree, Rep>;
    /// @brief Quantity alias for the angle of single decidegree unit
    template<Representation Rep = double> using ddeg = units::angle<decidegree, Rep>;
    /// @brief Quantity alias for the angle of single revolution unit
    template<Representation Rep = double> using rev = units::angle<revolution, Rep>;

    /// @brief Quantity alias for the electric angle of single radian unit
    template<Representation Rep = double> using e_rad = units::angle<radian, Rep>;
    /// @brief Quantity alias for the electric angle of single degree unit
    template<Representation Rep = double> using e_deg = units::angle<degree, Rep>;
    /// @brief Quantity alias for the electric angle of single decidegree unit
    template<Representation Rep = double> using e_ddeg = units::angle<decidegree, Rep>;

}

/* ================================================================================================================================ */

} // End namespace units

#endif
