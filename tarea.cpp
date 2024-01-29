#include <iostream>
#include <omp.h>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

#define N 1000
#define CHUNK 100
#define MOSTRAR 10

void imprimeArreglo(float *d);

int main() {
    std::cout << "Sumando Arreglos en Paralelo con elementos aleatorios!\n";
    float a[N], b[N], c[N];

    srand(static_cast<unsigned int>(time(0)));

    #pragma omp parallel for shared(a, b) schedule(static, CHUNK)
    for (int i = 0; i < N; i++) {
        a[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100.0; // Random numbers between 0 and 100
        b[i] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 100.0; // Random numbers between 0 and 100
    }

    #pragma omp parallel for shared(a, b, c) schedule(static, CHUNK)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "\nImprimiendo los primeros " << MOSTRAR << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "\nImprimiendo los primeros " << MOSTRAR << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
    std::cout << std::endl;

    return 0;
}

void imprimeArreglo(float *d) {
    for (int x = 0; x < MOSTRAR; x++) {
        std::cout << d[x] << " ";
    }
    std::cout << std::endl;
}
