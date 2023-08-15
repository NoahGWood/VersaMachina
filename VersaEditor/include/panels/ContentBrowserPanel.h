#pragma once

#include "Versa.h"

namespace VersaMachina
{
    class ContentBrowserPanel
    {
        public:
            ContentBrowserPanel() = default;

            void SetContext(const Ref<ECS::Scene>& scene);

            void OnImGuiRender();
        private:

    };

} // namespace VersaMachina
