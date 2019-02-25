cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall")

project(test_gl_wql)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
#    find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# 添加bx库
set(bx_dir ${CMAKE_CURRENT_SOURCE_DIR}/bx)
add_subdirectory(${bx_dir} bx)

# 添加bimg库
set(bimg_dir ${CMAKE_CURRENT_SOURCE_DIR}/bimg)
add_subdirectory(${bimg_dir} bimg)

# 添加bimg-decode库
set(bimg-decode_dir ${CMAKE_CURRENT_SOURCE_DIR}/bimg/src)
add_subdirectory(${bimg-decode_dir} bimg-decode)

# 添加dear-imgui库
set(dear-imgui_dir ${CMAKE_CURRENT_SOURCE_DIR}/bgfx/3rdparty/dear-imgui)
add_subdirectory(${dear-imgui_dir} dear-imgui)

# 添加ib-compress库
set(ib-compress_dir ${CMAKE_CURRENT_SOURCE_DIR}/bgfx/3rdparty/ib-compress)
add_subdirectory(${ib-compress_dir} ib-compress)

# 添加bgfx库
set(bgfx_dir ${CMAKE_CURRENT_SOURCE_DIR}/bgfx)
add_subdirectory(${bgfx_dir} bgfx)

# 添加examples-common库
set(examples-common_dir ${CMAKE_CURRENT_SOURCE_DIR}/bgfx/examples/common)
add_subdirectory(${examples-common_dir} common)




add_executable(test_gl_wql main.cpp ExampleFBO.cpp)

target_include_directories(test_gl_wql PRIVATE
        ${bx_dir}/include
        ${bimg_dir}/include
        ${bgfx_dir}/include
        ${bgfx_dir}/3rdparty
        ${examples-common_dir}
        ${GLEW_INCLUDE_DIRS}
        )

target_link_libraries(test_gl_wql
        ${GLEW_LIBRARIES}
        bgfx
        common
        dear-imgui
        -lGL
        -lGLU
        -lX11
        -lXxf86vm
        -lXrandr
        -pthread
        -lXi
        -lm
        -ldl
        Xinerama
        Xcursor
        -lglfw
        )