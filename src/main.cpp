#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

#include "modelo\Vector3.h"
#include "modelo\Matriz4x4.h"
#include "modelo\Camara.h"
#include "vista\Vista.h"
#include "Utilidades.h"

void funcion2d(std::vector<sf::Drawable *> &dibujables, int menorValorPantalla, int alto_Pantalla)
{
    auto calculada = Matematicas::calcularFuncion(menorValorPantalla);
    sf::VertexArray funcion(sf::PrimitiveType::LineStrip, calculada.size());

    for (size_t i = 0; i < calculada.size(); ++i)
    {
        float enY = (alto_Pantalla / 2) - calculada[i].second;
        funcion[i].position = sf::Vector2f(calculada[i].first, enY);
        funcion[i].color = sf::Color::Green; // Asigna color
    }
    dibujables.clear();
    dibujables.push_back(&funcion);
}

void superficie3d(std::vector<sf::Drawable *> &dibujables, Camara &camara, Controlador::configuracionPantalla &pantalla)
{
    Matematicas::funcionParametrica valores;
    Matematicas::proyeccionOrtografica proyeccion;
    static std::vector<Vector3> superficie;
    superficie.reserve(valores.xPuntos * valores.yPuntos);

    Matriz4x4 vista = Matriz4x4::lookAt(camara);

    superficie = Matematicas::calcularSuperficie(valores);
    auto proyectar = Matriz4x4::crearOrtografica(proyeccion);

    if(!proyectar.has_value()){
        proyectar = Matriz4x4();
    }
    auto matrizProyeccion = *proyectar;

    static sf::VertexArray funcion;
    funcion.clear();
    funcion.setPrimitiveType(sf::PrimitiveType::TriangleStrip);

    int filas = valores.xPuntos;
    int columnas = valores.yPuntos;
    int franjas = filas - 1;

    int verticesPorFranja = columnas * 2;
    int totalVertices = verticesPorFranja * franjas + 2 * (franjas - 1);
    funcion.resize(totalVertices);

    auto emitir = [&](int indice, int i, int j)
    {
        int idxPunto = i * columnas + j;
        const Vector3 &punto = superficie[idxPunto];
        auto ndc = matrizProyeccion * (vista * punto);
        float x_pantalla = (ndc.get_x() + 1.0f) * (pantalla.ancho_Pantalla / 2.0f);
        float y_pantalla = (ndc.get_y() + 1.0f) * (pantalla.alto_Pantalla / 2.0f);

        float z = punto.get_z();
        unsigned char intensidad = static_cast<unsigned char>((z + 1.0f) * 0.5f * 255.0f);

        funcion[indice].position = sf::Vector2f(x_pantalla, y_pantalla);
        funcion[indice].color = sf::Color(intensidad, 0, 255 - intensidad);
    };

    int indice = 0;
    for (int i = 0; i < franjas; i++)
    {
        if (i > 0)
        {
            emitir(indice, i, columnas - 1);
            ++indice;
            emitir(indice, i, 0);
            ++indice;
        }

        for (int j = 0; j < columnas; j++)
        {
            emitir(indice, i, j);
            ++indice;
            emitir(indice, i + 1, j);
            ++indice;
        }
    }

    dibujables.clear();
    dibujables.push_back(&funcion);
}
int main()
{
    // Configuración de ventana
    Controlador::configuracionPantalla pantalla;
    std::cout << "ancho: " << pantalla.ancho_Pantalla << ", alto: " << pantalla.alto_Pantalla << std::endl;
    int espacio_Entre_Casillas = 10;
    float menorValorPantalla = std::min(pantalla.ancho_Pantalla, pantalla.alto_Pantalla);

    sf::RenderWindow window(sf::VideoMode(pantalla.ancho_Pantalla, pantalla.alto_Pantalla), "Render de funciones");

    Vista vista(pantalla.ancho_Pantalla, pantalla.alto_Pantalla, window);

    window.setFramerateLimit(60);

    sf::Event evento;
    sf::Clock reloj;

    Camara camara;
    camara.anguloH = 0.0f;
    camara.anguloV = 0.0f;
    camara.distancia = 5.0f;
    camara.target = {0.0f, 0.0f, 0.0f};
    camara.up = {0.0f, 1.0f, 0.0f};
    camara.velocidadMovimiento = 2.0f;
    camara.updateEye(); // Calcula eye = (0, 0, 5)

    // Vector de elementos a dibujar
    std::vector<sf::Drawable *> dibujables;
    // Just in case, no creo que haya que dibujar más de 10 funciones juntas.
    dibujables.reserve(10);

    while (window.isOpen())
    {
        // 1. Procesar eventos
        while (window.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                window.close();

            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::M)
                vista.invertirModo3d();
            if (!vista.getModo3d() && evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::E)
            {
                vista.cambioEjes();
            }
        }

        // 2. Delta time
        float dt = reloj.restart().asSeconds();
        camara.update(dt);
        // PIPELINE 2D
        // funcion2d(dibujables, menorValorPantalla, pantalla.alto_Pantalla);

        // PIPELINE 3D
        superficie3d(dibujables, camara, pantalla);

        vista.mostrar(dibujables);
    }

    return 0;
}
