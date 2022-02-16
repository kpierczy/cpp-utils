/** ==================================================================================================================================
 * @file     cprt.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Sunday, 2nd January 2022 3:43:47 pm
 * @modified Thursday, 3rd February 2022 11:32:49 am
 * @project  Winder
 * @brief
 *    
 *    Header file of the base class for classes implementing CPRT static polymorphism
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __PATTERNS_CPR_H__
#define __PATTERNS_CPR_H__

/* ====================================================== Namespace patterns ====================================================== */

namespace patterns {

/* ========================================================= Declarations ========================================================= */

/**
 * @class CPRT
 * @brief Universal base class providing static cast methods used to implement 
 *    CPRT interface classes
 * @tparam T 
 *    target (derived) class of the CPRT pattern
 * 
 * @example 
 *    
 *    template<typename Derived> 
 *    class CPRTInterface : public CPRT<Derived> {
 *    private:
 *        using CPRT<Derived>::impl;
 *    public:
 *        
 *        void foo() { 
 *            impl().foo_impl(); 
 *        }
 *        
 *        void foo() const { 
 *            impl().foo_const_impl(); 
 *        }
 * 
 *    };
 * 
 */
template<typename T>
class CPRT {
protected:

    /**
     * @brief Static cast of @a this into the target class
     */
    T &impl();

    /**
     * @brief Static cast of @a this into the target class (const version)
     */
    const T &impl() const;
    
};

/* ================================================================================================================================ */

} // End namespace patterns

/* ==================================================== Implementation includes =================================================== */

#include "patterns/cprt/impl/cprt.hpp"

/* ================================================================================================================================ */

#endif
