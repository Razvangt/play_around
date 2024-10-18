require "lua_scripts.env_variables"
print("----------Run  program --------------")

os.setlocale(PrPath .. "/build/")
local run = PrPath .. "/build/main.exe"
print(run)
os.execute("cd build && " .. run)


