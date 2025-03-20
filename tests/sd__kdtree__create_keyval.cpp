#include <create/impl/keyval.hpp>
using namespace sd::kdtree::impl::create;

#include "pch.hpp"

using I = std::size_t;
using T = double;

constexpr I dim { 2 };
constexpr I n   { 10 };

using val_type = std::array<T, dim>;
using key_type = I;

namespace std {

template<typename U, std::size_t N>
std::ostream& 
operator<<(std::ostream& os, const std::array<U, N>& arr) 
{
        os << "{";
        for (std::size_t i = 0; i < N; ++i) {
                os << arr[i];
                if (i != N - 1) os << ", ";
        }
        os << "}";
        return os;
}

} // namespace std;

int 
main(void)
{

        std::array<key_type, n> arr__key = {
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9
        };

        std::array<val_type, n> arr__val = {{
                {10, 15}, {15, 43}, {25, 54}, {40, 33}, {44, 58},
                {45, 40}, {46, 63}, {53, 67}, {62, 69}, {68, 21}
        }};

        auto key { arr__key.begin() };
        auto val { arr__val.begin() };
        I axis   { 0 };

        keyval_t<decltype(key), decltype(val), I> kv(key, val, axis);

        auto it { kv.begin() };

        static_assert(
                std::random_access_iterator<decltype(it)>, 
                "iterator `it` is not a random access iterator"
        );

        "[basic_iterator]"_test = [&] {

                expect((*it).key == arr__key[0]);
                expect((*std::next(it, 3)).key == arr__key[3]);

                expect((*it).val == arr__val[0]);
                expect((*std::next(it, 4)).val == arr__val[4]);

                expect(it < std::next(it, 1));
                expect(std::next(it, 1) > it);
                expect(it <= std::next(it, 1));
                expect(std::next(it, 1) >= it);

        };

        "[ownership]"_test = [&] {
                
                for (I i{0}; i < n; ++i) {
                        auto iti { std::next(it, i) };
                        expect(&((*iti).key) == &arr__key[i]);
                        expect(&((*iti).val) == &arr__val[i]);
                }

        };

        "[less]"_test = [&] {

                I i { 0 };
                I j { 2 };

                expect((*std::next(it, i)).key < (*std::next(it, j)).key);
                expect((*std::next(it, i)).val < (*std::next(it, j)).val);

        };

        "[swap]"_test = [&] {

                I i { 0 };
                I j { 2 };

                const auto tmp__key { (*std::next(it, i)).key };
                const auto tmp__val { (*std::next(it, i)).val };

                (*std::next(it, i)).key = (*std::next(it, j)).key;
                (*std::next(it, i)).val = (*std::next(it, j)).val;
                (*std::next(it, j)).key = tmp__key;
                (*std::next(it, j)).val = tmp__val;

                expect(arr__key[0] == 2);
                expect(arr__key[2] == 0);

                expect(arr__val[0] == std::array<T, dim>{25, 54});
                expect(arr__val[2] == std::array<T, dim>{10, 15});

                expect((*std::next(it, i)).key == arr__key[0]);
                expect((*std::next(it, j)).key == arr__key[2]);
                expect((*std::next(it, i)).val == arr__val[0]);
                expect((*std::next(it, j)).val == arr__val[2]);

        };

        return 0;

}
