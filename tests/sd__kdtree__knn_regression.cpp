#include <search/knn.hpp>
#include "pch.hpp"

#ifdef _OPENMP
#include <omp.h>
#endif

#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <array>
#include <iostream>

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

#include <impl/concept.hpp>
#include <impl/context.hpp>
#include <impl/policy.hpp>
#include <impl/deref.hpp>

namespace ref {

template <sd::integral auto k, sd::integral auto dim,
                  sd::policy_list pl = sd::policy_list_t<>
                  >
constexpr inline auto 
knn(sd::iterator auto it,
        sd::integral auto n,
        sd::iterator auto q,
        sd::iterator auto out,
        sd::arithmet auto r_min,
        sd::arithmet auto r_max)
noexcept -> void
{

        using I = std::remove_cvref_t<decltype(out->idx())>;
        using T = std::remove_cvref_t<decltype(out->dst())>;

        std::vector<std::pair<I, T>> res;
        res.reserve(n);

        for (I i{0}; i < n; ++i) {

                const T dst {
                        sd::kdtree::impl::euclidian::dist2<pl>
                        (q, std::begin(sd::deref<pl>(it, i)), dim)
                };

                if (dst <= r_min) {
                        continue;
                }

                res.push_back({i, dst});

        }

        std::sort(res.begin(), res.end(),
                [](auto const &a, auto const &b) {
                        return a.second < b.second;
                }
        );

        for (size_t j{0}; j < k; ++j) {
                out[j].idx(res[j].first);
                out[j].dst(res[j].second);
        }

}

} // namespace ref

template <typename container>
static auto 
generate_random_dataset(container& c)
-> void
{
        using value_type = typename container::value_type;
        static std::random_device rd;
        static std::mt19937 rng(rd());

        const auto n { 
                static_cast<value_type>(std::size(c)) 
        };

        #if 0
        const auto v_min {
                static_cast<value_type>(
                std::sqrt(static_cast<double>
                        (std::numeric_limits<value_type>::min() / (4 * n))
                ))
        };

        const auto v_max {
                static_cast<value_type>(
                std::sqrt(static_cast<double>
                        (std::numeric_limits<value_type>::min() / (4 * n))
                ))
        };
        #else
        const auto v_min {0};
        const auto v_max {100};
        #endif

        for (auto& element : c) {
                if constexpr (std::integral<value_type>) {
                        std::uniform_int_distribution<value_type> dist(
                                v_min, v_max
                        );
                        element = dist(rng);
                }
                else if constexpr (std::floating_point<value_type>) {
                        std::uniform_real_distribution<value_type> dist(
                                v_min, v_max
                        );
                        element = dist(rng);
                }
        }
}

#include <create/create.hpp>

template <sd::integral I, sd::arithmet T, I n, I dim, sd::integral auto k>
static auto
test__knn_impl(void) 
-> void
{

        constexpr T r_min {0};
        constexpr T r_max { std::numeric_limits<T>::max() };

        std::vector<std::array<T, dim>> vec(n);
        for (auto& v : vec) generate_random_dataset(v);

        sd::kdtree::create(vec.begin(), n);

        std::vector<std::array<sd::kdtree::output_t<I, T>, k>> out(n);
        std::vector<std::array<sd::kdtree::output_t<I, T>, k>> ans(n);

        #ifdef _OPENMP
        #pragma omp parallel for
        #endif
        for (I i = 0; i < n; ++i) {

                auto q = vec[i];

                sd::kdtree::knn<k>(vec.begin(), n, q.begin(), out[i].begin(), 
                                   r_min, r_max);

                ref::knn<k, dim>(vec.begin(), n, q.begin(), ans[i].begin(),
                                 r_min, r_max);

        }

        std::vector<std::array<I, k>> idx__out(n);
        std::vector<std::array<I, k>> idx__ans(n);

        std::vector<std::array<T, k>> dst__out(n);
        std::vector<std::array<T, k>> dst__ans(n);

        #ifdef _OPENMP
        #pragma omp parallel for
        #endif
        for (I i = 0; i < n; ++i) {
                for (I j = 0; j < k; ++j) {

                        idx__out[i][j] = out[i][j].idx();
                        idx__ans[i][j] = ans[i][j].idx();

                        dst__out[i][j] = out[i][j].dst();
                        dst__ans[i][j] = ans[i][j].dst();

                }
        }
        
        expect(idx__out == idx__ans);
        expect(dst__out == dst__ans);

}

#define TEST_KNN(I, T, N, DIM, K)                                              \
                "[T="#T", I="#I", N="#N", DIM="#DIM", K="#K"]"_test = [] {     \
                                test__knn_impl<I, T, N, DIM, K>();             \
                };

int 
main(void)
{

        TEST_KNN(std::int32_t,  float,  1 << 10, 2, 16)

        return 0;

}
