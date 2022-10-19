/* ============================================================================================================================ *//**
 * @file       tag.hpp
 * @author     Krzysztof Pierczyk (kpierczyk@emka-project.com.pl)
 * @maintainer Krzysztof Pierczyk (kpierczyk@emka-project.com.pl)
 * @date       Tuesday, 18th October 2022 7:03:31 am
 * @modified   Wednesday, 19th October 2022 9:16:38 pm
 * @project    SHARK_KB
 * @brief      Generic types helping with handling types as values
 * 
 * 
 * @copyright EMKA Project © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_MISCELLANEOUS_TAG_H__
#define __ESTD_MISCELLANEOUS_TAG_H__

/* ========================================================== Namespaces ========================================================== */

namespace estd::miscellaneous {

/* ============================================================= Tags ============================================================= */

/**
 * @brief Type gathering collesion of TTPs
 */
template<typename...>
struct multitag { };

/**
 * @brief Type holding TTP
 */
template<typename T>
struct tag {
    using type = T;
};

/**
 * @brief Type gathering collesion of NTTPs
 */
template<auto V>
struct multivtag { };

/**
 * @brief Type holding NTTP
 */
template<auto V>
struct vtag {
    static constexpr auto value = V;
};

/* ============================================================ Aliases =========================================================== */

/**
 * @brief Alias for typename Tag::type
 */
template<typename Tag>
using tag_t = typename Tag::type;

/**
 * @brief Alias for typename Vtag::type
 */
template<typename Vtag>
using vtag_v = Vtag::value;

/* ================================================================================================================================ */

} // End namespace estd::miscellaneous

/* ================================================================================================================================ */

#endif