include(${PROJECT_SOURCE_DIR}/CMakeCommon)

file(GLOB QEDIS_MODUIE_SRC 
        "*.cpp"
        "*.cc"
        "*.h")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
add_library(qedismodule SHARED ${QEDIS_MODUIE_SRC})

target_include_directories(qedismodule PRIVATE
    ${PROJECT_SOURCE_DIR}/QedisCore
    ${PROJECT_SOURCE_DIR}/QBase)

add_dependencies(qedismodule qediscore leveldb)
   
target_link_directories(qedismodule PRIVATE ${PROJECT_SOURCE_DIR}/leveldb)
target_link_libraries(qedismodule PRIVATE qbaselib qediscore leveldb)

set_target_properties(qedismodule PROPERTIES 
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)