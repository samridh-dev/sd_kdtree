#include <sort/network.hpp>
#include <sort/traits.hpp>

#include "pch.hpp"

namespace std {

template<typename U, std::integral auto N>
std::ostream& 
operator<<(std::ostream &os, const std::array<U, N> &arr) 
{
        os << "{";
        for (std::size_t i = 0; i < N; ++i) {
                os << arr[i];
                if (i != N - 1)
                        os << ", ";
        }
        os << "}";
        return os;
}

} // namespace std

template <typename container>
static void 
generate_random_dataset(container& c)
{
        using value_type = typename container::value_type;
        static std::random_device rd;
        static std::mt19937 rng(rd());

        for (auto& element : c) {
                if constexpr (std::integral<value_type>) {
                        std::uniform_int_distribution<value_type> dist(
                                std::numeric_limits<value_type>::min(),
                                std::numeric_limits<value_type>::max()
                        );
                        element = dist(rng);
                }
                else if constexpr (std::floating_point<value_type>) {
                        std::uniform_real_distribution<value_type> dist(
                                std::numeric_limits<value_type>::min(),
                                std::numeric_limits<value_type>::max()
                        );
                        element = dist(rng);
                }
                else {
                }
        }
}

template <sd::integral auto n>
constexpr inline auto
test_network(void)
-> void
{
        {
                using T = double;
                std::array<T, n> arr;
                generate_random_dataset(arr);
                sd::sort__network<n>(arr.begin());
                expect(std::is_sorted(arr.begin(), arr.end()));
        }

        {
                using pl = sd::policy_list_t<sd::use_swap_if>;
                using T = double;
                std::array<T, n> arr;
                generate_random_dataset(arr);
                sd::sort__network<n, pl>(arr.begin());
                expect(std::is_sorted(arr.begin(), arr.end()));
        }
}

int
main(void) 
{

        "[n:0]"_test   = [] { test_network<0>();  };
        "[n:1]"_test   = [] { test_network<1>();  };
        "[n:2]"_test   = [] { test_network<2>();  };
        "[n:3]"_test   = [] { test_network<3>();  };
        "[n:4]"_test   = [] { test_network<4>();  };
        "[n:5]"_test   = [] { test_network<5>();  };
        "[n:6]"_test   = [] { test_network<6>();  };
        "[n:7]"_test   = [] { test_network<7>();  };
        "[n:8]"_test   = [] { test_network<8>();  };
        "[n:9]"_test   = [] { test_network<9>();  };
        "[n:10]"_test  = [] { test_network<10>(); };
        "[n:11]"_test  = [] { test_network<11>(); };
        "[n:12]"_test  = [] { test_network<12>(); };
        "[n:13]"_test  = [] { test_network<13>(); };
        "[n:14]"_test  = [] { test_network<14>(); };
        "[n:15]"_test  = [] { test_network<15>(); };
        "[n:16]"_test  = [] { test_network<16>(); };

}
