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
#include <string>
#include <cctype>

//Es una funcion que elimina los espacios en blanco además de convertir las letras en mayúsculas
std::string ConvertirMayuscula(std::string mensaje) {
  for (size_t i = 0; i < mensaje.length(); i++) {
    if (mensaje[i] != ' ' ) {
      if (mensaje[i] >= 'a' && mensaje[i] <= 'z') {
        mensaje[i] = mensaje[i] - 32;
      } else {
        mensaje[i] = mensaje[i];
      }
    } else {
      mensaje.erase(i, 1);  // Eliminar el espacio en blanco
            i--;  // Ajustar el índice después de eliminar el espacio en blanco
    } 
  }
  return mensaje;
}

// Utilizando el cifrado de César para cifrar y descifrar dependiendo de lo que se quiera hacer 
// descifrar = true, cifrar = false
char CifradoCesar(char letra, int clave, bool descifrar) {
    char letra_cifrada;
    // comprueba si la letra es mayúscula
    if (letra >= 'A' && letra <= 'Z') {
      if(!descifrar) {
        letra_cifrada = (letra - 'A' + clave) % 26 + 'A'; // Cifrado
      } else {
        letra_cifrada = (letra - 'A' - clave + 26) % 26 + 'A'; // Descifrado
      }
      // letra es minúscula o otro carácter se mantiene igual
    } else {
        letra_cifrada = letra;
    }
    return letra_cifrada;
}


// Funcion de cifrado de Vigenere
std::string CifradoVigenere(const std::string& mensaje,  std::string& clave, bool descifrado, bool autoclave) {
  std::string resultado;
  int longitudClave = clave.length();
  std::string clave_modificada=clave;
  // i es el índice del mensaje, j es el índice de la clave
  for (size_t i = 0,j=0; i < mensaje.length(); ++i) {
    // Verifica si el carácter actual es alfabético
    if (isalpha(mensaje[i])) {
      // Obtiene la letra de la clave correspondiente.
      char letraClave;
      if(autoclave) {
        letraClave = clave_modificada[i];
      } else {
        letraClave = clave[j%longitudClave];
      }
      // Aplica el cifrado de César a la letra actual y la agrega al resultado
      char letraCifrada = CifradoCesar(mensaje[i], letraClave - 'A', descifrado);
    
      resultado += letraCifrada;
      if(autoclave) {
        if(clave_modificada.length() < mensaje.length()) {
          clave_modificada += letraCifrada;
          //std::cout <<  "letra cifrada:" << letraCifrada << "\tclave:" <<clave_modificada << std::endl;
        }
      }
      clave = clave_modificada;
      // Incrementa el índice de la clave
      j++;
    } else {
      // Si el carácter no es alfabético, se mantiene igual y se agrega al resultado
      resultado += mensaje[i];
    }
  }

  return resultado;
}

// Imprime el texto pasado por comando y lo transforma en bloques de tamaño clave y imprime el resultado del cifrado o desifrado dependiendo de lo que se quiera
void ImprimirEnBloques(const std::string& texto, std::string& clave, const std::string& texto2,bool descifrado) {
  size_t longitudBloque = clave.length();
  if(descifrado) {
    std::cout << "Texto cifrado: \t ";
  } else {
    std::cout << "Texto claro: \t";
  }
    for (size_t i = 0; i < texto.length(); i += longitudBloque) {
      std::cout  << texto.substr(i, longitudBloque) << " ";
    }
    std::cout << std::endl  <<"Clave: \t\t" ;
    
    for (size_t i = 0; i < (texto.length()/longitudBloque); i++) {
     std::cout << clave << " ";
    }
    std::cout << std::endl;

  if(descifrado) {
    std::cout << "Texto original: ";
  } else {
    std::cout << "Texto cifrado: \t";
  }
  for (size_t i = 0; i <= texto2.length(); i += longitudBloque) {
    std::cout << texto2.substr(i, longitudBloque) << " ";
  }
  std::cout << std::endl;
}

//
std::string Cambiar_clave(const std::string& clave, const std::string& texto, bool autoclave) {
  std::string clave_modificada = clave;
  if(autoclave) {
    for(size_t i = clave.length(), j=0; i <texto.length(); i++ ) {
      clave_modificada += texto[j];
      j++;
    }
    std::cout << "Autoclave:\t " << clave_modificada << std::endl;
  }
  
  return clave_modificada;
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
  char respuesta;
  bool descifrado = false;
  std::string clave, textoOriginal, textoCifrado;
  do {
    LimpiarPantalla();
    std::cout << " ______________________________________________________________________________" << std::endl;
	  std::cout << std::endl << "                   CIFRADO DE VIGENERE             " << std::endl;
	  std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    std::cout << "Desea cifrar o descifrar. (C)ifrar - (D)escifrar" << std::endl;
    std::cin >> respuesta;
    if (respuesta == 'd' || respuesta == 'D') {
      descifrado = true;
      std::cout << "Ingrese la palabra clave: ";
      std::cin.ignore();
      std::getline(std::cin, clave);

      std::cout << "Ingrese el texto cifrado: ";
      std::getline(std::cin, textoCifrado);
        
      std::string clave_claro = ConvertirMayuscula(clave);
      std::string texto_claro = ConvertirMayuscula(textoCifrado);

      std::cout << "¿Quieres generar la Autoclave (S)i o (N)o?" << std::endl;
      std::cin >> respuesta;
      std::string clave_modificada;
      std::string texto_desifrado;
      if(respuesta == 'S' || respuesta == 's') {
        texto_desifrado = CifradoVigenere(texto_claro, clave_claro, descifrado, true);

      }else if( respuesta == 'n' || respuesta == 'N') {
        texto_desifrado = CifradoVigenere(texto_claro, clave_claro, descifrado, false);
      } else {
        std::cerr << "Error no es ninguna opcion" << std::endl;
        break;
      }

      ImprimirEnBloques(texto_claro, clave_claro,texto_desifrado,descifrado);
      
    
    } else if(respuesta == 'c' || respuesta == 'C') {
      descifrado = false;
      std::cout << "Ingrese la palabra clave: ";
      std::cin.ignore();
      std::getline(std::cin, clave);

      std::cout << "Ingrese el texto original: ";
      std::getline(std::cin, textoOriginal);

      std::cout << "¿Quieres generar la Autoclave (S)i o (N)o?" << std::endl;
      std::cin >> respuesta;
      std::string clave_modificada;
      if(respuesta == 'S' || respuesta == 's') {
        clave_modificada = Cambiar_clave(clave,textoOriginal, true);
      }else if( respuesta == 'n' || respuesta == 'N') {
        clave_modificada = Cambiar_clave(clave,textoOriginal, false);
      } else {
        std::cerr << "Error no es ninguna opcion" << std::endl;
        break;
      }

      std::string texto_claro = ConvertirMayuscula(textoOriginal);
      std::string clave_claro = ConvertirMayuscula(clave_modificada);
      textoCifrado = CifradoVigenere(texto_claro, clave_claro, descifrado, false);

      ImprimirEnBloques(texto_claro, clave_claro, textoCifrado,descifrado);

    } else {
      std::cout << "Opcion no valida" << std::endl;
      break;
    }

		std::cout << "Desea salir del. (S)i - (N)o" << std::endl;
    std::cin >> respuesta;

	} while (respuesta == 'n' || respuesta == 'N');
  return 0;
}
