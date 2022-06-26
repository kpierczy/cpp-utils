/* ============================================================================================================================ *//**
 * @file       locks.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 18th May 2022 1:24:47 pm
 * @modified   Sunday, 26th June 2022 3:41:37 pm
 * @project    cpp-utils
 * @brief      Implementations of helper synchronisation primitives
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_SYNCHRONISATION_LOCKS_LOCKS_H__
#define __ESTD_SYNCHRONISATION_LOCKS_LOCKS_H__

/* =========================================================== Includes =========================================================== */

// Private includes
#include "estd/locks.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ===================================================== spin_lock definitions ===================================================== */

spin_lock::spin_lock() : 
    state(State::Unlocked) 
{ }


spin_lock::spin_lock([[maybe_unused]] spin_lock &&rlock) : 
    state(State::Unlocked) 
{ }


void spin_lock::lock() { 
    while (state.exchange(State::Locked, std::memory_order_acquire) == State::Locked) { }
}


void spin_lock::unlock() { 
    state.store(State::Unlocked, std::memory_order_release); 
}

/* ================================================================================================================================ */

} // End namespace estd

#endif
