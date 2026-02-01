/******************************************************************************
*********** Tarea 1. Programación de una solución paralela ********************
Nombre: Isaura Yutsil Flores Escamilla
Matrícula: A01796552
Fecha: 01 de febrero del 2026

Objetivo: Generar un código que permita realizar una suma paralela en OpenMP

*******************************************************************************/

#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

int main() {
    int n, num_hilos;
    char opcion;

    //  Configuración de hilos por parte del usuario
    cout << "¿Cuántos hilos deseas utilizar?: ";
    cin >> num_hilos;
    // Establecemos el número de hilos antes de entrar a la zona paralela
    omp_set_num_threads(num_hilos);

    //  Configuración de datos (permitimos al usuario determinar sí desea hacer la configuración manualmente)
    cout << "¿Deseas ingresar los datos manualmente? (Y/N): ";
    cin >> opcion;

    if (opcion == 'Y' || opcion == 'y') {
        cout << "¿Cuántos elementos tendrá el arreglo?: ";
        cin >> n;
    } else {
        n = 1000; 
        cout << "Generando arreglos aleatorios de " << n << " elementos..." << endl;
    }

    vector<float> arregloA(n), arregloB(n), arregloSuma(n);

    // Llenado de datos por parte del usuario (esto es secuencial)
    if (opcion == 'Y' || opcion == 'y') {
        for (int i = 0; i < n; i++) {
            cout << "Arreglo A [" << i << "]: "; cin >> arregloA[i];
            cout << "Arreglo B [" << i << "]: "; cin >> arregloB[i];
        }
    } else {
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            arregloA[i] = rand() % 100;
            arregloB[i] = rand() % 100;
        }
    }

    // Sección paralela y medición de tiempo
    double inicio = omp_get_wtime(); // Marca de tiempo inicial

    #pragma omp parallel for shared(arregloA, arregloB, arregloSuma)
    for (int i = 0; i < n; i++) {
        arregloSuma[i] = arregloA[i] + arregloB[i];
    }

    double fin = omp_get_wtime(); // Marca de tiempo final

    // Impresión de resultados
    cout << "\n--- Estadísticas ---" << endl;
    cout << "Hilos usados: " << num_hilos << endl;
    printf("Tiempo de ejecución: %.6f segundos\n", fin - inicio);

    cout << "\n--- Muestra de resultados (Primeros 5) ---" << endl;
    int limite = (n < 5) ? n : 5;
    for (int i = 0; i < limite; i++) {
        printf("%.2f + %.2f = %.2f\n", arregloA[i], arregloB[i], arregloSuma[i]);
    }

    return 0;
}