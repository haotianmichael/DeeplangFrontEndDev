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

    cmake_parse_arguments(EXE "${option}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(EXE_INCLUDES

        
        
        )

    set(EXE_SOURCE
        
        
        )

    set(EXE_LIBS
        
        
        )

    add_executable()
    target_include_directories()
    target_link_libraries()
endfunction()

deeplang_executable(
    NAME dp
    SOURCES src/main.cpp 
)




#### testing cmake function and args
function (test) 

    set(option "ADULT")
    set(oneValueArgs "NAME") 
    set(multiValueArgs "SCORE") 

    cmake_parse_arguments(STUDENT "${option}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    MESSAGE(STATUS "name is ${STUDENT_NAME}")
    MESSAGE(STATUS "and he is ${STUDENT_ADULT}")
    MESSAGE(STATUS "his SCore is ${STUDENT_SCORE}")

endfunction()

# test(ADULT NAME michael SCORE 123 456 234)
# test(SCORE 123 456)
