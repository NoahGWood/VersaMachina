#pragma once

namespace VM
{
    class Project; // Forward declare
    class ICommand {
        public:
            virtual ~ICommand() = default;
            virtual const std::string Name() const = 0;
            virtual void Execute(Project& project) = 0;
            virtual void Undo(Project& project) = 0;
    };

} // namespace VM
