/** ==================================================================================================================================
 * @file     moment_of_inertia.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 2nd December 2021 2:22:27 pm
 * @modified Thursday, 3rd February 2022 11:41:15 am
 * @project  Winder
 * @brief
 *    
 *    Definitions of units, dimensions and quantities (based on the mp-units library) describing moment of inertia values 
 *    (extends mp-units nemspaces)
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_MOMENT_OF_INERTIA_H__
#define __UNITS_MOMENT_OF_INERTIA_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/mass.h"
#include "units/isq/si/length.h"

/* ================================================================================================================================ */
/*----------------------------------------------------------- Dimension------------------------------------------------------------ */
/* ================================================================================================================================ */

namespace units::isq {

/**
 * @brief Base of the moment of intertia dimension
 * @tparam Child 
 *    downacting target
 * @tparam U 
 *    unit of the dimension
 * @tparam ...
 *    dimension's recipi
 */
template<typename Child, Unit U, typename...>
struct dim_moment_of_inertia;

/// @brief Definition of the recipie for moment of inertia based on the 'mass' and 'length' dimensions (permutation 1)
template<typename Child, Unit U, DimensionOfT<dim_mass> M, DimensionOfT<dim_length> L>
struct dim_moment_of_inertia<Child, U, M, L> : derived_dimension<Child, U, exponent<M, 1>, exponent<L, 2>> {};

/// @brief Definition of the recipie for moment of inertia based on the 'mass' and 'length' dimensions (permutation 2)
template<typename Child, Unit U, DimensionOfT<dim_length> L, DimensionOfT<dim_mass> M>
struct dim_moment_of_inertia<Child, U, L, M> : derived_dimension<Child, U, exponent<L, 2>, exponent<M, 1>> {};

/**
 * @brief Concept of the quantity of moment of inertia
 * @tparam T 
 *    type to be tested against the concept
 */
template<typename T>
concept MomentOfInertia = QuantityOfT<T, dim_moment_of_inertia>;

}

/* ================================================================================================================================ */
/* ----------------------------------------------------------- System ------------------------------------------------------------- */
/* ================================================================================================================================ */

namespace units::isq::si {

/* =========================================================== Base Unit ========================================================== */

/**
 * @brief Base unit of the moment of inertia in the SI system (kg * m^2)
 */
struct kilogram_metre_squared : unit<kilogram_metre_squared> {};

/* =========================================================== Dimension ========================================================== */

/**
 * @brief Definition of the dimension of the moment of inertia in the SI untis system
 */
struct dim_moment_of_inertia : 
    isq::dim_moment_of_inertia<dim_moment_of_inertia, kilogram_metre_squared, dim_mass, dim_length> {};

/* ========================================================= Derived Units ======================================================== */

/// @brief Derived unit of the moment of inertia (g * cm^2)
struct gram_centimetre_squared : derived_unit<gram_centimetre_squared, dim_moment_of_inertia, gram, centimetre> {};
/// @brief Derived unit of the moment of inertia (10^1 * g * cm^2)
struct decagram_centimetre_squared : derived_unit<gram_centimetre_squared, dim_moment_of_inertia, decagram, centimetre> {};

/* ========================================================== Quantities ========================================================== */

/**
 * @brief Concept representing quantity of moment of inertia
 * @tparam T 
 *    quantity to be tested against concept
 */
template<typename T>
concept MomentOfInertia = QuantityOf<T, dim_moment_of_inertia>;

/**
 * @brief Alias name for quantity of moment of inertia
 * @tparam U 
 *    unit representing the quantity
 * @tparam Rep 
 *    numerical representation of the quantity
 */
template<UnitOf<dim_moment_of_inertia> U, Representation Rep = double>
using moment_of_inertia = quantity<dim_moment_of_inertia, U, Rep>;

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating moment of inertia quantity with kg * m^2 units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_kg_m2(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return moment_of_inertia<kilogram_metre_squared, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating moment of inertia quantity with kg * m^2 units
     *     from long double
     */
    constexpr auto operator"" _q_kg_m2(long double l) { 
        return moment_of_inertia<kilogram_metre_squared, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating moment of inertia quantity with g * cm^2 units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_g_cm2(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return moment_of_inertia<gram_centimetre_squared, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating moment of inertia quantity with g * cm^2 units
     *     from long double
     */
    constexpr auto operator"" _q_g_cm2(long double l) { 
        return moment_of_inertia<gram_centimetre_squared, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating moment of inertia quantity with dag * cm^2 units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_dag_cm2(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return moment_of_inertia<decagram_centimetre_squared, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating moment of inertia quantity with dag * cm^2 units
     *     from long double
     */
    constexpr auto operator"" _q_dag_cm2(long double l) { 
        return moment_of_inertia<decagram_centimetre_squared, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace moment_of_inertia_references {

    /// @brief Reference for the moment of inertia of kilogram meter squared
    inline constexpr auto kg_m2 = reference<dim_moment_of_inertia, kilogram_metre_squared>{};
    /// @brief Reference for the moment of inertia of gram centimeter squared
    inline constexpr auto g_cm2 = reference<dim_moment_of_inertia, gram_centimetre_squared>{};
    /// @brief Reference for the moment of inertia of decagram centimeter squared
    inline constexpr auto dag_cm2 = reference<dim_moment_of_inertia, decagram_centimetre_squared>{};
    
}

namespace references {  
    using namespace moment_of_inertia_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* =========================================================== Aliases ============================================================ */

namespace units::aliases::isq::si::inline moment_of_inertia {

    /// @brief Quantity alias for the moment of inertia of kilogram meter squared
    template<Representation Rep = double> using kg_m2 = units::isq::si::moment_of_inertia<units::isq::si::kilogram_metre_squared, Rep>;
    /// @brief Quantity alias for the moment of inertia of gram centimeter squared
    template<Representation Rep = double> using g_cm2 = units::isq::si::moment_of_inertia<units::isq::si::gram_centimetre_squared, Rep>;
    /// @brief Quantity alias for the moment of inertia of decagram centimeter squared
    template<Representation Rep = double> using dag_cm2 = units::isq::si::moment_of_inertia<units::isq::si::decagram_centimetre_squared, Rep>;

}

/* ================================================================================================================================ */

#endif
