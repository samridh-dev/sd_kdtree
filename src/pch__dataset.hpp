#ifndef __INCLUDE__SRC__PCH__DATASET_HPP
#define __INCLUDE__SRC__PCH__DATASET_HPP

#include <random>
#include <concepts>

enum dataset 
{
        basic = 0,
        clustured
};

template <typename container>
auto generate_dataset(
        container& c, 
        typename container::value_type v_min,
        typename container::value_type v_max,
        dataset type = dataset::basic
) -> void 
{
    using value_type = typename container::value_type;
    static std::random_device rd;
    static std::mt19937 rng(rd());

    if (type == dataset::basic) {
        if constexpr (std::is_integral_v<value_type>) {
            std::uniform_int_distribution<value_type> dist(v_min, v_max);
            for (auto& element : c) {
                element = dist(rng); 
            }
        } else if constexpr (std::is_floating_point_v<value_type>) {
            std::uniform_real_distribution<value_type> dist(v_min, v_max);
            for (auto& element : c) {
                element = dist(rng);
            }
        }
    } else if (type == dataset::clustured) {
        // Return early if container is empty.
        if(c.empty()) return;

        // Determine number of clusters: using roughly the square root of the number of elements.
        size_t n = c.size();
        size_t num_clusters = std::max<size_t>(1, static_cast<size_t>(std::sqrt(n)));

        // Generate cluster centers in the [v_min, v_max] range.
        std::vector<double> centers;
        {
            std::uniform_real_distribution<double> center_dist(static_cast<double>(v_min), static_cast<double>(v_max));
            for (size_t i = 0; i < num_clusters; ++i) {
                centers.push_back(center_dist(rng));
            }
            std::sort(centers.begin(), centers.end());
        }

        // Compute a cluster spread. Here we choose a std deviation that is 1/10 of the total range per cluster.
        double total_range = static_cast<double>(v_max) - static_cast<double>(v_min);
        double cluster_std = total_range / (num_clusters * 10.0);

        // Normal distribution for noise.
        std::normal_distribution<double> noise_dist(0.0, cluster_std);
        // Discrete distribution to pick a cluster center.
        std::uniform_int_distribution<size_t> cluster_choice(0, num_clusters - 1);

        // Fill the container with values drawn from a cluster.
        for (auto& element : c) {
            size_t chosen = cluster_choice(rng);
            double value = centers[chosen] + noise_dist(rng);
            // Clamp value to [v_min, v_max]
            if (value < static_cast<double>(v_min)) value = static_cast<double>(v_min);
            if (value > static_cast<double>(v_max)) value = static_cast<double>(v_max);

            if constexpr (std::is_integral_v<value_type>) {
                element = static_cast<value_type>(std::lround(value));
            } else {
                element = static_cast<value_type>(value);
            }
        }
    }
}
#endif // __INCLUDE__SRC__PCH__DATASET_HPP
