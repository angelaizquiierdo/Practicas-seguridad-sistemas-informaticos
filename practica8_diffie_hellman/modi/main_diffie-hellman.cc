/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Seguiridad de Sistemas Informático 2023-2024
  *
  * @file main_diffie-hellman.cc
  * @author Ángela Izquierdo Padrón  alu0101480442@ull.edu.es
  * @date 19 de marzo 2024
  * @brief Este programa implementa intecambio de clave de Diffie-Hellman 
  */


#include <iostream>
#include <cmath>
#include <vector>


bool esPrimo(long long numero) {
  if(numero <= 1) return false; // 0 y 1 no son primos
  if(numero <= 3) return true; // 2 y 3 son primos

  // Verificar divisibilidad hasta la raíz cuadrada de número
  for(long long i = 2; i <= sqrt(numero); ++i) {
      if(numero % i == 0) {
        return false; // Si es divisible, no es primo
      }
  }
  return true; // Si no es divisible por ningún número, es primo
}

long long mod_exp(long long base_alpha, long long Y_exponente, long long modulo_p) {
  long long resultado_k = 1;
  base_alpha = base_alpha % modulo_p;
  long long y = base_alpha;

  while (Y_exponente > 0 && y > 1) {
    if (Y_exponente % 2 == 1) {
      resultado_k = (resultado_k * y) % modulo_p;
      Y_exponente -= 1;
    } else {
      y = (y * y) % modulo_p;
      Y_exponente = Y_exponente / 2;
    }
  }

  return resultado_k;
}


void Diffie_hellman(long long p, long long alpha ,std::vector<long long> clavesPrivadas) {
  size_t numUsuarios = clavesPrivadas.size();

  // Vector para almacenar los valores públicos de los usuarios
  std::vector<long long> valoresPublicos(numUsuarios);

  // clave compartidas de los usuarios
  std::vector<long long> clavesCompartidas(numUsuarios);

  // abcedario
  std::string abecedario ="ABCDEFGHIJKLMNOPQRS";

  // Generar claves privadas y valores públicos para cada usuario
  std::cout << "\nValores públicos intercambiados:\n";
  for (size_t i = 0; i < numUsuarios; ++i) {
    valoresPublicos[i] = mod_exp(alpha, clavesPrivadas[i], p);
    std::cout << "Y_" << abecedario[i] << " = " << valoresPublicos[i] << std::endl;
    
  }
  
  // Cálculo de claves compartidas para cada par de usuarios
  std::cout << "\nClaves compartidas entre los usuarios:\n";
  for (size_t i = 0; i < numUsuarios; ++i) {
    int j = (i + 1) % numUsuarios; // Índice del siguiente usuario en el ciclo
    clavesCompartidas[i] = mod_exp(valoresPublicos[j], clavesPrivadas[i], p);
    std::cout << "Usuario " << i+1 << " y Usuario " << j+1 << ": " << clavesCompartidas[i] << std::endl;
  }

  long long claveComun = mod_exp(valoresPublicos[0], (clavesPrivadas[1] * clavesPrivadas[2]), p);
  std::cout << "\nClave compartida para los tres usuarios: " << claveComun << std::endl;
}


void LimpiarPantalla() {
  #ifdef _WIN32
  system("cls");
  #else
  system("clear");
  #endif
//  for (int i = 0; i < 50; ++i) {
      //std::cout << std::endl;
 //   }
}

int main() {
  // Solicitar al usuario los valores de p, α, xA y xB
  long long p, alpha, xA, xB, xC;

  char respuesta;

  do { 
    LimpiarPantalla();
    std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    std::cout << "                   IMPREMENTACIÓN DE CLAVES DE DIFFIE-HELLMAN                   " << std::endl;
    std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    
    bool esprimo = false ;

    do {
      std::cout << "Ingrese el valor de p (número primo): ";
      std::cin >> p;
      esprimo = esPrimo(p);
      if (!esprimo) {
         std::cout << "El número ingresado no es primo. Inténtelo de nuevo." << std::endl;
      }
    } while (!esprimo);
    
    std::cout << "Ingrese el valor de α (generador menor que p): ";
    std::cin >> alpha;

    if ( alpha >= p) {
      std::cout << "Error no se puede realizar la operación" << std::endl;
      return 1;
    }

 
    
    std::cout << "Ingrese el secreto de Alice (xA): ";
    std::cin >> xA;

    std::cout << "Ingrese el secreto de Bob (xB): ";
    std::cin >> xB;

    std::cout << "Ingrese el secreto de C (xC): ";
    std::cin >> xC;
    
    std::vector<long long> clavesprivadasUsuarios = {xA, xB, xC};
    Diffie_hellman(p, alpha, clavesprivadasUsuarios);
    std::cout << std::endl << "Desea salir del. (S)i - (N)o" << std::endl;
    std::cin >> respuesta;
  } while (respuesta == 'n' || respuesta == 'N');


 return 0;
}
