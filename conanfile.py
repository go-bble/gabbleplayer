import os
from conan import ConanFile


class CompressorRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    
    def requirements(self):
        # self.requires("qt/6.6.1")
        # self.requires("ffmpeg/6.1",override = True)
        self.requires("opencv/4.8.1")
        # self.requires("freetype/2.13.2",override = True)
        # self.requires("ffmpeg/4.4.4")
    # def build_requirements(self):
    #     self.tool_requires("cmake/3.22.6")
    
    #conan install . --output-folder=build --build=missing
    #cmake --build D:/workspace/CMake/conan/build --config Release --target gabbleplayer
    #D:\workspace\CMake\conan\build\Release\gabbleplayer.exe
    #"C:\Program Files\CMake\bin\cmake.EXE" -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_TOOLCHAIN_FILE=D:/workspace/CMake/conan/build/conan_toolchain.cmake -SD:/workspace/CMake/conan -BD:/workspace/CMake/conan/build -G "Visual Studio 16 2019" -T v142 -A x64
    