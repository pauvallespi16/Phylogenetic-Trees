/** @file Cjt_clusters.hh
    @brief Especificació de la clase Cjt_clusters
*/

#ifndef CJT_CLUSTERS_HH
#define CJT_CLUSTERS_HH

#include "Cjt_especies.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#include <iostream>
#endif

/** @class Cjt_clusters
    @brief Representa un conjunt de clústers

    Ofereix les operacions d'execució del pas WPGMA, juntament d'altres de
    consulta de clústers o de la mida del conjunt. També conté operacions
    d'escriptura i lectura del conjunt i de la taula de distàncies
    entre els clústers.
*/
typedef BinTree< pair<string, double> > Cluster;

class Cjt_clusters {
private:
  /** @brief Conjunt de clústers */
  map<string, Cluster> mclust;
  /** @brief Taula de distància entre clústers */
  map<string, map<string, double> > distancies;
  /** @brief Distància mínima entre clústers. S'inicialitza a 101 ja que
             la distància màxima entre dos clústers pot ser com a màxim 100 */
  double dist_min = 101;
  /** @brief Identificadors dels clústers a menor distància */
  string idn_min1, idn_min2;
  /** @brief Actualitza la variable dist_min
    \pre Cert
    \post dist_min conté la distància mínima de la taula de distàncies
  */
  void recalcular_dist_min();
public:
  //Constructores
  /** @brief Constructora per defecte
    \pre Cert
    \post Crea un conjunt de clústers buit
  */
  Cjt_clusters();

  /** @brief Constructora a partir d'un conjunt d'espècies
    \pre Conjunt d'espècies no buit
    \post Crea un conjunt de clústers basat en les espècies de "cesp"
  */
  Cjt_clusters(Cjt_especies cesp);

  //Destructora
  /** @brief Destructora per defecte
    \pre Cert
    \post El conjunt de clústers deixa d'existir
  */
  ~Cjt_clusters();

  //Modificadores
  /** @brief Fusiona els dos clústers a menor distància en un nou
    \pre Conjunts de clústers no buits
    \post S'ha fusionat els dos clústers a menor distància
  */
  void executa_pas_wpgma();

  //Consultores
  /** @brief Consulta la mida del conjunt
    \pre Cert
    \post Retorna la mida del conjunt de clústers
  */
  int mida();

  /** @brief Consulta si existeix en el p.i una espècie amb identificador "idn"
    \pre Cert
    \post Retorna cert o fals segons si existeix o no al p.i l'espècie de identificador "idn"
  */
  bool existeix_cluster(string idn);

  /** @brief Consulta el clúster amb identificador "idn"
    \pre El clúster es troba al conjunt
    \post Retorna el clúster amb identificador "idn"
  */
  Cluster consultar_cluster(string idn);

  //Lectura i escriptura
  /** @brief Operació d'escriptura d'un clúster
    \pre El clúster es troba al conjunt
    \post S'ha escrit el clúster amb identificador "idn"
  */
  void imprimir_cluster(const Cluster &clust);

  /** @brief Imprimeix l'arbre filogenètic pel conjunt d'espècies actual
    \pre Cert
    \post S'ha imprès l'arbre filogenètic pel conjunt d'espècies actual
  */
  void imprimir_arbre_filogenetic();

  /** @brief Imprimeix la taula de distancies
      \pre Cert
      \post S'ha imprès la taula de distàncies entre clústers
  */
  void imprimir_taula_distancies();
};
#endif
