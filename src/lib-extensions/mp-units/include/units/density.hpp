/* ============================================================================================================================ *//**
 * @file       density.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 28th January 2022 12:52:36 pm
 * @modified   Sunday, 26th June 2022 11:57:52 am
 * @project    cpp-utils
 * @brief      Definitions of units, dimensions and quantities (based on the mp-units library) describing density values (extends 
 *             mp-units nemspaces)
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UNITS_DENSITY_H__
#define __UNITS_DENSITY_H__

/* =========================================================== Includes =========================================================== */

#include <numbers>
#include "units/unit.h"
#include "units/isq/si/density.h"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ========================================================== References ========================================================== */

namespace references {

    /// @brief Reference for the density quantity expressed in kg/m^3
    inline constexpr auto kg_per_m3 = reference<dim_density, kilogram_per_metre_cub>{};

}

/* ================================================================================================================================ */

}

#endif
