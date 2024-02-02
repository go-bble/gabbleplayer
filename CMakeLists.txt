cmake_minimum_required(VERSION 3.15)

# 定义一个函数，根据输入的库名输出相关信息
function(print_library_info LIB_NAME)
    if(${LIB_NAME}_FOUND)
        message("++${LIB_NAME}_FOUND++")
        message("${LIB_NAME}_INCLUDE_DIRS: ${${LIB_NAME}_INCLUDE_DIRS}")
        message("${LIB_NAME}_LIBRARY_DIRS: ${${LIB_NAME}_LIBRARY_DIRS}")
        message("${LIB_NAME}_LIBRARIES: ${${LIB_NAME}_LIBRARIES}")
        message("${LIB_NAME}_DLLS: ${${LIB_NAME}_DLLS}")
        message("${LIB_NAME}_VERSION: ${${LIB_NAME}_VERSION}")
    else()
        message("--${LIB_NAME}_NOT_FOUND--")
    endif()
endfunction()

project(gabbleplayer)

set(CMAKE_POLICY_DEFAULT_CMP0091 "NEW")

set(PROJECT_BUILD_DIR "${PROJECT_SOURCE_DIR}/build")
set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(BINARY_DIR ${PROJECT_BUILD_DIR})

#设置工具链
# set(CMAKE_TOOLCHAIN_FILE "${PROJECT_BUILD_DIR}/conan_toolchain.cmake")
set(VCPKG_ROOT "G:/workspace-G/vcpkg/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
message("--${CMAKE_TOOLCHAIN_FILE}--1111111111111111111")


#-0- 设置 Qt 动态库和静态库的目录
set(PROJ_Qt6_MSVC_x64_PATH "G:/Qt/6.7.0/msvc2019_64")
message(STATUS "PROJ_Qt6_MSVC_x64_PATH------ 	${PROJ_Qt6_MSVC_x64_PATH}")
set(PROJ_Qt_PATH ${PROJ_Qt6_MSVC_x64_PATH})  		#* 引入动态的Qt库


# 设置 Qt 的 cmake 目录让系统能搜索到
set(PROJ_Qt_CMAKE_PATH ${PROJ_Qt_PATH}/lib/cmake/Qt6)
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PROJ_Qt_CMAKE_PATH}) #关键代码
#qt_standard_project_setup()

#* 寻找 Qt 包
find_package(Qt6  COMPONENTS Core 
							Gui 
							Widgets 
							REQUIRED PATHS ${PROJ_Qt_CMAKE_PATH})
	# 后续添加 Qt 模块! 勿删此注释

print_library_info(Qt6)
#-0- 


find_package(OpenCV REQUIRED)
print_library_info(OpenCV)

find_package(FFMPEG REQUIRED)
print_library_info(FFMPEG)

set(PROJECT_SOURCES
        src/main.cpp
)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

include_directories(${OpenCV_INCLUDE_DIRS}
                    ${FFMPEG_INCLUDE_DIRS}

)

target_link_directories(${PROJECT_NAME} PRIVATE 
                        ${FFMPEG_LIBRARY_DIRS}
                        )
target_link_libraries(${PROJECT_NAME} 
                        ${OpenCV_LIBRARIES}
                        ${FFMPEG_LIBRARIES}
                        # Qt6::Core 
                        # Qt6::Gui
                        # Qt6::Widgets 
)
# find_package(Qt6)
# find_package(OpenCV)
# target_link_libraries(... qt::qt opencv::opencv)

#—1—测试ffmpeg/{4.4.4},{6.1},{6.0.1}均只能获取库目录，无法获取头文件目录/VCPKG也有这个问题，暂时手动添加
# find_library(AVCODEC_LIBRARY avcodec)
# get_filename_component(AVCODEC_PARENT_DIR "${AVCODEC_LIBRARY}" DIRECTORY)
# get_filename_component(FFMPEG_INCLUDE_DIRS "${AVCODEC_PARENT_DIR}" DIRECTORY)
# set(FFMPEG_INCLUDE_DIRS "${FFMPEG_INCLUDE_DIRS}/include")
# message(ffmpeg_INCLUDE_DIRS:${FFMPEG_INCLUDE_DIRS})
#—1—

