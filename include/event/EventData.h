#pragma once
#include <common/Base.h>
namespace VM
{
    struct AppTickData
    {
        double deltaTime = 0.0;
        uint64_t frame = 0;
    };

    using EventData = std::variant<
        AppTickData
    >;
    
} // namespace VM
