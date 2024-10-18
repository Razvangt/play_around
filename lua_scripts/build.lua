require "lua_scripts.env_variables"
local flags = " -Wall -MJ fragments -g -std=c++20 "


local vulkan_include = "-I" .. LibPaths.vulkan .. "/Include"
local vulkan_lib_dir = "-L" .. LibPaths.vulkan .. "/Lib"
local vulkan_lib = "-lvulkan-1"

local glfw_include = "-I" .. LibPaths.glfw .. "/include"
local glfw_lib_dir = "-L" .. LibPaths.glfw .. "/lib"
local glfw_lib = "-lglfw3dll "

local glm_include = "-I" .. LibPaths.glm .. "/include"
local glm_lib_dir = "-L" .. LibPaths.glm .. "/lib"
local glm_lib = "-lglm"

-- Targets
local include = table.concat({
  vulkan_include,
  " ",
  glfw_include,
  " ",
  glm_include
})
local search_lib = table.concat({
  vulkan_lib_dir,
  " ",
  glfw_lib_dir,
  " ",
  glm_lib_dir
})
local link_lib = table.concat({
  vulkan_lib,
  " ",
  glfw_lib,
  " ",
  glm_lib
})

local source = table.concat({
  " src/main.cpp",
  " src/engine/debug.cpp",
  " src/engine/vk_tools.cpp",
  " src/engine/window.cpp",
  " src/engine/render_pipeline.cpp",
  " src/engine/swapchain.cpp",
  " src/engine/vk_commands.cpp",
  " src/engine/engine_lib.cpp",
})


print("----------Compile  program --------------")
local compile = table.concat({
  "clang++ ",
  flags,
  " ",
  include,
  " ",
  search_lib,
  " ",
  link_lib,
  " ",
  source,
  " -o build/main.exe",
})
print(compile)
os.execute(compile)



