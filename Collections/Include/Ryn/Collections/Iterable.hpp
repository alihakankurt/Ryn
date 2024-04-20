#ifndef __RYN_COLLECTIONS_ITERABLE_HPP__
#define __RYN_COLLECTIONS_ITERABLE_HPP__

#include <Ryn/Core.hpp>

namespace Ryn
{
    template <typename TSelf>
    concept Iterable = requires(TSelf self)
    {
        { self.Begin() } -> Pointer;
        { self.End() } -> Pointer;
    };

    template <Iterable TSelf>
    static inline constexpr auto begin(TSelf self)
    {
        return self.Begin();
    }

    template <Iterable TSelf>
    static inline constexpr auto end(TSelf self)
    {
        return self.End();
    }
}

#endif