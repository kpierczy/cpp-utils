/* ============================================================================================================================ *//**
 * @file       if_constexpr.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 4:42:02 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Header undefining macros defined in the if_constexpr.hpp file
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifdef __ESTD_PREPROCESSOR_IF_CONSTEXPR_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef IF_CONSTEXPR_NO_MATCH
#undef IF_CONSTEXPR_NO_MATCH
#endif

/* ================================================================================================================================ */

#undef __ESTD_PREPROCESSOR_IF_CONSTEXPR_H__
#endif
