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

# Ruta local a FunctionParser, para desarrollar los dos proyectos a la vez.
# Si no existe, se descarga desde GitHub (necesario para el CI).
set(FUNCTIONPARSER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../FunctionParser"
    CACHE PATH "Ruta local al repositorio de FunctionParser")

if(EXISTS "${FUNCTIONPARSER_DIR}/CMakeLists.txt")
    message(STATUS "FunctionParser: usando copia local en ${FUNCTIONPARSER_DIR}")
    FetchContent_Declare(FunctionParser SOURCE_DIR "${FUNCTIONPARSER_DIR}")
else()
    message(STATUS "FunctionParser: descargando desde GitHub")
    FetchContent_Declare(
        FunctionParser
        GIT_REPOSITORY https://github.com/MrAxelius/FunctionParser.git
        GIT_TAG main
    )
endif()

# FunctionParser no necesita compilar sus tests ni sus ejemplos aquí
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(sfml FunctionParser)

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
    src/vista/Transformador.cpp
    src/controlador/Input.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    FunctionParser::FunctionParser
)

# ---- BENCHMARK ----
add_executable(benchmark_matriz
    tests/benchmark_matriz.cpp
    ${MODELO_SOURCES}
)
target_include_directories(benchmark_matriz PRIVATE src)