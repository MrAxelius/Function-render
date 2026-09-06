#ifndef MATRIZ4X4_H
#define MATRIZ4X4_H

#include "Utilidades.h"
#include "Camara.h"


#include <array>
#include <initializer_list>
#include <optional>

class Vector3;

class Matriz4x4{

    private:
    std::array<std::array<float, 4>, 4> matriz;
    
    public:
    //Constructor por defecto es la identidad
    Matriz4x4();
    //Requiere de 16 parámetros
    Matriz4x4(std::initializer_list<float> valores);
    //Por comodidad para el cálculo
    Matriz4x4(const std::array<float, 16>& valores);
    

    //Operadores de multiplicacion necesarios
    Matriz4x4 operator*(const Matriz4x4& multiplo) const;
    Vector3 operator*(const Vector3& multiplo) const;

    //Operadores matriciales
    static Matriz4x4 traslacion(float tx, float ty, float tz);
    static Matriz4x4 escalado(float sx, float sy, float sz);

    //Matrices de rotación
    static Matriz4x4 rotacion_x(float angulo);
    static Matriz4x4 rotacion_y(float angulo);
    static Matriz4x4 rotacion_z(float angulo);

    //Matrices de proyección / TBD, ahora mismo no son necesarias como implementación, dejo la firma 
    static Matriz4x4 ortrografica(float izquierda, float derecha, float abajo, float arriba, float cerca, float lejos);
    static Matriz4x4 perspectiva(float fov, float aspecto, float cerca, float lejos);

    //Método para la cámara
    static Matriz4x4 lookAt(const Camara& camara);

    static std::optional<Matriz4x4> crearOrtografica(const Matematicas::proyeccionOrtografica& proyeccion);


    // Helper
    // Solo necesario de forma temporal para el benchmarking, evitar que el compilador optimice más de lo que queremos
    float getElemento(int fila, int columna) const ;
    // Setter 
    void setElemento(int fila, int columna, float elemento) ;
};
#endif