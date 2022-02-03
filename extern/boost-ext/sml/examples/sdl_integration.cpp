/** ==================================================================================================================================
 * @file     sdl_integration.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified Thursday, 23rd December 2021 7:45:53 pm
 * @brief 
 * 
 *    Example showing integration of SML with SDL2 library
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * @see https://pl.wikipedia.org/wiki/Simple_DirectMedia_Layer
 * ================================================================================================================================ */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>
#include "boost/sml/utility/dispatch_table.hpp"

namespace sml = boost::sml;

/* ================================================== Include/mimic SDL2 elements ================================================= */

#if __has_include(<SDL2/SDL_events.h>)
#include <SDL2/SDL_events.h>

namespace {

#else

namespace {

    /**
     * @brief Some constants defined in the library
     */
    enum { SDLK_SPACE = ' ' };

    /**
     * @brief Events defined in the library
     */
    enum SDL_EventType { 
        SDL_FIRSTEVENT = 0,
        SDL_QUIT,
        SDL_KEYUP,
        SDL_MOUSEBUTTONUP,
        SDL_LASTEVENT
    };

    /**
     * @brief Type describing the keyboard event
     */
    struct SDL_KeyboardEvent {
        
        // Type of the event
        SDL_EventType type;
        // Key symbol associated with the event
        struct { int sym; } keysym;
    };

    /**
     * @brief Type describing the mouse event
     */
    struct SDL_MouseButtonEvent {
        
        // Type of the event
        SDL_EventType type;
        // Mouse button associated with the event
        int button;
    };

    /**
     * @brief Type describing the mouse event
     */
    struct SDL_QuitEvent {

        // Type of the event
        SDL_EventType type;
    };

    /**
     * @brief Union summarizing all possible events
     */
    union SDL_Event {
        SDL_EventType type;
        SDL_KeyboardEvent key;
        SDL_MouseButtonEvent button;
        SDL_QuitEvent quit;
    };

#endif

    /**
     * @brief Class template representing SDL event along with ID of the event's type
     * 
     * @tparam Id 
     */
    template <SDL_EventType Id>
    struct sdl_event_impl {

        // Type-wide ID
        static constexpr auto id = Id;

        // Constructor
        explicit sdl_event_impl(const SDL_Event& data) noexcept : data(data) {}

        //Described event
        SDL_Event data;
    };

    /**
     * @brief Variable template instantiating an sml::event with the given sdl_event_impl<ID> type
     */
    template <SDL_EventType Id>
    decltype(sml::event<sdl_event_impl<Id>>) sdl_event{};

    /**
     * @brief Helper guard functor producer checking whether an event is associated with the given key
     */
    struct IsKey {
        auto operator()(int key) {
            return [=](auto event) { return event.data.key.keysym.sym == key; };
        }
    } is_key;

    // State machine
    struct sdl2 {
        auto operator()() const noexcept {
            using namespace sml;
            // Transition table
            return make_transition_table(
                                *"idle"_s                                               / [] { std::cout << "- initialization"       << std::endl; } = "wait_for_user_input"_s
                , "wait_for_user_input"_s + sdl_event<SDL_KEYUP> [ is_key(SDLK_SPACE) ] / [] { std::cout << "- space pressed"        << std::endl; } = "key_pressed"_s
                ,         "key_pressed"_s + sdl_event<SDL_MOUSEBUTTONUP>                / [] { std::cout << "- mouse button pressed" << std::endl; } = X
                ,   *"waiting_for_quit"_s + sdl_event<SDL_QUIT>                         / [] { std::cout << "- quit"                 << std::endl; } = X
            );
        }
    };
}

int main() {

    // State machine
    sml::sm<sdl2> sm;
    // Table of events dynamically dispatcehd at runtime
    auto dispatch_event = sml::utility::make_dispatch_table<
        SDL_Event,
        SDL_FIRSTEVENT, // min index
        SDL_LASTEVENT   // max index
    >(sm);

    // SDL event structure
    SDL_Event event;

    {
        // Prepare keyboard event
        SDL_KeyboardEvent keyboard_event;
        keyboard_event.type        = SDL_KEYUP;
        keyboard_event.keysym.sym  = SDLK_SPACE;
        event.key                  = keyboard_event;
        // Process event
        dispatch_event(event, event.type);
    }

    {
        // Prepare mouse event
        SDL_MouseButtonEvent mousebutton_event;
        mousebutton_event.type   = SDL_MOUSEBUTTONUP;
        mousebutton_event.button = 1;
        event.button             = mousebutton_event;
        // Process event
        dispatch_event(event, event.type);
    }

    {
        // Prepare quit event
        SDL_QuitEvent quit_event;
        quit_event.type = SDL_QUIT;
        event.quit      = quit_event;
        // Process event
        dispatch_event(event, event.type);
    }

    assert(sm.is(sml::X, sml::X));
}