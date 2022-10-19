/* ============================================================================================================================ *//**
 * @file     plantuml.cpp
 * @author   Krzysztof Jusiak (krzysztof@jusiak.net)
 * @date     Wednesday, 22nd December 2021 1:33:10 pm
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @brief 
 * 
 *    Example showing integration of SML with SDL2 library
 * 
 * @see https://boost-ext.github.io/sml/examples.html
 * @see https://plantuml.com/state-diagram
 * @todo Does not work for C++17 version (nope, just does not work in MinGW. On CompilerExplorer compiles just fine in C++17 mode)
 */// ============================================================================================================================= */

#if __cplusplus >= 201703L

/* =========================================================== Includes =========================================================== */

#include <boost/sml.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

/* ========================================================== Namespaces ========================================================== */

namespace sml = boost::sml;

/* ========================================================= State machine ======================================================== */

// Events
struct e1 {};
struct e2 {};
struct e3 {};
struct e4 {};
struct e5 {};

// Guards
struct guard  { bool operator()() const { return true; } } guard;
struct guard2 { bool operator()() const { return true; } } guard2;

// Actions
struct action  { void operator()() {} } action;
struct action2 { void operator()() {} } action2;

// On-entry/on-exit helper actions
void on_s1_entry_f() {}
void on_s2_exit_f() {}
struct on_s1_entry { auto operator()() { on_s1_entry_f(); } } on_s1_entry;
struct on_s2_exit  { auto operator()() { on_s2_exit_f();  } } on_s2_exit;

// Sub SM
struct sub_machine {
    auto operator()() const noexcept {
        using namespace sml;
        // Transition table
        return make_transition_table(
             *"orth1"_s = X
            ,*"orth2"_s = X
        );
    }
};

// State machine
    struct plant_uml {
    auto operator()() const noexcept {
        using namespace sml;
        // Transition table
        return make_transition_table(
            /* ----------------------------------- 'idle' state ----------------------------------- */
            *"idle"_s            + event<e1>                                          = "s1"_s
            /* ------------------------------------ 's1' state ------------------------------------ */
            ,  "s1"_s            + event<e2> [ !guard && guard2 ] / action            = "s2"_s
            ,  "s1"_s            + sml::on_entry<_>               / on_s1_entry
            /* ------------------------------------ 's2' state ------------------------------------ */
            ,  "s2"_s            + event<e3> [ guard || guard2 ]                      = "s1"_s
            ,  "s2"_s            + sml::on_exit<_>                / on_s2_exit
            ,  "s2"_s            + event<e4>                      / action            = state<sub_machine>
            /* --------------------------------- Submachine state --------------------------------- */
            , state<sub_machine> + event<e5>                      / (action, action2) = X
        );
    }
};

/* ========================================================== Environment ========================================================= */

bool state_initialized = false;  
std::vector<std::string> completed_submachines;  

/* ============================================================ Helpers =========================================================== */

/** 
 * @brief Allows for checking if the type is sml::front::seq_
 * @details This type is used by sml when there are lists of actions.
 */
template <class... Ts>
struct is_seq_ : sml::aux::false_type {};  
template <class... Ts>
struct is_seq_<sml::front::seq_<Ts...>> : sml::aux::true_type {};  

/** 
 * @brief Allows for checking if the type is sml::front::not_
 * @details This type is used by sml inside of guards, when the guard value is negated with !
 *
 * The partial specialization matches if the type passed in is sml::front::not_, causing the struct to
 * inherit from sml::aux::true_type, which gives it a member called "value" that is set to true.
 * If the type passed doesn't match sml::front::not_, it'll match the generic is_not_ which inherits
 * from sml::aux::false_type, giving it a member called "value" that is set to false.
 */
template <class... Ts>
struct is_not_ : sml::aux::false_type {};  
template <class... Ts>
struct is_not_<sml::front::not_<Ts...>> : sml::aux::true_type {};  

/** 
 * @brief Provides access to the template parameter type of an sml::front::not_<T>
 */
template <class T>
struct strip_not_ { using type = T; };  
template <class T>
struct strip_not_<sml::front::not_<T>> { using type = T; };  

/** 
 * @brief Allows for checking if the type is sml::front::and_
 * @details This type is used by sml inside of guards when two guard functions are combined with &&
 */
template <class... Ts>
struct is_and_ : sml::aux::false_type {};  
template <class... Ts>
struct is_and_<sml::front::and_<Ts...>> : sml::aux::true_type {};  

/** 
 * @brief Allows for checking if the type is sml::front::or_
 * @details This type is used by sml inside of guards when two guard functions are combined with ||
 */
template <class... Ts>
struct is_or_ : sml::aux::false_type {};  
template <class... Ts>
struct is_or_<sml::front::or_<Ts...>> : sml::aux::true_type {};  

/** 
 * @brief Uses std::tuple_element and std::tuple to access the Nth type in a parameter pack
 */
template <int N, class... Ts>
using NthTypeOf = typename std::tuple_element<N, std::tuple<Ts...>>::type;

/** 
 * @brief Gets the size of a parameter pack
 * @details This isn't really necessary, sizeof...(Ts) can be used directly instead
 */
template <class... Ts>
struct count {                                     
  static const std::size_t value = sizeof...(Ts);  
};

/** 
 * @brief Allows for checking if the type is sml::aux::zero_wrapper
 * @details SML puts this around types inside of guards and event sequences
 */
template <class T>
struct is_zero_wrapper : sml::aux::false_type {};  
template <class T>
struct is_zero_wrapper<sml::aux::zero_wrapper<T>> : sml::aux::true_type {};  

/** 
 * @brief If T is a zero wrapper, ::type will be the inner type. if not, it will be T.
 */
template <class T>
struct strip_zero_wrapper { using type = T; };  
template <class T>
struct strip_zero_wrapper<sml::aux::zero_wrapper<T>> { using type = T; };  

/** 
 * @brief Accesses the type of a state-machine, sml::back::sm
 */
template <class T>
struct submachine_type { using type = T; };  
template <class T>
struct submachine_type<sml::back::sm<T>> { using type = typename T::sm; };  

/* ================================================================================================================================ */
/* ---------------------------------------------------------- Formatters ---------------------------------------------------------- */
/* ================================================================================================================================ */

/**
 * @brief Prints intendation to the stdout
 * @param indent 
 *    width of the intendation
 */
inline void do_indent(unsigned int indent) { std::cout << std::string(indent, ' '); }

/* ======================================================= Sequence printer ======================================================= */

/** 
 * @brief Print the types inside a sml::front::seq_
 * @details These types came from a list of actions.
 */
template <class... Ts>
struct print_seq_types {  

    // Printing method
    template <int I>
    static void func() {
        
        // Check if param pack is empty
        constexpr auto param_pack_empty = (sizeof...(Ts) == I);
        // Print sequence
        if constexpr (!param_pack_empty) {  

            // Get currently printed type
            using current_type = NthTypeOf<I, Ts...>;
            // If current type is a sequence, call this function reqursively to print the inspected sequence
            if constexpr (is_seq_<typename current_type::type>::value) {  
                print_seq_types<typename current_type::type>::template func<0>();
            // Else, just print name of the type
            } else {  
                std::cout << sml::aux::string<typename strip_zero_wrapper<current_type>::type>{}.c_str();
            }

            // If the last element has been printed, print new line
            if constexpr (I + 1 < sizeof...(Ts)) {  
                std::cout << ",\\n ";
            }

            // Call this function recursively on the next element of the paramater's pack
            print_seq_types<Ts...>::template func<I + 1>();
        }
    }
};

/**
 * @brief Specialization of the printing class for the @ref sml::front::seq_
 * @tparam Ts 
 *    parameters pack to be printed (passed inside sml::front::seq_)
 */
template <class... Ts>
struct print_seq_types<sml::front::seq_<Ts...>> {  
  template <int I>
  static void func() {
    print_seq_types<Ts...>::template func<0>();
  }
};

/* ========================================================= Guard printer ======================================================== */

/** 
 * @brief Print the types inside a guard
 * @details These can be a functor, an sml::front::not_, an sml::front::and_, or an 
 *   sml::front::or_ which makes this one more complicated. They also involve the zero_wrapper.
 *   The various partial specializations handle all of the possible types.
 */
template <class... Ts>
struct print_guard {  

    // Printing method
    template <int I>
    static void func(const std::string& sep = "") {

        // Check if printed paramaters' list is empty
        constexpr auto param_pack_empty = (sizeof...(Ts) == I);
        // If not, get the current type
        if constexpr (!param_pack_empty) {  

            // Get currently printed tyoe
            using current_type = NthTypeOf<I, Ts...>;
            // If current type is zero wrapper, call function recursively on the underlying type
            if constexpr (is_zero_wrapper<current_type>::value) {  
                print_guard<typename strip_zero_wrapper<current_type>::type>::template func<0>();
            // Else, print type
            } else {  
                std::cout << sml::aux::string<current_type>{}.c_str();
            }

            // If NOT the last one type has been processed, print separator
            if constexpr (I + 1 < sizeof...(Ts)) {  
                if (!sep.empty()) {
                    std::cout << sep;
                }
            }

            // Call function for the next element to be printed
            print_guard<Ts...>::template func<I + 1>(sep);
        }
    }
};

/**
 * @brief Specialization of the printing class for the @ref sml::front::not_
 * @tparam T
 *    type to be printed (passed inside sml::front::not_)
 */
template <class T>
struct print_guard<sml::front::not_<T>> {  
    template <int I>
    static void func(const std::string& /*sep*/ = "") {
        std::cout << "!" << sml::aux::string<typename strip_zero_wrapper<T>::type>{}.c_str();
    }
};

/**
 * @brief Specialization of the printing class for the @ref sml::front::and_
 * @tparam Ts 
 *    parameters pack to be printed (passed inside sml::front::and_)
 */
template <class... Ts>
struct print_guard<sml::front::and_<Ts...>> {  
    template <int I>
    static void func(const std::string& /*sep*/ = "") {
        constexpr auto param_pack_empty = (sizeof...(Ts) == I);
        if constexpr (!param_pack_empty) {
            print_guard<Ts...>::template func<I>(" &&\\n ");
        }
    }
};

/**
 * @brief Specialization of the printing class for the @ref sml::front::or_
 * @tparam Ts 
 *    parameters pack to be printed (passed inside sml::front::or_)
 */
template <class... Ts>
struct print_guard<sml::front::or_<Ts...>> {  
  template <int I>
  static void func(const std::string& /*sep*/ = "") {
    constexpr auto param_pack_empty = (sizeof...(Ts) == I);
    if constexpr (!param_pack_empty) {
      print_guard<Ts...>::template func<I>(" ||\\n ");
    }
  }
};

/* ====================================================== Transitions printer ===================================================== */

/**
 * @brief Base of the helper class implementing dumpinf routine
 */
template <typename...>
struct dump_transitions;

/**
 * @brief Main function printing a single transition implemented by the SM
 * @tparam N 
 *    depth of intendation
 * @tparam T 
 *    transition to be printed
 */
template <int N, class T>
void dump_transition() noexcept {

    // Check if the source state of the transition is a State Machine
    constexpr auto src_is_sub_sm =
        !sml::aux::is_same<sml::aux::type_list<>, sml::back::get_sub_sms<typename T::src_state>>::value;
    // Check if the destination state of the transition is a State Machine
    constexpr auto dst_is_sub_sm =
        !sml::aux::is_same<sml::aux::type_list<>, sml::back::get_sub_sms<typename T::dst_state>>::value;

    // Prepare output strings for source and destination strings
    std::string src_state, dst_state;

    // If source state is State Machine, convert it's own source state to the string
    if constexpr (src_is_sub_sm) {
        src_state = std::string{sml::aux::string<typename submachine_type<typename T::src_state>::type>{}.c_str()};
    // Otherwise convert state directly
    } else {  
        src_state = std::string{sml::aux::string<typename T::src_state>{}.c_str()};
    }

    // If destination state is State Machine, convert it's own destination state to the string
    if constexpr (dst_is_sub_sm) {
        dst_state = std::string{sml::aux::string<typename submachine_type<typename T::dst_state>::type>{}.c_str()};
    // Otherwise convert state directly
    } else {  
        dst_state = std::string{sml::aux::string<typename T::dst_state>{}.c_str()};
    }

    // Get internals of the destination state
    const auto dst_internal = sml::aux::is_same<typename T::dst_state, sml::front::internal>::value;

    // Check if transitions has some traits
    const auto has_event = !sml::aux::is_same<typename T::event, sml::anonymous>::value;
    const auto has_guard = !sml::aux::is_same<typename T::guard, sml::front::always>::value;
    const auto has_action = !sml::aux::is_same<typename T::action, sml::front::none>::value;

    /* ------------------------------------------------- Printing ------------------------------------------------- */

    // Print deferred self transition
    if (has_event && has_action && sml::aux::is_same<typename T::action::type, sml::front::actions::defer>::value) {
        do_indent(N);
        std::cout << src_state << " : " << boost::sml::aux::get_type_name<typename T::event>() << " / defer" << std::endl;
        return;
    }

    // Print initial state
    if (T::initial) {

        // Create an orthogonal section
        if (state_initialized) {
            do_indent(N);
            std::cout << "--" << std::endl;
        }

        // Mark state as initialized
        state_initialized = true;
        // Print intendation
        do_indent(N);
        // Print initial transition
        std::cout << "[*] --> " << src_state << std::endl;
    }

    // Print source state being a substate machine
    if constexpr (src_is_sub_sm) {

        // Check if submachine ha sbeen already formatted
        auto already_in = std::find(completed_submachines.begin(), completed_submachines.end(), src_state) != completed_submachines.end();

        // If not, format it
        if (!already_in) {

            // Add submachine's string into the list
            completed_submachines.push_back(src_state);
            // Increase intendation
            constexpr int indent = N + 2;
            // Print intendation
            do_indent(N);

            // Keep actual initialization state
            bool prev_state = state_initialized;
            state_initialized = false;

            // Print transitions of the submachine
            std::cout << "state " << src_state << " {" << std::endl;
                dump_transitions<typename T::src_state::transitions>::template func<indent>();
                do_indent(N);
            std::cout << "}" << std::endl;

            // Restore initialization state
            state_initialized = prev_state;
        }
    }

    // If destination state is 'terminate', swap it to initial state [?]
    if (dst_state == "terminate") {
        dst_state = "[*]";
    }
    
    // Print transition between source and destination state
    do_indent(N);
    std::cout << src_state;
    if (!dst_internal) {
        std::cout << " --> " << dst_state;
    }

    // If guard, event or action is involved, print ':'
    if (has_event || has_guard || has_action) {
        std::cout << " :";
    }

    // Print event
    if (has_event) {
        std::cout << " " << std::string{sml::aux::string<typename T::event>{}.c_str()};
    }

    // Print guard
    if (has_guard) {
        std::cout << "\\n [";
        print_guard<typename T::guard::type>::template func<0>();
        std::cout << "]";
    }

    // Print action
    if (has_action) {

        std::cout << " /\\n ";

        // If action  is composed of subactions, print them in (...)
        if constexpr (is_seq_<typename T::action::type>::value) {  
            std::cout << "(";
            print_seq_types<typename T::action::type>::template func<0>();
            std::cout << ")";
        // Else, print single action without brackets
        } else {  
            std::cout << sml::aux::string<typename T::action::type>{}.c_str();
        }
    }

    std::cout << std::endl;

    // Print destination state being a substate machine
    if constexpr (dst_is_sub_sm) {

        // Check if submachine is already formatted
        auto already_in = std::find(completed_submachines.begin(), completed_submachines.end(), dst_state) != completed_submachines.end();

        // If NOT ...
        if (!already_in) {

            // Add state to the 'already formatted' list
            completed_submachines.push_back(dst_state);
            // Increase intendation
            constexpr int indent = N + 2;
            // Print intendation
            do_indent(N);

            // Keep actual initialization state
            bool prev_state = state_initialized;
            state_initialized = false;

            // Print submachine
            std::cout << "state " << dst_state << " {" << std::endl;
                dump_transitions<typename T::dst_state::transitions>::template func<indent>();
                do_indent(N);
            std::cout << "}" << std::endl;

            // Restore previous initialization state
            state_initialized = prev_state;
        }
    }
}

/**
 * @brief Helper function applying dump_transition() function to all subsequent transitions
 *    passed in the Ts paramaters pack
 * 
 * @tparam INDENT 
 *    initial intendation level
 * @tparam I 
 *    index of the elemnt in the Ts to be processed
 * @tparam Ts 
 *    list of transitions to be processed
 */
template <int INDENT, int I, class... Ts>
void apply_dump_transition() {

    // Check if given pack is empty
    constexpr auto param_pack_empty = (sizeof...(Ts) == I);
    // If not, process the next transition
    if constexpr (!param_pack_empty) {  

        // Print the transition
        dump_transition<INDENT, NthTypeOf<I, Ts...>>();
        // Call this function recursively to print the next transition
        apply_dump_transition<INDENT, I + 1, Ts...>();
        
    }
}

/**
 * @brief Helper structure template for deducing Ts... parameter of it's specialization
 */
template <typename...>
struct dump_transitions {  
    template <int INDENT>
    static void func() {}
};

/**
 * @brief Wrapper around @ref apply_dump_transition() function initializing printing
 *    of the given transitions' list
 * @tparam Ts 
 *    transitions' list to be printed
 */
template <typename... Ts>
struct dump_transitions<typename sml::aux::type_list<Ts...>> {  
    template <int INDENT>
    static void func() { apply_dump_transition<INDENT, 0, Ts...>(); }
};

/**
 * @brief Wrapper around @ref dump_transitions::func<...>() method template adding
 *    starting and ending tags of the plantuml to the dump of SM's transitions table
 * @tparam T 
 *    type of the state machine to be serialized
 */
template <class T>
void dump() noexcept {
    
    // Dump opening tag
    std::cout << "@startuml" << std::endl << std::endl;
    // Dump SM itself
    dump_transitions<typename sml::sm<T>::transitions>::template func<0>();
    // Dump closing tag
    std::cout << std::endl << "@enduml" << std::endl;
    
}

/* ============================================================= Main ============================================================= */

int main() {
    dump<plant_uml>();
}

/* ================================================================================================================================ */
/* --------------------------------- Simplified, pre-c++17 implementation (limited, no submachine) -------------------------------- */
/* ================================================================================================================================ */

#elif __cplusplus == 201402L

/* =========================================================== Includes =========================================================== */

#include <boost/sml.hpp>
#include <cassert>
#include <iostream>
#include <string>
#include <typeinfo>

/* =========================================================== Namespace ========================================================== */

namespace sml = boost::sml;

// Events
struct e1 {};
struct e2 {};
struct e3 {};
struct e4 {};

// Guards
struct guard { bool operator()() const { return true; } } guard;

// Actions
struct action { void operator()() {} } action;

// On-entry/on-exit actions
void on_s1_entry() {}
void on_s2_exit() {}

// State machine
struct plant_uml {
    // Transitions table
    auto operator()() const noexcept {
        using namespace sml;
        return make_transition_table(
            /* ----------------------------------- 'idle' state ----------------------------------- */
            *"idle"_s + event<e1>                                    = "s1"_s
            /* ------------------------------------ 's1' state ------------------------------------ */
            ,  "s1"_s + event<e2> [ guard ] / action                 = "s2"_s
            ,  "s1"_s + sml::on_entry<_>    / [] { on_s1_entry(); }
            /* ------------------------------------ 's2' state ------------------------------------ */
            ,  "s2"_s + event<e3> [ guard ]                          = "s1"_s
            ,  "s2"_s + sml::on_exit<_>     / [] { on_s2_exit();  }
            ,  "s2"_s + event<e4>           / action                 = X
        );
    }
};

/* ============================================================ Printer =========================================================== */

/**
 * @brief Printer of a single transition
 * @tparam T 
 *    type of the transition
 */
template <class T>
void dump_transition() noexcept {

    // Serialize src and dst states
    auto src_state = std::string{sml::aux::string<typename T::src_state>{}.c_str()};
    auto dst_state = std::string{sml::aux::string<typename T::dst_state>{}.c_str()};

    // If termination state given, switch it to initial state [?]
    if (dst_state == "X") {
        dst_state = "[*]";
    }

    // If initial state given, print initial transition
    if (T::initial) {
        std::cout << "[*] --> " << src_state << std::endl;
    }

    // Check traits of the transition
    const auto has_event = !sml::aux::is_same<typename T::event, sml::anonymous>::value;
    const auto has_guard = !sml::aux::is_same<typename T::guard, sml::front::always>::value;
    const auto has_action = !sml::aux::is_same<typename T::action, sml::front::none>::value;

    // Check if 'transition' is definition of on-entry/on-exit behaviour
    const auto is_entry = sml::aux::is_same<typename T::event, sml::back::on_entry<sml::_, sml::_>>::value;
    const auto is_exit = sml::aux::is_same<typename T::event, sml::back::on_exit<sml::_, sml::_>>::value;

    // Print entry / exit entry
    if (is_entry || is_exit) {
        std::cout << src_state;
    // Print transition
    } else {  
        std::cout << src_state << " --> " << dst_state;
    }

    // If any of events/gaurds/actions is defined, print separating ':'
    if (has_event || has_guard || has_action) {
        std::cout << " :";
    }

    // Print event
    if (has_event) {

        // Serialize event
        auto event = std::string(boost::sml::aux::get_type_name<typename T::event>());
        
        // Handle 'on_entry' and 'on_exit' per plant-uml syntax
        if (is_entry) {
            event = "entry";
        } else if (is_exit) {
            event = "exit";
        }

        // Print event
        std::cout << " " << event;
    }

    // Print guard
    if (has_guard) {
        std::cout << " [" << boost::sml::aux::get_type_name<typename T::guard::type>() << "]";
    }

    // Print action
    if (has_action) {
        std::cout << " / " << boost::sml::aux::get_type_name<typename T::action::type>();
    }

    // Finish transition line
    std::cout << std::endl;
}

/**
 * @brief Wrapper around @ref dump_transition() function calling it for all transitions passed
 *    in the parameters' list
 * 
 * @tparam T 
 * @tparam Ts 
 */
template <template <class...> class T, class... Ts>
void dump_transitions(const T<Ts...>&) noexcept {
    int _[]{0, (dump_transition<Ts>(), 0)...};
    (void)_;
}


/**
 * @brief Wrapper around @ref dump_transitions() function template adding
 *    starting and ending tags of the plantuml to the dump of SM's transitions table
 * @tparam TSM
 *    type of the state machine to be serialized
 */
template <class SM>
void dump(const SM&) noexcept {
    
    // Dump opening tag
    std::cout << "@startuml" << std::endl << std::endl;
    // Dump SM itself
    dump_transitions(typename SM::transitions{});
    // Dump closing tag
    std::cout << std::endl << "@enduml" << std::endl;
    
}

/* ============================================================= Main ============================================================= */

int main() {
  sml::sm<plant_uml> sm;
  dump(sm);
}

/* ================================================================================================================================ */

#endif
