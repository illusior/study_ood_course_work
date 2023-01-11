set(ILLUSIO_LIB_SRC
	illusio
	CACHE PATH "Illusio's library sources directory"
)

set(ILLUSIO_LIB illusio_lib)
set(ILLUSIO_APP illusio_app)

set(_illusio_lib_headers

	${ILLUSIO_LIB_SRC}/pch_illusio.h
	# Add new lib's headers here
)

set(_illusio_lib_sources

	${ILLUSIO_LIB_SRC}/pch_illusio.cpp
	# Add new lib's sources here
)


add_library(${ILLUSIO_LIB}
	${_illusio_lib_headers}
	${_illusio_lib_sources}
)

add_executable(${ILLUSIO_APP}
	pch.h

	pch.cpp
	main.cpp
)

target_link_libraries(
	${ILLUSIO_LIB}
PUBLIC
	${EXTERNALS_ILLUSIO_LIB}
)

target_link_libraries(
	${ILLUSIO_APP}
PRIVATE
	${ILLUSIO_LIB}
)

target_include_directories(
	${ILLUSIO_APP}
PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
	${ILLUSIO_LIB_SRC}
)

## MSVC ##

if(MSVC)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Header Files"
		FILES ${_illusio_lib_headers}
	)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Source Files"
		FILES ${_illusio_lib_sources}
	)
endif()

## MSVC ##
