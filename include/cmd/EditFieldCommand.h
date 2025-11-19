#pragma once
#include <common/Base.h>
#include <cmd/ICommand.h>
#include <ecs/EntitySnapshot.h>

namespace VM
{
    template<typename T>
    class EditFieldCommand : public ICommand
    {
        public:
            using Accessor = std::function<T&(Project&, entt::entity)>;

            EditFieldCommand(entt::entity e, Accessor acc, const T& oldVal, const T& newVal)
                : m_Entity(e), m_Accessor(std::move(acc)), m_Old(oldVal), m_New(newVal){
                }
            const std::string Name() const override { return "Edit Field"; }
            void Execute(Project& project) override {
                if(project.IsValid(m_Entity))
                    m_Accessor(project, m_Entity) = m_New;
            }
            void Undo(Project& project) override {
                if(project.IsValid(m_Entity))
                    m_Accessor(project, m_Entity) = m_Old;
            }
        private:
            entt::entity m_Entity;
            Accessor m_Accessor;
            T m_Old, m_New;
    };
} // namespace VM
