find_package(OpenGL REQUIRED)

## glfw ##

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

## imgui ##

add_library(imgui_src STATIC
  imgui/imgui.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_demo.cpp
  imgui/imgui_widgets.cpp
  imgui/imgui_tables.cpp

  imgui/backends/imgui_impl_glfw.cpp
  imgui/backends/imgui_impl_opengl3.cpp

  imgui/imconfig.h
  imgui/imgui.h
  imgui/imgui_internal.h
  imgui/imstb_rectpack.h
  imgui/imstb_textedit.h
  imgui/imstb_truetype.h
)

target_include_directories(imgui_src
PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
  imgui
  glfw/include
)

## app_external_deps ##

add_library(app_external_deps INTERFACE)
target_link_libraries(app_external_deps INTERFACE
  imgui_src
  glfw
  OpenGL::GL
)
