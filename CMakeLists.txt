cmake_minimum_required(VERSION 3.15)
project(Function_renderer)

# Estándar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flag para generar ensamblador (opcional)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /FA")

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
)

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

# También necesita el directorio src para incluir Utilidades.h
target_include_directories(benchmark_matriz PRIVATE src)

# Enlazar SFML (por si el benchmark usa gráficos, aunque no es necesario, no está de más)
target_link_libraries(benchmark_matriz PRIVATE sfml-graphics sfml-window sfml-system)