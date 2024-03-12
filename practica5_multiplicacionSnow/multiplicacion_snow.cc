#include <iostream>
#include <bitset>
#include <vector>


// Función para descomponer un número binario en la suma de sus componentes
std::vector<std::bitset<8>> descomponerNumero(std::bitset<8> numero) {
    std::vector<std::bitset<8>> componentes;

    // Iterar a través de los bits del número
    for (int i = 0; i < 8; ++i) {
        // Verificar si el bit actual está encendido
        if (numero.test(i)) {
            // Si el bit está encendido, agregar la componente correspondiente a la posición del bit a la lista
            std::bitset<8> componente = 1 << i;
            componentes.push_back(componente);
        }
    }

    return componentes;
}



// Función para realizar la multiplicación de polinomios en módulo con retroalimentación LFSR
std::bitset<8> Producto(std::bitset<8> num, std::bitset<8> num2, std::bitset<8> polinomio) {
  std::bitset<8> suma, auxsuma;
  
  int controlador_ultimobit;
  // Descomponer el número en la suma de sus componentes
  for (int i = 0; i < 8; i++) {
    // std::cout << "que contiene num2[i]: indice " << i << "\t numero es: "  << num2[i] << std::endl;
    if (num2[i] == 1) {
      auxsuma = num;
      std::cout <<"\t" << auxsuma << std::endl;
      for( int j=0; j < i; j++) {
        controlador_ultimobit = auxsuma[7];
        auxsuma = auxsuma << 1; // Desplazamiento correcto de bits
        if(controlador_ultimobit == 1) {
          std::cout << auxsuma <<  " + " << polinomio << " = ";
          auxsuma = auxsuma ^ polinomio;
          std::cout << auxsuma <<  " <= Suma polinomica SnowG3 o AES" << std::endl;
        }else {
          std::cout << auxsuma << std::endl;
        }
      }
        //std::bitset<8> multiplicacionParcial = num << 1; // Desplazamiento correcto de bits
        std::cout <<" \tbyte posición: "<< i << " total: "<< suma << " + " << auxsuma  << std::endl;

        suma = suma ^ auxsuma; // XOR con el resultado parcial
        std::cout << "\t\t SUMA: " << suma << std::endl;
      }   
    }

  return suma;
}

// Función para convertir un número hexadecimal a std::bitset<8>
std::bitset<8> hexToBitset(const std::string& hexStr) {
  unsigned long long num = std::stoull(hexStr, nullptr, 16); // Convertir de hexadecimal a entero
  return std::bitset<8>(num); // Inicializar el std::bitset<8> con el número entero
}

int main() {

    std::string hexSnow3g = "A9"; // Número hexadecimal Snow3g
    std::string hexAes = "1B";   // Número hexadecimal AES
    char algoritmo;
    std::cout << "Ingresa el algoritmo que quieres utilizar (S para SNOW3G, A para AES): ";
    std::cin >> algoritmo;
    std::cout << "El algoritmo seleccionado es: " << algoritmo << std::endl;

    int numero_multiplicador = 87;
    int numero2_multiplicando = 131;

    // Leer los números de entrada desde el usuario
    std::cout << "Ingresa el multiplicador número en formato binario (8 bits): ";
    std::cin >> numero_multiplicador;
    std::cout << "Ingresa el multiplicando número en formato binario (8 bits): ";
    std::cin >> numero2_multiplicando;

    // Convertir los números de cadena a std::bitset<8>
    std::bitset<8> num(numero_multiplicador);
    std::bitset<8> num2(numero2_multiplicando);
    if(algoritmo == 'S') {
      std::cout << "El algoritmo seleccionado es SNOW3G" << std::endl;  
      std::bitset<8> snow3gBitset = hexToBitset(hexSnow3g);
      std::bitset<8> resultado = Producto(num, num2, snow3gBitset);
      std::cout << "El resultado de la multiplicación es con SNOW3G: " << resultado << std::endl;
    } else if(algoritmo == 'A') {
      std::cout << "El algoritmo seleccionado es AES" << std::endl;
      std::bitset<8> aesBitset = hexToBitset(hexAes);
      std::bitset<8> resultado = Producto(num, num2, aesBitset);
      std::cout << "El resultado de la multiplicación es con AES: " << resultado << std::endl;
    } else {
      std::cout << "El algoritmo seleccionado no es válido" << std::endl;
    }
 
   
    return 0;
}

