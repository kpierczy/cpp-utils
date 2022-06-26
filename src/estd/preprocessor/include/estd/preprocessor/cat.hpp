/* ============================================================================================================================ *//**
 * @file       expand.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 5:32:36 pm
 * @modified   Sunday, 26th June 2022 11:56:59 am
 * @project    cpp-utils
 * @brief      Declaration of the concatenation macros
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

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
