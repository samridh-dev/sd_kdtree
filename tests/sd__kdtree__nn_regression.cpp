#include <search/nn.hpp>
#include "pch.hpp"

#ifdef _OPENMP
#include <omp.h>
#endif

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

}

#include <impl/concept.hpp>
#include <impl/context.hpp>
#include <impl/policy.hpp>
#include <impl/deref.hpp>

namespace ref {

template <sd::integral auto dim, sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
nn(sd::iterator auto    it,
   sd::integral auto     n,
   sd::iterator auto     q,
   sd::iterator auto     out,
   sd::arithmet auto     r_min,
   sd::arithmet auto     r_max)
noexcept -> void
{
        using I = std::remove_cvref_t<decltype(out->idx())>;
        using T = std::remove_cvref_t<decltype(out->dst())>;

        I best__idx {0};
        T best__dst {r_max};

        for (I i{0}; i < n; ++i) {

                const T dst {
                        sd::kdtree::impl::euclidian::dist2<pl>
                        (q, std::begin(sd::deref<pl>(it, i)), dim)
                };

                if (dst <= r_min) {
                        continue;
                }

                if (dst < best__dst) {
                        best__dst = dst;
                        best__idx = i;
                }
        }

        out->idx(best__idx);
        out->dst(best__dst);
}

} // namespace ref

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
                                value_type{0},
                                value_type{1}
                        );
                        element = dist(rng);
                }
                else if constexpr (std::floating_point<value_type>) {
                        std::uniform_real_distribution<value_type> dist(
                                value_type{0},
                                value_type{1}
                        );
                        element = dist(rng);
                }
                else {
                }
        }
}


#include <create/create.hpp>

template <sd::integral I, sd::arithmet T, I n, I dim>
static auto
test__nn_impl(void) 
-> void
{

        constexpr T r_min {0};
        constexpr T r_max { std::numeric_limits<T>::max() };

        std::vector<std::array<T, dim>> vec(n);

        for (auto& v : vec) generate_random_dataset(v);

        sd::kdtree::create(vec.begin(), vec.end());

        std::array<T, dim> q;

        std::vector<I> idx__out(n);
        std::vector<I> idx__ans(n);

        std::vector<T> dst__out(n);
        std::vector<T> dst__ans(n);

        #ifdef _OPENMP
        #pragma omp parallel for
        #endif
        for (I i = 0; i < n; ++i) {

                auto q { vec[i] };

                sd::kdtree::output_t<I, T> out;
                sd::kdtree::output_t<I, T> ans;

                sd::kdtree::nn(vec.begin(), n, q.begin(), out.begin(), 
                               r_min, r_max);

                ref::nn<dim>(vec.begin(), n, q.begin(), ans.begin(),
                             r_min, r_max);

                idx__out[i] = out.idx();
                dst__out[i] = out.dst();

                idx__ans[i] = ans.idx();
                dst__ans[i] = ans.dst();

        }
        
        expect(idx__out == idx__ans);
        expect(dst__out == dst__ans);

}

#define TEST_NN(I, T, N, DIM)                                                 \
        "[T="#T", I="#I", N="#N", DIM="#DIM"]"_test = [] {                    \
                test__nn_impl<I, T, N, DIM>();                                \
        };

int 
main(void) 
{

        TEST_NN(std::int32_t,  float,  1 << 10,   3)

        return 0;

}
