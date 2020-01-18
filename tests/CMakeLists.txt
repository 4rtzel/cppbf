add_executable(
    cppbf_test
    ${CMAKE_CURRENT_SOURCE_DIR}/simple_test.cpp
)

target_link_libraries(cppbf_test cppbf)

add_test(SimpleTest cppbf_test)
