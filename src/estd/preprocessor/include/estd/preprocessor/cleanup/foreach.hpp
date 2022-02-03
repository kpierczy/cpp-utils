/** ==================================================================================================================================
 * @file     foreach.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Thursday, 30th December 2021 4:42:02 pm
 * @modified Thursday, 3rd February 2022 11:38:04 am
 * @project  Winder
 * @brief
 *    
 *    Header undefining macros defined in the foreach.hpp file
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifdef __ESTD_PREPROCESSOR_FOREACH_H__

/* ========================================================== Namespaces ========================================================== */

#ifdef FOR_EACH_N
#undef FOR_EACH_N
#endif

#ifdef FOR_EACH_N_HELPER
#undef FOR_EACH_N_HELPER
#endif

#ifdef FOR_EACH_N_AGAIN
#undef FOR_EACH_N_AGAIN
#endif

#ifdef FOR_EACH
#undef FOR_EACH
#endif

#ifdef FOR_EACH_TUPLE2
#undef FOR_EACH_TUPLE2
#endif

#ifdef FOR_EACH_PAIR
#undef FOR_EACH_PAIR
#endif

#ifdef FOR_EACH_TUPLE3
#undef FOR_EACH_TUPLE3
#endif

#ifdef FOR_EACH_TRIPLET
#undef FOR_EACH_TRIPLET
#endif

#ifdef FOR_EACH_TUPLE4
#undef FOR_EACH_TUPLE4
#endif

#ifdef FOR_EACH_QUADRUPLET
#undef FOR_EACH_QUADRUPLET
#endif

#ifdef FOR_EACH_TUPLE5
#undef FOR_EACH_TUPLE5
#endif

#ifdef FOR_EACH_TUPLE6
#undef FOR_EACH_TUPLE6
#endif

#ifdef FOR_EACH_TUPLE7
#undef FOR_EACH_TUPLE7
#endif

#ifdef FOR_EACH_TUPLE8
#undef FOR_EACH_TUPLE8
#endif

#ifdef FOR_EACH_TUPLE9
#undef FOR_EACH_TUPLE9
#endif

#ifdef FOR_EACH_N_COM1
#undef OR_EACH_N_COM1
#endif

#ifdef FOR_EACH_N_HELPER_COM1
#undef OR_EACH_N_HELPER_COM1
#endif

#ifdef FOR_EACH_N_AGAIN_COM1
#undef OR_EACH_N_AGAIN_COM1
#endif

#ifdef FOR_EACH_COTIGUOUS_N
#undef OR_EACH_COTIGUOUS_N
#endif

#ifdef FOR_EACH_COTIGUOUS_N_HELPER
#undef OR_EACH_COTIGUOUS_N_HELPER
#endif

#ifdef FOR_EACH_COTIGUOUS_N_AGAIN
#undef OR_EACH_COTIGUOUS_N_AGAIN
#endif

#ifdef FOR_EACH_COTIGUOUS
#undef OR_EACH_COTIGUOUS
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE2
#undef OR_EACH_COTIGUOUS_TUPLE2
#endif

#ifdef FOR_EACH_COTIGUOUS_PAIR
#undef OR_EACH_COTIGUOUS_PAIR
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE3
#undef OR_EACH_COTIGUOUS_TUPLE3
#endif

#ifdef FOR_EACH_COTIGUOUS_TRIPLET
#undef OR_EACH_COTIGUOUS_TRIPLET
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE4
#undef OR_EACH_COTIGUOUS_TUPLE4
#endif

#ifdef FOR_EACH_COTIGUOUS_QUADRUPLET
#undef OR_EACH_COTIGUOUS_QUADRUPLET
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE5
#undef OR_EACH_COTIGUOUS_TUPLE5
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE6
#undef OR_EACH_COTIGUOUS_TUPLE6
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE7
#undef OR_EACH_COTIGUOUS_TUPLE7
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE8
#undef OR_EACH_COTIGUOUS_TUPLE8
#endif

#ifdef FOR_EACH_COTIGUOUS_TUPLE9
#undef OR_EACH_COTIGUOUS_TUPLE9
#endif

/* ===================================================== Dependencies' cleanup ==================================================== */

#include "estd/preprocessor/cleanup/va_opt_detect.hpp"

/* ================================================================================================================================ */

#undef __ESTD_PREPROCESSOR_FOREACH_H__
#endif
