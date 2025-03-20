#ifndef __INCLUDE__KDTREE_CREATE_HPP
#define __INCLUDE__KDTREE_CREATE_HPP

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"
  
namespace sd::kdtree {

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
create(sd::iterator auto beg, sd::iterator auto end)
-> void;

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
create(sd::iterator auto it, sd::integral auto n)
-> void;

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
create(sd::iterator auto beg, sd::iterator auto end, sd::context auto ctx)
-> void;

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
create(sd::iterator auto it, sd::integral auto n, sd::context auto ctx)
-> void;

} // namespace sd::kdtree

///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                             IMPLEMENTATION                              ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///////////////////////////////////////////////////////////////////////////////

template <sd::policy_list pl>
constexpr inline auto
sd::kdtree::create(sd::iterator auto beg, sd::iterator auto end)
-> void 
{
        sd::default_context ctx;
        return sd::kdtree::create<pl>(beg, end, ctx);
}

template <sd::policy_list pl>
constexpr inline auto
sd::kdtree::create(sd::iterator auto beg, sd::iterator auto end, 
                   sd::context  auto ctx)
-> void 
{
        return sd::kdtree::create<pl>(beg, std::distance(beg, end), ctx);
}

template <sd::policy_list pl>
constexpr inline auto
sd::kdtree::create(sd::iterator auto it, sd::integral auto n)
-> void 
{
        sd::default_context ctx;
        return sd::kdtree::create<pl>(it, n, ctx);
}


#include "../impl/traits.hpp"
#include "../impl/deref.hpp"
#include "../impl/size.hpp"
#include "../impl/bsr.hpp"

#include "impl/keyval.hpp" 
#include "impl/update.hpp"
#include "sort/sort.hpp"


#define USE_BENCHMARK 1

#if USE_BENCHMARK
#include <chrono>
#include <iostream>
#endif

template <sd::policy_list pl>
constexpr inline auto
sd::kdtree::create(sd::iterator auto it, sd::integral auto n,
                   sd::context  auto ctx)
-> void 
{        

        #if USE_BENCHMARK
        auto beg { std::chrono::high_resolution_clock::now() };
        auto end { std::chrono::high_resolution_clock::now() };
        auto dur { std::chrono::duration_cast
                <std::chrono::milliseconds>(end - beg)
        };
        #endif


        using I = std::remove_cvref_t<decltype(n)>;
        
        constexpr auto f__for { sd::get_f__for<pl>() };
        constexpr auto f__new { sd::get_f__new<pl>() };
        constexpr auto f__del { sd::get_f__del<pl>() };

        auto tag { f__new.template operator()<I>(n, ctx) };

        const I dim { static_cast<I>(sd::size<pl>(it)) };

        f__for(I{0}, n, [=](I i) {
                sd::deref<pl>(tag, i) = 0;
        }, ctx);

        using sort_policy = sd::policy_list_t<
                sd::kdtree::impl::create::keyval__f__less<pl>,
                sd::kdtree::impl::create::keyval__f__swap<pl>,
                sd::kdtree::impl::create::keyval__f__swap_if<pl>
                #if 0
                , sd::use_swap_if
                #endif
        >;
        using spl = sd::policy_list_append_t<
                sort_policy,
                pl>;


        for (I lvl{0}; lvl <= sd::kdtree::impl::bsr(n); ++lvl) {

                const I d { lvl % dim };

                sd::kdtree::impl::create::keyval_t 
                <decltype(tag), decltype(it), I>
                kv(tag, it, d);

                #if USE_BENCHMARK
                        beg = std::chrono::high_resolution_clock::now();
                #endif

                sd::sort<spl>(kv.begin(), n, ctx); 

                #if USE_BENCHMARK
                        end = std::chrono::high_resolution_clock::now();
                        dur = std::chrono::duration_cast
                              <std::chrono::milliseconds>(end - beg);
                        std::cout << "\t[sort] time:   " 
                                  << dur.count() 
                                  << " ms" 
                                  << std::endl;
                #endif

                #if USE_BENCHMARK
                        beg = std::chrono::high_resolution_clock::now();
                #endif

                sd::kdtree::impl::create::update<pl>(tag, n, lvl, ctx);

                #if USE_BENCHMARK
                        end = std::chrono::high_resolution_clock::now();
                        dur = std::chrono::duration_cast
                              <std::chrono::milliseconds>(end - beg);
                        std::cout << "\t[update] time: " 
                                  << dur.count() 
                                  << " ms" 
                                  << std::endl;
                #endif

        }

        f__del(tag, ctx);

}

#undef USE_BENCHMARK

#endif // __INCLUDE__KDTREE_CREATE_HPP
