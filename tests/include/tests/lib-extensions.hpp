/* ============================================================================================================================ *//**
 * @file       lib-extensions.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 28th February 2023 8:49:30 pm
 * @modified   Tuesday, 28th February 2023 8:53:01 pm
 * @project    cpp-utils
 * @brief      
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __TESTS_LIB_EXTENSIONS_H__
#define __TESTS_LIB_EXTENSIONS_H__

/* =========================================================== Includes =========================================================== */

// Compilation test for 'boost-sml'
#include "boost/sml/utils/actions.hpp"
#include "boost/sml/utils/events.hpp"
#include "boost/sml/utils/guards.hpp"
#include "boost/sml/utils/states.hpp"
#include "boost/sml/utils/dsl/sequence.hpp"
#include "boost/sml/utils/macros/events.hpp"
#include "boost/sml/utils/macros/states.hpp"
#include "boost/sml/utils/macros/transition_table.hpp"
#include "boost/sml/utils/macros/cleanup.hpp"
// Compilation test for 'mp-units'
#include "units/angle.hpp"
#include "units/angular_velocity.hpp"
#include "units/density.hpp"
#include "units/dimensionless.hpp"
#include "units/frequency.hpp"
#include "units/helpers.hpp"
#include "units/inductance.hpp"
#include "units/length_per_angle.hpp"
#include "units/moment_of_inertia.hpp"
#include "units/per_angle.hpp"
#include "units/power.hpp"
#include "units/prefixes.hpp"
#include "units/pulses.hpp"
#include "units/string.hpp"
#include "units/temperature.hpp"
#include "units/time.hpp"
#include "units/torque.hpp"
#include "units/voltage.hpp"

/* ========================================================== Definitions ========================================================= */

inline void lib_extensions_tests()
{
    
}

/* ================================================================================================================================ */

#endif

