/* ============================================================================================================================ *//**
 * @file       events.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 4:42:02 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Header undefining macros defined in the events.hpp file
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifdef __UTILS_SML_UTILS_MACROS_EVENTS_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef EMPTY_EVENT
#undef EMPTY_EVENT
#endif

#ifdef EMPTY_EVENTS
#undef EMPTY_EVENTS
#endif

#ifdef EVENT_MEMBER
#undef EVENT_MEMBER
#endif

/* ===================================================== Dependencies cleanup ===================================================== */

#include "estd/preprocessor/cleanup/foreach.hpp"

/* ================================================================================================================================ */

#undef __UTILS_SML_UTILS_MACROS_EVENTS_H__
#endif
