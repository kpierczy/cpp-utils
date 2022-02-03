/** ==================================================================================================================================
 * @file     length_per_angle.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 16th December 2021 2:07:50 pm
 * @modified Thursday, 3rd February 2022 11:42:00 am
 * @project  Winder
 * @brief
 *    
 *    Definitions of units, dimensions and quantities (based on the mp-units library) describing quantity of length per quantity of 
 *    angle (extends mp-units nemspaces)
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_LENGTH_PER_ANGLE_H__
#define __UNITS_LENGTH_PER_ANGLE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/generic/angle.h"
#include "units/angle.hpp"
#include "units/isq/si/length.h"

/* =========================================================== Namespace ========================================================== */

namespace units::isq {

/* ================================================================================================================================ */
/*----------------------------------------------------------- Dimension------------------------------------------------------------ */
/* ================================================================================================================================ */

/**
 * @brief Base of the length per angle dimension
 * @tparam Child 
 *    downacting target
 * @tparam U 
 *    unit of the dimension
 * @tparam ...
 *    dimension's recipi
 */
template<typename Child, Unit U, typename...>
struct dim_length_per_angle;

/// @brief Definition of the recipie for 'length per angle' dimension based on the 'length' and 'angle' dimensions (permutation 1)
template<typename Child, Unit U, DimensionOfT<dim_length> L, DimensionOfT<dim_angle> A>
struct dim_length_per_angle<Child, U, L, A> : derived_dimension<Child, U, exponent<L, 1>, exponent<A, -1>> {};

/// @brief Definition of the recipie for 'length per angle' dimension based on the 'length' and 'angle' dimensions (permutation 2)
template<typename Child, Unit U, DimensionOfT<dim_angle> A, DimensionOfT<dim_length> L>
struct dim_length_per_angle<Child, U, A, L> : derived_dimension<Child, U, exponent<A, -1>, exponent<L, 1>> {};

/**
 * @brief Concept of the quantity of length per angle
 * @tparam T 
 *    type to be tested against the concept
 */
template<typename T>
concept LengthPerAngle = QuantityOfT<T, dim_length_per_angle>;

}

/* ================================================================================================================================ */
/* ----------------------------------------------------------- System ------------------------------------------------------------- */
/* ================================================================================================================================ */

namespace units::isq::si {
    
/* =========================================================== Base Unit ========================================================== */

/// @brief Base unit of the 'length per angle' dimension
struct metre_per_radian : unit<metre_per_radian> {};

/* =========================================================== Dimension ========================================================== */

/// @brief Definition of the 'length per revolution' dimension based on the 'metre' and 'radian' units
struct dim_length_per_angle : 
    isq::dim_length_per_angle<dim_length_per_angle, metre_per_radian, dim_length, dim_angle<radian>> {};

/* ========================================================= Derived Units ======================================================== */

/// @brief Derived unit of the 'millimetre per radian' dimension expressing number of millimetres per radian
struct millimetre_per_radian : derived_unit<millimetre_per_radian, dim_length_per_angle, millimetre, radian> {};

/// @brief Derived unit of the 'metre per revolution' dimension expressing number of metres per revolution
struct metre_per_revolution : derived_unit<metre_per_revolution, dim_length_per_angle, metre, revolution> {};
/// @brief Derived unit of the 'millimetre per revolution' dimension expressing number of millimetres per revolution
struct millimetre_per_revolution : derived_unit<millimetre_per_revolution, dim_length_per_angle, millimetre, revolution> {};

/* ========================================================== Quantities ========================================================== */

/**
 * @brief Concept representing quantity of 'length per angle'
 * @tparam T 
 *    quantity to be tested against concept
 */
template<typename T>
concept LengthPerAngle =  QuantityOf<T, dim_length_per_angle>;

/**
 * @brief Alias name for quantity of length per angle
 * @tparam U 
 *    unit representing the quantity
 * @tparam Rep 
 *    numerical representation of the quantity
 */
template<UnitOf<dim_length_per_angle> U, Representation Rep = double>
using length_per_angle = quantity<dim_length_per_angle, U, Rep>;

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating 'metre per radian' quantity with base units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_m_per_rad(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return length_per_angle<metre_per_radian, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'metre per radian' quantity with base units
     *     from long double
     */
    constexpr auto operator"" _q_m_per_rad(long double l) { 
        return length_per_angle<metre_per_radian, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating 'millimetre per radian' quantity with base units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_mm_per_rad(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return length_per_angle<millimetre_per_radian, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'millimetre per radian' quantity with base units
     *     from long double
     */
    constexpr auto operator"" _q_mm_per_rad(long double l) { 
        return length_per_angle<millimetre_per_radian, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating 'metre per revolution' quantity with base units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_m_per_rev(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return length_per_angle<metre_per_revolution, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'metre per revolution' quantity with base units
     *     from long double
     */
    constexpr auto operator"" _q_m_per_rev(long double l) { 
        return length_per_angle<metre_per_revolution, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating 'millimetre per revolution' quantity with base units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_mm_per_rev(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return length_per_angle<millimetre_per_revolution, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating 'millimetre per revolution' quantity with base units
     *     from long double
     */
    constexpr auto operator"" _q_mm_per_rev(long double l) { 
        return length_per_angle<millimetre_per_revolution, long double>(l); 
    }


}

/* ========================================================== References ========================================================== */

namespace length_per_angle_references {

    /// @brief Reference for the length per angle of a single metre per radian
    inline constexpr auto m_per_rad = reference<dim_length_per_angle, metre_per_radian>{};
    /// @brief Reference for the length per angle of a single millimetre per radian
    inline constexpr auto mm_per_rad = reference<dim_length_per_angle, millimetre_per_radian>{};
    /// @brief Reference for the length per angle of a single metre per revolutuion
    inline constexpr auto m_per_rev = reference<dim_length_per_angle, metre_per_revolution>{};
    /// @brief Reference for the length per angle of a single millimetre per revolutuion
    inline constexpr auto mm_per_rev = reference<dim_length_per_angle, millimetre_per_revolution>{};
    
}

namespace references {  
    using namespace length_per_angle_references;
}

/* ================================================================================================================================ */

} // End namespace units

/* =========================================================== Aliases ============================================================ */

namespace units::aliases::isq::si::inline length_per_angle {

    /// @brief Quantity alias for the 'length per angle' quantity expressed in metres per radian
    template<Representation Rep = double> using m_per_rad = units::isq::si::length_per_angle<units::isq::si::metre_per_radian, Rep>;
    /// @brief Quantity alias for the 'length per angle' quantity expressed in millimetres per radian
    template<Representation Rep = double> using mm_per_rad = units::isq::si::length_per_angle<units::isq::si::millimetre_per_radian, Rep>;
    /// @brief Quantity alias for the 'length per angle' quantity expressed in metres per revolution
    template<Representation Rep = double> using m_per_rev = units::isq::si::length_per_angle<units::isq::si::metre_per_revolution, Rep>;
    /// @brief Quantity alias for the 'length per angle' quantity expressed in millimetres per revolution
    template<Representation Rep = double> using mm_per_rev = units::isq::si::length_per_angle<units::isq::si::millimetre_per_revolution, Rep>;
    
    
}

/* ================================================================================================================================ */

#endif
