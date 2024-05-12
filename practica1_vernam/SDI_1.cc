/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @file SDI_1.cc
  * @author Ángela Izquierdo Padrón  alu0101480442@ull.edu.es
  * @date 24 de enero 2024
  * @brief Este programa hace el cifrado de Vernam (modificación generador de pseudorandom )
  * Primero se pide un mensaje y luego una clave en binario sirve para cifrarlo.
  * @bug No hay bugs en el programa
  * @see https://stackoverflow.com/questions/867602/quickest-way-to-generate-random-bits
  */


#include <iostream>
#include <bitset>
#include <string>
#include <cstdlib> 
#include <ctime>   

// Función para convertir una cadena de texto a una cadena de bits
std::string Cinvertir_Cadena_Binario(const std::string& input) {
    std::string binaryString;
    for (char c : input) {
        binaryString += std::bitset<8>(c).to_string();
    }
    return binaryString;
}

// Función para convertir una cadena de bits a una cadena de texto
std::string Convertir_Binario_Cadena(const std::string& binaryInput) {
    std::string result;
    for (size_t i = 0; i < binaryInput.length(); i += 8) {
        std::bitset<8> byte(binaryInput.substr(i, 8));
        result += static_cast<char>(byte.to_ulong());
    }
    return result;
}

// Función para cifrar un mensaje usando el cifrado de Vernam
std::string CifradoVernam(const std::string& mensajeBinario, const std::string& claveBinaria) {
  if (mensajeBinario.length() != claveBinaria.length()) {
      std::cerr << "Error: La longitud del mensaje y la clave deben ser iguales." << std::endl;
      return "";
  }
  // cifrado = mensaje XOR clave
  std::string cifrado;
  for (size_t i = 0; i < mensajeBinario.length(); ++i) {
    char mensaje_bit = mensajeBinario[i];
    char clave_bit = claveBinaria[i];

    // Operación XOR entre el bit del mensaje y el bit de la clave
    char cifrado_bit = (mensaje_bit == clave_bit) ? '0' : '1';

    cifrado += cifrado_bit;
  }

  return cifrado;
}

std::string GeneradorClave(size_t tamayo) {
  std::srand(std::time(0));

  // Declarar un vector para almacenar los bits aleatorios
  std::string cadena_bit_random;
  int bitrandom;
  for (size_t i = 0; i < tamayo; i++) {
    // Generar un bit aleatorio (0 o 1) y convertirlo en cadena
      bitrandom = std::rand() % 2;
      cadena_bit_random += std::to_string(bitrandom);
    }
  return cadena_bit_random;
}

// funcion principal
int main() {
  std::string mensaje, clave;

  // Ingresar el mensaje y la clave
  std::cout << "Ingrese el mensaje: ";
  std::getline(std::cin, mensaje);
  // Convertir mensaje y clave a binario
  std::string mensajeBinario = Cinvertir_Cadena_Binario(mensaje);
  std::cout << "Mensaje Cifrado: " << mensajeBinario << std::endl;
  std::cout << "Longitud del mensaje binario: " << mensajeBinario.length() << std::endl << std::endl;
  //std::cout << "Ingrese la clave: ";
  clave = GeneradorClave(mensajeBinario.length());
  std::cout << "Generador de pseudoclave:" << clave << std::endl;
  //std::cin >> clave;

  std::cout << "Clave (en texto): " << Convertir_Binario_Cadena(clave) << std::endl;

  // Cifrar el mensaje
  std::string mensajeCifradoBinario = CifradoVernam(mensajeBinario, clave);

  // Mostrar el resultado
  std::cout << "Mensaje Cifrado en binario: " << mensajeCifradoBinario << std::endl;
  std::cout << "Menseje Cifrado (en texto): " << Convertir_Binario_Cadena(mensajeCifradoBinario) << std::endl;

  return 0;
}
