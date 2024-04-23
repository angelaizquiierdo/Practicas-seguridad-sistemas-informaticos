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
    std::string mensaje = "MANDA DINEROS";
   // Solicitar el texto del mensaje al usuario
    // std::cout << "Ingrese texto original: ";
    // std::getline(std::cin, mensaje);


    unsigned long pa, qa, ea;
  
    // // Solicitar los parámetros p, q y d al usuario
    // std::cout << "Ingrese el valor de pa: ";
    // std::cin >> pa;
    // std::cout << "Ingrese el valor de qa: ";
    // std::cin >> qa;
    // std::cout << "Ingrese el valor de e: ";
    // std::cin >> ea;
    pa = 421;
    qa = 7;
    ea = 1619;
    try {
        RSA rsa(pa, qa, ea);
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


        unsigned long na, ea;
  
    // // Solicitar los parámetros p, q y d al usuario
    // std::cout << "Ingrese el valor de na: ";
    // std::cin >> na;
    // std::cout << "Ingrese el valor de ea: ";
    // std::cin >> ea;
    na = 39;
    ea = 7;

        RSA rsa2(na, ea);
        std::cout << "Texto descifrado:" << std::endl;
        std::vector<unsigned long> texto_descifrado;
        for (unsigned long bloque : texto_cifrado) {
            unsigned long descifrado = rsa.DescifrarRSA(bloque);
            texto_descifrado.push_back(descifrado);
        }

        for (unsigned long bloque : texto_descifrado) {
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
