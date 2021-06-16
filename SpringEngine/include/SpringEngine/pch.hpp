#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <set>

#include <Windows.h>
#include <vulkan/vulkan.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <SpringEngine/Core/Core.hpp>
#include <SpringEngine/Debug/Instrumentator.hpp>
#include <SpringEngine/Debug/Logger.hpp>