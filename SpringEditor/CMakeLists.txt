# ISU Flight simulator

project(SpringEditor)
cmake_minimum_required (VERSION 3.8)


#no console
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")


# SpringEngine definitions
add_compile_definitions(SE_PLATEFORM_WINDOWS)
add_compile_definitions(SE_EDITOR)

include_directories("../SpringEngine/include" "include/" "lib/ImGui/" "lib/Assimp/Include/" "lib/freetype/" "GLEW/include" "GLFW/include" "lib/spdlog/include")

set(SRCS
	"src/SpringEditorApp.cpp"
)

set(IMGUI_SRCS
	"../SpringEngine/lib/ImGui/imgui.cpp"
	"../SpringEngine/lib/ImGui/imgui_demo.cpp"
	"../SpringEngine/lib/ImGui/imgui_tables.cpp"
	"../SpringEngine/lib/ImGui/imgui_widgets.cpp"
	"../SpringEngine/lib/ImGui/imgui_draw.cpp"
	"../SpringEngine/lib/ImGui/backends/imgui_impl_vulkan.cpp"
	"../SpringEngine/lib/ImGui/backends/imgui_impl_glfw.cpp"
	#"../SpringEngine/lib/ImGuizmo-master/ImGuizmo.cpp"
)


add_executable (SpringEditor ${SRCS} ${IMGUI_SRCS})

target_link_libraries(SpringEditor PUBLIC SpringEngine)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("On n'enlève pas la console")
else()
    message("On enlève la console")
    set_target_properties(SpringEditor PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup /SUBSYSTEM:WINDOWS")
endif()


#add_custom_command(
#        TARGET SpringEditor
#        COMMAND ${CMAKE_COMMAND} -E copy
#                "${CMAKE_CURRENT_SOURCE_DIR}/src/imgui-niceEditorConfig.ini"
#                "${CMAKE_BINARY_DIR}/bin/imgui.ini"
#)