#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <FunctionParser/FunctionParser.h>

#include "modelo/Vector3.h"
#include "modelo/Matriz4x4.h"
#include "modelo/Camara.h"
#include "vista/Vista.h"
#include "Utilidades.h"
#include "controlador/Input.h"
#include "controlador/Entrada.h"


void superficie3d(Vista& vista, Camara &camara)
{
    Matematicas::funcionParametrica valores;
    Matematicas::proyeccionOrtografica proyeccion;
    std::vector<Vector3> superficie;
    superficie.reserve(valores.xPuntos * valores.yPuntos);

    Matriz4x4 matrizVista = Matriz4x4::lookAt(camara);

    superficie = Matematicas::calcularSuperficie(valores);
    auto proyectar = Matriz4x4::crearOrtografica(proyeccion);

    if (!proyectar.has_value())
    {
        proyectar = Matriz4x4();
    }
    auto matrizProyeccion = *proyectar;

    sf::VertexArray funcion;
    funcion.clear();
    funcion.setPrimitiveType(sf::PrimitiveType::TriangleStrip);

    int filas = valores.xPuntos;
    int columnas = valores.yPuntos;
    int franjas = filas - 1;

    int verticesPorFranja = columnas * 2;
    int totalVertices = verticesPorFranja * franjas + 2 * (franjas - 1);
    funcion.resize(totalVertices);

    // función Lambda
    auto emitir = [&](int indice, int i, int j)
    {
        int idxPunto = i * columnas + j;
        const Vector3 &punto = superficie[idxPunto];
        auto ndc = matrizProyeccion * (matrizVista * punto);
        float x_pantalla = (ndc.get_x() + 1.0f) * (vista.getAnchoPantalla() / 2.0f);
        float y_pantalla = (ndc.get_y() + 1.0f) * (vista.getAltoPantalla() / 2.0f);

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
    vista.setSuperficie(funcion);
}
int main()
{
    // Configuración de ventana
    Controlador::configuracionPantalla pantalla;
    Controlador::rango rango{-2, 2}; 
    int espacio_Entre_Casillas = 10;
    float menorValorPantalla = std::min(pantalla.anchoPantalla, pantalla.altoPantalla);

    sf::RenderWindow window(sf::VideoMode(pantalla.anchoPantalla, pantalla.altoPantalla), "Render de funciones");


    Vista vista(rango, window);

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

    FunctionParser::Expression expresion(" x * x");
    FunctionParser::Rango rangoFuncion{-2, 2, 99};
    auto resultado = expresion.evaluateMesh(rangoFuncion);

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

        Entrada entrada = leerEntrada();
        camara.update(dt, entrada);
        if (!vista.getModo3d())
        {
            // PIPELINE 2D
            vista.construirFuncion(resultado);
        }
        else
        {
            // PIPELINE 3D
            superficie3d(vista, camara);
        }

        vista.mostrar();
    }

    return 0;
}
