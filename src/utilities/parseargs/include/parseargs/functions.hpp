/** ==================================================================================================================================
 * @file     functions.hpp
 * @author   Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date     Friday, 18th February 2022 2:00:39 pm
 * @modified Friday, 18th February 2022 2:29:03 pm
 * @project  cpp-utils
 * @brief
 *    
 *    Set of the helper functions used in the implementation of `parseargs` module
 *    
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __UTILITIES_PARSEARGS_FUNCTIONS_H__
#define __UTILITIES_PARSEARGS_FUNCTIONS_H__

/* =========================================================== Includes =========================================================== */

#include <string>
#include <sstream>

/* ========================================================= Declarations ========================================================= */

/**
 * @brief Helper function template creating stringified representation of the object
 * 
 * @tparam T 
 *    type of the object to be stringified
 * @param val 
 *    object to be stringified
 * @returns 
 *    representation of the object
 */
template <typename T>
std::string to_string(T const &val) {

    // Maximum number of container's element output to the string
    constexpr std::size_t repr_max_container_size = 5;

    // Representation for booleans
    if constexpr (std::is_same_v<T, bool>) {

        return val ? "true" : "false";

    // Representation for string-like objects
    } else if constexpr (std::is_convertible_v<T, std::string_view>) {
        
        return '"' + std::string{ std::string_view{val} } + '"';

    // Representation for containers
    } else if constexpr (is_container_v<T>) {

        std::stringstream out;

        // Open the container
        out << "{";
        
        // Check container's size
        const auto size = val.size();
        // For multielement containers...
        if (size > 1) {

            // Ooutput first element
            out << to_string(*val.begin());
            // Ooutput other elements
            std::for_each(

                // Iterate from first to last representable elements
                std::next( val.begin()                                                           ),
                std::next( val.begin(), std::min<std::size_t>(size, repr_max_container_size) - 1 ),
                /// Output'em with spaces between
                [&out](const auto &v) { out << " " << repr(v); }

            );

            // Finish string with '...' if container has too many elements
            if (size <= repr_max_container_size)
                out << " ";
            else
                out << "...";
                
        }
        // For 'at-least-single-element' containers
        if (size > 0)
            out << to_string( *std::prev(val.end()) );

        // Close the container
        out << "}";

        return out.str();

    // Representation for streamable objects
    } else if constexpr (is_streamable_v<T>) {

        std::stringstream out;
        out << val;
        return out.str();

    // Representation for other objects
    } else 
        return "<not representable>";
}

/* ================================================================================================================================ */


#endif
