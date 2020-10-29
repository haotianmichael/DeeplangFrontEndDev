cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(Deeplang)

option(DEEPLANG_ANTLR4_GEN "Use Antlr4 generating parser codes" ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
    set(CMAKE_CXX_FLAGS "-pthread")
endif(UNIX)


if(DEEPLANG_ANTLR4_GEN) 
    #    MESSAGE(STATUS "source dir is :${CMAKE_CURRENT_SOURCE_DIR}")
    execute_process(
        COMMAND sh build.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
endif()


function (deeplang_executable)

    set(option "")    
    set(oneValueArgs "NAME")
    set(multiValueArgs "SOURCES;INCLUDE;LIBS")

    cmake_parse_arguments(ELF "${option}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(ELF_INCLUDE
        PRIVATE
        #SOURCE
        src/include
        src/ast/lib

        #LIB
        lib/
        gen/lib/antlr
        lib/include
        third_party/
        ${WABT_SOURCE_DIR}
        ${WABT_BINARY_DIR}

        ${ELF_INCLUDE}
    )

    set(ELF_SOURCES

        gen/lib/antlr/DLLexer.cpp
        gen/lib/antlr/DLParser.cpp
        gen/lib/antlr/DLParserVisitor.cpp
        gen/lib/antlr/DLParserBaseVisitor.cpp

        src/ast/include/ast.h
        src/ast/include/type.h
        src/ast/include/parsing.h
        src/ast/parsing.cpp 
        src/include/error.h

        ${ELF_SOURCES}     
    )

    set(ELF_LIBS
        antlr4_static        
        wabt
        ${ELF_LIBS}
    )

    add_executable(${ELF_NAME} ${ELF_SOURCES})
    target_include_directories(${ELF_NAME} ${ELF_INCLUDE})
    target_link_libraries(${ELF_NAME} ${ELF_LIBS})
endfunction()


add_subdirectory(third_party/antlr_runtime)
add_subdirectory(third_party/wabt)


deeplang_executable(
    NAME dp
    SOURCES src/main.cpp 
)
