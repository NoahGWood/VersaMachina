# Development

## Repo Setup

1. Clone the repo

   ` git clone https://github.com/NoahGWood/VersaMachina.git `

2. Initialize Submodules

   ` git submodule init `

3. Install Submodules
   ` git submodule update `

**Note:** It's not uncommon for github to fail to clone all submodules the first time, if this occurs verify each submodule is not empty (will only have .git file), if a submodule is empty, delete its' folder from VersaLib/vendor/ and  run ` git submodule update` again.

### ImGuizmo Changes

In order to use the GraphEditor from ImGuizmo, it's necessary to replace the following code within `VersaLib/vendor/ImGuizmo/GraphEditor.h`:

```
#include "imgui.h"
#include "imgui_internal.h"
```

with:

```
#ifdef VERSA_MACHINA
    #include <imgui/imgui.h>
    #include <imgui/imgui_internal.h>
#else
    #include "imgui.h"
    #include "imgui_internal.h"
#endif
```