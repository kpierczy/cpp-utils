/* ============================================================================================================================ *//**
 * @file       states.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 4:42:02 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Header undefining macros defined in the states.hpp file
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifdef __UTILS_SML_UTILS_MACROS_STATES_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef EMPTY_STATE
#undef EMPTY_STATE
#endif

#ifdef OK_STATE
#undef OK_STATE
#endif

#ifdef CHOICE_PSEUDOSTATE
#undef CHOICE_PSEUDOSTATE
#endif

#ifdef EMPTY_STATES
#undef EMPTY_STATES
#endif

#ifdef OK_STATES
#undef OK_STATES
#endif

#ifdef CHOICE_PSEUDOSTATES
#undef CHOICE_PSEUDOSTATES
#endif

/* ===================================================== Dependencies cleanup ===================================================== */

#include "estd/preprocessor/cleanup/foreach.hpp"

/* ================================================================================================================================ */

#undef __UTILS_SML_UTILS_MACROS_STATES_H__
#endif
