#ifndef RYN_FRAMEWORK_ENTITY
#define RYN_FRAMEWORK_ENTITY

#include <Ryn/Core.hpp>

namespace Ryn
{
    class Entity
    {
      public:
        virtual ~Entity() = default;

        virtual void Update(f32 deltaTime) = 0;
        virtual void Render() = 0;
    };
}

#endif