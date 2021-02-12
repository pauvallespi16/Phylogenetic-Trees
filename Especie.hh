/** @file Especie.hh
    @brief Especificació de la clase Especie
*/
#ifndef ESPECIE_HH
#define ESPECIE_HH

#ifndef NO_DIAGRAM
#include <vector>
#include <map>
#include <iostream>
#endif

using namespace std;
/** @class Especie
    @brief Representa una espècie

    Ofereix l'operació de càlcul de distàncies entre espècies, vàries operacions
    de consulta i de lectura i escriptura.
*/

class Especie {
private:
  /** @brief Gen de l'espècie */
  string gen;
  /** @brief Identificador de l'espècie */
  string idn;
  /** @brief Kmer de l'espècie */
  map<string, int> kmer;
  /** @brief Paràmetre K utilitzat per al càlcul dels kmers */
  int static K;
  /** @brief Executa el mètode kmer
    \pre Cert
    \post kmer conté els k-mers del gen en ordre lexicogràfic creixent
  */
  void fer_kmer();

public:
  //Constructores
  /** @brief Constructora per defecte
    \pre Cert
    \post Crea una especie buida
  */
  Especie();

  /** @brief Constructora amb gen i identificador
    \pre Cert
    \post Crea una espècie amb gen i identificador
  */
  Especie(string gen, string idn);

  //Destructora
  /** @brief Destructora
    \pre Cert
    \post L'espècie deixa d'existir
  */
  ~Especie();

  //Modificadores
  /** @brief Calcula la distància entre dues espècies
    \pre Espècies no buides
    \post Retorna la distància entre les dues espècies
  */
  double distancia(Especie e);

  /** @brief Assigna un valor a la variable privada "k" del p.i.
    \pre k >= 1
    \post S'ha assignat el valor a la variable "k" del p.i.
  */
  static void valor_k(int k);

  /** @brief Consulta l'identificador del p.i.
    \pre Espècie no buida
    \post Retorna l'identificador de l'espècie
  */
  string consultar_idn();

  /** @brief Consula el gen del p.i.
    \pre Espècie no buida
    \post Retorna el gen de l'espècie
  */
  string consultar_gen();

  //Lectura i escriptura
  /** @brief Operació de lectura
    \pre Cert
    \post Es llegeix una espècie
  */
  void llegir();

  /** @brief Operació d'escriptura
    \pre Cert
    \post S'imprimeix una espècie
  */
  void escriure() const;
};
#endif
