#include "pch.hpp"

using T = float;
using I = std::uint32_t;

constexpr I dim  { 3 };
constexpr I imax { 18 };
constexpr I k    { 16 };

const T v_min {0};
const T v_max {1};

constexpr T r_min {0};
constexpr T r_max { std::numeric_limits<T>::max() };

namespace ref {

template <sd::integral auto k, sd::integral auto dim,
          sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
knn(sd::iterator auto it,
    sd::integral auto n,
    sd::iterator auto q,
    sd::iterator auto out,
    sd::arithmet auto r_min,
    sd::arithmet auto r_max) noexcept -> void
{
        using I = std::remove_cvref_t<decltype(out->idx())>;
        using T = std::remove_cvref_t<decltype(out->dst())>;

        struct neighbor_t {
                I idx;
                T dst;
        };

        std::array<neighbor_t, k> res;
        I count = 0;

        for (I i = 0; i < n; ++i) {

                const T dst { 
                        sd::kdtree::impl::euclidian::dist2<pl>(
                                q, std::begin(sd::deref<pl>(it, i)), dim
                        )
                };

                if (dst <= r_min || dst > r_max) {
                        continue;
                }

                if (count < k) {
                        I j = count;
                        while (j > 0 && res[j - 1].dst > dst) {
                                res[j] = res[j - 1];
                                --j;
                        }
                        res[j] = { i, dst };
                        ++count;
                }

                else if (dst < res[count - 1].dst) {
                        I j = count - 1;
                        while (j > 0 && res[j - 1].dst > dst) {
                                res[j] = res[j - 1];
                                --j;
                        }
                        res[j] = { i, dst };
                }

        }

        I num_neighbors = (count < k ? count : k);
        for (I j = 0; j < num_neighbors; ++j) {
                out[j].idx(res[j].idx);
                out[j].dst(res[j].dst);
        }

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

        std::vector<I> vidx(n * k);
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
 
                std::array<sd::kdtree::output_t<I, T>, k> out;
 
                ref::knn<k, dim>(usm__vec, n, q.begin(), out.begin(),
                                 r_min, r_max);

                for (I j{0}; j < k; ++j) { usm__vidx[k * i + j] = out[j].idx(); }
                
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

        save_vec(vidx, "exact_knn_" + std::to_string(k));

        } // for (I iter1}; iter <= imax; ++iter)

        return 0;
}

