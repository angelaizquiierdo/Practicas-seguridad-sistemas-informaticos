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


void Diffie_hellman(long long p, long long alpha, long long xA, long long xB) {
  // Paso 1: Calcula yA = α^xA mod p y muestra el valor
  long long yA = mod_exp(alpha, xA, p);
  std::cout << "yA = α^xA mod p = " << yA << std::endl;

  // Paso 2: Calcula yB = α^xB mod p y muestra el valor
  long long yB = mod_exp(alpha, xB, p);
  std::cout << "yB = α^xB mod p = " << yB << std::endl;

  // Paso 3: Genera la clave compartida k para Alice y muestra el valor
  long long k_Alice = mod_exp(yB, xA, p);
  std::cout << "k Alice =  " << k_Alice << std::endl;

  // Paso 4: Genera la clave compartida k para Bob y muestra el valor
  long long k_Bob = mod_exp(yA, xB, p);
  std::cout << "k Bob =  " << k_Bob << std::endl;
  
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
  long long p, alpha, xA, xB;

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


    Diffie_hellman(p, alpha, xA, xB);
    std::cout << std::endl << "Desea salir del. (S)i - (N)o" << std::endl;
    std::cin >> respuesta;
  } while (respuesta == 'n' || respuesta == 'N');


 return 0;
}
