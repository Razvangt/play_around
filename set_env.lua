local  toolchain_vcpkg ="C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake"
local  BuildType = "Debug"
local  sourceF =  "C:/Users/razvan/pro/code/c/play_around"
local  buildF = "C:/Users/razvan/pro/code/c/play_around/out/build/default"
local  generator = "Ninja"
local command = "cmake  -DCMAKE_TOOLCHAIN_FILE:FILEPATH="..toolchain_vcpkg..
                      " -DCMAKE_BUILD_TYPE="..BuildType..
                      " -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -S"..sourceF..
                      " -B"..buildF..
                      " -G " .. generator

os.execute(command)
