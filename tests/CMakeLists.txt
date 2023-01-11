set(TEST_PROJECT_TARGET tests)

project(${TEST_PROJECT_TARGET}
	LANGUAGES CXX
)

set(TEST_UNIT_DIR
	unit
	CACHE PATH "Illusio's Unit Tests directory" FORCE	
)

set(UNIT_TEST_SOURCES

	${TEST_UNIT_DIR}/test.unit.cpp
)

set(TEST_HEADERS

	pch.h
)

set(TEST_SOURCES

	pch.cpp
)

add_executable(${TEST_PROJECT_TARGET}
	${TEST_SOURCES}

	${UNIT_TEST_SOURCES}
)

target_include_directories(
	${TEST_PROJECT_TARGET}
PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}

	${ILLUSIO_LIB_SRC}
)

target_link_libraries(
	${TEST_PROJECT_TARGET}
PRIVATE
	${PROJECT_LIBRARY_TARGET}
	Catch2::Catch2WithMain
)

catch_discover_tests(${TEST_PROJECT_TARGET})

## MSVC ##

if(MSVC)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Header Files"
		FILES ${TEST_HEADERS}
	)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Source Files"
		FILES ${UNIT_TEST_SOURCES} ${TEST_SRC}
	)
endif()

## MSVC ##
