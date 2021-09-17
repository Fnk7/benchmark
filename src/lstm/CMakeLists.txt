add_library(lstm STATIC
    lstm.cpp
)

add_executable(
    lstm_base
    lstm_base.cpp
)

target_link_libraries(
    lstm_base
    lstm
    workload
)

add_executable(
    lstm_wave
    lstm_base.cpp
)

target_link_libraries(
    lstm_wave
    lstm
    workload
)
