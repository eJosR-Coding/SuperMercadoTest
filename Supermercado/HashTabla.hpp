#pragma once
#ifndef HASHTABLA_HPP
#define HASHTABLA_HPP

#include <iostream>
#include <vector>
#include "HashEntidad.hpp"
using namespace std;

class HashTabla {
private:
    vector<HashEntidad*> tabla;
    int numElementos;
    int TABLE_SIZE;

    int hashFunction(const string& key) const {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % TABLE_SIZE;
        }
        return hash;
    }

public:
    HashTabla(int TABLE_SIZE = 128) : TABLE_SIZE(TABLE_SIZE), numElementos(0) {
        tabla.resize(TABLE_SIZE, nullptr);
    }

    ~HashTabla() {
        for (auto& entry : tabla) {
            if (entry != nullptr) {
                delete entry;
            }
        }
    }

    void insertar(const string& key, const Producto& value) {
        if (numElementos == TABLE_SIZE) return;

        int index = hashFunction(key);
        while (tabla[index] != nullptr) {
            index = (index + 1) % TABLE_SIZE;
        }

        tabla[index] = new HashEntidad(key, value);
        numElementos++;
    }

    int size() const {
        return TABLE_SIZE;
    }

    int sizeActual() const {
        return numElementos;
    }

    const Producto* buscar(const std::string& key) const {
        int index = hashFunction(key);
        int startIndex = index;
        while (tabla[index] != nullptr) {
            if (tabla[index]->getKey() == key) {
                return &tabla[index]->getValue();
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) break;
        }
        return nullptr;
    }

    void eliminar(const std::string& key) {
        int index = hashFunction(key);
        int startIndex = index;
        while (tabla[index] != nullptr) {
            if (tabla[index]->getKey() == key) {
                delete tabla[index];
                tabla[index] = nullptr;
                numElementos--;
                reorganizar(index);
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) break;
        }
    }

private:
    void reorganizar(int vaciado) {
        int index = (vaciado + 1) % TABLE_SIZE;
        while (tabla[index] != nullptr) {
            HashEntidad* entidadMover = tabla[index];
            tabla[index] = nullptr;
            numElementos--;
            insertar(entidadMover->getKey(), entidadMover->getValue());
            delete entidadMover;
            index = (index + 1) % TABLE_SIZE;
        }
    }
};

#endif // HASHTABLA_HPP
