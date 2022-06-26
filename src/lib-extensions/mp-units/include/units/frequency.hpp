/* ============================================================================================================================ *//**
 * @file       frequency.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 2nd December 2021 6:45:04 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing pwoer values (extends 
 *             mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_FREQUENCY_H__
#define __UNITS_FREQUENCY_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/frequency.h"
#include "units/isq/si/prefixes.h"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ============================================================= Units ============================================================ */

/// @brief Unit representing tens of hertzs
struct decahertz : prefixed_unit<decahertz, deca, hertz> {};
/// @brief Unit representing tenths of hertzs
struct decihertz : prefixed_unit<decahertz, deci, hertz> {};

/* =========================================================== Literals =========================================================== */

inline namespace literals {

    /**
     * @brief UDL (User-Define Literal) creating frequency quantity with decahertz units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_daHz(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return frequency<decahertz, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating frequency quantity with decahertz units
     *     from long double
     */
    constexpr auto operator"" _q_daHz(long double l) { 
        return frequency<decahertz, long double>(l); 
    }

    /**
     * @brief UDL (User-Define Literal) creating frequency quantity with decihertz units
     *     from unsigned long long number
     */
    constexpr auto operator"" _q_dHz(unsigned long long l) { 
        gsl_ExpectsAudit(std::in_range<std::int64_t>(l)); 
        return frequency<decihertz, std::int64_t>(static_cast<std::int64_t>(l)); 
    }
    
    /**
     * @brief UDL (User-Define Literal) creating frequency quantity with decihertz units
     *     from long double
     */
    constexpr auto operator"" _q_dHz(long double l) { 
        return frequency<decihertz, long double>(l); 
    }

}

/* ========================================================== References ========================================================== */

namespace frequency_references {

    /// @brief Reference for the frequency in magnitude of decahertz
    inline constexpr auto daHz = reference<dim_frequency, decahertz>{};
    /// @brief Reference for the frequency in magnitude of decihertz
    inline constexpr auto dHz = reference<dim_frequency, decihertz>{};

}

namespace references {  
    using namespace frequency_references;
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

/* ========================================================== Aliases ========================================================== */

namespace units::aliases::isq::si::inline frequency {

    /// @brief Alias for the quantity of frequency expressed in decahertz
    template<Representation Rep = double> using daHz = units::isq::si::frequency<units::isq::si::decahertz, Rep>;
    /// @brief Alias for the quantity of frequency expressed in decihertz
    template<Representation Rep = double> using dHz = units::isq::si::frequency<units::isq::si::decihertz, Rep>;

}

/* ================================================================================================================================ */

#endif
