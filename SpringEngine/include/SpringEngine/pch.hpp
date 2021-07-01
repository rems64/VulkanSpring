#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <set>

#include <Windows.h>
#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <SpringEngine/Core/Core.hpp>
#include <SpringEngine/Misc/Instrumentator.hpp>
#include <SpringEngine/Misc/Logger.hpp>

#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/bundled/ostream.h>