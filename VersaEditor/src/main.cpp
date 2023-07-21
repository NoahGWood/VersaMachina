#include "Versa.h"
#include "entry.h"
#include <iostream>
namespace VersaMachina
{

class Sandbox : public VersaMachina::Application
{
    public:
        Sandbox()
        {
            std::cout << "Hello, VersaMachina World" << std::endl;
        }
        ~Sandbox()
        {

        }
};

Application* CreateApplication()
{
    return new Sandbox();
}


} // namespace VersaMachina

