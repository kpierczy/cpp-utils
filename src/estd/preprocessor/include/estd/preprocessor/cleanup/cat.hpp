/** ==================================================================================================================================
 * @file     cat.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 4:42:02 pm
 * @modified Thursday, 3rd February 2022 11:44:02 am
 * @project  Winder
 * @brief
 *    
 *    Header undefining macros defined in the cat.hpp file
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

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
