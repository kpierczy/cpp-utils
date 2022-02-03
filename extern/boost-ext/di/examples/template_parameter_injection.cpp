/** ==================================================================================================================================
 * @file     template_parameter_injection.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Thursday, 23rd December 2021 6:35:42 pm
 * @brief 
 *  
 *    Example showing injection of class template's parameters
 * 
 * @see https://boost-ext.github.io/di/examples.html
 * ================================================================================================================================ */

#include <boost/di.hpp>
#include <cassert>
#include <typeinfo>
#include <iostream>

namespace di = boost::di;

/**
 * @brief Class template to be injected
 * @note 'class Greater' is in-place declaration of the 'Greater' class. This class may be not defined.
 *    It's name is used to point type template argument to be bound by @ref di::bind<class Greater> call
 *    in the main function
 */
template <typename T = class Greater>
struct example { 
    using type = T;
};

// Injected template argument
struct hello {};

int main() {

    // Injector
    const auto injector = di::make_injector(
        di::bind<class Greater>.to<hello>()
    );

    // Creation of object with injected template parameters
    auto object = injector.create<example>();
    
    static_assert(std::is_same<hello, decltype(object)::type>{});
}
