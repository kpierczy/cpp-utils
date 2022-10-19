/* ============================================================================================================================ *//**
 * @file       guards.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 19th October 2022 9:01:48 pm
 * @modified   Wednesday, 19th October 2022 9:53:55 pm
 * @project    cpp-utils
 * @brief      Helpers concerning usage of the Boost::sml guards
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __BOOST_SML_UTILS_ACTIONS_H__
#define __BOOST_SML_UTILS_ACTIONS_H__

/* =========================================================== Includes =========================================================== */

#include "boost/sml.hpp"
#include "estd/traits.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace boost::sml {

/* ========================================================= Declarations ========================================================= */

namespace details {

    // Helper implementation for nonstatic-method-implemented guards
    template<auto Callable>
    struct RequiresGuardNonstaticMethod {

        void operator()(method_class_t<decltype(Callable)> &impl) const
        {
            return [](auto& impl) -> bool {
                return (impl.*Callable)();       
            }(impl);                       
        }
        
    };

    // Helper implementation for static-method-implemented guards
    template<auto Callable>
    struct RequiresGuardStaticMethod {

        bool operator()() const
        {
            return Callable();                    
        }
        
    };

    // Helper implementation for method-implemented guards
    template<auto Callable>
    struct RequiresGuardMethod :
        std::conditional_t<not requires { Callable(); }
            , details::RequiresGuardNonstaticMethod<Callable>
            , details::RequiresGuardStaticMethod<Callable>
        >
    { };

    // Helper implementation for function-implemented guards
    template<auto Callable>
    struct RequiresGuardFunction {

        void operator()() const
        {
            bool Callable();       
        }
        
    };

}

/**
 * @brief Functor template trying to give an alternative for @ref REQUIRES_GUARD()
 *    macro by providing strong-typed DSL interface. Enables following require-guard
 *    semantic
 * 
 *    @code
 *  
 *    namespace state_machines {
 *    
 *        template<typename Implementation>
 *        struct Driver {                                              
 *                                                                
 *            static constexpr RequiresGuard<&Implementation::g1> g1 { };
 *                                                                           
 *            auto operator()() {                                            
 *                using namespace sml;                                       
 *                return make_transition_table(                              
 *                    * "s1"_s + "e1"_e [g1] = X                             
 *                );                                                         
 *            }                                                              
 *        };                                                                 
 *    
 *    }
 *    
 *    struct Driver {
 *        void g1() { return true; }
 *        boost::sml::sm<state_machines::Driver<Driver>> sm { *this };
 *    };
 * 
 *    @endcode
 * 
 * @tparam Callable 
 *    target callable to be wrapped for the transition table 
 */
template<auto Callable>
struct RequiresGuard :
    std::conditional_t<std::is_member_function_pointer_v<decltype(Callable)>
        , details::RequiresGuardMethod<Callable>
        , details::RequiresGuardFunction<Callable>
    >
{
    RequiresGuard() = default;
};

/**
 * @brief Factory function for @ref RequiresGuard callables
 * 
 * @code 
 *    static constexpr auto g1 { requires_guard<&Implementation::g1>() };
 * @endcode 
 * 
 * @tparam Callable 
 *    target callable to be wrapped for the transition table 
 */
template<auto Callable>
constexpr auto requires_guard() {
    return RequiresGuard<Callable>{ };
}

/* ================================================================================================================================ */

} // End namespace boost::sml

#endif
