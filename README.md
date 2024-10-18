# Vulkan tutorial

[tutorial](https://vulkan-tutorial.com/Uniform_buffers/Descriptor_pool_and_sets)

## BUILD 

Add a script called env_variables under the lua_scripts folder 

```lua 
LibPaths = {}
-- libraries
LibPaths.vulkan = "c:/path/to/vulkan"
LibPaths.glfw = "c:/path/to/glfw"
LibPaths.glm = "c:/path/to/glm"
PrPath = "ActualPathOfRepo"
```
Run this scripts on this order 
- set_up.lua  
- compile_shaders.lua 
- run.lua 
- reload_commands.lua 

## DEBUG
- [raddebugger](https://github.com/EpicGamesExt/raddebugger/tree/master)
- vulkan configurator

## Editor 
nvim + lazyvim + clang lsp  + Exrc Plugin + Overseer 
