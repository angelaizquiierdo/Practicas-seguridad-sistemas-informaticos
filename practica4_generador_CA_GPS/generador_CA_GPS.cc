#include <iostream>
#include <vector>
#include <string>


void ImprimirVector(std::string texto, const std::vector<int>& mivector) {
  std::cout << texto << std::endl;

    for (int elem : mivector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}



/**
 * Esta función es el que genera el cifrado y devulve la salida de ella.
*/
std::vector<int> GeneradorCA_GPS( std::vector<int>& lfsr1,  std::vector<int>& lfsr2, const int& id_satelite, const int& tamayo) {
  std::vector <int> secuencia_CA_PRN1;
  for(int iterar=0; iterar < tamayo ; iterar++) {
   
    int xor1 = lfsr1[2] ^ lfsr1[9];
    //std::cout << "xor1: " << xor1;
    int xor2 = lfsr2[1] ^ lfsr2[2] ^ lfsr2[5] ^ lfsr2[7] ^ lfsr2[8] ^ lfsr2[9];
    //std::cout << "xr2: " << xor2 << std::endl;
   
    if( iterar >= 9) {
       ImprimirVector("1. Sin ultimo elemento", lfsr1);
    }
     
     if( iterar >= 9)  {
       ImprimirVector("2. Sin ultimo elemento", lfsr2);
     }
    const int ultimo_elemento_lfsr = lfsr1[9];
    switch (id_satelite)
    {
    case 1:
      //std::cout << lfsr1[10] << " ^ (" <<  (lfsr2[1] ^ lfsr2[5]) << std::endl;
      secuencia_CA_PRN1.push_back( ultimo_elemento_lfsr ^ (lfsr2[1] ^ lfsr2[5]));
      break;
    case 2:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^ (lfsr2[2] ^ lfsr2[6]));
      break;
    case 3:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^ (lfsr2[3] ^ lfsr2[7]));
      break;
    case 4:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[4] ^ lfsr2[8]));
      break;
    case 5:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[0] ^ lfsr2[8]));
      break;
    case 6:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[1] ^ lfsr2[9]));
      break;
    case 7:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[0] ^ lfsr2[7]));
      break;
    case 8:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[1] ^ lfsr2[8]));
      break;
    case 9:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[2] ^ lfsr2[9]));
      break;
    case 10:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[1] ^ lfsr2[2]));
      break;
    case 11:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[2] ^ lfsr2[3]));
      break;
    case 12:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[5] ^ lfsr2[4]));
      break;
    case 13:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[5] ^ lfsr2[6]));
      break;
    case 14:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[6] ^ lfsr2[7]));
      break;
    case 15:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[7] ^ lfsr2[8]));
      break;
    case 16:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[8] ^ lfsr2[9]));
      break;
    case 17:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[0] ^ lfsr2[3]));
      break;
    case 18:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[1] ^ lfsr2[4]));
      break;
    case 19:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[2] ^ lfsr2[5]));
      break;
    case 20:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[3] ^ lfsr2[6]));
      break;
    case 21:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[4] ^ lfsr2[7]));
      break;
    case 22:
     secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[5] ^ lfsr2[8]));
      break;
    case 23:
      secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[0] ^ lfsr2[2]));
      break;
    case 24:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[3] ^ lfsr2[5]));
      break;
    case 25:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[4] ^ lfsr2[6])); 
      break;
    case 26:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[5] ^ lfsr2[7]));
    break;
    case 27:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^(lfsr2[6] ^ lfsr2[8]));
    break;
    case 28:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^( lfsr2[7] ^lfsr2[9]));
    break;
    case 29:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^ ( lfsr2[0] ^lfsr2 [5]));
    break;
    case 30:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^ ( lfsr2[1] ^lfsr2[6]));
    break;
    case 31:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^ ( lfsr2[2] ^lfsr2[7]));
    break;
    case 32:
    secuencia_CA_PRN1.push_back(ultimo_elemento_lfsr ^ ( lfsr2[3] ^lfsr2[8]));
    break;
    default:
       std::cerr << "ID de satélite no reconocido" << std::endl;
                return std::vector<int>(); // Devuelve un vector vacío en caso de que el ID de satélite no sea reconocido
        
    
    }
    lfsr1.pop_back();
    lfsr2.pop_back();

    lfsr1.insert(lfsr1.begin(), xor1);
    lfsr2.insert(lfsr2.begin(), xor2);
  }
 // ImprimirVector("resultado Final:", secuencia_CA_PRN1);
  return secuencia_CA_PRN1;
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

  int id_satelite;
  int logitud_secuencia;
  char respuesta;
  
  do{
    std::vector<int> lfsr1(10,1); // rellenar con 1111111111
    std::vector<int> lfsr2(10,1); // rellenar con 1111111111
    LimpiarPantalla();
    std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    std::cout << "                  IMPREMENTAR EL GENERADOR C/A USANDO EN GPS                   " << std::endl;
    std::cout << " ______________________________________________________________________________" << std::endl << std::endl;
    std::cout << "ID del sátelite: ";
    std::cin >> id_satelite;
     while (id_satelite < 1 || id_satelite > 32) {
      std::cout << "No valida ID satelite es del rango 1 a 32. Ingrese un número entre 1 y 32: " << std::endl;
      std::cin >> id_satelite;
    }

    std::cout << "Logitud de la secuencia de salida: ";
    std::cin >> logitud_secuencia;
    while (logitud_secuencia <= 0) {
      std::cout << "Longitud de secuencia no válida. Ingrese un número mayor que cero: " << std::endl;
      std::cin >> logitud_secuencia;
    }
    ImprimirVector("Salida de Secuencia C/A PRN1", GeneradorCA_GPS(lfsr1, lfsr2, id_satelite, logitud_secuencia));
    
    std::cout << std::endl << "Desea salir del. (S)i - (N)o" << std::endl;
    std::cin >> respuesta;
  } while (respuesta == 'n' || respuesta == 'N');
  return 0;
}