#pragma once
#ifndef __HASHENTIDAD_HPP__
#define __HASHENTIDAD_HPP__
using namespace std;

#include "Arbolb.h"
#include <string>

class HashEntidad {
private:
    string key;
    Producto value;

public:
    HashEntidad(const string& key, const Producto& value) : key(key), value(value) {}

    const string& getKey() const { return key; }
    const Producto& getValue() const { return value; }
};

#endif // !__HASHENTIDAD_HPP__

