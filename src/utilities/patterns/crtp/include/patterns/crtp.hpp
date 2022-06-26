/** ==================================================================================================================================
 * @file       crtp.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Sunday, 2nd January 2022 3:43:47 pm
 * @modified   Thursday, 3rd February 2022 11:32:49 am
 * @project    cpp-utils
 * @brief      Header file of the base class for classes implementing CRTP static polymorphism
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __PATTERNS_CRTP_H__
#define __PATTERNS_CRTP_H__

/* ====================================================== Namespace patterns ====================================================== */

namespace patterns {

/* ========================================================= Declarations ========================================================= */

/**
 * @class CRTP
 * @brief Universal base class providing static cast methods used to implement 
 *    CRTP interface classes
 * @tparam T 
 *    target (derived) class of the CRTP pattern
 * 
 * @example 
 *    
 *    template<typename Derived> 
 *    class CRTPInterface : public CRTP<Derived> {
 *    private:
 *        using CRTP<Derived>::impl;
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
class CRTP {
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

#include "patterns/crtp/impl/crtp.hpp"

/* ================================================================================================================================ */

#endif
