#include "pch.hpp"

using T = float;
using I = std::uint32_t;

constexpr I dim { 3 };
constexpr I i_max { 20 };

const T v_min {0};
//const T v_max { std::sqrt(std::numeric_limits<T>::max() / dim) };
const T v_max {1};

int
main(void)
{

        std::vector<std::array<T, dim>> vec; 

        for (I i{1}; i <= i_max; ++i) {

                const I n { I{1} << i };

                vec.clear();
                vec.resize(n);

                load_kdtree<I, T>(vec, v_min, v_max);

        }

        return 0;

}
