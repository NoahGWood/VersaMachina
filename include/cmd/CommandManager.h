#pragma once
#include <common/Base.h>
#include <cmd/ICommand.h>
namespace VM
{
    class Project; // Forward declare
    class CommandManager {
        public:
            void Run(std::unique_ptr<ICommand> cmd, Project& project){
                cmd->Execute(project);
                m_RedoStack.clear();
                // CORE_INFO("Push command: {}", cmd->Name());
                m_UndoStack.push_back(std::move(cmd));
            }

            void Undo(Project& project){
                if(m_UndoStack.empty()){
                    CORE_INFO("Nothing to undo.");
                    return;
                }
                auto cmd = std::move(m_UndoStack.back());
                // CORE_INFO("Undo command: {}", cmd->Name());
                m_UndoStack.pop_back();
                cmd->Undo(project);
                m_RedoStack.push_back(std::move(cmd));
            }

            void Redo(Project& project) {
                if (m_RedoStack.empty()){
                    CORE_INFO("Nothing to redo.");
                    return;
                }
                auto cmd = std::move(m_RedoStack.back());
                m_RedoStack.pop_back();

                cmd->Execute(project);
                // CORE_INFO("Redo command: {}", cmd->Name());
                m_UndoStack.push_back(std::move(cmd));
            }

            bool CanUndo() const { return !m_UndoStack.empty(); }
            bool CanRedo() const { return !m_RedoStack.empty(); }
        private:
            std::vector<std::unique_ptr<ICommand>> m_UndoStack;
            std::vector<std::unique_ptr<ICommand>> m_RedoStack;
    };
} // namespace VM
