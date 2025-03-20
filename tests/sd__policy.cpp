#include <impl/policy.hpp>
#include "pch.hpp"

struct pl_base {};
struct pl_derived : pl_base {};
struct pl_other {};
struct pl_derived2 : pl_base {};
struct pl_irrelevant {};

int main() {

        "[policy_list_get_size]"_test = [] {
                using list = sd::policy_list_t<pl_base, pl_derived, pl_other>;
                expect(sd::policy_list_get_size<list>::value == 3ull);
        };

        "[policy_list_empty]"_test = [] {
                using list = sd::policy_list_t<>;
                expect(sd::policy_list_get_size<list>::value == 0ull);
        };

        "[policy_list_append]"_test = [] {
                using list = sd::policy_list_t<pl_base, pl_derived>;
                using appended = typename sd::policy_list_append<pl_other, list>::type;
                expect(sd::policy_list_get_size<appended>::value == 3ull);
        };

        "[policy_list_append_multiple]"_test = [] {
                using list = sd::policy_list_t<pl_base>;
                using appended = typename sd::policy_list_append<
                        pl_derived, 
                        typename sd::policy_list_append<pl_other, list>::type
                >::type;
                expect(sd::policy_list_get_size<appended>::value == 3ull);
        };

        "[policy_list_find - match by base]"_test = [] {
                using list = sd::policy_list_t<pl_derived, pl_other>;
                using found = typename sd::policy_list_find<pl_base, void, list>::type;
                expect((std::is_same_v<found, pl_derived>));
        };

        "[policy_list_find - no match]"_test = [] {
                using list = sd::policy_list_t<pl_other>;
                using found = typename sd::policy_list_find<pl_base, int, list>::type;
                expect((std::is_same_v<found, int>));
        };

        "[policy_list_find - nested search]"_test = [] {
                using inner = sd::policy_list_t<pl_derived>;
                using outer = sd::policy_list_t<inner, pl_other>;
                using found = typename sd::policy_list_find<pl_base, void, outer>::type;
                expect((std::is_same_v<found, pl_derived>));
        };

        "[policy_list_find - multiple derived]"_test = [] {
                using list = sd::policy_list_t<pl_derived2, pl_derived>;
                using found = typename sd::policy_list_find<pl_base, void, list>::type;
                expect((std::is_same_v<found, pl_derived2>));
        };

        "[policy_list_find - duplicates]"_test = [] {
                using list = sd::policy_list_t<pl_derived, pl_derived, pl_other>;
                using found = typename sd::policy_list_find<pl_base, void, list>::type;
                expect((std::is_same_v<found, pl_derived>));
                expect(sd::policy_list_get_size<list>::value == 3ull);
        };

        return 0;
        
}
