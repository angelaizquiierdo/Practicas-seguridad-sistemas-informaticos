
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include <algorithm>



class ChaCha20 {
public:
// constructor
    ChaCha20(const std::string& clave, const std::string& nonce, const std::string& contador)
        : clave_(ObtenerVectorDesdeHex(clave)),
          nonce_(ObtenerVectorDesdeHex(nonce)),
          contador_(ObtenerVectorDesdeHex(contador)) {}


    /**
     * @brief Cifra el mensaje con el algoritmo de cifrado ChaCha20 y muestra en pantalla el estado inicial,
     *  el estado final tras 20 iteraciones y el estado de salida del generador. Además al principio se concatena
     * los valores de constante, clave, el contador y el nonce. en un
    */
    void Cifrar() {
        std::vector<uint32_t> estado = kconst_;
        Concatenar(estado, clave_);
        //ImprimirEstado("Contenido de key:", clave_);
        Concatenar(estado, contador_);
        Concatenar(estado, nonce_);
        ImprimirEstado("Estado nonce=", nonce_);
        ImprimirEstado("Estado Inicial=", estado);
        std::vector<uint32_t> estadoInicial = estado;

        for (int ronda = 0; ronda < 1; ronda += 2) {
            // operador columna
            OperacionQR(estado[0], estado[4], estado[8], estado[12]); // columna 0
            OperacionQR(estado[1], estado[5], estado[9], estado[13]); // columna 1
            OperacionQR(estado[2], estado[6], estado[10], estado[14]);  // columna 2
            OperacionQR(estado[3], estado[7], estado[11], estado[15]);  // columna 3
            // operador diagonalmente
            OperacionQR(estado[0], estado[5], estado[10], estado[15]);  // diagonal 1 (principal)
            OperacionQR(estado[1], estado[6], estado[11], estado[12]);  // diagonal 2
            OperacionQR(estado[2], estado[7], estado[8], estado[13]);   // diagonal 3
            OperacionQR(estado[3], estado[4], estado[9], estado[14]);   // diagonal 4
        }

        ImprimirEstado("Estado final tras 20 iteraciones=", estado);
        for (int i = 0; i < ESTADO_TAMANO; ++i) {
            estado[i] += estadoInicial[i];
        }

        ImprimirEstado("Estado de salida del generador=", estado);
    }

private:
    // constantes estaticas que no cambian
    static const int RONDAS = 20; // numero de  rondas
    static const int ESTADO_TAMANO = 16; // tamaño del estado
    const std::vector<uint32_t> kconst_ = { 0x61707865, 0x3320646e, 0x79622d32, 0x6b206574 }; // constante que no cambia

    // atributos privados
    std::vector<uint32_t> clave_;
    std::vector<uint32_t> nonce_;
    std::vector<uint32_t> contador_;

    // métodos privados

    /**
     * @brief Concatena el vector origen al vector destino
     * @param destino: Vector al que se le va a concatenar el vector origen
     * @param origen: Vector que se va a concatenar al vector destino
     */
    void Concatenar(std::vector<uint32_t>& destino, const std::vector<uint32_t>& origen) {
        for (size_t i = 0; i < origen.size(); ++i) {
            destino.push_back(origen[i]);
            //std::cout << origen[i] <<" ";
        }
        
    }

    /**
     * @brief Concatena el valor al vector destino
     * @param destino: Vector al que se le va a concatenar el valor
     * @param valor: Valor que se va a concatenar al vector destino
     */
    void Concatenar(std::vector<uint32_t>& destino, uint32_t valor) {
        destino.push_back(valor);
    }

    /**
     * @brief Realiza la operación de ChaCha20 sumando y realizando un XOR y rotaciones a los valores a, b, c y d
     * @param a: Valor a
     * @param b: Valor b
     * @param c: Valor c
     * @param d: Valor d
     */
    void OperacionQR(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d) {
        a += b; d ^= a; d = ROTL32(d, 16); // a = a + b, d = d XOR a, d = rotl(d, 16)
        std::cout << "a:" << a << "\t b:" << b << "\t c:" << c << "\t d:" << d << std::endl;
        c += d; b ^= c; b = ROTL32(b, 12); // c = c + d, b = b XOR c, b = rotl(b, 12)
        std::cout << "a:" << a << "\t b:" << b << "\t c:" << c << "\t d:" << d << std::endl;
        a += b; d ^= a; d = ROTL32(d, 8);  // a = a + b, d = d XOR a, d = rotl(d, 8)
        std::cout << "a:" << a << "\t b:" << b << "\t c:" << c << "\t d:" << d << std::endl;
        c += d; b ^= c; b = ROTL32(b, 7);  // c = c + d, b = b XOR c, b = rotl(b, 7)
        std::cout << "a:" << a << "\t b:" << b << "\t c:" << c << "\t d:" << d << std::endl;
    }

    /**
     * @brief Realiza una rotación a la izquierda de 32 bits
     * @param valor: Valor al que se le va a realizar la rotación
     * @param desplazamiento: Número de bits que se va a desplazar
     * @return Devuelve el valor rotado
     */
    uint32_t ROTL32(uint32_t valor, int desplazamiento) {
        return (valor << desplazamiento) | (valor >> (32 - desplazamiento));
    }

    /**
     * @brief Obtiene un vector de enteros de 32 bits a partir de una cadena de caracteres de 8 bits hexadecimal
     * 6436943a 437824c5 32a9c7d2 8f3a7e91 4f9b5c4d 3f3c3f3c 3f3c3f3c 3f3c3f3c .... un total de 128 caracteres en hexadecimal
     * de los cuales se obtienen 16 enteros de 32 bits 4x4
     * @param hex: Cadena de caracteres en hexadecimal
     * @return Devuelve un vector de enteros de 32 bits
     */
    std::vector<uint32_t> ObtenerVectorDesdeHex(const std::string& hex) {
        std::vector<uint32_t> resultado;
        for (size_t i = 0; i < hex.length(); i += 8) {
            std::string subcadena = hex.substr(i, 8);
            resultado.push_back(std::stoul(subcadena, nullptr, 16));
        }
        return resultado;
    }

    /**
     * @brief Imprime en pantalla el estado del generador dependiendo del mensaje que se le pasa
     * @param mensaje: Mensaje que se va a imprimir
     * @param estado: Estado del generador
     */
    void ImprimirEstado(const std::string& mensaje, const std::vector<uint32_t>& estado) {

        std::cout << std::endl<< std::endl;
        std::cout << mensaje << std::endl;
        for (int i = 0; i < ESTADO_TAMANO; i += 4) {
            for (int j = 0; j < 4; ++j) {
                std::cout << std::hex << std::setw(8) << std::setfill('0') << estado[i + j] << " ";
            }
            std::cout << std::endl;
        }

    }
};
