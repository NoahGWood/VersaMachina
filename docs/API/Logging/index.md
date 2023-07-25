# Logging API

Logging within the VersaMachina project is accomplished by using the [spdlog](https://github.com/gabime/spdlog) library.

## Logging Levels

There are 5 levels of logging in the VersaMachina engine:

- VM_TRACE
- <span style="color:green">VM_INFO</span>
- <span style="color:yellow">VM_WARN</span>
- <span style="color:red">VM_ERROR</span>
- <span style="background-color:red">VM_CRITICAL</span>

## Logging Macros (C++)

App logging macros for C++ are defined in the `VersaLib/Core/Log.h` file which is automatically imported into `Versa.h` for you and should work out of the box in your applications.

`Log.h` defines the following macros:

```
#define VM_TRACE(...) ::VersaMachina::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VM_INFO(...) ::VersaMachina::Log::GetClientLogger()->info(__VA_ARGS__)
#define VM_WARN(...) ::VersaMachina::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VM_ERROR(...) ::VersaMachina::Log::GetClientLogger()->error(__VA_ARGS__)
#define VM_CRITICAL(...) ::VersaMachina::Log::GetClientLogger()->critical(__VA_ARGS__)
```


Using these macros is very easy and should work with all types and classes in the system. If something doesn't work, please submit a new [issue](github.com/NoahGWood/VersaMachina/issues) so we can implement it. Here is a quick example of how to use the logging macro.

```
#include "Versa.h"
//#include "Core/Log.h" // Alternative include 
int x = 10;
VM_INFO("Info"); // Log with just a string
VM_TRACE("This is {0}: {1}", "ten", x); // Log with 1 or more variables
```



## Logging Macros (C#)

(To be implemented)

