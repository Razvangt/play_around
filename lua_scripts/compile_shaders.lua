require "lua_scripts.env_variables"
local compiler = LibPaths.vulkan .. "/Bin/glslc.exe"

os.execute('mkdir  build\\shaders')

os.execute(compiler .. " resources/shaders/shader.frag  -o build/shaders/frag.spv")
os.execute(compiler .. " resources/shaders/shader.vert  -o build/shaders/vert.spv")
