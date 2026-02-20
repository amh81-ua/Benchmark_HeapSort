#include <iostream>
#include <vector>
#include <algorithm> // Para std::swap
#include <chrono>    // Para medir el tiempo
#include <cstdlib>

using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Inicializa el mas grande como raiz

    // Formulas
    int left = 2 * i + 1;  // Hijo izquierdo = 2*i + 1
    int right = 2 * i + 2; // Hijo derecho = 2*i + 2

    // Si el hijo izquierdo es mas grande que la raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Si el hijo derecho es mas grande que el mas grande hasta ahora
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Si el mas grande no es la raiz
    if (largest != i) {
        swap(arr[i], arr[largest]); // Intercambiamos

        // Recursivamente "heapificamos" el subarbol afectado
        heapify(arr, n, largest);
    }
}

// Funcion principal de ordenacion
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Reorganiza el array
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extrae elementos
    for (int i = n - 1; i > 0; i--) {
        // Mueve la raiz actual al final
        swap(arr[0], arr[i]);

        // Llamar a heapify en el array reducido
        heapify(arr, i, 0);
    }
}

int main() {

    const int TAMANIO = 20000000;

    vector<int> datos(TAMANIO);
    srand(0);

    for (int i = 0; i < TAMANIO; i++) {
        datos[i] = rand();
    }

    auto inicio = chrono::high_resolution_clock::now();
    heapSort(datos);
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion = fin - inicio;

    // SOLO EL NUMERO PARA PYTHON
    cout << duracion.count();

    return 0;
}