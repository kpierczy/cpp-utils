/** ==================================================================================================================================
 * @file     events.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 4:42:02 pm
 * @modified Thursday, 3rd February 2022 12:31:42 pm
 * @project  Winder
 * @brief
 *    
 *    Header undefining macros defined in the events.hpp file
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

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

#include "utils/miscellaneous/macros/cleanup/foreach.hpp"

/* ================================================================================================================================ */

#undef __UTILS_SML_UTILS_MACROS_EVENTS_H__
#endif
