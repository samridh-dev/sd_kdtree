#include <kdtree.hpp>

#include <iostream>
#include <vector>
#include <array>

int 
main(void) {

        using I = std::int32_t;
        using T = std::int32_t;

        constexpr I dim { 2 };
        constexpr I n { 10 };

        std::vector<std::array<T, dim>> vec = {
                { { 10, 15 } }, { { 46, 63 } },
                { { 68, 21 } }, { { 40, 33 } },
                { { 25, 54 } }, { { 15, 43 } },
                { { 44, 58 } }, { { 45, 40 } },
                { { 62, 69 } }, { { 53, 67 } }
        };

        std::cout << "vec : [ ";
        for (const auto& i : vec) {
                  std::cout << "[ "; 
                  for (const auto& j : i) {
                          std::cout << j << " ";
                  }
                  std::cout << "]";
        }
        std::cout << " ]" << std::endl;

        sd::kdtree::create(vec.begin(), vec.end());

        std::cout << "vec : [ ";
        for (auto& i : vec) {
                  std::cout << "[ "; 
                  for (auto& j : i) {
                          std::cout << j << " ";
                  }
                  std::cout << "]";
        }
        std::cout << " ]" << std::endl;

        {
                std::array<T, dim> q { 50, 50 };
                sd::kdtree::output_t<I, T> out;
                        
                T r_min {0};
                T r_max {100};

                sd::kdtree::nn(vec.begin(), n, q.begin(), out.begin(), 
                               r_min, r_max);

                std::cout << "NN index:    " << out.idx() << "\n";
                std::cout << "NN distance: " << out.dst() << "\n";
                std::cout << "NN coordinates: ("
                          << vec[static_cast<size_t>(out.idx())][0] << ", "
                          << vec[static_cast<size_t>(out.idx())][1] << ")\n";
                std::cout << std::endl;
        }

        {

                constexpr I k { 4 };
                std::array<T, dim> q { 50, 50 };
                std::array<sd::kdtree::output_t<I, T>, k> out;
                        
                T r_min {0};
                T r_max {100};

                sd::kdtree::knn<k>(vec.begin(), n, q.begin(), out.begin(), 
                                   r_min, r_max);

                std::cout << "KNN Results:" << "\n";
                for (size_t i = 0; i < k; ++i) {
                        std::cout << "Neighbor " << i << ":\n";
                        std::cout << "\tIndex:    " << out[i].idx() << "\n";
                        std::cout << "\tDistance: " << out[i].dst() << "\n";
                        std::cout << "\tCoordinates: (" 
                                 << vec[static_cast<size_t>(out[i].idx())][0] 
                                 << ", " 
                                 << vec[static_cast<size_t>(out[i].idx())][1] 
                                 << ")\n";
                }
                std::cout << std::endl;

        }


        return 0;


}
