require "lua_scripts.env_variables"
local compiler = LibPaths.vulkan .. "/Bin/glslc.exe"
os.execute(compiler .. "resources/shaders/shader.frag build/shaders/frag.spv")
os.execute(compiler .. "resources/shaders/shader.vert build/shaders/vert.spv")
