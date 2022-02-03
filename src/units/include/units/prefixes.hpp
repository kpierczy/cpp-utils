/** ==================================================================================================================================
 * @file     prefixes.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 2nd December 2021 6:15:42 pm
 * @modified Thursday, 3rd February 2022 11:41:15 am
 * @project  Winder
 * @brief
 *    
 *    Definition of custom units' prefixes extending prefixes defined by mp-units library
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_PREFIXES_H__
#define __UNITS_PREFIXES_H__

/* =========================================================== Includes =========================================================== */

#include "units/symbol_text.h"
#include "units/isq/si/prefixes.h"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ========================================================== Declarations ======================================================== */

/**
 * @brief Use shortcut for basic symbol text
 */
template<typename StandardCharT, std::size_t N, std::size_t M>
using bst = units::basic_symbol_text<StandardCharT, N, M>;

/**
 * @brief Use shortcut for IS prefixes' family
 */
using sip = units::isq::si::prefix;

/* ============================================-=============== Prefixes ========================================================== */

struct     tens_of_micros : units::prefix<tens_of_micros,       sip, bst{"tens of \u00b5",     "tens of u"},       ratio(1, 1,   -5)> {};
struct hundreds_of_micros : units::prefix<hundreds_of_micros,   sip, bst{"hundreds of \u00b5", "hundreds of u"},   ratio(1, 1,   -4)> {};
struct      tens_of_nanos : units::prefix<tens_of_nanos,        sip, bst{                      "tens of u"},       ratio(1, 1,   -8)> {};
struct  hundreds_of_nanos : units::prefix<hundreds_of_nanos,    sip, bst{                      "hundreds of u"},   ratio(1, 1,   -7)> {};
struct      tens_of_picos : units::prefix<tens_of_picos,        sip, bst{                      "tens of p"},       ratio(1, 1,  -11)> {};
struct  hundreds_of_picos : units::prefix<hundreds_of_picos,    sip, bst{                      "hundreds of p"},   ratio(1, 1,  -10)> {};

/* ================================================================================================================================ */

} // End namespace units::isq::si

#endif
