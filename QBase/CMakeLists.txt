include(${PROJECT_SOURCE_DIR}/CMakeCommon)

file(GLOB_RECURSE QBASE_SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_library(qbaselib SHARED ${QBASE_SRC})

target_include_directories(qbaselib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(qbaselib PRIVATE pthread)

set_target_properties(qbaselib PROPERTIES 
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# add_executable(UnboundedBufferTest src/UnboundedBuffer.cpp)
# target_include_directories(UnboundedBufferTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)