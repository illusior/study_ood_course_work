## Illusio's lib ##

set(ILLUSIO_LIB_SRC
	illusio
	CACHE PATH "Illusio's library sources directory"
)

set(ILLUSIO_LIB illusio_lib)

set(_illusio_lib_headers

	${ILLUSIO_LIB_SRC}/pch_illusio.h
	# Add new lib's headers here

	#CANVAS#
	${ILLUSIO_LIB_SRC}/canvas/ICanvas_fwd.h
	${ILLUSIO_LIB_SRC}/canvas/ICanvas.h

	${ILLUSIO_LIB_SRC}/canvas/CCanvas/imgui/CanvasImGui.h
	#CANVAS#

	#COMMON#
	${ILLUSIO_LIB_SRC}/common/signals/signal.hpp
	${ILLUSIO_LIB_SRC}/common/uuid/Uuid.h
	#COMMON#

	#DOMAIN#
		#DOMAIN_EVENT#
	${ILLUSIO_LIB_SRC}/domain/object/positionable/event/DomainPositionableModelEvent.h

	${ILLUSIO_LIB_SRC}/domain/object/positionable/event/DomainPositionableModelEventTypes.h
		#DOMAIN_EVENT#

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
#	${ILLUSIO_LIB_SRC}/domain/common/style/CStyle/StyleComposite.h
		#COMMON#

		#OBJECT#
	${ILLUSIO_LIB_SRC}/domain/object/IObject_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/IObject.h
	${ILLUSIO_LIB_SRC}/domain/object/ObjectImpl.hpp

			#POSITIONABLE#
	${ILLUSIO_LIB_SRC}/domain/object/positionable/IPositionable_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/IPositionable.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/PositionableImpl.hpp

	${ILLUSIO_LIB_SRC}/domain/object/positionable/IPositionables_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/IPositionables.h

	${ILLUSIO_LIB_SRC}/domain/object/positionable/group/IPositionableGroup_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/group/IPositionableGroup.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/group/CPositionableGroup/PositionableGroup.hpp

				#SHAPE#
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/ShapeTypes.h

	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/IShape_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/IShape.h

	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/simple/ShapeImpl.hpp

	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/IShapeSolid_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/IShapeSolid.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/ShapeSolidImpl.hpp

	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/ellipse/IEllipse.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/ellipse/IEllipse_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/ellipse/CEllipse/Ellipse.h

	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/rectangle/IRectangle.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/rectangle/IRectangle_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/rectangle/CRectangle/Rectangle.h

	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/triangle/ITriangle.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/triangle/ITriangle_fwd.h
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/triangle/CTriangle/Triangle.h
				#SHAPE#
			#POSITIONABLE#
		#OBJECT#
	#DOMAIN#
)

set(_illusio_lib_sources

	${ILLUSIO_LIB_SRC}/pch_illusio.cpp
	# Add new lib's sources here

	#CANVAS#
	${ILLUSIO_LIB_SRC}/canvas/CCanvas/imgui/CanvasImGui.cpp
	#CANVAS#

	#COMMON#
	${ILLUSIO_LIB_SRC}/common/uuid/Uuid.cpp
	#COMMON#

	#DOMAIN#
		#COMMON#
	${ILLUSIO_LIB_SRC}/domain/common/frame/Frame.cpp
	${ILLUSIO_LIB_SRC}/domain/common/point/Point.cpp
	${ILLUSIO_LIB_SRC}/domain/common/size/Size.cpp
	${ILLUSIO_LIB_SRC}/domain/common/style/CStyle/Style.cpp
		#COMMON#

		#OBJECT#
			#POSITIONABLE#
				#SHAPE#
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/ellipse/CEllipse/Ellipse.cpp
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/rectangle/CRectangle/Rectangle.cpp
	${ILLUSIO_LIB_SRC}/domain/object/positionable/shape/solid/CShapeSolid/triangle/CTriangle/Triangle.cpp
				#SHAPE#
			#POSITIONABLE#
		#OBJECT#
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

set(ILLUSIO_APP_SRC
	app
	CACHE PATH "Illusio's library sources directory"
)

set(_illusio_app_headers

	pch.h

	#APP#

	${ILLUSIO_APP_SRC}/Defenitions.h

	${ILLUSIO_APP_SRC}/Application.h

		#PRESENTER#
	${ILLUSIO_APP_SRC}/presenter/IPositionablesDraftPresenter_fwd.h
	${ILLUSIO_APP_SRC}/presenter/IPositionablesDraftPresenter.h

	${ILLUSIO_APP_SRC}/presenter/draft/DraftPresenter.h
		#PRESENTER#

		#EDIT#
	${ILLUSIO_APP_SRC}/edit/IUndoableEdit_fwd.h
	${ILLUSIO_APP_SRC}/edit/IUndoableEdit.h

	${ILLUSIO_APP_SRC}/edit/CEdit/AbstractUndoableEdit.h

	${ILLUSIO_APP_SRC}/edit/CEdit/compound/IUndoableCompoundEdit_fwd.h
	${ILLUSIO_APP_SRC}/edit/CEdit/compound/IUndoableCompoundEdit.h

	${ILLUSIO_APP_SRC}/edit/CEdit/compound/CUndoableCompoundEdit/CompoundEdit.h

	${ILLUSIO_APP_SRC}/edit/manager/UndoManager.h
		#EDIT#

		#WINDOW#
	${ILLUSIO_APP_SRC}/window/Layout.h

	${ILLUSIO_APP_SRC}/window/IWindow_fwd.h
	${ILLUSIO_APP_SRC}/window/IWindow.h

	${ILLUSIO_APP_SRC}/window/manager/IWindowManager_fwd.h
	${ILLUSIO_APP_SRC}/window/manager/IWindowManager.h

	${ILLUSIO_APP_SRC}/window/manager/CWindowManager/imgui/WindowManagerImGui.h

	${ILLUSIO_APP_SRC}/window/CWindow/BaseWindow.h

	${ILLUSIO_APP_SRC}/window/CWindow/imgui/WindowImGui.h
	${ILLUSIO_APP_SRC}/window/CWindow/imgui/backends/ImGuiBackends.h

	${ILLUSIO_APP_SRC}/window/CWindow/main/imgui/WMainImGui.h

	${ILLUSIO_APP_SRC}/window/CWindow/draft_editor/imgui/WDraftEditorImGui.h

			#WINDOW_EVENT#
	${ILLUSIO_APP_SRC}/window/event/WindowEvent.h
	${ILLUSIO_APP_SRC}/window/event/WindowEventTypes.h
			#WINDOW_EVENT#
		#WINDOW#

	#APP#
)

set(_illusio_app_sources

	pch.cpp
	main.cpp

	#APP#

	${ILLUSIO_APP_SRC}/Application.cpp

		#PRESENTER#
	${ILLUSIO_APP_SRC}/presenter/draft/DraftPresenter.cpp
		#PRESENTER#

		#EDIT#
	${ILLUSIO_APP_SRC}/edit/CEdit/AbstractUndoableEdit.cpp

	${ILLUSIO_APP_SRC}/edit/CEdit/compound/CUndoableCompoundEdit/CompoundEdit.cpp

	${ILLUSIO_APP_SRC}/edit/manager/UndoManager.cpp
		#EDIT#

		#WINDOW#
	${ILLUSIO_APP_SRC}/window/Layout.cpp

	${ILLUSIO_APP_SRC}/window/manager/CWindowManager/imgui/WindowManagerImGui.cpp

	${ILLUSIO_APP_SRC}/window/CWindow/BaseWindow.cpp

	${ILLUSIO_APP_SRC}/window/CWindow/imgui/WindowImGui.cpp
	${ILLUSIO_APP_SRC}/window/CWindow/imgui/backends/ImGuiBackends.cpp

	${ILLUSIO_APP_SRC}/window/CWindow/main/imgui/WMainImGui.cpp

	${ILLUSIO_APP_SRC}/window/CWindow/draft_editor/imgui/WDraftEditorImGui.cpp
		#WINDOW#
	#APP#

)

add_executable(${ILLUSIO_APP}
	${_illusio_app_headers}
	${_illusio_app_sources}
)

target_link_libraries(
	${ILLUSIO_APP}
PUBLIC
	${ILLUSIO_LIB}
)

target_include_directories(
	${ILLUSIO_APP}
PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
	${ILLUSIO_LIB_SRC}
)

set_target_properties(
	${ILLUSIO_APP}
PROPERTIES
	VS_USER_PROPS "${FASTSIGNALS_VS_USER_PROPS_PATH}"
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

	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Header Files"
		FILES ${_illusio_app_headers}
	)
	source_group(
		TREE ${CMAKE_CURRENT_SOURCE_DIR}
		PREFIX "Source Files"
		FILES ${_illusio_app_sources}
	)
endif()

## MSVC ##
