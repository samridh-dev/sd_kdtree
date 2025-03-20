#ifndef __INCLUDE__SRC__PCH__HPP
#define __INCLUDE__SRC__PCH__HPP

#include <kdtree.hpp>

#ifdef _OPENMP
#include <omp.h>
#endif

#if defined(SYCL_LANGUAGE_VERSION)
#include <sycl/sycl.hpp>
#define _SYCL
#endif

#include <filesystem>
#include <concepts>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <random>
#include <chrono>
#include <vector>
#include <array>

#include "pch__dataset.hpp"

template <typename int_t, typename type_t, typename container>
auto
get_kdtree_key(container& c) 
-> std::string
{

        const auto N { c.size() };
        const auto D { c[0].size() };

        const std::string str { "dat/"
                "kdtree__n" + std::to_string(N)
                     + "_d" + std::to_string(D) 
                     + "_I" + typeid(int_t).name()
                     + "_T" + typeid(type_t).name()
                     + ".dat"
        };

        return str;

}

template <typename container>
auto
get_vec_key(container& c) 
-> std::string
{

        const auto N { c.size() };

        const std::string str { "dat/"
                "kdtree__n" + std::to_string(N)
                     + "_T" + typeid(typename container::value_type).name()
                     + ".dat"
        };

        return str;

}


template <typename I, typename T, typename container>
auto
save_kdtree(container& c)
-> void
{

        const std::string fname { get_kdtree_key<I, T>(c) };

        std::filesystem::create_directories("dat");
        
        {
                std::ofstream ofs(fname, std::ios::binary);
                if (!ofs) {
                        std::cerr << "Error: failed to open " 
                                  << fname 
                                  << " for writing.\n";
                        exit(EXIT_FAILURE);
                }

                for (auto const& c_i : c) {
                        ofs.write(
                                reinterpret_cast<const char*>(c_i.data()),
                                c_i.size() * sizeof(
                                typename container::value_type::value_type
                                )
                        );
                        if (!ofs) {
                                std::cerr << "Error: failed to write data to " 
                                          << fname 
                                          << "\n";
                                exit(EXIT_FAILURE);
                        }
                }
        }

        {
                std::ofstream ofs(fname + ".txt");
                if (!ofs) {

                        std::cerr << "Error: failed to open " 
                                  << fname + ".txt" 
                                  << " for writing.\n";

                        exit(EXIT_FAILURE);
                }

                for (auto const& c_i : c) {
                        for (const auto& val : c_i) {
                                ofs<< val << " ";
                        }
                        ofs << "\n";
                }
        }

        std::cout << "kd-tree generated and saved to file: " << fname << ".\n";

}

template <typename I, typename T, typename container>
auto
load_kdtree(
        container& c,
        typename container::value_type::value_type v_min,
        typename container::value_type::value_type v_max
) 
-> void
{

        const std::string fname { get_kdtree_key<I, T>(c) };

        auto beg = std::chrono::high_resolution_clock::now();

        if (std::filesystem::exists(fname)) {

                std::ifstream ifs(fname, std::ios::binary);

                if (!ifs) {
                        std::cerr << "Error: failed to open " << fname << "\n";
                        exit(EXIT_FAILURE);
                }

                for (auto& c_i : c) {

                        ifs.read(reinterpret_cast<char*>(c_i.data()),
                                 c_i.size() * sizeof(
                                 typename container::value_type::value_type
                                 )
                        );

                        if (!ifs) {

                                std::cerr << "Error: failed to read data from " 
                                          << fname 
                                          << "\n";

                                exit(EXIT_FAILURE);

                        }

                }

                std::cout << "kd-tree loaded from file: " << fname << ".\n";

        }

        else {

                for (auto& c_i : c) generate_dataset(c_i, v_min, v_max);

                auto beg1 = std::chrono::high_resolution_clock::now();

                sd::kdtree::create(c.begin(), c.size());

                auto end1 { 
                        std::chrono::high_resolution_clock::now()
                };
                auto dur1 {
                        std::chrono::duration_cast<std::chrono::milliseconds>
                        (end1 - beg1)
                };

                std::cout << "[kdtree::create][time]: " 
                          << dur1.count() 
                          << " ms" 
                          << std::endl;

                save_kdtree<I, T>(c);

        }

        auto end { 
                std::chrono::high_resolution_clock::now()
        };
        auto dur {
                std::chrono::duration_cast<std::chrono::milliseconds>
                (end - beg)
        };

        std::cout << "[kdtree::load][time]: " 
                  << dur.count() 
                  << " ms" 
                  << std::endl;

}

template <typename container>
auto 
save_vec(const container& c, const std::string& suffix)
-> void
{

        const std::string fname { get_vec_key(c) + std::string("-") + suffix };

        std::ofstream ofs(fname, std::ios::binary);
        if (!ofs) {
                std::cerr << "Error: failed to open "
                          << fname 
                          << " for writing.\n";
                exit(EXIT_FAILURE);
        }

        ofs.write(reinterpret_cast<const char*>(
                c.data()), static_cast<int>(
                c.size() * sizeof(typename container::value_type)
                )
        );

        if (!ofs) {
                std::cerr << "Error: failed to write data to " 
                          << fname 
                          << "\n";
                exit(EXIT_FAILURE);
        }

        std::cout << "Vector saved to file: " << fname << ".\n";

}

template <typename container>
auto 
load_vec(container& c, const std::string& suffix)
-> void
{

        const std::string fname { get_vec_key(c) + std::string("-") + suffix };

        if (!std::filesystem::exists(fname)) {
                std::cerr << "Error: file " 
                          << fname 
                          << " does not exist.\n";
                exit(EXIT_FAILURE);
        }

        std::ifstream ifs(fname, std::ios::binary);
        if (!ifs) {
                std::cerr << "Error: failed to open " 
                          << fname 
                          << " for reading.\n";
                exit(EXIT_FAILURE);
        }

        ifs.read(reinterpret_cast<char*>(
                c.data()), static_cast<int>(
                c.size() * sizeof(typename container::value_type)
                )
        );

        if (!ifs) {
                std::cerr << "Error: failed to read data from " 
                          << fname 
                          << "\n";
                exit(EXIT_FAILURE);
        }

        std::cout << "Vector loaded from file: " << fname << ".\n";


}

#endif // __INCLUDE__SRC__PCH__HPP
