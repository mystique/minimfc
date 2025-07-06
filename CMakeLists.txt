cmake_minimum_required(VERSION 3.20)

# Project configuration
project(minimfc VERSION 1.0.0.0 LANGUAGES CXX RC)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows only
if(NOT WIN32)
    message(FATAL_ERROR "This project is designed for Windows only")
endif()

# MFC configuration (2 = Shared MFC)
set(CMAKE_MFC_FLAG 2)

if(MSVC)
  add_compile_options(/utf-8)
endif()

# Unicode support
add_definitions(-DUNICODE -D_UNICODE)

# Create executable
add_executable(${PROJECT_NAME} WIN32
    main.cpp
    main_app.cpp
    main_app.h
    main_frame.cpp
    main_frame.h
    resource.h
    main.rc
    app.ico
)

# Target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "minimfc"
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE shell32)

# Preprocessor definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    WIN32
    _WINDOWS
    _AFXDLL
)
