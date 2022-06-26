/* ============================================================================================================================ *//**
 * @file       pointers.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 28th January 2022 11:53:13 am
 * @modified   Sunday, 26th June 2022 11:56:58 am
 * @project    cpp-utils
 * @brief      Header file of general pointers -related tools
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

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
