/* ============================================================================================================================ *//**
 * @file       actions.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 19th October 2022 9:01:48 pm
 * @modified   Wednesday, 19th October 2022 9:52:58 pm
 * @project    cpp-utils
 * @brief      Helpers concerning usage of the Boost::sml actions
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

    // Helper implementation for nonstatic-method-implemented actions
    template<auto Callable>
    struct RequiresActionNonstaticMethod {

        void operator()(method_class_t<decltype(Callable)> &impl) const
        {
            [](auto& impl) -> void {
                (impl.*Callable)();       
            }(impl);                       
        }
        
    };

    // Helper implementation for static-method-implemented actions
    template<auto Callable>
    struct RequiresActionStaticMethod {

        void operator()() const
        {
            Callable();                    
        }
        
    };

    // Helper implementation for method-implemented actions
    template<auto Callable>
    struct RequiresActionMethod :
        std::conditional_t<not requires { Callable(); }
            , details::RequiresActionNonstaticMethod<Callable>
            , details::RequiresActionStaticMethod<Callable>
        >
    { };

    // Helper implementation for function-implemented actions
    template<auto Callable>
    struct RequiresActionFunction {

        void operator()() const
        {
            Callable();       
        }
        
    };

}

/**
 * @brief Functor template trying to give an alternative for @ref REQUIRES_ACTION()
 *    macro by providing strong-typed DSL interface. Enables following require-action
 *    semantic
 * 
 *    @code
 *  
 *    namespace state_machines {
 *    
 *        template<typename Implementation>
 *        struct Driver {                                              
 *                                                                
 *            static constexpr RequiresAction<&Implementation::a1> a1 { };
 *                                                                           
 *            auto operator()() {                                            
 *                using namespace sml;                                       
 *                return make_transition_table(                              
 *                    * "s1"_s + "e1"_e / a1 = X                             
 *                );                                                         
 *            }                                                              
 *        };                                                                 
 *    
 *    }
 *    
 *    struct Driver {
 *        void a1() { std::cout << "Hello world" << std::endl; }
 *        boost::sml::sm<state_machines::Driver<Driver>> sm { *this };
 *    };
 * 
 *    @endcode
 * 
 * @tparam Callable 
 *    target callable to be wrapped for the transition table 
 */
template<auto Callable>
struct RequiresAction :
    std::conditional_t<std::is_member_function_pointer_v<decltype(Callable)>
        , details::RequiresActionMethod<Callable>
        , details::RequiresActionFunction<Callable>
    >
{
    RequiresAction() = default;
};

/**
 * @brief Factory function for @ref RequiresAction callables
 * 
 * @code 
 *    static constexpr auto a1 { requires_action<&Implementation::a1>() };
 * @endcode 
 * 
 * @tparam Callable 
 *    target callable to be wrapped for the transition table 
 */
template<auto Callable>
constexpr auto requires_action() {
    return RequiresAction<Callable>{ };
}

/* ================================================================================================================================ */

} // End namespace boost::sml

#endif
