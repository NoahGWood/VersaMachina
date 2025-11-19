#pragma once
#include <common/Base.h>

namespace VM
{
    class BlockRegistry{
        public:
            BlockRegistry& Instance(){
                static BlockRegistry instance;
                return instance;
            }

        private:
            BlockRegistry(){
                LoadConfigs();
            }
    }; 
} // namespace VM
