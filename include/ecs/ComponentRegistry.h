#pragma once
#include "common/Base.h"
#include <typeindex>
#include <typeinfo>
#include <any>


namespace VM
{
    struct ComponentOps
    {
        using SnapshotFn = std::function<void(entt::registry &, entt::entity, std::unordered_map<std::type_index, std::any> &)>;
        using RestoreFn = std::function<void(entt::registry &, entt::entity, const std::unordered_map<std::type_index, std::any> &)>;
        using CloneFn = std::function<void(entt::registry &, entt::entity, entt::entity)>;
        std::string name;
        SnapshotFn snapshot{};
        RestoreFn restore{};
        CloneFn clone{};
    };

    class ComponentRegistry
    {
    public:
        static ComponentRegistry &Instance()
        {
            static ComponentRegistry inst;
            return inst;
        }

        template <typename T>
        void Register(const char* overrideName = nullptr)
        {
            std::type_index ti = typeid(T);
            if (m_ByType.count(ti))
                return;
            
            std::string name = overrideName ? overrideName : typeid(T).name();
            ComponentOps ops{};
            ops.name = name;

            ops.snapshot = [ti](entt::registry &reg, entt::entity e,
                              std::unordered_map<std::type_index, std::any> &out)
            {
                if (auto *c = reg.try_get<T>(e))
                    out[ti] = *c;
            };
            ops.restore = [ti](entt::registry &reg, entt::entity e,
                             const std::unordered_map<std::type_index, std::any> &data)
            {
                auto it = data.find(ti);
                if (it != data.end())
                    reg.emplace_or_replace<T>(e, std::any_cast<T>(it->second));
            };
            ops.clone = [ti](entt::registry &reg, entt::entity src, entt::entity dst)
            {
                if (auto *c = reg.try_get<T>(src))
                    reg.emplace_or_replace<T>(dst, *c);
            };
            m_ByType.emplace(ti, ops);
            m_ByName.emplace(ops.name, ti);
        }

        const ComponentOps *Get(std::type_index ti) const
        {
            auto it = m_ByType.find(ti);
            return it == m_ByType.end() ? nullptr : &it->second;
        }

        const ComponentOps *GetByName(const std::string &name) const
        {
            auto it = m_ByName.find(name);
            return it == m_ByName.end() ? nullptr : Get(it->second);
        }

        const auto &All() const { return m_ByType; }

    private:
        std::unordered_map<std::type_index, ComponentOps> m_ByType;
        std::unordered_map<std::string, std::type_index> m_ByName;
    };

} // namespace VM
