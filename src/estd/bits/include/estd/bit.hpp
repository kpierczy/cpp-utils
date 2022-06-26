/* ============================================================================================================================ *//**
 * @file       bit.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Monday, 13th June 2022 1:18:14 am
 * @modified   Sunday, 26th June 2022 3:11:18 pm
 * @project    cpp-utils
 * @brief      Definitions of common utilities for handling bit-aligned data
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_BIT_H__
#define __ESTD_BIT_H__

/* =========================================================== Includes =========================================================== */

// Private includes
#include <cstdint>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* =========================================================== Constants ========================================================== */

/// Number of bits in a byte
inline constexpr std::size_t BITS_IN_BYTE = 8;

/// Number of bits in a byte
inline constexpr std::size_t BITS_IN_WORD = 16;

/* =========================================================== Functions ========================================================== */

/**
 * @brief Gets value of the bit at position @p position
 */
template<typename ValueT>
static constexpr auto get_bit(ValueT &&value, std::size_t position);

/**
 * @brief Sets @p position bit in the @p value
 */
template<typename ValueT>
static constexpr auto set_bit(ValueT &value, std::size_t position);

/**
 * @brief Clears @p position bit in the @p value
 */
template<typename ValueT>
static constexpr auto clear_bit(ValueT &value, std::size_t position);

/**
 * @brief Copies @p n bytes from @p src to @p dst
 */
static inline void copy_bytes(const uint8_t *src, uint8_t *dst, std::size_t n);

/**
 * @brief Copies @p n bytes from @p src to @p dst given the @p bitoffset of data in @p src
 */
static void copy_bytes_from_bitshifted(const uint8_t *src, uint8_t *dst, std::size_t n, std::size_t bitoffset);

/**
 * @brief Copies @p n bytes from @p src to @p dst with the required @p bitoffset of data in @p dst
 */
static void copy_bytes_to_bitshifted(const uint8_t *src, uint8_t *dst, std::size_t n, std::size_t bitoffset);

/**
 * @brief Copies @p n bits from @p src to @p dst
 */
static inline void copy_bits(const uint8_t *src, uint8_t *dst, std::size_t n);

/**
 * @brief Copies @p n bits from @p src to @p dst given the @p bitoffset of data in @p src
 */
static inline void copy_bits_from_bitshifted(const uint8_t *src, uint8_t *dst, std::size_t n, std::size_t bitoffset);

/**
 * @brief Copies @p n bits from @p src to @p dst with the required @p bitoffset of data in @p dst
 */
static inline void copy_bits_to_bitshifted(const uint8_t *src, uint8_t *dst, std::size_t n, std::size_t bitoffset);

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/bit/bit.hpp"

/* ================================================================================================================================ */

#endif
