/** ==================================================================================================================================
 * @file     inductance.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 2nd December 2021 6:41:31 pm
 * @modified Thursday, 3rd February 2022 11:42:00 am
 * @project  Winder
 * @brief
 *    
 *    Definitions of units, dimensions and quantities (based on the mp-units library) describing inductance values (extends 
 *    mp-units nemspaces)
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_INDUCTANCE_H__
#define __UNITS_INDUCTANCE_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/inductance.h"
#include "units/isq/si/prefixes.h"
#include "units/prefixes.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/**
 * @brief Unit representing tens of microhenries
 */
struct tens_of_microhenries : prefixed_unit<tens_of_microhenries, tens_of_micros, henry> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating inductance quantity with tens of microhenries units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_ts_of_uH(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return inductance<tens_of_microhenries, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating inductance quantity with tens of microhenries units
     *     from long double
     */
    constexpr auto operator"" _q_ts_of_uH(long double l) { 
        return inductance<tens_of_microhenries, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace inductance_references {

    /// @brief Reference for the electric inductance in magnitude of tens of microhenries
    inline constexpr auto ts_of_uH = reference<dim_inductance, tens_of_microhenries>{};

}

namespace references {  
    using namespace inductance_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline inductance {

    /// @brief Alias for the quantity of electric inductance expressed in tens of microhenries
    template<Representation Rep = double> using ts_of_uH = units::isq::si::inductance<units::isq::si::tens_of_microhenries, Rep>;

}

/* ================================================================================================================================ */

#endif
