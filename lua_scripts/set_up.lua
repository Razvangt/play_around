require "lua_scripts.env_variables"


os.execute("mkdir build")



-- In windows we need the glwf dll from the bin in the build file
local origin = LibPaths.glfw .. "/bin"
local dest = PrPath .. "/build"
local glfw_command = 'xcopy ' .. origin .. ' ' .. dest
glfw_command = string.gsub(glfw_command,'/','\\');
glfw_command = glfw_command .. " /d"
print(glfw_command)
os.execute(glfw_command )
