#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

#include <cctype> // Para la función std::toupper
#include <algorithm>

class RSA {
  public:
    RSA();
    RSA(unsigned long p, unsigned long q, unsigned long d);
    RSA(unsigned long n, unsigned long e);
    
    unsigned long getp() {return p_;};
    unsigned long getq() {return q_;}; 
    unsigned long getd() {return d_;};
    unsigned long getfi() {return fi_;};
    unsigned long getn() {return n_;};
    unsigned long gete() {return e_;};
    
    bool LehmanPeralta(unsigned long n);
    bool EuclidesExtendido(unsigned long a, unsigned long b);
    
    void CalcularEinverso(unsigned long a, unsigned long b);
    unsigned long CifrarRSA(unsigned long mensaje);
    unsigned long DescifrarRSA(unsigned long mensaje);
    std::vector<unsigned long> cifrarTexto(const std::vector<unsigned long>& bloques_codificados);
    std::vector<unsigned long> codificarTexto(const std::string& texto, unsigned long j);
  private:
    unsigned long p_, q_, d_, fi_, e_,n_ ;
    unsigned long ExponeciacionRapida(unsigned long base, unsigned long exponente, unsigned long modulo);

};