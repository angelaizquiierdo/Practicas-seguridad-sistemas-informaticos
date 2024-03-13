/**
 * Universidad de La Laguna
 * Grado en Ingeniería Informática
 * Curso: 3º 
 * Asignatura: Seguridad en Sistemas Informáticos
 * @author Ángela Izquierdo Padrón
 * @file main.cc
 * @brief Programa principal para cifrar un bloque de texto con AES.
*/

#include <iostream>
#include <vector>
#include <string>


#include "aes.h"


/**
 * @brief Convierte una cadena de caracteres en un vector de uint8_t.
 * @param[in] str Cadena de caracteres.
 * @return Vector de uint8_t.
 */
std::vector<u_int8_t> stringToUint8Array(const std::string& str) {
  if (str.size() % 2 != 0) {
    throw std::invalid_argument("La longitud de la cadena debe ser par");
  }

  std::vector<uint8_t> key_vector;
  for (size_t i = 0; i < str.size(); i += 2) {
    std::string byteString = str.substr(i, 2);
    key_vector.push_back(std::stoi(byteString, nullptr, 16));
  }
  return key_vector; 

}

/*
  * Programa principal.
*/
int main() {
  std::string llave_string = "000102030405060708090A0B0C0D0E0F";
  std::string texto_string = "00112233445566778899aabbccddeeff";
  
  // Si es necesario, pedir al usuario que introduzca la llave y el texto

  /*
  std::cout << "Introduce la llave (32, 48 o 64 caracteres): ";
  std:cin>> llave; 
  std::cout << "Introduce el texto (32 caracteres): ";
  std:cin>> texto;
  */

  if (llave_string.size() != 32 && llave_string.size() != 48 && llave_string.size() != 64 && llave_string.size() != 128) {
    std::cout << "La longitud de la llave debe ser de 32, 48 o 64 caracteres" << std::endl;
    return 1;
  }

  if (texto_string.size() != 32) {
    std::cout << "La longitud del texto debe ser de 32 caracteres" << std::endl;
    return 1;
  }

  // Convertir la llave y el texto a un vector de uint8_t
  std::vector<uint8_t> key_vector = stringToUint8Array(llave_string);
  std::vector<uint8_t> texto_vector = stringToUint8Array(texto_string);
 
  uint8_t llave_aux[key_vector.size()];  
  for (size_t i = 0; i < key_vector.size(); i++) {
    llave_aux[i] = key_vector[i];
    std::cout << std::hex << (int)llave_aux[i] << " ";
  }

  uint8_t texto[texto_vector.size()];
  for (size_t i = 0; i < texto_vector.size(); i++) {
    texto[i] = texto_vector[i];
  }
  
 
  // Crear una instancia de AES
  AES aes(AES::AES_128, llave_aux);

    
  // Buffer para almacenar el resultado del cifrado
  uint8_t encriptar_aes[16];

    int tamayo = sizeof(texto);
    // Realizar el cifrado
    aes.Encrypt(texto, tamayo , encriptar_aes);

    // Mostrar el resultado del cifrado
    std::cout << "Bloque de Texto Cifrado: ";
    for (size_t i = 0; i < sizeof(encriptar_aes); ++i) {
        std::cout << std::hex << (int)encriptar_aes[i];
    }
    std::cout << std::endl;

    return 0;
}