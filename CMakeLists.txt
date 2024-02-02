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

#设置工具链
set(VCPKG_ROOT "G:/workspace-G/vcpkg/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")


find_package(OpenCV REQUIRED)
print_library_info(OpenCV)

find_package(FFMPEG REQUIRED)
print_library_info(FFMPEG)

#-0- 设置 Qt 动态库和静态库的目录
set(PROJ_Qt6_MSVC_x64_PATH "G:/Qt/6.7.0/msvc2019_64")
# message(STATUS "PROJ_Qt6_MSVC_x64_PATH------ 	${PROJ_Qt6_MSVC_x64_PATH}")


#* 寻找 Qt 包
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH ${PROJ_Qt6_MSVC_x64_PATH})
find_package(Qt6 REQUIRED 
                            COMPONENTS 
                            Widgets 
                            LinguistTools)
print_library_info(Qt6)

#-0- 
#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

set(TS_FILES "${FORMS_DIR}/gabbleplayer_zh_CN.ts")
file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
    "${TS_FILES}"
)

# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)
# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})


add_executable(${PROJECT_NAME} ${SOURCES})

# Add the target includes for MY_PROJECT 
target_include_directories(${PROJECT_NAME} PRIVATE ${FORMS_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_DIR})

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
                        Qt6::Widgets 
)
set(CMAKE_INSTALL_PREFIX "G:/workspace-G/Cpp/gabbleplayer/build/Release")
message("CMAKE_INSTALL_PREFIX---------++${CMAKE_INSTALL_PREFIX}")
install(FILES
				${PROJ_Qt6_MSVC_x64_PATH}/bin/Qt6Core.dll
				${PROJ_Qt6_MSVC_x64_PATH}/bin/Qt6Gui.dll
				${PROJ_Qt6_MSVC_x64_PATH}/bin/Qt6Widgets.dll
			  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
install(
	FILES ${PROJ_Qt6_MSVC_x64_PATH}/plugins/platforms/qwindows.dll 
	DESTINATION ${CMAKE_INSTALL_PREFIX}/platforms
)
install(
	FILES ${PROJ_Qt6_MSVC_x64_PATH}/plugins/styles/qwindowsvistastyle.dll 
	DESTINATION ${CMAKE_INSTALL_PREFIX}/styles
)
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY---------++${CMAKE_RUNTIME_OUTPUT_DIRECTORY}") 
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

