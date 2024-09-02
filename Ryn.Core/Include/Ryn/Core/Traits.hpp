#pragma once

namespace Ryn::Core
{
    template <typename TValue>
    struct RemoveReference
    {
        using Type = TValue;
    };

    template <typename TValue>
    struct RemoveReference<TValue&>
    {
        using Type = TValue;
    };

    template <typename TValue>
    struct RemoveReference<TValue&&>
    {
        using Type = TValue;
    };

    template <typename TValue>
    using RemoveReferenceType = typename RemoveReference<TValue>::Type;
}
