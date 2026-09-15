# Render de funciones
Un render en 3D hecho en C++ y SFML. El proyecto nace de el amor por las matemáticas y las ganas de entender como funcionan los gráficos en 3D por debajo.
El cómo se mueve la cámara, como transforman los puntos, como hacer las proyecciones... 
SFML es una librería de trabajo 2D, así que la implementación el pipeline de transformación y las proyecciones viene desde cero.

En el estado actual, permite visualizar un cubo 3D, con rotaciones y cámara orbital interactiva. También permite el uso del 2D para representar funciones
matemáticas básicas. Se puede alternar entre ambos modos desde el teclado.

## Que hace
- **Modo 3D**: Muestra un cubo que rota sobre si mismo, el cual es orbitable con WASD. Se está trabajando en un zoom
- **Modo 2D**: Representa la funcion 'y = - x ^ 2' sobre una cuadrícula.
- **Cámara Orbital**: Control total por teclado
- **Pipeline completo**: modelo -> vista -> proyección, implementado desde cero.

## Como compilar
Requiere CMake, y un compilador C++17. SFML se descarga desde el CMakeList con el FetchContent(puede ser necesario compilar dos veces)
BASH:
git clone https://github.com/mraxeliuss-cloud/Function-render.git
cd Function-renderer
cmake -B build
cmake --build build --config Release

El ejecutable se genera en build/Release/Function_renderer.exe

## Controles
- M -> Alterna modo
- W/S -> Orbita verticalmente
- A/D -> Orbita Horizontalmente

## Estructura de archivos
Sigue una estructura MVC.
el código está en el /src
src/
|
|---modelo/ modelo de datos y lógica de negocio
|
|---vista / nada aún

## Que queda por hacer (TBD)
· Superficies paramétricas (En desarrollo)
· Proyección en perspectiva (En desarrrollo)
· Iluminación básica
· Input de funciones

## Que he aprendido con el proyecto
· Como funcionan por dentro las transformaciones 3D
· Implementar álgebra lineal desde 0 en C++
· Manejo básico de CMake y SFML
· Depuración de bugs, sobretodo comportamientos indefinidos
