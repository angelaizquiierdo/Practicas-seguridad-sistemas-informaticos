#include "rsa.h"
// cosntructor
RSA::RSA(unsigned long p, unsigned long q, unsigned long e) : p_(0), q_(0), d_(0) ,fi_(0), e_(0) {
  std::cout << "Generando claves RSA..." << std::endl;

  if(LehmanPeralta(p) && LehmanPeralta(q)) {
    
    // privada
    p_ = p;
    q_ = q;
    fi_ = (p_ - 1) * (q_ - 1);
    e_ = e;
    n_ = p_ * q_;
    // publica
    if( !EuclidesExtendido(e_, fi_)) {
      throw std::invalid_argument("Error: d no es primo con φ(n).");
    }
    
      
    if(EuclidesExtendido(e_, fi_)) {
      CalcularEinverso(e_, fi_);
      std::cout << "Calcular d: " << d_ << std::endl;
      std::cout << "Clave Publica generada (n, e) =  ("<<  n_ << "," << e_ << ")"<<  std::endl;
      std::cout << "Clave Privada generada (p,q, fi, d) = ("<<  p_ << "," << q_ << ", "<< fi_ << ", " << d_<< ")"  << std::endl;
    } else { 
      throw std::invalid_argument("Error: d no es primo con φ(n).");
    }

  } else {
    throw std::invalid_argument("Error: p y/o q no son primos.");
  }
}


RSA::RSA(unsigned long n, unsigned long e) : p_(0), q_(0), d_(0) ,fi_(0), e_(0) {
  std::cout << "Generando claves RSA..." << std::endl;
  n_ = n;
  e_ = e;
  std::cout << "Clave Publica generada (n, e) "<<  n_ << "," << e_ << std::endl;
} 


/**
 * Codifica un texto en bloques del tamaño j.
*/
std::vector<unsigned long> RSA::codificarTexto(const std::string& texto, unsigned long j) {
  std::vector<unsigned long> bloques_codificados;
  std::string textoSinEspacios;
  std::cout << "texto original "<<texto << std::endl;
  // Eliminar los espacios en blanco y convertir todo a mayúsculas
  for (char c : texto) {
    if (!std::isspace(static_cast<unsigned char>(c))) {
      textoSinEspacios += std::toupper(c);
    }
  }
  std::cout << "Texto sin espacios: " << textoSinEspacios << std::endl;
  // Completar con X si es necesario para obtener bloques del tamaño j
  if (textoSinEspacios.length() % j != 0) {
    std::cout << "Completando con X..." << std::endl;
    unsigned long caracteresFaltantes = j - (textoSinEspacios.length() % j);
    textoSinEspacios.append(caracteresFaltantes, 'X');
  }

  std::cout << "Texto sin espacios y completado: " << textoSinEspacios << std::endl;
    // Codificar el texto en bloques del tamaño j
    for (size_t i = 0; i < textoSinEspacios.length(); i += j) {
        unsigned long valorDecimal = 0;
        for (size_t k = 0; k < j; ++k) {
            // Obtener el valor numérico de la letra (A=0, B=1, ..., Z=25)
            unsigned long valor = textoSinEspacios[i + k] - 'A';
            // Calcular el valor decimal del bloque
            valorDecimal += valor * pow(26, j - 1 - k);
        }
        bloques_codificados.push_back(valorDecimal);
    }

    return bloques_codificados;
}



/**
 * Verifica si un número es primo usando el test de Lehman-Peralta.
*/
bool RSA::LehmanPeralta(unsigned long n) {
  std::cout << "funciona (entra en lehmanPeralta)" << std::endl;
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    // Comprobar que n no es divisible por ningún primo pequeño (2, 3, 5, 7, 11)
    std::vector<unsigned long> primos_pequenos = {2, 3, 5, 7, 11};
    for (unsigned long primo : primos_pequenos) {
      if (n % primo == 0){
        if (n != primo) {
          return false; // n no es primo
        } else {
          return true; // n es primo
        }
      }
    }

    // Elegir enteros aleatorios a, entre 2 y n-1
    srand(time(nullptr)); // Inicializar la semilla aleatoria
    unsigned long a = rand() % (n - 2) + 2;

    // Calcular a^((n-1)/2) mod n
    unsigned long exp = (n - 1) / 2;
    unsigned long  result = 1;
    for (unsigned long i = 0; i < exp; ++i) {
      
      result = (result * a) % n;
      //std::cout << "a^((n-1)/2) mod n: " << result << std::endl;
    }

    // Verificar si n es compuesto
    if (result == 1 || result == n - 1) {
      return true; // n tal vez es primo
    }
    for (unsigned long i = 1; i < exp; ++i) {
      result = (result * result) % n;
      if (result == n - 1) {
        return true; // n tal vez es primo
      } 
    }
    
  return false; // n es compuesto
}

/**
 * Esta función calcula el inverso multiplicativo de un número d_ módulo φ(n)φ(n), 
 * que se utiliza para hallar la clave pública ee
*/
void RSA::CalcularEinverso(unsigned long modulo, unsigned long numero) {
  long long x_previo = 1, x_actual = 0, y_previo = 0, y_actual = 1;
  unsigned long dividendo_previo = modulo, dividendo_actual = numero;
  //encotrar el max comun divisor (MCD) 
  while (dividendo_actual != 0) {
    unsigned long cociente = dividendo_previo / dividendo_actual;
    long long temp_x = x_actual, temp_y = y_actual;
    x_actual = x_previo - cociente * x_actual;
    y_actual = y_previo - cociente * y_actual;
    x_previo = temp_x;
    y_previo = temp_y;
    unsigned long temp_dividendo = dividendo_actual;
    dividendo_actual = dividendo_previo - cociente * dividendo_actual;
    dividendo_previo = temp_dividendo;
  }
  
  // Si el coeficiente x resulta ser negativo después de los cálculos, 
  // se suma el valor de φ(n)φ(n) (fi_) para hacerlo positivo. 
  if (x_previo < 0) {
    x_previo += fi_;
  }
  std::cout << "d: " << x_previo << std::endl;
  d_ = x_previo;
}

/**
 * Calcula la exponenciación rápida de un número, para cifrar y descifrar
*/
unsigned long RSA::ExponeciacionRapida(unsigned long base, unsigned long exponente, unsigned long modulo) {
  long long A=base, P=1, E=exponente;	
	while (1) {		
		if (E == 0) { // exponente 0
			return P;
		}		
		else if (E % 2 != 0) { // exponente impar
			P = (A * P) % modulo; // reducción del módulo n para cada multiplicación
			E = (E - 1) / 2;
		}
		else { // exponente par
			E = E / 2;
		}
		A = (A * A) % modulo; //Calcula a sequência de potências
	}
}



/**
 * Calcula el inverso multiplicativo de a módulo b, para hallar la clave pública d.
*/
bool RSA::EuclidesExtendido(unsigned long a, unsigned long b) {
 std::vector<unsigned long> residuos, coeficientes;
    
    // Colocar el número más grande en x y el otro en y
    if (a > b) {
        residuos.push_back(a);
        residuos.push_back(b);
    } else {
        residuos.push_back(b);
        residuos.push_back(a);
    }
    
    // Inicializar los coeficientes iniciales
    coeficientes.push_back(0);
    coeficientes.push_back(1);

    unsigned i = 1;
    while (residuos[i-1] % residuos[i] != 0) {
        // Calcular el siguiente residuo y el siguiente coeficiente
        residuos.push_back(residuos[i-1] % residuos[i]);
        coeficientes.push_back(-(residuos[i-1] / residuos[i]) * coeficientes[i] + coeficientes[i-1]);
        i++;
    }

    if (residuos[i] == 1) {
        // Si el inverso es negativo, sumar fi_
        if (coeficientes[i] < 0) {
            coeficientes[i] += fi_;
        }
        return true;
    }
  
    // Si el MCD no es 1, los números no son coprimos
    return false;
}

/**
 * Cifra un texto codificado en bloques.
*/
std::vector<unsigned long> RSA::cifrarTexto(const std::vector<unsigned long>& bloques_codificados) {
  std::vector<unsigned long> texto_cifrado;

  for (unsigned long bloque : bloques_codificados) {
    unsigned long cifrado = ExponeciacionRapida(bloque, d_, n_);
    texto_cifrado.push_back(cifrado);
  }

  return texto_cifrado;
}

/**
 * Descifra un mensaje cifrado usando RSA.
*/
unsigned long RSA::DescifrarRSA(unsigned long mensaje) {
  return ExponeciacionRapida(mensaje, e_, p_ * q_);
}