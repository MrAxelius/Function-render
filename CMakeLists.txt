cmake_minimum_required(VERSION 3.20)
project(Function_renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(FUNCTION_RENDERER_WERROR "Treat compiler warnings as errors" OFF)

# ---------------------------------------------------------------------------
# Avisos del compilador, como objetivo INTERFACE.
#
# Esto sustituye al add_compile_options() que habia aqui, que aplicaba
# -Wall -Wextra a TODO lo creado en este directorio y por debajo: tambien a
# SFML y a FunctionParser, que llegan por FetchContent como subdirectorios.
# Con -Werror eso seria fallar el build por avisos de codigo que no es nuestro.
#
# -Wconversion queda fuera a proposito: son 20 avisos en el codigo de matrices,
# casi todos conversiones float/double deliberadas de geometria.
# ---------------------------------------------------------------------------
add_library(render_avisos INTERFACE)

if(MSVC)
    target_compile_options(render_avisos INTERFACE /utf-8 /W4)
    if(FUNCTION_RENDERER_WERROR)
        target_compile_options(render_avisos INTERFACE /WX)
    endif()
else()
    target_compile_options(render_avisos INTERFACE -Wall -Wextra)
    if(FUNCTION_RENDERER_WERROR)
        target_compile_options(render_avisos INTERFACE -Werror)
    endif()
endif()

# ---- DEPENDENCIAS ----
include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    SYSTEM
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
        GIT_TAG v1.0.1
    )
endif()

# ---------------------------------------------------------------------------
# Todo estatico, y no es opcional.
#
# SFML declara option(BUILD_SHARED_LIBS ... ON) y se procesa antes que
# FunctionParser, asi que el option() de FunctionParser no llega a aplicarse:
# la variable de cache ya existe. FunctionParser acabaria como DLL sin
# simbolos exportados, MSVC no generaria la .lib de importacion, y el
# enlazado del ejecutable falla con LNK1181.
#
# Estatico ademas evita tener que dejar los DLL al lado del .exe.
# ---------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# SFML: solo lo que usamos
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

# FunctionParser no necesita compilar sus tests ni sus ejemplos aqui
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
    render_avisos
)

# ---- BENCHMARK ----
add_executable(benchmark_matriz
    tests/benchmark_matriz.cpp
    ${MODELO_SOURCES}
)
target_include_directories(benchmark_matriz PRIVATE src)
target_link_libraries(benchmark_matriz PRIVATE render_avisos)