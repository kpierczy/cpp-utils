/* ============================================================================================================================ *//**
 * @file       synchronised_reference.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Friday, 22nd April 2022 1:09:36 am
 * @modified   Sunday, 26th June 2022 3:41:37 pm
 * @project    cpp-utils
 * @brief      Definitions of the synchronised_reference class template
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __ESTD_SYNCHRONISATION_SYNCHRONISED_REFERENCE_H__
#define __ESTD_SYNCHRONISATION_SYNCHRONISED_REFERENCE_H__

/* =========================================================== Includes =========================================================== */

// Standard includes
#include <mutex>
#include <atomic>

/* ========================================================== Namespaces ========================================================== */

namespace estd {

/* ===================================================== synchronised_reference =================================================== */

/**
 * @brief Auxiliary RAII class providing synchronised reference to an arbitrary object
 * @details Class wraps handle to an arbitrary object calling lock() and unlock() methods
 *    on it at it's construction and destruction respectively. Reference is safely movable
 *    but non-copyable
 * 
 * @tparam T 
 *    type of the referenced object
 */
template<typename T>
class synchronised_reference {
    
public: /* ----------------------------------------------------- Public types ----------------------------------------------------- */

    /// Synchronised type
    using Type = T;

public: /* ------------------------------------------- Public ctors, dtors & operators -------------------------------------------- */

    /**
     * @brief Constructs reference to the given object. Locks the object
     */
    constexpr synchronised_reference(T &obj);

    /**
     * @brief Destroys the reference unlocking the referenced object (if reference
     *    has not been moved)
     * @todo Make it constexpr while C++20 is available
     */
    ~synchronised_reference();

    /// No copy-constructible
    synchronised_reference(const synchronised_reference &rref) = delete;
    /// No copy-asignable
    synchronised_reference &operator=(const synchronised_reference &rref) = delete;
    /// Move-constructible
    constexpr synchronised_reference(synchronised_reference &&rref);
    /// Move-asignable
    constexpr synchronised_reference &operator=(synchronised_reference &&rref);

public: /* ---------------------------------------------------- Public methods ---------------------------------------------------- */

    /// @returns reference to the object
    constexpr T &get();

    /// @returns const reference to the object
    constexpr const T &get() const;

private: /* ---------------------------------------------------- Private data ----------------------------------------------------- */

    /// Flag stating whether object still holds the reference ( @c false when object has been moved )
    bool moved { false };
    /// Reference to the synchronised obejct
    T *obj;

};

/* ================================================================================================================================ */

} // End namespace estd

/* ==================================================== Implementation includes =================================================== */

#include "estd/synchronised_reference/synchronised_reference.hpp"

/* ================================================================================================================================ */

#endif
