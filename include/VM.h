#pragma once
#include <common/Base.h>
#include <common/ImGuiLogging.h>
#include <app/Application.h>
#include <event/EventRouter.h>
#include <window/Window.h>

// Command handling
#include <cmd/CommandManager.h>
#include <cmd/EntityCommand.h>
#include <cmd/EditFieldCommand.h>

// ECS System
#include <ecs/Project.h>
#include <ecs/Components.h>
#include <ecs/ComponentFieldUI.h>
// UI Menus
#include <ui/Menus/FileMenu.h>
#include <ui/Menus/EditMenu.h>
#include <ui/Menus/ToolsMenu.h>
#include <ui/Menus/ViewMenu.h>
#include <ui/Menus/HelpMenu.h>

// UI Panels
#include <ui/MainPanel.h>
#include <ui/Panels/ConsolePanel.h>
#include <ui/Panels/ExporterPanel.h>
#include <ui/Panels/HardwarePanel.h>
#include <ui/Panels/InspectorPanel.h>
#include <ui/Panels/ProjectPanel.h>
#include <ui/Panels/InspectorPanel.h>
#include <ui/Panels/ToolboxPanel.h>
#include <ui/Panels/StylePanel.h>