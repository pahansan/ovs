add_library(my_lib
    files.cpp
    schedule.cpp
    strings.cpp
    task.cpp
    tournament_tree.cpp
)

target_include_directories(my_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
