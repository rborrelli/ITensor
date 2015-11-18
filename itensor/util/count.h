//
// Distributed under the ITensor Library License, Version 1.2
//    (See accompanying LICENSE file.)
//
#ifndef __ITENSOR_COUNT_H_
#define __ITENSOR_COUNT_H_

#include <type_traits>

namespace itensor {

namespace detail {

template <typename size_type>
class RangeHelper
    {
    size_type curr_;
    size_type end_;
    public:

    constexpr
    RangeHelper(size_type b,
                size_type e)
      : curr_(b),
        end_(e)
        { }

    size_type const&
    operator*() const { return curr_; }

    RangeHelper& 
    operator++() 
        { 
        ++curr_; 
        return *this;
        }

    bool
    operator!=(RangeHelper const& other) const
        {
        return curr_ != other.curr_;
        }

    RangeHelper 
    begin() const { return RangeHelper(curr_,end_); }

    RangeHelper 
    end() const { return RangeHelper(end_,end_); }
    };

} //namespace detail

template <typename T,
          class=typename std::enable_if<std::is_integral<T>::value>::type>
auto constexpr
range(T end) 
    -> detail::RangeHelper<T>
    {
    return detail::RangeHelper<T>(0,end);
    }

template <typename ST, typename T,
          class=typename std::enable_if<
                         std::is_integral<ST>::value
                      && std::is_integral<T>::value>::type>
auto constexpr
range(ST start, T end) 
    -> detail::RangeHelper<T>
    {
    return detail::RangeHelper<T>(T(start),end);
    }

template <typename T,
          class=typename std::enable_if<std::is_integral<T>::value>::type>
auto constexpr
range1(T end) -> detail::RangeHelper<T>
    {
    return detail::RangeHelper<T>(1,1+end);
    }

template <typename ST, typename T,
          class=typename std::enable_if<
                         std::is_integral<ST>::value
                      && std::is_integral<T>::value>::type>
auto constexpr
range1(ST start, T end) -> detail::RangeHelper<T>
    {
    return detail::RangeHelper<T>(start,1+end);
    }

template <typename C> constexpr
auto
range(C const& container) 
    -> detail::RangeHelper<decltype(container.size())>
    {
    using size_type = decltype(container.size());
    return detail::RangeHelper<size_type>(0,container.size());
    }

template <typename C> constexpr
auto
range1(C const& container) 
    -> detail::RangeHelper<decltype(container.size())>
    {
    using size_type = decltype(container.size());
    return detail::RangeHelper<size_type>(1,1+container.size());
    }

}

#endif
