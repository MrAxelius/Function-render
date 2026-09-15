cmake_minimum_required(VERSION 3.15)
project(Function_renderer)

# Estándar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Descarga automática de SFML
include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)

# ---- TARGET PRINCIPAL ----
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/modelo/Vector3.cpp
    src/modelo/Vector4.cpp
    src/modelo/Matriz4x4.cpp
    src/modelo/Camara.cpp
    src/vista/Vista.cpp
    src/controlador/input.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# Copiar las DLLs de SFML junto al ejecutable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)

# Incluir directorio src para cabeceras (Utilidades.h, etc.)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Enlazar módulos de SFML
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)

# ---- BENCHMARK ----
add_executable(benchmark_matriz
    tests/benchmark_matriz.cpp
    src/modelo/Vector3.cpp
    src/modelo/Vector4.cpp
    src/modelo/Matriz4x4.cpp
)
target_compile_options(benchmark_matriz PRIVATE /FA)

# También necesita el directorio src para incluir Utilidades.h
target_include_directories(benchmark_matriz PRIVATE src)