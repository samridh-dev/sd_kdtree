#include "pch.hpp"

using T = float;
using I = std::uint32_t;

constexpr I dim  { 3 };
constexpr I imax { 20 };

const T v_min {0};
const T v_max {1};

constexpr T r_min {0};
constexpr T r_max { std::numeric_limits<T>::max() };

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

int
main(void)
{

        for (I iter{1}; iter <= imax; ++iter) {

        const I n { I{1} << iter };

        const I block_size  { 512 };
        const I global_size { 
                ((n + block_size - 1) / block_size) * block_size 
        };

        std::vector<std::array<T, dim>> vec(n); 


        auto beg { std::chrono::high_resolution_clock::now() };
        auto end { std::chrono::high_resolution_clock::now() };
        auto dur {
                std::chrono::duration_cast<std::chrono::milliseconds>
                (end - beg)
        };

        #ifdef _SYCL
        sycl::queue queue;
        #endif

        load_kdtree<I, T>(vec, v_min, v_max);

        std::vector<I> vidx(n);
        #ifdef _SYCL
        auto* usm__vidx {
                sycl::malloc_device<
                        typename decltype(vidx)::value_type
                >(vidx.size(), queue) 
        };
        #endif

        #ifdef _SYCL

        beg = std::chrono::high_resolution_clock::now();

        auto* usm__vec  {
                sycl::malloc_device<
                        typename decltype(vec)::value_type
                >(vec.size(), queue) };

        queue.submit([&](sycl::handler &h) {
                h.copy(vec.data(), usm__vec, vec.size());
        }).wait();

        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

        std::cout << "[sycl::usm][generation]: " 
                  << dur.count() 
                  << " ms" 
                  << std::endl;

        beg = std::chrono::high_resolution_clock::now();
        
        queue.parallel_for(
        sycl::nd_range<1>(global_size, block_size),
        [=](sycl::nd_item<1> item) {
                const I i = item.get_global_id(0);
                if (i >= n) return;
 
                auto q = usm__vec[i];
 
                sd::kdtree::output_t<I, T> out;
 
                ref::nn<dim>(usm__vec, n, q.begin(), out.begin(),
                             r_min, r_max);
 
                usm__vidx[i] = out.idx();
                
        });
        queue.wait();

        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

        std::cout << "[ref::nn]: " 
                  << "\t[time]: " 
                          << dur.count() 
                          << " ms" 
                          << "\n"
                  << std::endl;
        
        queue.submit([&](sycl::handler &h) {
                h.copy(usm__vidx, vidx.data(), vidx.size());
        }).wait();

        sycl::free(usm__vidx, queue);
        sycl::free(usm__vec, queue);

        #else
        std::cerr << "ERROR: Not supported without SYCL\n";
        (void) global_size;
        std::abort();
        #endif

        save_vec(vidx, "exact_nn");

        } // for (I iter1}; iter <= imax; ++iter)

        return 0;
}

