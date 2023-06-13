# CMakeList.txt: ModernGlut에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ModernGlut")

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (ModernGlut "test/OpenGL.cpp" "test/OpenGL.h" "src/_internal.ixx" "src/Callbacks.ixx" "src/Types.ixx" "src/WindowDefinitions.ixx" "src/Commons.ixx")

set_target_properties(ModernGlut PROPERTIES LINKER_LANGUAGE CXX)
set_property(TARGET ModernGlut PROPERTY CXX_STANDARD 23)
set_property(TARGET ModernGlut PROPERTY CXX_EXTENSIONS ON)
set_property(TARGET ModernGlut PROPERTY CXX_SCAN_FOR_MODULES ON)

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
