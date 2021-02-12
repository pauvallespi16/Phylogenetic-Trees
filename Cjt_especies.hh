/** @file Cjt_especies.hh
    @brief Especificació de la clase Cjt_especies
*/

#ifndef CJT_ESP_HH
#define CJT_ESP_HH

#include "Especie.hh"

#ifndef NO_DIAGRAM
#include <vector>
#include <map>
#include <iostream>
#endif

using namespace std;
/** @class Cjt_especies
    @brief Representa un conjunt d'espècies

    Ofereix les operacions de crear i eliminar espècies, vàries operacions
    de consulta (entre elles: la mida del conjunt) i la de lectura i
    escriptura tant del conjunt com de la taula de distàncies.
*/

class Cjt_especies {
private:
  /** @brief Taula de distàncies del conjunt */
  map<string, map<string, double> > distancies;
  /** @brief Conjunt d'espècies */
  map<string, Especie> mesp;
  /** @brief Iterador utilitzat per a la inicialització posterior dels clústers */
  map<string, Especie>::iterator it;
public:
  //Constructores
  /** @brief Constructora per defecte
    \pre Cert
    \post Crea un conjunt d'especies buit
  */
  Cjt_especies();

  //Destructores
  /** @brief Destructora
    \pre Cert
    \post El conjunt deixa d'existir
  */
  ~Cjt_especies();

  //Modificadores
  /** @brief Inicialització de l'iterador del p.i.
    \pre Cert
    \post L'iterador s'ha inicialitzat amb el primer element del conjunt
  */
  void primer();

  /** @brief Crea una especie amb idn i gen de l'espècie "e"
    \pre L'espècie no es troba al conjunt
    \post Crea una espècie amb els paràmetres de "e" i s'afegeix al conjunt.
  */
  void crea_especie(Especie e);

  /** @brief Elimina una espècie del conjunt
    \pre L'espècie es troba al conjunt
    \post S'elimina l'espècie amb identificador "idn" del conjunt.
  */
  void eliminar_especie(string idn);

  //Consultores
  /** @brief Consulta la mida del conjunt
    \pre Cert
    \post Retorna la mida del conjunt d'espècies
  */
  int mida();

  /** @brief Consulta l'identificador de l'espècie apuntada per l'iterador del p.i.
    \pre Cert
    \post Retorna l'identificador de l'espècie a la que apunta l'iterador del p.i. i el fa avançar
  */
  string proper();

  /** @brief Consulta si l'iterador del p.i. és al final
    \pre Cert
    \post Retorna cert si l'iterador és al final i fals altrament
  */
  bool final();

  /** @brief Consulta la distància entre dues espècies
    \pre Les espècies es troben al conjunt
    \post Retorna la distància entre les espècies amb identificadors "idn1" i "idn2"
  */
  double consultar_distancia(string idn1, string idn2);

  /** @brief Consulta si l'espècie amb identificador "idn" es troba al conjunt
    \pre Cert
    \post Si l'espècie amb identificador "idn" es troba al conjunt, retorna un pair que conté l'espècie i un booleà cert, altrament
          retorna una espècie buida i un booleà fals
  */
  pair<Especie, bool> existeix_especie(string idn);

  //Lectura i escriptura
  /** @brief Operació de lectura
    \pre Cert
    \post S'ha llegit el conjunt d'espècies
  */
  void llegir_cjt_especies();

  /** @brief Operació d'escriptura
    \pre Cert
    \post S'ha imprès el conjunt d'espècies
  */
  void imprimir_cjt_especies();

  /** @brief S'imprimeix la taula de distancies
    \pre Cert
    \post S'ha imprès la taula de distàncies entre espècies
  */
  void imprimir_taula_distancies();
};
#endif
