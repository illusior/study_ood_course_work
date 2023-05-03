message(STATUS "Getting externals")

Include(FetchContent)

## OpenGl ##

find_package(OpenGL REQUIRED)

## OpenGl ##

## glfw ##

message(STATUS "Fetching GLFW...")

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG        3.3.8
)

FetchContent_GetProperties(glfw)

if(NOT glfw_POPULATED)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    FetchContent_Populate(glfw)

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

set(EXTERNAL_ILLUSIO_GLFW_INCLUDE_DIR
	${glfw_SOURCE_DIR}/include
	CACHE PATH "Illusio's GLFW include directory path" FORCE
)

## glfw ##

## imgui ##

message(STATUS "Setting up ImGui...")

set(EXTERNAL_ILLUSIO_IMGUI_LIB
	imgui_lib
	CACHE STRING "Illusio's ImGui library's name" FORCE
)

set(EXTERNAL_ILLUSIO_IMGUI_SRC
	imgui/imgui.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_demo.cpp
	imgui/imgui_widgets.cpp
	imgui/imgui_tables.cpp
	
	CACHE INTERNAL "Illusio's ImGUI's Source Files" FORCE
)

set(EXTERNAL_ILLUSIO_IMGUI_BACKENDS_GLFW_OPENGL3_SRC
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_opengl3.cpp

	CACHE INTERNAL "Illusio's ImGUI Backend's Source Files" FORCE
)

set(EXTERNAL_ILLUSIO_IMGUI_HEADERS
	imgui/imconfig.h
	imgui/imgui.h
	imgui/imgui_internal.h
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h

	CACHE INTERNAL "Illusio's ImGUI's Header Files" FORCE
)

add_library(
	${EXTERNAL_ILLUSIO_IMGUI_LIB}
STATIC
	${EXTERNAL_ILLUSIO_IMGUI_HEADERS}
	${EXTERNAL_ILLUSIO_IMGUI_SRC}
	${EXTERNAL_ILLUSIO_IMGUI_BACKENDS_GLFW_OPENGL3_SRC}
)

target_include_directories(
	${EXTERNAL_ILLUSIO_IMGUI_LIB}
PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
		imgui
	${EXTERNAL_ILLUSIO_GLFW_INCLUDE_DIR}
)

## imgui ##

## Catch2 ##

function(fetch_catch2)

	message(STATUS "Fetching Catch2...")

	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v3.2.1
	)

	FetchContent_MakeAvailable(Catch2)
	list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

	include(Catch)

endfunction()

## Catch2 ##

## Boost ##

message(STATUS "Fetching Boost...")

FetchContent_Declare(
	Boost
	URL https://github.com/boostorg/boost/releases/download/boost-1.81.0/boost-1.81.0.tar.xz
	URL_MD5 6cf0cdd797bca685910d527ae3c08cb3
	DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_ENABLE_MPI OFF)
set(BOOST_ENABLE_PYTHON OFF)
set(BOOST_STACKTRACE_ENABLE_NOOP OFF)
set(BOOST_STACKTRACE_ENABLE_BACKTRACE OFF)
set(BOOST_STACKTRACE_ENABLE_ADDR2LINE OFF)
set(BOOST_STACKTRACE_ENABLE_BASIC OFF)
set(BOOST_STACKTRACE_ENABLE_WINDBG OFF)
set(BOOST_STACKTRACE_ENABLE_WINDBG_CACHED OFF)

set(BOOST_INCLUDE_LIBRARIES uuid)

message(STATUS "Configuring Boost")

FetchContent_MakeAvailable(Boost)

## Boost ##

## ISpringTech's FastSignals ##

FetchContent_Declare(
	FastSignals
	GIT_REPOSITORY https://github.com/beta442/ispring_fast_signals
)

if(NOT fastsignals_POPULATED)
	set(BUILD_TESTING OFF)

	message(STATUS "Fetching ISpringTech's FastSignals")
	FetchContent_Populate(FastSignals)

	message(STATUS "Configuring ISpringTech's FastSignals")
	add_subdirectory(${fastsignals_SOURCE_DIR} ${fastsignals_BINARY_DIR})

	set(fastsignals_SOURCE_DIR
		${fastsignals_SOURCE_DIR}
		CACHE PATH "ISpringTech's FastSignal's library source directory path" FORCE
	)
	set(FASTSIGNALS_LIB_NAME
		libfastsignals
		CACHE STRING "ISpringTech's FastSignal's library name" FORCE
	)
	get_target_property(_temp libfastsignals VS_USER_PROPS)
	set(FASTSIGNALS_VS_USER_PROPS_PATH
		${_temp}
		CACHE FILEPATH "Path to file that contains user macros in MSCV" FORCE
	)
endif()

## ISpringTech's FastSignals ##

## app_external_deps ##

set(EXTERNALS_ILLUSIO_LIB
	externals_illusio_lib
	CACHE STRING "Application's externals library name" FORCE
)

add_library(${EXTERNALS_ILLUSIO_LIB} INTERFACE)

target_link_libraries(
	${EXTERNALS_ILLUSIO_LIB}
INTERFACE
	${EXTERNAL_ILLUSIO_IMGUI_LIB}
	glfw
	OpenGL::GL

	Boost::uuid
)

## app_external_deps ##

## MSVC ##

if(MSVC)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Header Files"
		FILES ${EXTERNAL_ILLUSIO_IMGUI_HEADERS}
	)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Source Files"
		FILES ${EXTERNAL_ILLUSIO_IMGUI_SRC} ${EXTERNAL_ILLUSIO_IMGUI_BACKENDS_GLFW_OPENGL3_SRC}
	)
endif()

## MSVC ##
