/* ============================================================================================================================ *//**
 * @file     dynamic_injection.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 *  
 *    Example showing usage of DI in case of dynamic injection of construction parameters
 * 
 * @see https://boost-ext.github.io/di/examples.html
 */// ============================================================================================================================= */

#include <boost/di.hpp>
#include <cassert>
#include <typeinfo>
#include <iostream>

namespace di = boost::di;

/* ======================================================= Example MVC model ====================================================== */

// View interface
class iview {
public:
    virtual ~iview() noexcept = default;
    virtual void update() = 0;
};

// Renderer fo GUI view
struct renderer { int device; };
// GUI variant of the view
class gui_view : public iview {
public:
    gui_view(std::string /*title*/, const renderer& r) { assert(42 == r.device); }
    void update() override {}
};
// Text variant of the view
class text_view : public iview {
 public:
  void update() override {}
};

// Model
class model {};

// Controller
class controller {
public:
    controller(model&, iview&) {}
};

// User
class user {};
// Application
class app {
public:
    app(controller&, user&) {}
};

/* ======================================================= Dynamic dispatch ======================================================= */

int main(int argc, char const *argv[])
{
    // Run-time condition of dispatch
    auto use_gui_view = true;

    // Injector
    const auto injector = di::make_injector(

        /**
         * @brief Run-time injector deifned by the template lambda
         * @note To get description of the 'injector.template ...' syntax  @see 
         *   https://stackoverflow.com/questions/610245/where-and-why-do-i-have-to-put-the-template-and-typename-keywords
         */
        di::bind<iview>.to([&](const auto& injector) -> iview& {
            
            // Return type injector depending on the run-time condition
            return use_gui_view ?
                injector.template create<gui_view&>() :
                injector.template create<text_view&>();
        }), 
        
        // Bind compile-time construction argument
        di::bind<>.to(42)
        
    );

    return 0;
}
