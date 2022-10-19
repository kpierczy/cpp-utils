/* ============================================================================================================================ *//**
 * @file       namedtuple.hpp
 * @author     Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @maintainer Krzysztof Pierczyk (krzysztof.pierczyk@gmail.com)
 * @date       Tuesday, 15th February 2022 3:54:46 am
 * @modified   Wednesday, 19th October 2022 9:57:37 pm
 * @project    cpp-utils
 * @brief      Unit test of the estl::namedtuple class
 * 
 * 
 * @copyright Krzysztof Pierczyk © 2022
 */// ============================================================================================================================= */

#ifndef __TESTS_ESTL_NAMEDTUPLE_H__
#define __TESTS_ESTL_NAMEDTUPLE_H__
#ifdef __GNUC__ 
#if (GCC_VERSION >= 12'00'00)

/* =========================================================== Includes =========================================================== */

#include "boost/ut.hpp"
#include "estl/namedtuple.hpp"

/* ========================================================== Namespaces ========================================================== */

using namespace std::literals;
using namespace boost::ut;

/* ============================================================= Tests ============================================================ */

"named tuple"_test = [] {

    should("allow empty") = [] {
        const auto nt = namedtuple();
        expect(not [](auto t) {
            return requires { t[""_t]; };
        }(nt));
    };

    should("support direct initialization") = [] {
        
        const auto nt = namedtuple<"Trade">("price"_t = 42, "size"_t = 100);
        std::cout << nt << std::endl;
        
        expect([](auto t) {
            return requires { t["price"_t]; };
        }(nt));

        expect([](auto t) {
            return requires { t["size"_t]; };
        }(nt));

        expect(not [](auto t) {
            return requires { t["quantity"_t]; };
        }(nt));

        expect(42_i == nt["price"_t] and 100_i == nt["size"_t]);

    };

    should("support initialization") = [] {

        using record_t = nt::namedtuple<"", arg<"price", int>, arg<"size", int>>;
        auto record1 = record_t{
            "price"_t = 42,
            "size"_t = 10
        };
        auto record2 = record_t{
            "price"_t = 43,
            "size"_t = 20
        };

        expect(42_i == record1["price"_t]);
        expect(20_i == record2["size"_t]);
    };

    should("support extends") = [] {

        using record_t = decltype(namedtuple("price"_t = int{}, "size"_t = std::size_t{}));
        auto record = record_t{42, 100ul};
        
        expect(100_ul == record["size"_t]);

        static_assert(not extends<record_t, "quantity">);
        static_assert(not extends<record_t, "price", "quantity">);
        static_assert(not extends<record_t, "price", "size", "value">);
        static_assert(not extends<record_t, "price", "size", "value">);

        static_assert(extends<record_t, "price", "size">);
        static_assert(extends<record_t, "size", "price">);

        auto empty = namedtuple();
        static_assert(not extends<decltype(empty), "name">);

        auto name = namedtuple(empty, "name"_t = 42);
        static_assert(extends<decltype(name), "name">);

        constexpr auto get_name = [](const extends<"name"> auto& t) {
            return t["name"_t];
        };

        expect(42_i == get_name(name));

    };

    should("support assignment") = [] {

        auto nt = namedtuple("price"_t = int{}, "size"_t = std::size_t{});
        expect(0_i == nt["price"_t] and 0_ul == nt["size"_t]);

        nt.assign(42, 99u);
        expect(42_i == nt["price"_t] and 99_ul == nt["size"_t]);

        nt.assign("price"_t = 11, "size"_t = 1234ul);
        expect(11_i == nt["price"_t] and 1234_ul == nt["size"_t]);
    };

    should("support modification") = [] {

        auto nt = namedtuple("price"_t = int{}, "size"_t = std::size_t{});
        nt["price"_t] = 12;
        nt["size"_t] = 34u;

        expect(12_i == nt["price"_t] and 34_u == nt["size"_t]);
    };

    should("support any type") = [] {

        auto nt = namedtuple("price"_t, "size"_t);
        nt["price"_t] = 12;
        nt["size"_t] = 34u;

        expect(12_i == int(nt["price"_t]) and 34_u == unsigned(nt["size"_t]));
    };

    should("support composition") = [] {

        auto n1 = namedtuple("quantity"_t = 42);
        auto n2 = namedtuple("value"_t = 100u);
        auto nt = namedtuple<"Msg">(n1, "price"_t, "size"_t, n2);
        nt["price"_t] = 12;
        nt["size"_t] = 34u;

        expect(12_i == int(nt["price"_t]) and 34_u == unsigned(nt["size"_t]) and
                42_i == nt["quantity"_t]);

        std::cout << n1 << std::endl << n2 << std::endl << nt << std::endl;
    };

    should("support nesting") = [] {

        auto nt1 = namedtuple("first"_t, "last"_t);
        auto nt2 = namedtuple<"Attendee">("name"_t = nt1, "position"_t);
        
        nt2["name"_t]["first"_t] = "Kris"sv;
        nt2["name"_t]["last"_t] = "Jusiak"sv;
        nt2["position"_t] = "Software Architect"sv;
        
        std::cout << nt2 << std::endl;
    };

    should("get by value") = [] {
        
        auto nt = namedtuple("price"_t = 100, "size"_t = 42u);
        
        expect(100_i == nt.get<0>().value and 42_u == nt.get<1>().value);
    };

    should("support decomposition") = [] {
        
        auto nt = namedtuple("price"_t = 100, "size"_t = 42u);
        auto [price, size] = nt;
        
        expect(100_i == price.value and 42_u == size.value);
    };

    should("pack the tuple") = [] {
        
        auto nt = namedtuple("_1"_t = char{}, "_2"_t = int{}, "_3"_t = char{});
        
        expect(constant<12_u == sizeof(nt)>);
    };

    should("support arrays") = [] {
        
        auto nt = namedtuple<"Person">("name"_t = std::string{}, "children"_t);
        nt.assign("name"_t = std::string{"John"}, "children"_t.operator=<estd::any>(any(std::array{"Mike", "Keke"})));
        std::cout << nt << std::endl;

        nt.assign("Mike", std::array{"John"});
        std::cout << nt << std::endl;
    };

    should("apply") = [] {

        auto nt = namedtuple("price"_t = 42, "size"_t = 100);
        auto f = [](const auto&... args) {

        std::cout << '{';
        ((std::cout << "\"" << std::string_view{args.name} << "\" :" << args.value << ','), ...);
        std::cout << '}';
        };

        [&]<auto... Ns>(std::index_sequence<Ns...>) {
            f(nt.template get<Ns>()...);
        }(std::make_index_sequence<decltype(nt)::size>{});
    };

    should("showcase") = [] {

        auto employee = namedtuple<"Employee">("name"_t, "age"_t, "title"_t);
        
        std::vector<decltype(employee)> employees{};
        
        employees.emplace_back("John", 22, "Software Engineer");
        employees.emplace_back("Michael", 36, "Senior Software Engineer");

        const auto to_json = [](std::ostream& os, const auto& vs) {
            std::cout << "[{";
            for (const auto& v : vs) {
                os << "\"" << std::string_view{v.name_v} << "\" : {";
                [&]<auto... Ns>(std::index_sequence<Ns...>) {
                ((os << (Ns ? "," : "")
                    << "\"" << std::string_view{v.template get<Ns>().name} << "\" : " << v.template get<Ns>().value),
                ...);
                }
                (std::make_index_sequence<std::remove_cvref_t<decltype(v)>::size>{});
                os << "}";
            }
            std::cout << "}]";
        };

        to_json(std::cout, employees);

    };

};

/* ================================================================================================================================ */

#endif
#endif
#endif
