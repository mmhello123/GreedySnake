cmake_minimum_required(VERSION 3.10)

# 设置策略 CMP0087 为新行为（支持 generator expressions）
if(POLICY CMP0087)
    cmake_policy(SET CMP0087 NEW)
endif()

project(GREEDY_SNAKE)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
# 设置 C++ 标准必须使用
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置 C++ 标准扩展必须关闭
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

# 安装 exe 到 bin/
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# 在安装阶段插入一段 CMake 脚本代码
install(CODE [[
file(GET_RUNTIME_DEPENDENCIES
    RESOLVED_DEPENDENCIES_VAR RESOLVED_DEPS
    UNRESOLVED_DEPENDENCIES_VAR UNRESOLVED_DEPS
    LIBRARIES $<TARGET_FILE:GREEDY_SNAKE>
    DIRECTORIES 
        $<TARGET_FILE_DIR:GREEDY_SNAKE>
        "D:/MinGW-w64/mingw64-v15.1.0/bin"
        "C:/Program Files (x86)/Windows Kits/10/Windows Performance Toolkit"
    # PRE_INCLUDE_REGEXES $<TARGET_FILE_DIR:GREEDY_SNAKE>
    PRE_EXCLUDE_REGEXES "system32"
    # POST_INCLUDE_REGEXES $<TARGET_FILE_DIR:GREEDY_SNAKE>
    POST_EXCLUDE_REGEXES "system32"
)

foreach(DEP_LIB ${RESOLVED_DEPS})
    file(INSTALL ${DEP_LIB} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endforeach()

# 打印未解析的依赖
# if(UNRESOLVED_DEPS)
#     message(WARNING "以下依赖项未能解析:")
#     foreach(UNRESOLVED ${UNRESOLVED_DEPS})
#         message(WARNING "未解析: ${UNRESOLVED}")
#     endforeach()
# endif()
]])