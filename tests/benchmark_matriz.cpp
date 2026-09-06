#include <chrono>
#include <iostream>

#include "../src/modelo/Matriz4x4.h"

int main()
{
    // Matrices de prueba (valores fijos no constantes en tiempo de compilación)
    Matriz4x4 A({
        1.2f, 0.3f, 2.1f, 0.7f,
        0.5f, 1.8f, 0.4f, 1.1f,
        2.3f, 0.6f, 1.5f, 0.2f,
        0.9f, 1.4f, 0.8f, 1.7f
    });
    Matriz4x4 B({
        1.2f, 0.3f, 2.1f, 0.7f,
        0.5f, 1.8f, 0.4f, 1.1f,
        2.3f, 0.6f, 1.5f, 0.2f,
        0.9f, 1.4f, 0.8f, 1.7f
    });

    constexpr int iteraciones = 10'000'000;
    volatile float acumulador = 0.0f;  // Volátil para evitar optimización

    // Calentar caché (100 iteraciones)
    for (int i = 0; i < 100; ++i) {
        Matriz4x4 C = A * B;
        acumulador += C.getElemento(0, 0);  // Usar solo un elemento
    }

    // Medición
    auto inicio = std::chrono::steady_clock::now();

    for (int i = 0; i < iteraciones; ++i) {
        Matriz4x4 C = A * B;
        acumulador += C.getElemento(0, 0);  // Forzar uso del resultado
    }

    auto fin = std::chrono::steady_clock::now();

    double tiempo = std::chrono::duration<double>(fin - inicio).count();

    std::cout << "Tiempo total: " << tiempo << " s\n";
    std::cout << "Tiempo por operación: " << (tiempo / iteraciones) * 1e9 << " ns\n";
    std::cout << "Acumulador (evita optimización): " << acumulador << "\n";

    return 0;
}