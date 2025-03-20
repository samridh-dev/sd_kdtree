#include <create/create.hpp>
                      
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

template <typename I>
static inline constexpr auto 
level_of(I i) 
-> I
{
        I l{0};
        i = i + 1;
        while (i > 1) {
                i >>= 1;
                ++l;
        }
        return l;
}

template <typename I, sd::policy_list pl>
static bool
none_above(sd::iterator auto it, const I n, 
           const I i, const I d, const auto& v) 
{

        if (i >= n) {
                return true;
        }

        auto x { sd::deref<pl>(it, i, d) };

        if (x > v) {
                return false;
        }

        return none_above<I, pl>(it, n, 2 * i + 1, d, v)
            && none_above<I, pl>(it, n, 2 * i + 2, d, v);

}

template <typename I, sd::policy_list pl>
static bool
none_below(sd::iterator auto it, const I n,
           const I i, const I d, const auto& v) 
{

        if (i >= n) {
                return true;
        }

        auto x { sd::deref<pl>(it, i, d) };

        if (x < v) {
                return false;
        }

        return none_below<I, pl>(it, n, 2 * i + 1, d, v)
            && none_below<I, pl>(it, n, 2 * i + 2, d, v);

}

template <typename I, sd::policy_list pl = sd::policy_list_t<>>
static bool
kdtree_is_valid(sd::iterator auto it, const I n, const I dim, const I i = I{0}) 
{

        if (i >= n) {
                return true;
        }

        I l {level_of(i)};

        I d {l % dim};

        auto v { sd::deref<pl>(it, i, d) };

        if (!none_above<I, pl>(it, n, 2 * i + 1, d, v)) {
                return false;
        }

        if (!none_below<I, pl>(it, n, 2 * i + 2, d, v)) {
                return false;
        }

        return kdtree_is_valid<I, pl>(it, n, dim, 2 * i + 1)
            && kdtree_is_valid<I, pl>(it, n, dim, 2 * i + 2);

}

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

#define TEST__KDTREE(T, V, N, DIM)                                             \
"[test: T="#T", N="#N", DIM="#DIM"]"_test = [&]{                               \
        constexpr T dim = DIM;                                                 \
        constexpr T n = N;                                                     \
        std::vector<std::array<V, dim>> vec(n);                                \
        for (auto &v : vec) generate_random_dataset(v);                        \
        sd::kdtree::create(vec.begin(), n);                                    \
        expect(kdtree_is_valid<decltype(n)>(vec.begin(), n, dim));             \
};

int 
main(void)
{

        TEST__KDTREE(std::uint32_t, float,  1e2, 1);
        TEST__KDTREE(std::uint64_t, int,    1e2, 2);
        TEST__KDTREE(std::int64_t,  float,  1e2, 6);
        TEST__KDTREE(std::int32_t,  double, 1e2, 2);
 
        return 0;

}

#undef TEST__KDTREE
