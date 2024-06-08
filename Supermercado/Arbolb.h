#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <iostream>
#include <string>
using namespace std;

class Producto {
public:
    int Id;
    string nombre;
    float precio;
    string categoria;
    int stock;
    string FechaCaducidad;

    // Constructor predeterminado
    Producto() : Id(0), precio(0.0), stock(0) {}

    // Constructor con parámetros
    Producto(int id, const string& nombre, float precio, const string& categoria, int stock, const string& fechaCaducidad)
        : Id(id), nombre(nombre), precio(precio), categoria(categoria), stock(stock), FechaCaducidad(fechaCaducidad) {}

    Producto(const string& nombre, float precio)
        : nombre(nombre), precio(precio), Id(0), categoria(""), stock(0), FechaCaducidad("") {}

    bool operator<(const Producto& other) const {
        return this->precio < other.precio;
    }

    bool operator==(const Producto& other) const {
        return this->Id == other.Id;
    }

    bool operator>(const Producto& other) const {
        return this->precio > other.precio;
    }

    friend ostream& operator<<(ostream& os, const Producto& producto) {
        os << "Producto(Id: " << producto.Id << ", Nombre: " << producto.nombre << ", Precio: " << producto.precio << ", Categoria: " << producto.categoria << ", Stock: " << producto.stock << ", Fecha de Caducidad: " << producto.FechaCaducidad << ")";
        return os;
    }
};

#endif
