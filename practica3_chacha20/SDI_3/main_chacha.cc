/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica 2023-2024
  *
  * @file chacha20.cc
  * @author Ángela Izquierdo Padrón  alu0101480442@ull.edu.es
  * @date 2 de febrero 2024
  * @brief Este programa realiza el cifrado del chacha20 
  * @bug No hay bugs en el programa
  * @see 
  * https://datatracker.ietf.org/doc/html/rfc8439
  * https://medium.com/@parejaemi/algoritmo-de-cifrado-chacha20-119a6d7c19a7
  */

#include <iostream>
#include <cctype>

#include "chacha20.cc"


/**
 * @brief Cambia el formato de la clave que no tenga espacios ni comillas
 * @param entrada: Clave o nonce o contador
 * @return Devuelve la clave en un formato que no tenga espacios ni comillas
*/
std::string Cambiar_sin_espacio_comillas(const std::string& entrada) {
  std::string cadena_corta = "";
  for (char caracter : entrada) {
    if (caracter != ':') {
      cadena_corta += caracter;
    }
  }
  for (size_t i = 0; i < cadena_corta.length(); i++) {
    if (cadena_corta[i] == ' ') {
      cadena_corta.erase(i, 1);
    }
  }
  return cadena_corta;
}

/**
 * @brief Cambia el formato de la clave
 * @param entrada: Clave
 * @return Devuelve la clave en el formato correcto
*/
std::string Cambiar_formato(const std::string& entrada) {
  
  std::string cadena_corta = Cambiar_sin_espacio_comillas(entrada);
  std:: string cadena_salida;

  //  guardar los espacios en un vector
  std::vector<std::pair<char, char>> vector_almacen;
  const int vector[4] = {0, 2, 4, 6};

  for (size_t i = 0; i < cadena_corta.length(); i += 8) {
    std::string valor = cadena_corta.substr(i, 8);
    //std::cout << valor << " " << std::endl;

    for (int j = 0; j < 4; j++) {
   
      //std::cout << "valor: " << valor.substr(vector[j], 2) << " ";
      char primer_caracter = valor[vector[j]];
      char segundo_caracter = valor[vector[j] + 1];
      vector_almacen.push_back(std::make_pair(primer_caracter, segundo_caracter));
      //std::cout << "\tprimer caracter: " << primer_caracter << " " << segundo_caracter;
    }
    //std::cout << std::endl;
     std::reverse(vector_almacen.begin(), vector_almacen.end());
    for (int j = 0; j < 4; j++) {
      cadena_salida += vector_almacen[j].first;
      
      cadena_salida += vector_almacen[j].second;
      //std::cout << "cadena salida: " << cadena_salida << std::endl;
    }
  }
  //std::cout << "cadena salida: " << cadena_salida << std::endl;
  return cadena_salida;
}

/**
 * @brief Comprueba si la clave es válida
 * @param entrada: Clave
 * @param tamayo: Tamaño de la clave
 * @return Devuelve true si la clave es válida
*/
bool EsClaveValida(const std::string& entrada, size_t tamayo) {
  if (entrada.length() != tamayo) {
    return false;
  }
  for (size_t i = 0; i < entrada.length(); i++) {
    if (!((entrada[i] >= '0' && entrada[i] <= '9') || (entrada[i] >= 'a' && entrada[i] <= 'f'))) {
      return false;
    }
  }
  return true;
}



void LimpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
//    for (int i = 0; i < 50; ++i) {
        //std::cout << std::endl;
 //   }
}


int main() {
// 
  std::string clave_a_modi = "";
  std::string contador_a_modi = "";
  std::string nonce_a_modi = "";
  char respuesta;
  do {
    LimpiarPantalla();
    std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    std::cout << "                      IMPREMENTACIÓN DE GENERADOR CHACHA20                   " << std::endl;
    std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    std::cout << "Clave de 256 bits en forma de 8 palabras en hexadecimal: " << std::endl;
    std::getline(std::cin, clave_a_modi);
    std::string clave = Cambiar_sin_espacio_comillas(clave_a_modi);
    while (!EsClaveValida(Cambiar_sin_espacio_comillas(clave_a_modi), 64)) {
      std::cout << "Clave no válida. Introduzca una clave de 256 bits en forma de 8 palabras en hexadecimal: " << std::endl;
      std::getline(std::cin, clave_a_modi);
    }
    clave = Cambiar_formato(clave);
    std::cout << "Contador de 32 bits en forma de 1 palabra en hexadecimal: " << std::endl;
    std::cin >> contador_a_modi;
    std::string contador = Cambiar_sin_espacio_comillas(contador_a_modi);
    while (!EsClaveValida(Cambiar_sin_espacio_comillas(contador_a_modi), 8)) {
      std::cout << "Contador no válida. Introduzca una clave de 32 bits en forma de 1 palabras en hexadecimal: " << std::endl;
      std::getline(std::cin, contador_a_modi);
    }
    contador= Cambiar_formato(contador_a_modi);

    std::cin.ignore();
    std::cout << "Nonce de 96 bits en forma de 3 palabras en hexadecimal: " << std::endl;
    std::getline(std::cin, nonce_a_modi);
    std::string nonce = Cambiar_sin_espacio_comillas(nonce_a_modi);
    while (!EsClaveValida(Cambiar_sin_espacio_comillas(nonce_a_modi), 24)) {
      std::cout << "Nonce no válida. Introduzca una clave de 96 bits en forma de 3 palabras en hexadecimal: " << std::endl;
      std::getline(std::cin, nonce);
    }

    nonce = Cambiar_formato(nonce_a_modi);

    try {
        ChaCha20 cifrador(clave, nonce, contador);
        cifrador.Cifrar();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Salir con código de error
    }

    
    std::cout << std::endl << "Desea salir del. (S)i - (N)o" << std::endl;
    std::cin >> respuesta;
  } while (respuesta == 'n' || respuesta == 'N');

  return 0; // Éxito
}
