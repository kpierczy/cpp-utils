/** ==================================================================================================================================
 * @file     helpers.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Saturday, 4th December 2021 6:42:03 pm
 * @modified Thursday, 3rd February 2022 11:42:00 am
 * @project  Winder
 * @brief
 *    
 *    Set of helper tools to be used with dimensionfull values
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_HELPERS_H__
#define __UNITS_HELPERS_H__

/* =========================================================== Includes =========================================================== */

#include "units/quantity.h"

/* =========================================================== Namespace ========================================================== */

namespace units {
    
/* ========================================================= Declarations ========================================================= */

/**
 * @brief Checks whether two equivalent quantities are equal with tolerance of @p tol
 * @tparam Left 
 *    type of the first quantity to be compared
 * @tparam Right 
 *    type of the second quantity to be compared
 * @tparam Tol 
 *    type of the tolerance value
 * @param left 
 *     first quantity to be compared
 * @param right 
 *     second quantity to be compared
 * @param tol 
 *     multiple of tolerance epsilon
 * @returns 
 *    @retval @c true if @p left and @p right are equal
 *    @retval @c false otherwise
 */
template<units::Quantity Left, units::QuantityEquivalentTo<Left> Right, units::QuantityEquivalentTo<Left> Tol>
inline constexpr bool is_equal(Left left, Right right, Tol tol);

/**
 * @brief Checks whether two equivalent quantities are equal with tolerance of unequality
 *    being @p tol times epsilon of the representation of the wider type of representation
 *    types of @p left and @p right
 * @tparam Left 
 *    type of the first quantity to be compared
 * @tparam Right 
 *    type of the second quantity to be compared
 * @param left 
 *     first quantity to be compared
 * @param right 
 *     second quantity to be compared
 * @param tol
 *     multiple of tolerance epsilon
 * @returns 
 *    @retval @c true if @p left and @p right are equal
 *    @retval @c false otherwise
 */
template<units::Quantity Left, units::QuantityEquivalentTo<Left> Right>
inline constexpr bool is_equal(Left left, Right right, unsigned tol = 1);

/**
 * @enum Range
 * @brief Type of the quantity range
 */
enum class Range {
    Inclusive,
    Exclusive
};

/**
 * @brief Helper constexpr class implementing comparisons used by the units::in_range function
 * @tparam range 
 *    type of the range to compare against (eithe rinclusive or exclusive)
 * @tparam Left 
 *    type of the left limit
 * @tparam Right 
 *    type of the right limit
 */
template<Range range_type, Quantity Left, units::QuantityEquivalentTo<Left> Right>
class range {
public:

    /**
     * @brief Creats comparison object with given limits
     * @param left 
     *    left limit of the range
     * @param right 
     *    right limit of the range
     */
    inline constexpr range(Left left, Right right);

    /**
     * @brief Tests @p value against the constructed range
     * @param value 
     *    value to eb tested
     * @returns 
     *    @retval @c true if @p value is in the range
     *    @retval @c false otherwise
     */
    template<units::QuantityEquivalentTo<Left> Value>
    inline constexpr bool operator()(Value value) const;

public:

    /// Left limit of the range
    Left left;
    /// Right limit of the range
    Right right;
    
};

/**
 * @brief Function constructing a 'range' functor obejct that can be called with a quantity 
 *    equivalent to both @ref decltype(left) and @ref decltype(right) to check whether it it
 *    in the given range
 * @tparam range_type ( optional, default: @c Range::Inclusive )
 *    type of the range (eithe rinclusive or exclusive)
 * @param left 
 *    left limit of the range
 * @param right 
 *    right limit of the range
 * @returns 
 *    callable range object constructed with given limits
 */
template<Range range_type = Range::Inclusive>
constexpr auto in_range(auto left, auto right) -> range<range_type, decltype(left), decltype(right)>;

/* ================================================================================================================================ */

} // End namespace units

/* ==================================================== Implementation includes =================================================== */

#include "units/helpers/impl/helpers.hpp"

/* ================================================================================================================================ */

#endif
