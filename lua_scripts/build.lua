require "lua_scripts.env_variables"

local flags_list = {}
local include_list = {}
local search_lib_list = {}
local link_lib_list = {}
local source_list = {}
local compile_list = {}

local function include_path(path,folder)
  local result = "-I" .. path .. "/" .. folder
  table.insert(include_list,result)
end
local function lib_path(path,folder)
  path =  "-L" .. path .. "/" .. folder
  table.insert(search_lib_list,path)
end

local function lib_to_link(name)
  local result =  "-l" .. name
  table.insert(link_lib_list,result)
end
local function add_flags(name)
  table.insert(flags_list,name)
end
local function add_source(name)
  table.insert(source_list,name)
end
local function add_compile(name)
  table.insert(compile_list,name)
end




--- LIBRARIES 

include_path(LibPaths.stb,"include")
include_path(LibPaths.vulkan, "Include")
include_path(LibPaths.glfw, "include")
include_path(LibPaths.glm, "include")

lib_path(LibPaths.vulkan, "Lib")
lib_path(LibPaths.glfw, "lib")
lib_path(LibPaths.glm, "lib")

lib_to_link("vulkan-1")
lib_to_link("glfw3dll")
lib_to_link("glm")

-- COMPILER
local compiler = "clang++"
add_flags("-Wall")
add_flags("-MJ fragments ")
add_flags("-g")
add_flags("-std=c++20")

--- SOURCE 
add_source("src/main.cpp")
add_source("src/engine/vk_tools.cpp")
add_source("src/engine/pipeline.cpp")
add_source("src/engine/window.cpp")
add_source("src/engine/engine_lib.cpp")
local result = "-o build/main.exe"

print("----------Compile  program --------------")
local include = table.concat(include_list," ")
local search_lib = table.concat(search_lib_list," ")
local link_lib = table.concat(link_lib_list," ")
local flags =  table.concat(flags_list, " ")
local source = table.concat(source_list, " ")
add_compile(compiler)
add_compile(flags)
add_compile(include)
add_compile(search_lib)
add_compile(link_lib)
add_compile(source)
add_compile(result)
local compile = table.concat(compile_list," ")
print(compile)

os.execute(compile)



