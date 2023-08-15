#pragma once

#include "Versa.h"

#include "panels/Settings.h"


namespace VersaMachina
{
    class EditorSettingsPanel
    {
        public:
            void OnImGuiRender();
            
        private:
            EditorSettings m_EditorSettings;


    };

} // namespace VersaMachina
