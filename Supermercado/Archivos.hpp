#pragma once
#ifndef ARCHIVOS_HPP
#define ARCHIVOS_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include "Arbolb.h"

#define nombre_archivo "productos.csv"

void guardarProductosEnArchivo(const std::vector<Producto*>& productos) {
    std::ofstream archOUT;
    archOUT.open(nombre_archivo, std::ios::out); // Apertura

    if (!archOUT.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo !!!" << std::endl;
        return;
    }

    // Escribimos el encabezado
    archOUT << "Id|Nombre|Precio|Categoria|Stock|FechaCaducidad\n";

    // Escribimos los datos de cada producto
    for (const auto& producto : productos) {
        archOUT << producto->Id << "|"
            << producto->nombre << "|"
            << producto->precio << "|"
            << producto->categoria << "|"
            << producto->stock << "|"
            << producto->FechaCaducidad << "\n";
    }

    // Cerramos el archivo
    archOUT.close();
    std::cout << "Datos guardados en el archivo " << nombre_archivo << " exitosamente." << std::endl;
}

void cargarProductosDesdeArchivo(std::vector<Producto*>& productos) {
    std::ifstream archIN;
    archIN.open(nombre_archivo, std::ios::in); // Apertura

    if (!archIN.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo !!!" << std::endl;
        return;
    }

    std::string linea;
    char delimitador = '|';

    // Leemos la primera línea (encabezado)
    std::getline(archIN, linea);

    // Leemos todas las líneas
    while (std::getline(archIN, linea)) {
        std::stringstream stream(linea); // Convertir la cadena a un stream

        std::string id, nombre, precio, categoria, stock, fechaCaducidad;
        std::getline(stream, id, delimitador);
        std::getline(stream, nombre, delimitador);
        std::getline(stream, precio, delimitador);
        std::getline(stream, categoria, delimitador);
        std::getline(stream, stock, delimitador);
        std::getline(stream, fechaCaducidad, delimitador);

        // Crear un nuevo objeto Producto y añadirlo al vector
        Producto* nuevoProducto = new Producto(std::stoi(id), nombre, std::stof(precio), categoria, std::stoi(stock), fechaCaducidad);
        productos.push_back(nuevoProducto);
    }

    // Cerramos el archivo
    archIN.close();
    std::cout << "Datos cargados desde el archivo " << nombre_archivo << " exitosamente." << std::endl;
}

#endif // ARCHIVOS_HPP
