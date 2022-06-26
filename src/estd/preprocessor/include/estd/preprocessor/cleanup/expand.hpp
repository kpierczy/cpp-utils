/* ============================================================================================================================ *//**
 * @file       expand.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 4:42:02 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Header undefining macros defined in the expand.hpp file
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifdef __ESTD_PREPROCESSOR_EXPAND_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef EXPAND9
#undef EXPAND9
#endif

#ifdef EXPAND8
#undef EXPAND8
#endif

#ifdef EXPAND7
#undef EXPAND7
#endif

#ifdef EXPAND6
#undef EXPAND6
#endif

#ifdef EXPAND5
#undef EXPAND5
#endif

#ifdef EXPAND4
#undef EXPAND4
#endif

#ifdef EXPAND3
#undef EXPAND3
#endif

#ifdef EXPAND2
#undef EXPAND2
#endif

#ifdef EXPAND1
#undef EXPAND1
#endif

#ifdef EXPAND
#undef EXPAND
#endif

/* ================================================================================================================================ */

#undef __ESTD_PREPROCESSOR_EXPAND_H__
#endif
