add_executable(${PROJECT_NAME}
  main.cpp
 "pch.h" "pch.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE app_external_deps)
include_directories(${PROJECT_NAME} PRIVATE "../external/glfw/include")
