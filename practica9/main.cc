#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "rsa.h"

int calcularTamanoBloque(unsigned long n, int base=26) {
    // Calcular la parte entera de log_b(n)
    int tamanoBloque = static_cast<int>(log(n) / log(base));
    return tamanoBloque;
}


int main() {
    std::string mensaje;
   // Solicitar el texto del mensaje al usuario
    std::cout << "Ingrese texto original: ";
    std::getline(std::cin, mensaje);


    unsigned long p, q, d;
  
    // Solicitar los parámetros p, q y d al usuario
    std::cout << "Ingrese el valor de p: ";
    std::cin >> p;
    std::cout << "Ingrese el valor de q: ";
    std::cin >> q;
    std::cout << "Ingrese el valor de d: ";
    std::cin >> d;
    try {
        RSA rsa(p, q, d);
        unsigned long j = calcularTamanoBloque(rsa.getn());
     
        std::cout << "Tamaño del bloque: " << j << std::endl;
        std::vector<unsigned long> bloques_codificados = rsa.codificarTexto(mensaje, j);
        std::cout << "Bloques codificados:" << std::endl;
        for (unsigned long bloque : bloques_codificados) {
            std::cout << bloque << " ";
        }
        std::cout << std::endl;
        std::vector<unsigned long> texto_cifrado = rsa.cifrarTexto(bloques_codificados);

        std::cout << "Texto cifrado:" << std::endl;
        for (unsigned long bloque : texto_cifrado) {
            std::cout << bloque << " ";
        }
        std::cout << std::endl;
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    //int base = 26; // Ejemplo de base (alfabeto sin la letra Ñ)
    


    return 0;
}
