/** ==================================================================================================================================
 * @file     sequence.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Saturday, 15th January 2022 1:44:31 pm
 * @modified Saturday, 15th January 2022 6:38:25 pm
 * @project  Winder
 * @brief
 *    
 *    DSL-sequence macros cleanup
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */


#ifdef __UTILS_SML_DSL_MACROS_SEQUENCE_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef ACTIONS_SEQUENCE_STATE_TRANSITIONS
#undef ACTIONS_SEQUENCE_STATE_TRANSITIONS
#endif

#ifdef ACTIONS_SEQUENCE_OR
#undef ACTIONS_SEQUENCE_OR
#endif

#ifdef ACTIONS_SEQUENCE_OR_IMPL
#undef ACTIONS_SEQUENCE_OR_IMPL
#endif

#ifdef ACTIONS_SEQUENCE_OR_IMPL_AGAIN
#undef ACTIONS_SEQUENCE_OR_IMPL_AGAIN
#endif

/* ================================================================================================================================ */

#undef __UTILS_SML_DSL_MACROS_SEQUENCE_H__
#endif
