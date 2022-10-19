/* ============================================================================================================================ *//**
 * @file       torque.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 3rd December 2021 12:48:07 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing torque values (extends 
 *             mp-units nemspaces)
 *   
 * @note This defintion of the torque differs from the mp-unit's definition when it comes to dimension. mp-unit's definition
 *    uses FLA^(-1) dimension when this one sticks to the FL. The rational behind np's dimplementation is that the torque has the
 *    same dimenion as energy (J = N * m). Moreover it can be handy to use FLA^(-1) definition (e.g. when the overall work, i.e.
 *    integral of the torque over the angle, is calculated).
 * @copyright Krzysztof Pierczyk © 2021
 */// ============================================================================================================================= */

#ifndef __UNITS_MOMENT_OF_TORQUE_H__
#define __UNITS_MOMENT_OF_TORQUE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/energy.h"
#include "units/isq/si/force.h"
#include "units/isq/si/length.h"

/* ================================================================================================================================ */
/*----------------------------------------------------------- Dimension------------------------------------------------------------ */
/* ================================================================================================================================ */

namespace units::isq {

/// @brief Definition of the recipie for torque based on the 'force' and 'length' dimensions (permutation 1) [aliasing dim_energy]
template<typename Child, Unit U, typename F_or_L, typename L_or_F>
using dim_torque = dim_energy<Child, U, F_or_L, L_or_F>;

/**
 * @brief Concept of the quantity of torque
 * @tparam T 
 *    type to be tested against the concept
 */
template<typename T>
concept Torque = QuantityOfT<T, dim_torque>;

}

/* ================================================================================================================================ */
/* ----------------------------------------------------------- System ------------------------------------------------------------- */
/* ================================================================================================================================ */

namespace units::isq::si {

/* =========================================================== Base Unit ========================================================== */

/**
 * @brief Base unit of the torque in the SI system (N * m)
 */
struct newton_metre : scaled_unit<ratio(1), joule> {};

/* =========================================================== Dimension ========================================================== */

/**
 * @brief Definition of the dimension of the torque in the SI untis system
 * @note This is a non-perfect trick to use two 'separate' dimensions types with the
 *    same physical dimension (FL). This is non-perfect as the base unit of the
 *    @ref dim_torque is still @ref joule. In general this is not problem as user will
 *    usually use literals/reference/aliases to construct this kind of quantities, but
 *    it is worth noticing.
 */
using dim_torque = dim_energy;

/* ========================================================= Derived Units ======================================================== */

/**
 * @brief Derived unit of the torque (N * cm)
 * @note Definition of the @ref centinewton_metre cannot use @ref prefixed_unti
 *    as the newton_metre has to be constructed as @ref scaled_unit type that
 *    cannot be prefixed (one should not use @ref alias_unit as it requires
 *    a name for the unit that is abusive, as this unit is derived from newtons
 *    and metres). Morover the unti has to derive from @ref joule to has the same 
 *    reference unit as @ref newton_metre
 */
struct centinewton_metre : scaled_unit<ratio(1, 100), joule> {};

/* ========================================================== Quantities ========================================================== */

/**
 * @brief Concept representing quantity of torque
 * @tparam T 
 *    quantity to be tested against concept
 */
template<typename T>
concept Torque = QuantityOf<T, dim_torque>;

/**
 * @brief Alias name for quantity of torque
 * @tparam U 
 *    unit representing the quantity
 * @tparam Rep 
 *    numerical representation of the quantity
 */
template<UnitOf<dim_torque> U, Representation Rep = double>
using torque = quantity<dim_torque, U, Rep>;

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating torque quantity with N * m units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_Nm(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return torque<newton_metre, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating torque quantity with N * m units
     *     from long double
     */
    constexpr auto operator"" _q_Nm(long double l) { 
        return torque<newton_metre, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating torque quantity with N * cm units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_cNm(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return torque<centinewton_metre, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating torque quantity with N * cm units
     *     from long double
     */
    constexpr auto operator"" _q_cNm(long double l) { 
        return torque<centinewton_metre, long double>(l); 
    }


}

/* ========================================================== References ========================================================== */

namespace torque_references {

    /// @brief Reference for the torque of one newton metre
    inline constexpr auto Nm = reference<dim_torque, newton_metre>{};
    /// @brief Reference for the torque of one centinewton metre
    inline constexpr auto cNm = reference<dim_torque, centinewton_metre>{};
    
}

namespace references {  
    using namespace torque_references;
}


/* ================================================================================================================================ */

} // End namespace units::isq::si

/* =========================================================== Aliases ============================================================ */

namespace units::aliases::isq::si::inline torque {

    /// @brief Quantity alias for the torque of one newton metre
    template<Representation Rep = double> using Nm = units::isq::si::torque<units::isq::si::newton_metre, Rep>;
    /// @brief Quantity alias for the torque of one centinewton metre
    template<Representation Rep = double> using cNm = units::isq::si::torque<units::isq::si::centinewton_metre, Rep>;

}

/* ================================================================================================================================ */

#endif
