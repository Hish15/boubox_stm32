cmake_minimum_required(VERSION 3.16)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32-cmake/cmake/stm32_gcc.cmake)


project(stm32-blinky C CXX ASM)
set(MAIN_SOURCE_FILE src/blinky.cpp)

stm32_fetch_cube(H7)

find_package(CMSIS COMPONENTS STM32H7_M7 REQUIRED)
find_package(HAL COMPONENTS STM32H7_M7 RCC GPIO CORTEX REQUIRED)


add_executable(${PROJECT_NAME} ${MAIN_SOURCE_FILE})
target_link_libraries(${PROJECT_NAME}
    HAL::STM32::H7::M7::RCC
    HAL::STM32::H7::M7::GPIO
    HAL::STM32::H7::M7::CORTEX
    #CMSIS::STM32::F407VG
    CMSIS::STM32::H743ZI::M7
    STM32::NoSys
)
target_include_directories(${PROJECT_NAME} PRIVATE inc)
stm32_print_size_of_target(${PROJECT_NAME})
stm32_generate_hex_file(${PROJECT_NAME})

add_custom_target(flash
    COMMAND STM32_Programmer_CLI.exe --connect port=SWD --write "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex" --go
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

