/** ==================================================================================================================================
 * @file     va_opt_detect.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 4:42:02 pm
 * @modified Thursday, 3rd February 2022 11:37:42 am
 * @project  Winder
 * @brief
 *    
 *    Header undefining macros defined in the va_opt_detect.hpp file
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifdef __ESTD_PREPROCESSOR_VA_OPT_DETECT_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef PP_THIRD_ARG
#undef PP_THIRD_ARG
#endif

#ifdef VA_OPT_SUPPORTED_I
#undef VA_OPT_SUPPORTED_I
#endif

#ifdef VA_OPT_SUPPORTED
#undef VA_OPT_SUPPORTED
#endif

/* ================================================================================================================================ */

#undef __ESTD_PREPROCESSOR_VA_OPT_DETECT_H__
#endif
