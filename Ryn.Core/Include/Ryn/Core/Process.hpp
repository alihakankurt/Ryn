#pragma once

namespace Ryn
{
    class Process
    {
      public:
        [[noreturn]]
        static void Exit(int code);
    };
}
