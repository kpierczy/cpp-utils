/** ==================================================================================================================================
 * @file     expand.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 5:32:36 pm
 * @modified Thursday, 3rd February 2022 11:37:42 am
 * @project  Winder
 * @brief
 *    
 *    Declaration of the concatenation macros
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_PREPROCESSOR_CAT_H__
#define __ESTD_PREPROCESSOR_CAT_H__

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Concatenates two tokens with each other
 */
#define CAT(a, b) CAT_IMP(a, b)
#define CAT_IMP(a, b) a ## b

/* ================================================================================================================================ */

#endif
