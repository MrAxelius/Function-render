# Function-render

Un visor de funciones matemáticas en C++20 y SFML. Nace de las ganas de
entender cómo funcionan los gráficos 3D por debajo: cómo se mueve la cámara,
cómo se transforman los puntos, cómo se proyectan sobre la pantalla.

SFML es una biblioteca 2D, así que el pipeline de transformación y las
proyecciones están implementados desde cero.

Las expresiones las analiza y evalúa
[FunctionParser](https://github.com/MrAxelius/FunctionParser), una biblioteca
propia desarrollada en paralelo a este proyecto.

## Qué hace

- **Modo 2D**: representa `y = f(x)` sobre unos ejes, con la curva partida en
  los puntos donde la función no tiene valor (divisiones por cero, logaritmos
  fuera de dominio).
- **Modo 3D**: muestra la superficie `sin(x) * cos(y)` con cámara orbital.
- **Cámara orbital**: control por teclado.
- **Pipeline completo**: modelo → vista → proyección, escrito a mano.

## Controles

| Tecla | Acción |
|---|---|
| `M` | alternar entre 2D y 3D |
| `E` | ciclar entre sin ejes, ejes y cuadrícula (solo en 2D) |
| `WASD` | orbitar la cámara (solo en 3D) |

## Cómo compilar

Requiere CMake 3.20 o superior y un compilador con soporte de C++20.
SFML y FunctionParser se descargan automáticamente con `FetchContent`.

```bash
git clone https://github.com/MrAxelius/Function-render.git
cd Function-render
cmake -B build -DBUILD_SHARED_LIBS=OFF
cmake --build build --config Release
```

El ejecutable queda en `build/` (o `build/Release/` con Visual Studio).

Si tienes [FunctionParser](https://github.com/MrAxelius/FunctionParser) clonado
como carpeta hermana, se usa esa copia local en lugar de descargarla.

## Estado

En desarrollo. La expresión a representar está fija en el código; la entrada
por teclado y el zoom están pendientes.
