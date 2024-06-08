#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Arbolb.h"
#include "ArbolB.hpp"
#include "HashTabla.hpp"
#include "Sorting.hpp"
#include "archivos.hpp"

using namespace std;

void mostrarmenu() {
    /* Mostrar el menú de opciones */
    std::cout << "\n========================================\n";
    std::cout << "===            Menu productos          ===\n";
    std::cout << "========================================\n\n";
    std::cout << "1. Insertar 300 productos a hashtable\n";
    std::cout << "2. Insertar 300 productos a arbol binario\n";
    std::cout << "3. Buscar por ID\n";
    std::cout << "4. Ordenar por precio\n";
    std::cout << "5. Eliminar producto por ID\n";
    std::cout << "6. Verificar si el nodo mayor es múltiplo de 5\n";
    std::cout << "7. Guardar productos en archivo\n";
    std::cout << "8. Cargar productos desde archivo\n";
    std::cout << "9. Salir\n";
    std::cout << "========================================\n";
    std::cout << "Seleccione una opcion: ";
}

string generarNombreAleatorio() {
    /* Generar nombre aleatorio de producto */
    const vector<string> nombres = { "Leche", "Pan", "Queso", "Jamon", "Cereal", "Mantequilla", "Arroz", "Azucar", "Sal", "Aceite" };
    return nombres[rand() % nombres.size()];
}

string generarCategoriaAleatoria() {
    /* Generar categoría aleatoria de producto */
    const vector<string> categorias = { "Lacteos", "Panaderia", "Carnes", "Cereales", "Condimentos" };
    return categorias[rand() % categorias.size()];
}

string generarFechaCaducidadAleatoria() {
    /* Generar fecha de caducidad aleatoria */
    const vector<string> fechas = { "2024-01-01", "2024-02-01", "2024-03-01", "2024-04-01", "2024-05-01" };
    return fechas[rand() % fechas.size()];
}

Producto generarProductoAleatorio() {
    /* Generar producto aleatorio */
    static int id = 1;
    string nombre = generarNombreAleatorio();
    double precio = (rand() % 1000) / 10.0;
    string categoria = generarCategoriaAleatoria();
    int stock = rand() % 100;
    string fechaCaducidad = generarFechaCaducidadAleatoria();
    return Producto(id++, nombre, precio, categoria, stock, fechaCaducidad);
}

void generarDatosProductos(vector<Producto*>& productos, int n) {
    /* Generar datos de productos aleatorios */
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        productos.push_back(new Producto(generarProductoAleatorio()));
    }
}

bool compararPorPrecio(const Producto* a, const Producto* b) {
    /* Comparar productos por precio */
    return a->precio < b->precio;
}

vector<int> buscarTodosLosIndices(const vector<Producto*>& productos, const Producto& target) {
    /* Buscar todos los índices de un producto en el vector */
    vector<int> indices;
    for (size_t i = 0; i < productos.size(); ++i) {
        if (*productos[i] == target) {
            indices.push_back(i);
        }
    }
    return indices;
}

int main() {
    HashTabla hashTable(300);
    ArbolB<Producto> arbolBinario;
    vector<Producto*> productos;
    Sorting<Producto*> sorter;
    int opcion;

    // Generar datos de productos
    generarDatosProductos(productos, 300);

    do {
        mostrarmenu();
        cin >> opcion;
        switch (opcion) {
        case 1:
            system("cls");
            /* Inserción de productos en HashTable */
            for (const auto& producto : productos) {
                hashTable.insertar(to_string(producto->Id), *producto);
            }
            cout << "Se han insertado 300 productos en la tabla hash." << endl;
            break;
        case 2:
            system("cls");
            /* Inserción de productos en Árbol Binario */
            for (const auto& producto : productos) {
                arbolBinario.insertar(*producto);
            }
            cout << "Se han insertado 300 productos en el árbol binario." << endl;
            break;
        case 3: {
            system("cls");
            /* Búsqueda de productos por ID */
            int idBuscado;
            cout << "Ingrese el ID del producto que desea buscar: ";
            cin >> idBuscado;

            const Producto* productoHash = hashTable.buscar(to_string(idBuscado));
            const Producto* productoArbol = arbolBinario.buscar(Producto(idBuscado, "", 0, "", 0, ""));

            if (productoHash != nullptr) {
                cout << "Producto encontrado en la tabla hash: " << *productoHash << endl;
            }
            else {
                cout << "Producto no encontrado en la tabla hash." << endl;
            }

            if (productoArbol != nullptr) {
                cout << "Producto encontrado en el árbol binario: " << *productoArbol << endl;
            }
            else {
                cout << "Producto no encontrado en el árbol binario." << endl;
            }
            break;
        }
        case 4:
            system("cls");
            /* Ordenación de productos */
            int metodoOrdenamiento;
            cout << "Seleccione el método de ordenamiento:\n";
            cout << "1. QuickSort\n";
            cout << "2. MergeSort\n";
            cout << "3. HeapSort\n";
            cout << "Seleccione una opción: ";
            cin >> metodoOrdenamiento;

            switch (metodoOrdenamiento) {
            case 1:
                cout << "Ordenando con QuickSort..." << endl;
                sorter.quicksort(productos, compararPorPrecio);
                for (const auto& producto : productos) {
                    cout << *producto << endl;
                }
                break;
            case 2:
                cout << "Ordenando con MergeSort..." << endl;
                sorter.mergesort(productos, compararPorPrecio);
                for (const auto& producto : productos) {
                    cout << *producto << endl;
                }
                break;
            case 3:
                cout << "Ordenando con HeapSort..." << endl;
                sorter.heapsort(productos, compararPorPrecio);
                for (const auto& producto : productos) {
                    cout << *producto << endl;
                }
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
            }
            break;
        case 5: {
            system("cls");
            /* Eliminación de productos por ID */
            int idAEliminar;
            cout << "Ingrese el ID del producto que desea eliminar: ";
            cin >> idAEliminar;

            bool eliminadoArbol = arbolBinario.eliminar(Producto(idAEliminar, "", 0, "", 0, ""));
            const Producto* productoHash = hashTable.buscar(to_string(idAEliminar));
            if (productoHash != nullptr) {
                hashTable.eliminar(to_string(idAEliminar));
                cout << "Producto eliminado de la tabla hash." << endl;
            }
            else {
                cout << "Producto no encontrado en la tabla hash." << endl;
            }

            if (eliminadoArbol) {
                cout << "Producto eliminado del árbol binario." << endl;
            }
            else {
                cout << "Producto no encontrado en el árbol binario." << endl;
            }
            break;
        }
        case 6:
            system("cls");
            /* Verificar si el nodo mayor es múltiplo de 5 */
            arbolBinario.verificarMayorMultiploDe5();
            break;
        case 7:
            system("cls");
            /* Guardar productos en archivo */
            guardarProductosEnArchivo(productos);
            break;
        case 8:
            system("cls");
            /* Cargar productos desde archivo */
            cargarProductosDesdeArchivo(productos);
            break;
        case 9:
            system("cls");
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opción no válida.\n";
            break;
        }
    } while (opcion != 9);

    // Liberar memoria de los productos
    for (auto producto : productos) {
        delete producto;
    }

    return 0;
}
