cmake_minimum_required(VERSION 3.0...3.13)
project(Top)

# Windows
if (WIN32)
    # OpenCV 4.9.0
    set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/third_party/opencv/build)

    # Header files
    include_directories(${OpenCV_DIR}/include)

    # Libraries
    #if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #    message(CMAKE_BUILD_TYPE=Debug)
    #    set(OpenCV_LIBS  ${OpenCV_DIR}/x64/vc16/lib/opencv_world490d.lib) # to be consistent with APPLE
    #    set(OpenCV_DYNAMIC_LIB ${OpenCV_DIR}/x64/vc16/bin/opencv_world490d.dll)
    #endif()
    
    #if (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_BUILD_TYPE Release)
        message(CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE})
        set(OpenCV_LIBS  ${OpenCV_DIR}/x64/vc16/lib/opencv_world490.lib) # to be consistent with APPLE
        set(OpenCV_DYNAMIC_LIB ${OpenCV_DIR}/x64/vc16/bin/opencv_world490.dll)
    #endif()

    # FFMPEG for videos
    set(FFMPEG_DYNAMIC_LIB ${OpenCV_DIR}/bin/opencv_videoio_ffmpeg490_64.dll)

# APPLE, UNIX
else()
    # (1) Install opencv
    
    # (1.1) For Mac OS, install brew first and then opencv using brew as below
    # $ brew update
    # $ brew install opencv

    # (1.2) For Linux, install opencv using apt as below
    # $ sudo apt install opencv

    # (2) Then, create a build directory, move to it, run cmake and make it
    # $ mkdir build
    # $ cd build
    # $ cmake ..
    # $ make

    find_package(OpenCV REQUIRED)
    include_directories(${OpenCV_INCLUDE_DIRS})

    message(OpenCV_DIR="${OpenCV_DIR}")
    message(OpenCV_INCLUDE_DIRS="${OpenCV_INCLUDE_DIRS}")
endif()

# Data
set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)

# Projects
add_subdirectory("${CMAKE_SOURCE_DIR}/project/01_hello_opencv")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/02_images")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/03_videos_and_cameras")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/04_drawing")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/05_user_interface")
add_subdirectory("${CMAKE_SOURCE_DIR}/project/71_template_1234567890_HW_01")
#add_subdirectory("${CMAKE_SOURCE_DIR}/project/81_homework_01")