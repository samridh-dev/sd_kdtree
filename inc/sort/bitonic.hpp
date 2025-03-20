#ifndef __INCLUDE__KDTREE_SORT_NETWORK_HPP
#define __INCLUDE__KDTREE_SORT_NETWORK_HPP

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"

namespace sd {

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
sd::sort__bitonic(sd::iterator auto it, sd::integral auto n, 
                  sd::integral auto lo = 0, bool ascending = false) 
-> void;

} // namespace sd

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


function bitonicSort(arr, lo, n, ascending):
    if n > 1 then
        m = floor(n / 2)
        // Sort first half in ascending order
        bitonicSort(arr, lo, m, True)
        // Sort second half in descending order
        bitonicSort(arr, lo + m, n - m, False)
        // Merge the entire sequence in the desired order
        bitonicMerge(arr, lo, n, ascending)

function bitonicMerge(arr, lo, n, ascending):
    if n > 1 then
        // Find the greatest power of 2 less than n
        m = greatestPowerOfTwoLessThan(n)
        for i from lo to lo + n - m - 1 do:
            if (ascending and arr[i] > arr[i + m])
               or (not ascending and arr[i] < arr[i + m]) then
                swap(arr[i], arr[i + m])
        bitonicMerge(arr, lo, m, ascending)
        bitonicMerge(arr, lo + m, n - m, ascending)

namespace sd::impl {

template <sd::policy_list pl>
constexpr inline auto
bitonic_merge(sd::iterator auto it, sd::integral auto n,
              sd::integral auto lo, bool ascending)
-> void
{
}

} // namespace sd::impl

template <sd::policy_list pl>
constexpr inline auto 
sd::sort__bitonic(sd::iterator auto it, sd::integral auto n, 
                  sd::integral auto lo, bool ascending) 
-> void
{

        if (n <= 1) {
                return;
        }

        auto m { n / 2 };

        sd::sort__bitonic<pl>(it, m,    lo,  1);
        sd::sort__bitonic<pl>(it, lo+m, n-m, 0);
        sd::impl::bitonic_merge<pl>(it, lo, n, 1);


}

#endif // __INCLUDE__KDTREE_SORT_NETWORK_HPP
