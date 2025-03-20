#include "pch.hpp" 

using T = float;
using I = std::uint32_t;

constexpr I dim { 3 };
constexpr I   n { 1 << 20 };

const T v_min {0};
const T v_max { std::cbrt(std::numeric_limits<T>::max() / dim) };

constexpr T r_min {0};
constexpr T r_max { std::numeric_limits<T>::max() };

constexpr I block_size  { 512 };
constexpr I global_size { 
        ((n + block_size - 1) / block_size) * block_size 
};

std::vector<std::array<T, dim>> vec(n); 

int
main(void)
{

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
 
                sd::kdtree::nn(usm__vec, n, q.begin(), out.begin(),
                               r_min, r_max);
 
                usm__vidx[i] = out.idx();
                
        });
        queue.wait();

        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

        std::cout << "[kdtree::nn]: " 
                  << "\t[time]: " 
                          << dur.count() 
                          << " ms" 
                          << "\n"
                  << "\t[thoughput]: " 
                          << static_cast<I>((n * 1e-6) / (dur.count() / 1e3))
                          << "M"
                  << std::endl;
        
        queue.submit([&](sycl::handler &h) {
                h.copy(usm__vidx, vidx.data(), vidx.size());
        }).wait();

        sycl::free(usm__vidx, queue);
        sycl::free(usm__vec, queue);

        #else
        std::cerr << "ERROR: Not supported without SYCL\n";
        std::abort();
        #endif

        I counter{0};
        std::vector<I> ans(vidx.size());
        load_vec(ans, "exact_nn");
        for (I i{0}; i < vidx.size(); ++i) {
                counter += vidx[i] == ans[i];
        }

        std::cout << "\t[accuracy]: "
                  << static_cast<double>(counter * 100) / double(vidx.size())
                  << "%"
                  << std::endl;

        return 0;
}

