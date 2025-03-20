#include <sort/sort.hpp>
#include "pch.hpp"

struct custom_less_descending : sd::f__less {
        template <typename iter>
        constexpr inline auto 
        operator()(iter a, iter b)
        const -> bool
        {
                return *a > *b;
        }
};

struct custom_swap_if : sd::f__swap_if {
        template <typename iter>
        constexpr inline auto
        operator()(const bool do_swap, iter a, iter b)
        const -> void
        {
                if (do_swap) {
                        auto tmp { *a };
                        *a = *b;
                        *b = *tmp;
                }
        }

};

int main(void)
{
        "[basic usage] sd::sort random test"_test = [] {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(-1000, 1000);
                
                for (std::size_t n{0}; n <= 128; ++n) {
                        std::vector<int> dataset(n);
                        for (auto &x : dataset) x = dis(gen);
                        auto expected = dataset;
                        std::sort(expected.begin(), expected.end());
                        sd::sort(dataset.begin(), n);
                        expect(std::is_sorted(dataset.begin(), dataset.end()));
                        expect(dataset == expected);
                }
        };

        "[custom less descending] sd::sort random test"_test = [] {
                using pl = sd::policy_list_t<custom_less_descending>;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(-1000, 1000);
                
                for (std::size_t n{0}; n <= 128; ++n) {
                        std::vector<int> dataset(n);
                        for (auto &x : dataset) x = dis(gen);
                        auto expected = dataset;
                        std::sort(expected.begin(), expected.end(), std::greater<>());
                        sd::sort<pl>(dataset.begin(), n);
                        expect(std::is_sorted(dataset.begin(), dataset.end(), std::greater<>()));
                        expect(dataset == expected);
                }
        };

        "[use_swap_if] sd::sort random test"_test = [] {
                using my_policy = sd::policy_list_t<custom_swap_if>;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(-1000, 1000);
                
                for (std::size_t n {0}; n <= 128; ++n) {
                        std::vector<int> dataset(n);
                        for (auto &x : dataset) x = dis(gen);
                        auto expected = dataset;
                        std::sort(expected.begin(), expected.end());
                        sd::sort<my_policy>(dataset.begin(), n);
                        expect(std::is_sorted(dataset.begin(), dataset.end()));
                        expect(dataset == expected);
                }
        };

        return 0;
}

