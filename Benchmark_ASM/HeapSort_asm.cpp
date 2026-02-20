#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

using namespace std;

// Funcion Heapify optimizada para x86 con SSE2
void heapify_x86_sse(int* arr, int n, int i) {
    __asm {
        mov esi, arr
        mov ebx, i

        loop_start :
        mov ecx, ebx
            shl ecx, 1
            inc ecx

            mov edx, ecx
            inc edx

            mov edi, ebx

            cmp ecx, n
            jge check_right

            movd xmm0, [esi + ecx * 4]
            movd xmm1, [esi + edi * 4]
            pcmpgtd xmm0, xmm1
            movd eax, xmm0
            test eax, eax
            jz check_right
            mov edi, ecx

            check_right :
        cmp edx, n
            jge perform_swap

            movd xmm0, [esi + edx * 4]
            movd xmm1, [esi + edi * 4]
            pcmpgtd xmm0, xmm1
            movd eax, xmm0
            test eax, eax
            jz perform_swap
            mov edi, edx

            perform_swap :
        cmp edi, ebx
            je end_asm

            mov eax, [esi + ebx * 4]
            mov edx, [esi + edi * 4]
            mov[esi + ebx * 4], edx
            mov[esi + edi * 4], eax

            mov ebx, edi
            jmp loop_start

            end_asm :
    }
}

void heapSort_asm(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_x86_sse(arr.data(), n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify_x86_sse(arr.data(), i, 0);
    }
}

int main() {

    const int TAMANIO = 20000000;

    vector<int> datos(TAMANIO);
    srand(0);

    for (int i = 0; i < TAMANIO; i++)
        datos[i] = rand();

    auto inicio = chrono::high_resolution_clock::now();
    heapSort_asm(datos);
    auto fin = chrono::high_resolution_clock::now();

    chrono::duration<double> duracion = fin - inicio;

    // IMPORTANTE: solo el numero
    cout << duracion.count();

    return 0;
}