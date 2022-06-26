/* ============================================================================================================================ *//**
 * @file       cat.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 4:42:02 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Header undefining macros defined in the cat.hpp file
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifdef __ESTD_PREPROCESSOR_CAT_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef CAT
#undef CAT
#endif

#ifdef CAT_IMP
#undef CAT_IMP
#endif

/* ================================================================================================================================ */

#undef __ESTD_PREPROCESSOR_CAT_H__
#endif
