#ifndef VECTOR4_H
#define VECTOR4_H

#include <array>

class Vector3;

class Vector4
{

    private:

    float x;
    float y; 
    float z;
    float w = 1.f;

    public:

    Vector4(float x, float y, float z, float w);
    explicit Vector4(const Vector3& original);
    Vector4(const std::array<float, 4>& array);

    //Getters
    float get_x() const{ return this->x; }
    float get_y() const{ return this->y; }
    float get_z() const{ return this->z; }
    float get_w() const{ return this->w; }

    //setters
    void set_x(float numero) { this->x = numero; }
    void set_y(float numero) { this->y = numero; }
    void set_z(float numero) { this->z = numero; }
    void set_w(float numero) { this->w = numero; }



    Vector3 toVector3() const;

    //Necesarios como pasos intermedios
    float componentesEscaladas(float multiplo) const;
    
    Vector4 operator*(float multiplo);

    //Por comodidad operativa
    std::array<float,4> toArray() const;

};

#endif
