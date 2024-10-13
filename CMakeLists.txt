
cmake_minimum_required(VERSION 3.10)
project(VulkanApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the source files
set(SOURCE_FILES src/main.cpp src/vk_app.cpp src/debug.cpp)

# Find Vulkan, GLM, and GLFW packages
find_package(Vulkan REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 REQUIRED)


# Include directories for Vulkan, GLM, and GLFW
include_directories( ${Vulkan_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} include)


# Add executable
add_executable(VulkanApp ${SOURCE_FILES} ${HEADER_FILES})

# Link libraries
target_link_libraries(VulkanApp ${Vulkan_LIBRARIES} glm::glm glfw)

