require "lua_scripts.env_variables"


os.execute("mkdir build")


local origin = LibPaths.glfw .. "/bin"
local dest = PrPath .. "/build"
local glfw_command = 'xcopy ' .. origin .. ' ' .. dest
glfw_command = string.gsub(glfw_command,'/','\\');
glfw_command = glfw_command .. " /d"

print(glfw_command)
os.execute(glfw_command )
