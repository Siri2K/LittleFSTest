cmake_minimum_required(VERSION 3.10)  # Specify the minimum CMake version required
project(LittleFSExample)  # Replace with your project name

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)  # or 14, 17, etc., depending on your needs
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the source files for your project
set(SOURCES
    main.c
    
)

# Add LittleFS source files if they are included directly
set(LITTLEFS_SOURCES
    littlefs/lfs.c
    littlefs/lfs_util.c
    bd/lfs_filebd.c
)

# Include directories for LittleFS and your own code
include_directories(
    bd
    littlefs
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${LITTLEFS_SOURCES})

# Include directories for LittleFS and your own code
target_include_directories(${PROJECT_NAME} PRIVATE bd littlefs)
