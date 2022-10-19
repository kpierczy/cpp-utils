/* ============================================================================================================================ *//**
 * @file       transition_table.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Sunday, 9th January 2022 5:35:19 pm
 * @modified   Wednesday, 19th October 2022 9:01:03 pm
 * @project    cpp-utils
 * @brief      Header file defining helper macros related to dealing with SML transition tables. This header does NOT include boost::sml 
 *             module
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __UTILS_SML_UTILS_MACROS_TRANSITION_TABLE_H__
#define __UTILS_SML_UTILS_MACROS_TRANSITION_TABLE_H__

/* ============================================================ Actions =========================================================== */

/**
 * @brief Defines a static constexpr lambda expression wrapping call to the
 *    non-static method of the @p Implementation class (object taken by reference
 *    by the action) that can be called with @p action name directly from the
 *    transition table (assuming macro is called inside transition-table class)
 * 
 * @details Here is the problem: ideally we would like to implement transition-table
 *    class as a nested type of the outer class [1]. In such a setup the inner class to
 *    implements transition table (that can be defined in the header file of the 
 *    outer class as a part of API's documentatiion) and the otuer class to implement:
 *    
 *      - data management
 *      - action routines
 *      - guard routines
 * 
 *    It would like like this:
 * 
 *    @code
 * 
 *    class Driver {
 *    private:
 *  
 *         struct StateMachine {
 * 
 *             // Action must be a lambda so we need to wrap
 *             static constexpr auto a1 = [](Driver &driver) { driver.a1(); };
 *  
 *             auto operator()() {
 *                 using namespace sml;
 *                 return make_transition_table(
 *                     * "s1"_s + "e1"_e / a1 = X
 *                 );
 *             }
 *         };
 * 
 *    private:
 * 
 *         void a1() { ... }
 * 
 *    private:
 * 
 *        boost::sml::sm<Driver> sm { *this };
 *    };
 * 
 *    @endcode
 * 
 *    This however cannot be achieved with today C++ standard. This is because to instantiate
 *    boost::sml::sm<Driver> compiler needs to resolve the template completely. This in turn
 *    requires deducing type returned by StateMachine::operator() that **will not happen until
 *    definition of the Driver is complete** (see <a href="https://github.com/boost-ext/sml/issues/48">here</a>).
 *    Thus we cannot have instance of the SM that wraps transition template defined as a nested type.
 * 
 *    We need to move StateMachine outside the Driver class.
 * 
 *    @code
 *  
 *    namespace state_machines {
 * 
 *        template<typename Implementation>
 *        struct Driver {                                              
 *                                                                           
 *            // Action must be a lambda so we need to wrap                  
 *            static constexpr auto a1 = [](Implementation &driver) { driver.a1(); };
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
 *    class Driver {
 *    private:
 * 
 *         void a1() { std::cout << "Hello world" << std::endl; }
 * 
 *    private:
 * 
 *        boost::sml::sm<state_machines::Driver<Driver>> sm { *this };
 *    };
 * 
 *    @endcode
 * 
 *    Unfortunately this also does not solve the problem. The Driver type is incomplete
 *    at the point where boost::sml::sm<...> instantiation is made and so call to:
 *    
 *        driver.a1()
 *    
 *    inside the action lambda is 'invalid use of incomplete type class Driver'. In general
 *    there is not much to do with the current C++ standard. However... There is some workaround
 *    that exploits the fact of 'postponed auto deduction in lambda expression' 
 *    (see <a href="https://github.com/boost-ext/sml/issues/137">here</a>). This however requires
 *    in-place lambda call that is only available since C++17. Here is the code
 * 
 *    @code
 *  
 *    namespace state_machines {
 *    
 *        template<typename Implementation>
 *        struct Driver {                                              
 *                                                                           
 *            // Action must be a lambda so we need to wrap                  
 *            static constexpr auto a1 = [](Implementation &driver) { 
 *                [](auto& driver) -> void { // Here the auto& magically postpones the type resolution
 *                    driver.a1();
 *                }(driver);
 *            };
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
 *    class Driver {
 *    
 *        friend class state_machines::Driver<Driver>;
 * 
 *    private:
 *    
 *        void a1() { std::cout << "Hello world" << std::endl; }
 *    
 *    private:
 *    
 *        boost::sml::sm<state_machines::Driver<Driver>> sm { *this };
 *    };
 * 
 *    @endcode
 *    
 *    At the moment this is the best we can do to minimize number of classes required
 *    to implement convinient state-machine-managed Driver class. Without this trick
 *    such an approach requires building 3-way setup:
 * 
 *    @code
 * 
 *        template<typename Implementation>
 *        struct TransitionTable{ ... };
 * 
 *        struct Imlementation{ ... };
 * 
 *        template<typename Implementation>
 *        struct Driver{ 
 *        public:
 *        
 *            // Public API wrapping Implementation methods
 *        
 *        private:
 *             Imlementation impl;
 *             boost::sml::sm<TransitionTable<Imlementation>> sm { impl };
 *        };
 * 
 *    @endcode
 * 
 *    The macro aims to shorten the explot syntax with a name that can server as a part
 *    of in-code documentation of implemented state machines.
 * 
 * @note [1] We wouldn't like our outer class to be transition-table descriptor itself.
 *    It is because boost::sml actualy does not provide explicit way to construct the
 *    transition-table class. We would rather have our 'implementation' class as
 *    a dependency of the transition-table class that is constructed explicitly and passed
 *    to the state machine manually.
 * 
 * @param Implementation 
 *    type of the class providing implementation method for the action
 * @param action 
 *    name of the action (both action used in transition table and method in the
 *    Implementation class need to have the same name)
 */
#define REQUIRES_ACTION(Implementation, action)                       \
    static constexpr auto action = [](Implementation &impl) -> void { \
        [](auto& impl) -> void {                                      \
            impl.action();                                            \
        }(impl);                                                      \
    }

/* ============================================================ Actions =========================================================== */

/**
 * @brief Counterpart of @ref REQUIRES_ACTION macro for guards
 * 
 * @param Implementation 
 *    type of the class providing implementation method for the action
 * @param guard 
 *    name of the guard (both guard used in transition table and method in the
 *    Implementation class need to have the same name)
 */
#define REQUIRES_GUARD(Implementation, guard)                        \
    static constexpr auto guard = [](Implementation &impl) -> bool { \
        return [](auto& impl) -> bool {                              \
            return impl.guard();                                     \
        }(impl);                                                     \
    }

/* ======================================================= Transition tables ====================================================== */

/**
 * @brief Helper macro defining common elements of the transition tables' 
 *    definition
 */
#define TRANSITION_TABLE(...)                      \
    auto operator()() const noexcept {             \
        return make_transition_table(__VA_ARGS__); \
    }

/**
 * @brief Defines transition table with enabled @b boost::sml namespace
 * @see TRANSITION_TABLE
 */
#define TRANSITION_TABLE_NM(...)                   \
    auto operator()() const noexcept {             \
        using namespace boost::sml;                \
        return make_transition_table(__VA_ARGS__); \
    }

/**
 * @brief Helper macro desired to be used with @ref TRANSITION_TABLE_DEFS* as a wrapper around
 *    subsequent definitions passed as @p defs. Delays expansion of commas in the deinition statement
 */
#define SM_DEF(...) __VA_ARGS__

/**
 * @brief Helper macro desired to be used with @ref TRANSITION_TABLE_DEFS* as a wrapper around
 *    subsequent definitions passed as @p defs. Delays expansion of commas in the deinition statement
 */
#define SM_DEFS(...) EXPAND5(__VA_ARGS__)

/**
 * @brief Helper macro defining common elements of the transition tables' 
 *    definition. Inserts @p defs into the body of the @b operator()
 */
#define TRANSITION_TABLE_DEFS(defs, ...)           \
    auto operator()() const noexcept {             \
        defs;                                      \
        return make_transition_table(__VA_ARGS__); \
    }

/**
 * @brief Defines transition table with enabled @b boost::sml namespace
 * @see TRANSITION_TABLE
 */
#define TRANSITION_TABLE_DEFS_NM(defs, ...)        \
    auto operator()() const noexcept {             \
        using namespace boost::sml;                \
        defs;                                      \
        return make_transition_table(__VA_ARGS__); \
    }

/* ======================================================== State machines ======================================================== */

/**
 * @brief Helper macro defining a structure named @p name with the
 *    transition table defined int @p ...
 * @param name 
 *    name of the class wrapping transition table
 * @param ...
 *    definiton of the transition table
 */
#define STATE_MACHINE(name, ...) \
    struct name { TRANSITION_TABLE(__VA_ARGS__) }

/**
 * @brief Defines state machine with enabled @b boost::sml namespace
 * @see STATE_MACHINE
 * 
 */
#define STATE_MACHINE_NM(name, ...) \
    struct name { TRANSITION_TABLE_NM(__VA_ARGS__) }

/**
 * @brief Helper macro defining common elements of the transition tables' 
 *    definition. Inserts @p defs into the body of the @b operator()
 */
#define STATE_MACHINE_DEFS(name, defs, ...) \
    struct name { TRANSITION_TABLE_DEFS(DEFER(defs), __VA_ARGS__) }

/**
 * @brief Defines transition table with enabled @b boost::sml namespace
 * @see TRANSITION_TABLE
 */
#define STATE_MACHINE_DEFS_NM(name, defs, ...) \
    struct name { TRANSITION_TABLE_DEFS_NM(DEFER(defs), __VA_ARGS__) }
    
/* ========================================================== Submachines ========================================================= */

/**
 * @brief Helper macro defining a structure named @p name with the
 *    transition table defined int @p ... . Defines boost::sml::state<_>
 *    wrapper around defined class named @p instance
 * @param name 
 *    name of the class wrapping transition table
 * @param instance 
 *    name of the boost::sml::state<_> wrapper around @p name class
 * @param ...
 *    definiton of the transition table
 * 
 * @bug Defining @a boost::sml::state<name> as an independent object results in premature
 *    instantiation of the @ref boost::sml::front::state_sm<T>::type for the @p name class.
 *    This results in invalid behaviour of the whole state machine.
 *    To enable using short name for the @b boost::sml::state<name> one need to define 
 *    @b instance=boost::sml::state<name> in the local scope of the transition-table maker
 *    (i.e. operator()(...)) as an automatic constance
 */
#define STATE_SUBMACHINE(name, instance, ...) \
    STATE_MACHINE(name, __VA_ARGS__); static constexpr auto instance = boost::sml::state<name>

/**
 * @brief Defines submachine with enabled @b boost::sml namespace
 * @see STATE_SUBMACHINE
 */
#define STATE_SUBMACHINE_NM(name, instance, ...) \
    STATE_MACHINE_NM(name, __VA_ARGS__); static constexpr auto instance = boost::sml::state<name>

/* ================================================================================================================================ */

#endif
