/** ==================================================================================================================================
 * @file     time.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Sunday, 5th December 2021 2:19:26 pm
 * @modified Thursday, 3rd February 2022 7:04:02 pm
 * @project  Winder
 * @brief
 *    
 *    Implementation of helper functions templates from the units/time module
 *    
 * @copyright Krzysztof Pierczyk © 2021
 * ================================================================================================================================ */

#ifndef __UNITS_TIME_IMPL_TIME_H__
#define __UNITS_TIME_IMPL_TIME_H__

/* =========================================================== Includes =========================================================== */

#include "units/time.hpp"
#include "estd/preprocessor/if_constexpr.hpp"

/* ========================================================== Namespaces ========================================================== */

namespace units::isq::si {

/* ========================================================== Definitions ========================================================= */

template<typename T> requires
    Time<T>
constexpr auto time_to_chrono(const T &time) {

    if constexpr(std::is_same_v<T, units::aliases::isq::si::time::ns<typename T::rep>>)
        return std::chrono::nanoseconds(static_cast<std::chrono::nanoseconds::rep>(time.number()));
    else if constexpr(std::is_same_v<T, units::aliases::isq::si::time::us<typename T::rep>>)
        return std::chrono::microseconds(static_cast<std::chrono::microseconds::rep>(time.number()));
    else if constexpr(std::is_same_v<T, units::aliases::isq::si::time::ms<typename T::rep>>)
        return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(time.number()));
    else if constexpr(std::is_same_v<T, units::aliases::isq::si::time::s<typename T::rep>>)
        return std::chrono::seconds(static_cast<std::chrono::seconds::rep>(time.number()));
    else if constexpr(std::is_same_v<T, units::aliases::isq::si::time::min<typename T::rep>>)
        return std::chrono::minutes(static_cast<std::chrono::minutes::rep>(time.number()));
    else if constexpr(std::is_same_v<T, units::aliases::isq::si::time::h<typename T::rep>>)
        return std::chrono::hours(static_cast<std::chrono::hours::rep>(time.number()));
    else if constexpr(std::is_same_v<T, units::aliases::isq::si::time::d<typename T::rep>>)
        return std::chrono::days(static_cast<std::chrono::days::rep>(time.number()));
    else
        IF_CONSTEXPR_NO_MATCH("[time_to_chrono] type T has not a correspnding std::chrono::duration representation");

}

template<typename T> requires
    estd::is_specialization_of<T, std::chrono::duration>::value
constexpr auto chrono_to_time(const T &time) {

    if constexpr(std::is_same_v<T, std::chrono::nanoseconds>)
        return units::aliases::isq::si::time::ns<typename T::rep>(time.count());
    else if constexpr(std::is_same_v<T, std::chrono::microseconds>)
        return units::aliases::isq::si::time::us<typename T::rep>(time.count());
    else if constexpr(std::is_same_v<T, std::chrono::milliseconds>)
        return units::aliases::isq::si::time::ms<typename T::rep>(time.count());
    else if constexpr(std::is_same_v<T, std::chrono::seconds>)
        return units::aliases::isq::si::time::s<typename T::rep>(time.count());
    else if constexpr(std::is_same_v<T, std::chrono::minutes>)
        return units::aliases::isq::si::time::min<typename T::rep>(time.count());
    else if constexpr(std::is_same_v<T, std::chrono::hours>)
        return units::aliases::isq::si::time::h<typename T::rep>(time.count());
    else if constexpr(std::is_same_v<T, std::chrono::days>)
        return units::aliases::isq::si::time::d<typename T::rep>(time.count());
    else
        IF_CONSTEXPR_NO_MATCH("[chrono_to_time] type T has not a correspnding mp-units type");

}


template<isq::Time Early, isq::Time Late>
constexpr auto time_diff(Early early, Late late) -> decltype(early - late) {
    if(late > early)
        return (late - early);
    else
        return (Late::max - early + late + 1);
}

/* ================================================================================================================================ */

} // End namespace units::isq::si

#endif
