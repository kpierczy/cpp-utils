/** ==================================================================================================================================
 * @file       robber.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Wednesday, 12th January 2022 12:40:52 pm
 * @modified   Thursday, 3rd February 2022 11:27:38 am
 * @project    cpp-utils
 * @brief      Helper, devilish template class enabling access to the private members of the class using template-hack
 *    
 * @see http://bloglitb.blogspot.com/2010/07/access-to-private-members-thats-easy.html
 * @copyright Krzysztof Pierczyk © 2022
 * ================================================================================================================================ */

#ifndef __ESTD_ROBBER_H__
#define __ESTD_ROBBER_H__

/* =========================================================== Namespace ========================================================== */

namespace estd {
    
/* ========================================================== Definitions ========================================================= */

/**
 * @brief Helper structure template defining alias for @tparam Tag::type type as well
 *    as static instance of such type
 * @tparam Tag 
 *    class defining @tparam Tag::type type aliasing pointer to the private member
 *    to be accessed by the @ref robber class
 */
template<typename Tag>
struct robbing_result {
    typedef typename Tag::type type;
    static type ptr;
};

/**
 * @brief Explicit initialization of the @ref robbing_result::ptr static member required to acoid
 *    linking error when @ref robbing_result specification is instantiated
 * @tparam Tag 
 *    class defining @tparam Tag::type type aliasing pointer to the private member
 *    to be accessed by the @ref robber class
 */
template<typename Tag>
typename robbing_result<Tag>::type robbing_result<Tag>::ptr;

/**
 * @brief Class enabling access to the private/protected members of an arbitrary class
 * @tparam Tag 
 *    class defining @tparam Tag::type type aliasing pointer to the private member
 *    to be accessed by the @ref robber class
 * @tparam p 
 *    type of the pointer to the member to be accessed
 * 
 * @example
 * 
 *      // Accessed class
 *      class Robbed {
 *      private:
 *           int hidden_int = 5;
 *      };
 *      
 *      // Helper tag
 *      struct RobberTag { typedef int Robbed::*type; };
 *      
 *      // Specialization of the robber for the Robbed class
 *      template class robber<RobberTag, &Robbed::hidden_int>;
 *      
 *      // Access
 *      int main() {
 *          Robbed robbed;
 *          std::cout << robbed.*robbing_result<RobberTag>::ptr << std::endl;
 *      }
 * 
 */
template<typename Tag, typename Tag::type p>
struct robber : robbing_result<Tag> {
    struct filler { filler() { robbing_result<Tag>::ptr = p; } };
    static filler filler_obj;
};

/**
 * @brief Explicit initialization of the @ref robber::filler_obj static member required
 *    to avoid linking error when @ref robber specification is instantiated
 * @tparam Tag 
 *    class defining @tparam Tag::type type aliasing pointer to the private member
 *    to be accessed by the @ref robber class
 * @tparam p 
 *    type of the pointer to the member to be accessed
 */
template<typename Tag, typename Tag::type p>
typename robber<Tag, p>::filler robber<Tag, p>::filler_obj;

/* ================================================================================================================================ */

} // End namespace estd

#endif
