#ifndef __INCLUDE__KDTREE_CREATE_KEYVAL_HPP
#define __INCLUDE__KDTREE_CREATE_KEYVAL_HPP

#include "../../impl/concept.hpp"

namespace sd::kdtree::impl::create {

template <typename key_value_type, typename val_value_type>
struct keyval_proxy_t
{

        key_value_type& key;
        val_value_type& val;

        constexpr 
        keyval_proxy_t(key_value_type& k, val_value_type& v)
        : key(k), val(v) {}

        keyval_proxy_t(const keyval_proxy_t&) = default;
        keyval_proxy_t(keyval_proxy_t&&) = default;
        ~keyval_proxy_t(void) = default;

        keyval_proxy_t& operator=(const keyval_proxy_t&) = delete;
        keyval_proxy_t& operator=(keyval_proxy_t&&) = delete;

};

template <sd::iterator key_t, sd::iterator val_t, sd::integral int_t>
class keyval_t 
{

private:

        key_t iter__key;
        val_t iter__val;

public:

        int_t axis;

        using iterator_category = std::random_access_iterator_tag;
        
        using key_value_type = std::iter_value_t<key_t>;
        using val_value_type = std::iter_value_t<val_t>;
        
        using value_type      = keyval_proxy_t<key_value_type, val_value_type>;
        using reference       = value_type;
        using pointer         = void;
        using difference_type = std::make_signed_t<int_t>;

        constexpr inline keyval_t() = default;
        constexpr inline keyval_t(key_t k, val_t v, int_t a)
                : iter__key(k), iter__val(v), axis(a) {}

        constexpr inline auto
        begin(void)
        const -> keyval_t 
        {
                return *this;
        }

        constexpr inline auto
        operator*()
        const -> reference 
        {
                return { *iter__key, *iter__val };
        }

        constexpr inline auto
        operator[](difference_type n)
        const -> reference 
        {
                return { *(iter__key + n), *(iter__val + n) };
        }

        constexpr inline auto
        operator++()
        -> keyval_t& 
        {
                ++iter__key;
                ++iter__val;
                return *this;
        }
        constexpr inline auto
        operator++(int)
        -> keyval_t 
        {
                keyval_t tmp(*this);
                ++(*this);
                return tmp;
        }

        
        constexpr inline auto
        operator--()
        -> keyval_t& 
        {
                --iter__key;
                --iter__val;
                return *this;
        }

        constexpr inline auto
        operator--(int)
        -> keyval_t 
        {
                keyval_t tmp(*this);
                --(*this);
                return tmp;
        }

        
        constexpr inline auto
        operator+=(difference_type n)
        -> keyval_t& 
        {
                iter__key = std::next(iter__key, n);
                iter__val = std::next(iter__val, n);
                return *this;
        }

        friend constexpr inline auto 
        operator+(keyval_t it, difference_type n)
        -> keyval_t 
        {
                it += n;
                return it;
        }

        friend constexpr inline auto 
        operator+(difference_type n, keyval_t it)
        -> keyval_t 
        {
                it += n;
                return it;
        }

        
        constexpr inline auto
        operator-=(difference_type n)
        -> keyval_t& 
        {
                iter__key = std::prev(iter__key, n);
                iter__val = std::prev(iter__val, n);
                return *this;
        }

        friend constexpr inline auto 
        operator-(keyval_t it, difference_type n)
        -> keyval_t 
        {
                it -= n;
                return it;
        }

        friend constexpr inline auto
        operator-(const keyval_t &lhs, const keyval_t &rhs)
        -> difference_type 
        {
                return (lhs.iter__key - rhs.iter__key);
        }

        
        constexpr inline auto
        operator==(const keyval_t& other)
        const -> bool 
        {
                return iter__key == other.iter__key 
                    && iter__val == other.iter__val;
        }

        constexpr inline auto
        operator!=(const keyval_t& other)
        const -> bool 
        {
                return !(*this == other);
        }

        constexpr inline auto
        operator<(const keyval_t& other)
        const -> bool 
        {
                return iter__key < other.iter__key;
        }

        constexpr inline auto
        operator<=(const keyval_t& other)
        const -> bool 
        {
                return !(other < *this);
        }

        constexpr inline auto
        operator>(const keyval_t& other)
        const -> bool 
        {
                return other < *this;
        }

        constexpr inline auto
        operator>=(const keyval_t& other)
        const -> bool 
        {
                return !(*this < other);
        }

};

} // namespace sd::kdtree::impl::create

#include "../../sort/traits.hpp"
#include "../../impl/policy.hpp"

namespace sd::kdtree::impl::create {

template <sd::policy_list pl>
struct keyval__f__less : f__less {

        template <sd::iterator iter>
        constexpr inline auto 
        operator()(iter i, iter j)
        const -> bool
        {
                return (((*i).key  < (*j).key) ||
                       (((*i).key == (*j).key) && 
                        (sd::deref<pl>(std::begin((*i).val), i.axis)) < 
                        (sd::deref<pl>(std::begin((*j).val), j.axis)) 
                       ));
        }

};

template <sd::policy_list pl>
struct keyval__f__swap : f__swap {

        template <sd::iterator iter>
        constexpr inline auto 
        operator()(iter i, iter j)
        const -> void
        {
                const auto tmp__key { (*i).key };
                const auto tmp__val { (*i).val };
                (*i).key = (*j).key;
                (*i).val = (*j).val;
                (*j).key = tmp__key;
                (*j).val = tmp__val;
        }

};

template <sd::policy_list pl>
struct keyval__f__swap_if : f__swap_if {

        template <sd::iterator iter>
        constexpr inline auto 
        operator()(const bool do_swap, std::iter_value_t<iter>& i,
                                       std::iter_value_t<iter>& j)
        const -> void
        {
                if (do_swap) {
                        const auto tmp__key { (*i).key };
                        const auto tmp__val { (*i).val };
                        (*i).key = (*j).key;
                        (*i).val = (*j).val;
                        (*j).val = tmp__val;
                        (*j).key = tmp__key;
                }
        }

};

} // namespace sd::kdtree::impl::create

#endif // __INCLUDE__KDTREE_CREATE_KEYVAL_HPP
