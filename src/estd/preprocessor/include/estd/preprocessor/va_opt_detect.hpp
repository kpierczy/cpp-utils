/** ==================================================================================================================================
 * @file       va_opt_detect.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Thursday, 30th December 2021 5:32:36 pm
 * @modified   Thursday, 3rd February 2022 11:37:42 am
 * @project    cpp-utils
 * @brief      Declaration of the __VA_OPT__ detector macros
 *    
 * @see https://www.scs.stanford.edu/~dm/blog/va-opt.pdf
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_PREPROCESSOR_VA_OPT_DETECT_H__
#define __ESTD_PREPROCESSOR_VA_OPT_DETECT_H__

/* ========================================================= Declarations ========================================================= */

#define PP_THIRD_ARG(a,b,c,...) c
#define VA_OPT_SUPPORTED_I(...) PP_THIRD_ARG(__VA_OPT__(,),true,false,)
#define VA_OPT_SUPPORTED VA_OPT_SUPPORTED_I(?)

/* ================================================================================================================================ */

#endif
