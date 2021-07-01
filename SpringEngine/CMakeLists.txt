cmake_minimum_required (VERSION 3.8)

project(SpringEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# SpringEngine definitions
add_compile_definitions(SE_PLATEFORM_WINDOWS)
add_compile_definitions(SE_BUILD_DLL)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_compile_definitions(SE_DEBUG)
endif()

include_directories( "include/" "lib/ImGui" "lib/ImGuizmo-master" "lib/ImGui/backends" "lib/GLFW/include" "lib/GLEW/include" "include/external" "lib/spdlog/include" "lib/Assimp/Include" "lib/json/include" )

set(SRCS
	"src/Core/Application.cpp"
	"src/Misc/Instrumentator.cpp"
	"src/Misc/Logger.cpp"
	"src/Core/Window.cpp"
	"src/Graphics/Renderer.cpp"
	"src/Graphics/OpenGL/OpenGLRenderer.cpp"
	"src/Graphics/Vulkan/VulkanRenderer.cpp"
	"src/Graphics/OpenGL/OpenGLApi.cpp"
	"src/Graphics/Vulkan/VulkanApi.cpp"
	"src/Graphics/Vulkan/VulkanDevice.cpp"
	"src/Graphics/Vulkan/VulkanPhysicalDevice.cpp"
	"src/Graphics/Vulkan/VulkanQueueFamily.cpp"
	"src/Graphics/Vulkan/VulkanRenderer2D.cpp"
	"src/Graphics/Surface.cpp"
	)

set(IMGUI_SRCS
	"lib/ImGui/imgui.cpp"
	"lib/ImGui/imgui_demo.cpp"
	"lib/ImGui/imgui_tables.cpp"
	"lib/ImGui/imgui_widgets.cpp"
	"lib/ImGui/imgui_draw.cpp"
	"lib/ImGui/backends/imgui_impl_vulkan.cpp"
	"lib/ImGui/backends/imgui_impl_glfw.cpp"
#	"lib/ImGuizmo-master/ImGuizmo.cpp"
)

add_library(SpringEngine SHARED ${SRCS} ${IMGUI_SRCS} "include/SpringEngine/Core/Core.hpp")
find_package(Vulkan REQUIRED)

target_include_directories(SpringEngine PUBLIC "include/" "lib/ImGui" "lib/ImGuizmo-master" "lib/ImGui/backends" "lib/GLFW/include" "lib/GLEW/include" "include/external" "lib/spdlog/include" "lib/Assimp/Include" "lib/json/include")

target_precompile_headers(SpringEngine
  PUBLIC
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/SpringEngine/pch.hpp>"
)

add_subdirectory("lib/spdlog")

target_link_libraries(SpringEngine "./lib/GLFW/glfw3")
target_link_libraries(SpringEngine "./lib/GLEW/glew32")
target_link_libraries(SpringEngine "./lib/freetype/freetype")
target_link_libraries(SpringEngine "./lib/FMOD/fmod_vc")
target_link_libraries(SpringEngine "./lib/FMOD/fmodstudio_vc")
target_link_libraries(SpringEngine "./lib/Assimp/Release/assimp-vc141-mt")
target_link_libraries(SpringEngine Vulkan::Vulkan)

file(COPY "lib/GLFW/lib-vc2019/glfw3.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/GLFW/)
file(COPY "lib/GLFW/lib-vc2019/glfw3.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/GLEW/lib/glew32.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/GLEW/)
file(COPY "lib/GLEW/bin/Release/x64/glew32.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/freetype/freetype.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/freetype/)
file(COPY "lib/freetype/freetype.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/FMOD/fmod_vc.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/FMOD/)
file(COPY "lib/FMOD/fmod.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/FMOD/fmodstudio_vc.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/FMOD/)
file(COPY "lib/FMOD/fmodstudio.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/Assimp/assimp-vc141-mt.dll" DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "lib/Assimp/Release/assimp-vc141-mt.lib" DESTINATION ${CMAKE_BINARY_DIR}/lib/Assimp/Release)

set_target_properties(SpringEngine PROPERTIES PUBLIC_HEADER "include/SpringEngine/SpringEngine.hpp")