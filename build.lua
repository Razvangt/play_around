local  buildF = "C:/Users/razvan/pro/code/c/play_around/out/build/default"
local  target = "VulkanApp"
local command = "cmake --build " .. buildF .." --parallel 14 --target " ..target 
local run_command = buildF .. "./".. target


print("----------Build---------------")
print(command)
os.execute(command)
print("----------Run---------------")

print(run_command)
os.execute(run_command)

