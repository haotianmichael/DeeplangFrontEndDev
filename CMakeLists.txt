cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
project(Deeplang)


option(DEEPLANG_ANTLR4_GEN "Use Antlr4 generating parser codes" OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
if(UNIX)
    set(CMAKE_CXX_FLAGS "-pthread")
endif(UNIX)



if(DEEPLANG_ANTLR4_GEN) 
    #    MESSAGE(STATUS "source dir is :${CMAKE_CURRENT_SOURCE_DIR}")
    execute_process(
        COMMAND sh test.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
endif()


function (deeplang_executable)

    set(option "")    
    set(oneValueArgs "NAME")
    set(multiValueArgs "SOURCES; INCLUDE; LIBS")

    cmake_parse_arguments(ELF "${option}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(ELF_INCLUDE
        PRIVATE
        gen/src/parsing
        src/
        third-party/
        
        # backend
        ${ELF_INCLUDE}
    )

    set(ELF_SOURCES
          

        ${ELF_SOURCES}
    )
    set(ELF_LIBS
        
        
        ${ELF_LIBS}
    )



    add_executable(${ELF_NAME} ${ELF_SOURCES})
    #target_include_directories(${ELF_NAME} ${ELF_INCLUDE})
    #target_link_libraries(${ELF_NAME} ${ELF_LIBS})
endfunction()

deeplang_executable(
    NAME dp
    SOURCES src/main.cpp 
)
