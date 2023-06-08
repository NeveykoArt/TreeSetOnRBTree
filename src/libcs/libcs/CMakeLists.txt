set(target_name libcs)

# file(GLOB_RECURSE LIBCS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE LIBCS_HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(${target_name} INTERFACE ${LIBCS_SOURCE_FILES})

target_include_directories(${target_name} INTERFACE ${PROJECT_SOURCE_DIR}/src/libcs)
