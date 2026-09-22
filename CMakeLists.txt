cmake_minimum_required(VERSION 3.20)
project(Function_renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# ---- DEPENDENCIAS ----
include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(sfml)

# Ruta a FunctionParser. Ajusta si mueves las carpetas.
set(FUNCTIONPARSER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../FunctionParser"
    CACHE PATH "Ruta al repositorio de FunctionParser")
add_subdirectory(${FUNCTIONPARSER_DIR} ${CMAKE_BINARY_DIR}/FunctionParser)

# ---- FUENTES COMPARTIDAS ----
set(MODELO_SOURCES
    src/modelo/Vector3.cpp
    src/modelo/Vector4.cpp
    src/modelo/Matriz4x4.cpp
)

# ---- TARGET PRINCIPAL ----
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${MODELO_SOURCES}
    src/modelo/Camara.cpp
    src/vista/Vista.cpp
    src/controlador/input.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    FunctionParser::FunctionParser
)

# Copiar las DLLs de SFML junto al ejecutable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS)

# ---- BENCHMARK ----
add_executable(benchmark_matriz
    tests/benchmark_matriz.cpp
    ${MODELO_SOURCES}
)
target_include_directories(benchmark_matriz PRIVATE src)