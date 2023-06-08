set(target_name Tests)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    test_treeset.cpp
)

target_link_libraries(
  ${target_name}
  PRIVATE
    libcs
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(${target_name})
