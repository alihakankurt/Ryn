#ifndef __RYN_CORE_ITERABLE_HPP__
#define __RYN_CORE_ITERABLE_HPP__

#include <Ryn/Core/Concepts.hpp>

namespace Ryn
{
    template <typename TSelf>
    concept Iterable = requires(TSelf self)
    {
        { self.Begin() } -> Pointer;
        { self.End() } -> Pointer;
    };

    template <Iterable TSelf>
    static inline constexpr decltype(auto) begin(const TSelf& self)
    {
        return self.Begin();
    }

    template <Iterable TSelf>
    static inline constexpr decltype(auto) end(const TSelf& self)
    {
        return self.End();
    }
}

#endif