#ifndef __INCLUDE__KDTREE_SEARCH_OUTPUT_HPP
#define __INCLUDE__KDTREE_SEARCH_OUTPUT_HPP

#include "../impl/concept.hpp"
#include <limits> 
#include <cstdint> 
#include <bit>

namespace sd::kdtree {

#if 0
template <sd::integral I, sd::arithmet T,
          bool pack = (sizeof(I) + sizeof(T)) <= sizeof(std::uint64_t)
          >
class output_t;

template <sd::integral I, sd::arithmet T>
class output_t<I, T, true>
{

private:

    std::uint64_t n;

    static constexpr std::size_t   OFFS = 8 * sizeof(T);
    static constexpr std::uint64_t MASK = ((std::uint64_t{1} << OFFS) - 1ULL);

    static constexpr std::uint64_t pack(I i, T d) noexcept
    {
        // Convert I -> uint64_t
        const auto i_bits = static_cast<std::uint64_t>(i);

        // Convert T -> uint64_t
        // For float/double, we can use std::bit_cast if C++20 is allowed
        // (or a union approach otherwise). Here, for brevity, assume C++20:
        const auto d_bits = std::bit_cast<std::conditional_t<sizeof(T) == 4, std::uint32_t, std::uint64_t>>(d);

        // Combine: idx in upper bits, dst in lower bits
        return (i_bits << OFFS) | (static_cast<std::uint64_t>(d_bits) & MASK);
    }

    // Decodes the top bits into I
    static constexpr I unpack_idx(std::uint64_t bits) noexcept
    {
        const auto i_bits = bits >> OFFS;
        return static_cast<I>(i_bits); // if I < 64 bits, truncation happens here
    }

    // Decodes the bottom bits into T
    static constexpr T unpack_dst(std::uint64_t bits) noexcept
    {
        if constexpr (std::is_integral_v<T>) {
            return static_cast<T>(bits & MASK);
        } else {
            using BitsType = std::conditional_t<(sizeof(T) == 4), std::uint32_t, std::uint64_t>;
            return std::bit_cast<T>(static_cast<BitsType>(bits & MASK));
        }
    }

public:
    // Default constructor: idx=0, dst=std::numeric_limits<T>::max()
    explicit constexpr output_t() noexcept
        : n{pack(static_cast<I>(0), std::numeric_limits<T>::max())}
    {
    }

    // Parameter constructor
    constexpr output_t(I idx, T dst) noexcept
        : n{pack(idx, dst)}
    {
    }

    // idx() const
    constexpr inline auto idx() const noexcept -> I
    {
        return unpack_idx(n);
    }

    // idx() & (non-const) - usually return a reference, but we can't directly
    // return a reference here since it's packed. We mimic the signature by
    // returning I by value, consistent with the old usage.
    constexpr inline auto idx() noexcept -> I
    {
        return unpack_idx(n);
    }

    // dst() const
    constexpr inline auto dst() const noexcept -> T
    {
        return unpack_dst(n);
    }

    // dst() & (non-const)
    constexpr inline auto dst() noexcept -> T
    {
        return unpack_dst(n);
    }

    // setters
    constexpr inline void idx(I i) noexcept
    {
        const auto d = unpack_dst(n);
        n = pack(i, d);
    }

    constexpr inline void dst(T d) noexcept
    {
        const auto i = unpack_idx(n);
        n = pack(i, d);
    }

    // operator-> (returns pointer to self)
    constexpr inline auto operator->() noexcept -> output_t*
    {
        return this;
    }

    // begin() returns pointer to self
    constexpr inline auto begin() noexcept -> output_t*
    {
        return this;
    }

    // operator+ : returns a new output_t with sum of each field
    constexpr inline auto operator+(const output_t &other) const noexcept -> output_t
    {
        return output_t(idx() + other.idx(), dst() + other.dst());
    }

    // operator- : returns a new output_t with difference of each field
    constexpr inline auto operator-(const output_t &other) const noexcept -> output_t
    {
        return output_t(idx() - other.idx(), dst() - other.dst());
    }

    // operator+=
    constexpr inline auto operator+=(const output_t &other) noexcept -> output_t&
    {
        const auto new_i = idx() + other.idx();
        const auto new_d = dst() + other.dst();
        n = pack(new_i, new_d);
        return *this;
    }

    // operator-=
    constexpr inline auto operator-=(const output_t &other) noexcept -> output_t&
    {
        const auto new_i = idx() - other.idx();
        const auto new_d = dst() - other.dst();
        n = pack(new_i, new_d);
        return *this;
    }

    // friend operator*(S, output_t)
    template <typename S>
    friend constexpr inline auto operator*(const S &s, const output_t &o) noexcept -> output_t
    {
        return output_t(static_cast<I>(s * o.idx()), static_cast<T>(s * o.dst()));
    }
};

template <sd::integral I, sd::arithmet T>
class output_t<I, T, false>
{
#else
template <sd::integral I, sd::arithmet T>
class output_t
{
#endif

private:

        I idx_;
        T dst_;

public:

        explicit constexpr 
        output_t(void)
        noexcept : idx_{0}, dst_{std::numeric_limits<T>::max()} 
        {}

        constexpr 
        output_t(I idx, T dst)
        noexcept : idx_{idx}, dst_{dst} 
        {}

        constexpr inline auto 
        idx(void) 
        const noexcept -> decltype(idx_)
        {
                return idx_;
        }

        constexpr inline auto 
        idx(void) 
        noexcept -> const decltype(idx_)&
        {
                return idx_;
        }

        constexpr inline auto 
        dst(void) 
        const noexcept -> decltype(dst_)
        {
                return dst_;
        }

        constexpr inline auto 
        dst(void) 
        noexcept -> const decltype(dst_)&
        {
                return dst_;
        }

        constexpr inline auto 
        idx(I i) 
        noexcept -> void
        {
                idx_ = i;
        }

        constexpr inline auto 
        dst(T d) 
        noexcept -> void
        {
                dst_ = d;
        }

        constexpr inline auto 
        operator->() 
        noexcept -> output_t*
        {
                return this;
        }

        constexpr inline auto 
        begin(void) 
        noexcept -> output_t* {
                 return this;
        }

        constexpr inline auto 
        operator+(const output_t& other) 
        const noexcept -> output_t
        {
                return output_t(idx_ + other.idx_, dst_ + other.dst_);
        }

        constexpr inline auto 
        operator-(const output_t& other) 
        const noexcept -> output_t 
        {
                return output_t(idx_ - other.idx_, dst_ - other.dst_);
        }

        constexpr inline auto
        operator+=(const output_t& other)
        noexcept -> output_t& 
        {
                idx_ += other.idx_;
                dst_ += other.dst_;
                return *this;
        }

        constexpr inline auto
        operator-=(const output_t& other)
        noexcept -> output_t& 
        {
                idx_ -= other.idx_;
                dst_ -= other.dst_;
                return *this;
        }
        
        template<typename S>
        friend constexpr inline auto 
        operator*(const S& s, const output_t& o)
        noexcept -> output_t 
        {
                return output_t(s * o.idx_, s * o.dst_);
        }

};

template <typename T>
struct is_output_t : std::false_type {};

template <integral I, arithmet U>
struct is_output_t<output_t<I, U>> : std::true_type {};

template <typename T>
concept output = is_output_t<T>::value;

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


#endif // __INCLUDE__KDTREE_SEARCH_OUTPUT_HPP
