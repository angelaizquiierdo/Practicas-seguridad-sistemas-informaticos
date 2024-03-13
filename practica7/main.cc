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

std::vector<uint8_t> stringToUint8Array(const std::string& str) {
    // Eliminar espacios de la cadena
    std::string str_no_spaces;
    for (char c : str) {
        if (!std::isspace(c)) {
            str_no_spaces += c;
        }
    }

    // Verificar que la longitud de la cadena sea par
    if (str_no_spaces.size() % 2 != 0) {
        throw std::invalid_argument("La longitud de la cadena debe ser par");
    }

    // Convertir la cadena sin espacios en un vector de uint8_t
    std::vector<uint8_t> key_vector;
    for (size_t i = 0; i < str_no_spaces.size(); i += 2) {
        std::string byteString = str_no_spaces.substr(i, 2);
        key_vector.push_back(std::stoi(byteString, nullptr, 16));
    }
    return key_vector;
}

/*
  * Programa principal.
*/
int main() {
  std::string clave_string =  "00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";
  
  std::string Bloque2_texto = "00 11 22 33 44 55 66 77 88 99 AA BB CC DD EE FF 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";
  std::string IV_string = "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";
  // Si es necesario, pedir al usuario que introduzca la llave y el texto

  
  // std::cout << "Introduce la llave (32, 48 o 64 caracteres): ";
  // std:cin >> clave_string; 
  // std::cout << "Introduce bloque texto (32 caracteres): ";
  // std:cin>> Bloque1_texto;
  // std::cout << "Introduce bloque texto (32 caracteres): ";
  // std:cin>> Bloque2_texto;
  // std::cout << "Introduce el IV (32 caracteres): ";
  // std:cin>> IV_string;
  
  // Convertir la llave y el texto a un vector de uint8_t
  std::vector<uint8_t> key_vector = stringToUint8Array(clave_string);

  std::vector<uint8_t> bloque2_vector = stringToUint8Array(Bloque2_texto);
  std::vector<uint8_t> IV_vector = stringToUint8Array(IV_string);

  if (key_vector.size() != 16 && clave_string.size() != 24 && clave_string.size() != 32 && clave_string.size() != 64) {
    std::cout << "La longitud de la llave debe ser de 32, 48 o 64 caracteres" << std::endl;
    return 1;
  }

  std::cout << "tamaño de texto:" << bloque2_vector.size() << std::endl;

  uint8_t llave_aux[key_vector.size()];  
  std::cout << "llave:";
  for (size_t i = 0; i < key_vector.size(); i++) {
    llave_aux[i] = key_vector[i];
    std::cout << std::hex << (int)llave_aux[i] << " ";
  }
  std::cout << std::endl;

  uint8_t bloque2[bloque2_vector.size()];
  for (size_t i = 0; i < bloque2_vector.size(); i++) {
    bloque2[i] = bloque2_vector[i];
  }

  uint8_t IV[IV_vector.size()];
  for (size_t i = 0; i < IV_vector.size(); i++) {
    IV[i] = IV_vector[i];
  }
 
  // Crear una instancia de AES
  AES aes(AES::AES_128, llave_aux, IV);

  aes.set_lengith_plaintext(bloque2_vector.size());
  uint8_t salida[bloque2_vector.size()];
  aes.EncryptCBC(bloque2, IV,salida);
  
    //int tamayo = sizeof(texto);
    // Realizar el cifrado
    //aes.Encrypt(texto, tamayo , encriptar_aes);

    // Mostrar el resultado del cifrado
  std::cout << "Bloque 1: " << sizeof(salida) << std::endl;
  for (size_t i = 0; i < sizeof(salida); ++i) {
    std::cout << std::hex << (int)salida[i];
  }
  std::cout << std::endl;



  return 0;
}