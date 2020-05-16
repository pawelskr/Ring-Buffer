cmake_minimum_required(VERSION 3.0)
set(This RingBufferTests)
set(ThisClass RingBufferClassTests)

set(Sources
    ${This}.cpp
    # ${ThisClass}.cpp 
)

add_executable(${This} ${Sources})
# add_executable(${ThisClass} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main  # Linking GoogleTest
    RingBuffer     # This is an output from root's CMakeLists.txt
)

# target_link_libraries(${ThisClass} PUBLIC
#     gtest_main  # Linking GoogleTest
#     RingBuffer     # This is an output from root's CMakeLists.txt
# )

add_test(
    NAME ${This}
    COMMAND ${This}
)