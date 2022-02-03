/** ==================================================================================================================================
 * @file     pointers.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Friday, 28th January 2022 11:53:13 am
 * @modified Thursday, 3rd February 2022 11:34:22 am
 * @project  Winder
 * @brief
 *    
 *    Header file of general pointers -related tools
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_POINTERS_PTR_H__
#define __ESTD_POINTERS_PTR_H__

/* =========================================================== Includes =========================================================== */

#include <cstddef>

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ====================================================== Abstract utilities ====================================================== */

/**
 * @brief Helper method calculating offset of the member of the type @tparam T
 * @tparam T 
 *    type of the member
 * @tparam U 
 *    type fo the parent
 * @param member 
 *    pointer to the member
 * @returns 
 *    calculated offset
 */
template<class T, typename U>
std::ptrdiff_t member_offset(U T::* member);

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/pointers/impl/pointers.hpp"

/* ================================================================================================================================ */

#endif
