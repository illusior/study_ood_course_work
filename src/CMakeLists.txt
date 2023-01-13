## Illusio's lib ##

set(ILLUSIO_LIB_SRC
	illusio
	CACHE PATH "Illusio's library sources directory"
)

set(ILLUSIO_LIB illusio_lib)

set(_illusio_lib_headers

	${ILLUSIO_LIB_SRC}/pch_illusio.h
	# Add new lib's headers here

	#COMMON#
	${ILLUSIO_LIB_SRC}/common/signals/signal.hpp
	${ILLUSIO_LIB_SRC}/common/uuid/uuid.hpp
	#COMMON#

	#DOMAIN#
		#COMMON#
	${ILLUSIO_LIB_SRC}/domain/common/domain_common.h

	${ILLUSIO_LIB_SRC}/domain/common/color/RGBAColor.h

	${ILLUSIO_LIB_SRC}/domain/common/frame/Frame.h
	${ILLUSIO_LIB_SRC}/domain/common/frame/CFrame/FrameD.h

	${ILLUSIO_LIB_SRC}/domain/common/point/Point.h
	${ILLUSIO_LIB_SRC}/domain/common/point/CPoint/PointD.h

	${ILLUSIO_LIB_SRC}/domain/common/size/Size.h
	${ILLUSIO_LIB_SRC}/domain/common/size/CSize/SizeD.h

	${ILLUSIO_LIB_SRC}/domain/common/style/IStyle_fwd.h
	${ILLUSIO_LIB_SRC}/domain/common/style/IStyle.h
	${ILLUSIO_LIB_SRC}/domain/common/style/CStyle/Style.h
	${ILLUSIO_LIB_SRC}/domain/common/style/CStyle/StyleComposite.h
		#COMMON#
		#SHAPE#
	${ILLUSIO_LIB_SRC}/domain/shape/IShape_fwd.h
	${ILLUSIO_LIB_SRC}/domain/shape/IShape.h
	${ILLUSIO_LIB_SRC}/domain/shape/simple/ShapeImpl.h

	${ILLUSIO_LIB_SRC}/domain/shape/IShapes_fwd.h
	${ILLUSIO_LIB_SRC}/domain/shape/IShapes.h

	${ILLUSIO_LIB_SRC}/domain/shape/group/IShapeGroup_fwd.h
	${ILLUSIO_LIB_SRC}/domain/shape/group/IShapeGroup.h
	${ILLUSIO_LIB_SRC}/domain/shape/group/CShapeGroup/ShapeGroup.h
	${ILLUSIO_LIB_SRC}/domain/shape/group/CShapeGroup/ShapesDraft.h

	${ILLUSIO_LIB_SRC}/domain/shape/solid/IShapeSolid_fwd.h
	${ILLUSIO_LIB_SRC}/domain/shape/solid/IShapeSolid.h
	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/ShapeSolidImpl.h

	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/ellipse/Ellipse.h
	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/rectangle/Rectangle.h
	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/triangle/Triangle.h
		#SHAPE#
	#DOMAIN#

	#VIEW#
	${ILLUSIO_LIB_SRC}/view/canvas/ICanvas_fwd.h
	${ILLUSIO_LIB_SRC}/view/canvas/ICanvas.h
	#VIEW#
)

set(_illusio_lib_sources

	${ILLUSIO_LIB_SRC}/pch_illusio.cpp
	# Add new lib's sources here

	#DOMAIN#
		#COMMON#
	${ILLUSIO_LIB_SRC}/domain/common/Frame/Frame.cpp
	${ILLUSIO_LIB_SRC}/domain/common/point/Point.cpp
	${ILLUSIO_LIB_SRC}/domain/common/size/Size.cpp
	${ILLUSIO_LIB_SRC}/domain/common/style/CStyle/Style.cpp
	${ILLUSIO_LIB_SRC}/domain/common/style/CStyle/StyleComposite.cpp
		#COMMON#
		#SHAPE#
	${ILLUSIO_LIB_SRC}/domain/shape/group/CShapeGroup/ShapeGroup.cpp
	${ILLUSIO_LIB_SRC}/domain/shape/group/CShapeGroup/ShapesDraft.cpp

	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/ellipse/Ellipse.cpp
	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/rectangle/Rectangle.cpp
	${ILLUSIO_LIB_SRC}/domain/shape/solid/CShapeSolid/triangle/Triangle.cpp
		#SHAPE#
	#DOMAIN#
)


add_library(${ILLUSIO_LIB}
	${_illusio_lib_headers}
	${_illusio_lib_sources}
)

target_link_libraries(
	${ILLUSIO_LIB}
PUBLIC
	${EXTERNALS_ILLUSIO_LIB}

	${Boost_LIBRARIES}

	${FASTSIGNALS_LIB_NAME}
)

target_include_directories(
	${ILLUSIO_LIB}
PUBLIC
	${ILLUSIO_LIB_SRC}
	${Boost_INCLUDE_DIRS}
	${fastsignals_SOURCE_DIR}
)

## Illusio's lib ##

## Illusio application ##

set(ILLUSIO_APP illusio_app)

add_executable(${ILLUSIO_APP}
	pch.h

	pch.cpp
	main.cpp
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

## Illusio application ##

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
