cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 14)
#C:/opencv-bulid/CMakeFiles
#E:/taha/code/lib/opencv/build/include/opencv2
set(CMAKE_TOOLCHAIN_FILE "C:/opencv-bulid/CMakeFiles")
# set the project name
project(histeq)

# Set OpenCVConfig.cmake Search Directory
set( OpenCV_DIR )
if( NOT CMAKE_CL_64 )
    set( OpenCV_DIR "E:/taha/code/lib/opencv/build/include/opencv2")
else()
    set( OpenCV_DIR "E:/taha/code/lib/opencv/build/include/opencv2" )
endif()
#"C:/Program Files/vcpkg/vcpkg/installed/x86-windows/share/opencv"
#C:/Program Files/vcpkg/vcpkg/packages/opencv4_x86-windows/share/opencv4

find_package(OpenCV REQUIRED)

# Additional Include Directories
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Additional Library Directories
link_directories( ${OpenCV_LIB_DIR} )

# add the executable
add_executable(histeq histeq.cpp)

# Additional Dependencies
target_link_libraries(histeq ${OpenCV_LIBS})

message("${OpenCV_DIR}")
message("${OpenCV_INCLUDE_DIRS}")

#"E:/taha/code/lib/opencv/build/include/opencv2"