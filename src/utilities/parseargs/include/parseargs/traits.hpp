/** ==================================================================================================================================
 * @file       traits.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 18th February 2022 2:00:39 pm
 * @modified   Friday, 18th February 2022 2:17:39 pm
 * @project    cpp-utils
 * @brief      Set of the helper traits used in the implementation of `parseargs` module
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __UTILITIES_PARSEARGS_TRAITS_H__
#define __UTILITIES_PARSEARGS_TRAITS_H__

/* =========================================================== Includes =========================================================== */

#include "parseargs/concepts.hpp"

/* ============================================================ Helpers =========================================================== */

/**
 * @brief Helper macro defining trait named @p trait met by the types
 *    fulfilling @p concept conept
 */
#define CONCEPT_TO_TRAIT(concept, trait)                \
                                                        \
    namespace details {                                 \
                                                        \
        template <typename T, typename = void>          \
        struct trait : std::false_type {};              \
                                                        \
        template <concept T>                            \
        struct trait<T> : std::true_type {};            \
                                                        \
    }                                                   \
                                                        \
    template <typename T>                               \
    struct trait<T> : details::trait {};                \
                                                        \
    template <typename T>                               \
    static constexpr bool trait ## _v = trait<T>::value;

/* ========================================================= Declarations ========================================================= */


/**
 * @brief Helper trait identifying container types
 */
CONCEPT_TO_TRAIT(Container, is_container);

/**
 * @brief Helper trait identifying streamable types
 */
CONCEPT_TO_TRAIT(Streamable, is_streamable);

/**
 * @brief Helper trait describing types that can be represented graphically
 */
CONCEPT_TO_TRAIT(Representable, is_representable);

/* ================================================================================================================================ */


#endif
