/** ==================================================================================================================================
 * @file     fixed_string.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Monday, 12th July 2021 9:29:30 am
 * @modified Tuesday, 15th February 2022 10:44:55 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of the compile-time strings literal
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __ESTD_FIXED_STRING_IMPL_FIXED_STRING_DETAILS_H__
#define __ESTD_FIXED_STRING_IMPL_FIXED_STRING_DETAILS_H__

/* =========================================================== Includes =========================================================== */

#include "estd/fixed_string.hpp"

/* =========================================================== Namespace ========================================================== */

namespace estd {

/* ========================================================== Algorithms ========================================================== */

namespace details {

    /**
     * @brief Implementation of the std::copy for compilers where constexpr std::copy is not available
     * @tparam InputIterator 
     *     type of the input iterator
     * @tparam OutputIterator 
     *     type of the output iterator
     * @param ifirst 
     *     first element of the source range
     * @param ilast 
     *     last element of the source range
     * @param ofirst 
     *     first element of the destination range
     * @returns
     *     last element of the output range
     */
    template <typename InputIterator, typename OutputIterator>
    constexpr OutputIterator copy(InputIterator ifirst, InputIterator ilast, OutputIterator ofirst) {
    #if CPP20_CONSTEXPR_ALGORITHMS_PRESENT
        return std::copy(ifirst, ilast, ofirst);
    #else
        while (ifirst != ilast) {
            *ofirst++ = *ifirst++;
        }
        return ofirst;
    #endif 
    }

    /**
     * @brief Implementation of the std::fill for compilers where constexpr std::fill is not available
     * @tparam InputIterator 
     *     type of the input iterator
     * @tparam OutputIterator 
     *     type of the output iterator
     * @param ifirst 
     *     first element of the source range
     * @param ilast 
     *     last element of the source range
     * @param value 
     *     value to fill range with
     * @returns
     *     last element of the output range
     */
    template <typename ForwardIterator, typename T>
    constexpr void fill(ForwardIterator ifirst, ForwardIterator ilast, const T& value) {
    #if CPP20_CONSTEXPR_ALGORITHMS_PRESENT
        std::fill(ifirst, ilast, value);
    #else
        for (; ifirst != ilast; ++ifirst) {
            *ifirst = value;
        }
    #endif
    }

}

/* ================================================================================================================================ */

} // End namespace estd

#endif
