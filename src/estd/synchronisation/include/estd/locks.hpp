/* ============================================================================================================================ *//**
 * @file       locks.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 22nd April 2022 1:09:36 am
 * @modified   Sunday, 26th June 2022 3:41:37 pm
 * @project    cpp-utils
 * @brief      Definitions of helper synchronisation primitives
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_SYNCHRONISATION_LOCKS_H__
#define __ESTD_SYNCHRONISATION_LOCKS_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#include <mutex>
#include <atomic>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ========================================================== Empty lock ========================================================== */

/**
 * @brief Auxiliary class implementing stub for locking object
 */
struct empty_lock {

    /// Stub for lock() method
    inline void lock() { }

    /// Stub for unlock() method
    inline void unlock() { }

};

/* =========================================================== Spinlock =========================================================== */

/**
 * @brief Auxiliary class implementing atomic-based spinlock
 */
class spin_lock {

public: /* ---------------------------------------------------- Public methods ---------------------------------------------------- */

    /**
     * @brief Constructs the spinlock
     */
    inline spin_lock();

    /**
     * @brief Move-constructs the spinlock
     * @warning Usually synchronisation primitives should not be moved as it implies need
     *    of some communication protocol between synchronised threads to ensure that all
     *    of them refer to the same primitve. The move-constructor for the spin_lock class 
     *    has been introduced @b only to allow storing such locks in dynamically-allocated
     *    containers that can be reallocated during it's lifetime. spin_lock should not be
     *    moved it any other context
     */
    inline spin_lock(spin_lock &&rlock);

    /**
     * @brief Locks the spinlock
     */
    inline void lock();
    
    /**
     * @brief Unlocks the spinlock
     */
    inline void unlock();
    
private: /* ---------------------------------------------------- Private types ---------------------------------------------------- */

    /// State of the lock
    enum class State : bool { 
        Locked,
        Unlocked
    };

private: /* ---------------------------------------------------- Private data ----------------------------------------------------- */

    /// State of the lock
    std::atomic<State> state;
    
};

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/locks/locks.hpp"

/* ================================================================================================================================ */

#endif
