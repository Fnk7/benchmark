add_library(database STATIC
    database.cpp
)

target_link_libraries(
    database
    workload
)

add_executable(
    q1.1
    q1.1.cpp
)

target_link_libraries(
    q1.1
    database
)
