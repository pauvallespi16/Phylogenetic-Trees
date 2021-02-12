/** @mainpage Disseny modular de la manipulació d'un conjunt d'espècies i la creació d'arbres filogenètics
  <b>Data: </b> 20/05/2020

  <b>Llenguatge: </b> C++

  <b>Versió: </b> 1.0.0

  <b>Autor: </b> Pau Vallespí Monclús
*/


/** @file program.cc
    @brief Programa principal per a la pràctica.
*/

#include "Cjt_clusters.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif
using namespace std;

/** @brief Programa principal per a la pràctica

  Aquesta pràctica ens permet treballar amb espècies, conjunt d'espècies, clústers
  i conjunt de clústers a través de les representacions fetes amb classes.

  El programa principal comença llegint un int que utilitzarem per al càlcul dels kmers,
  posteriorment es llegeix un string. Mentre aquest string sigui diferent de "fin", el nostre
  programa anirà fent una sèrie d'operacions que estan relacionades directament amb
  les classes que tenim. Un cop escrivim "fin", s'acabarà l'execució del programa.

  Les operacions són les següents:
  * - <b>crea_especie: </b> Crea una espècie amb el gen i identificador donats, i si aquesta no es troba al conjunt, l'afegeix. Altrament
      mostra un missatge d'error.
  * - <b>obtener_gen: </b> Mostra el gen lligat a l'espècie amb l'identificador donat. Si aquesta espècie no es troba al conjunt, mostra
      un missatge d'error.
  * - <b>distancia: </b> Donats dos identificadors, calcula la distància entre les dues espècies. Si alguna d'elles o ambdues no es troben al conjunt,
      imprimeix un missatge d'error.
  * - <b>elimina_especie: </b>  Donat un identificador, elimina la espècie amb aquest identificador del conjunt. Si aquesta espècie no existeix,
      s'imprimeix un missatge d'error.
  * - <b>existe_especie: </b> Donat un identificador, imprimeix una indicació dient si l'espècie amb aquest identificador es troba al conjunt
  * - <b>lee_cjt_especies: </b> Es llegeix un conjunt d'espècies.
  * - <b>imprime_cjt_especies: </b> S'imprimeix el conjunt d'espècies.
  * - <b>tabla_distancias: </b> S'imprimeix la taula de distàncies entre espècies.
  * - <b>inicializa_clusters: </b> Inicialitza el conjunt de clústers amb el conjunt d'espècies actual i s'imprimeix la taula de distàncies
      entre clústers. Si el conjunt és buit, no es mostra cap informació.
  * - <b>ejecuta_paso_wpgma: </b> S'executa un pas de l'algoritme WPGMA sempre que la mida del conjunt sigui major que 1. Altrament
      s'imprimeix un missatge d'error.
  * - <b>imprime_cluster: </b> Donat un identificador, imprimeix el clúster amb aquest identificador. Si aquest clúster no existeix,
      es mostra un missatge d'error.
  * - <b>imprime_arbol_filogenetico: </b> Imprimeix l'arbre filogenètic per al conjunt d'espècies actual. Aquest arbre agrupa totes les espècies, resultat
      d'aplicar l'algoritme WPGMA. El contingut del conjunt de clústers es descarta i es reinicialitza amb el conjunt d'espècies
      actual. En cas que el conjunt sigui buit, es mostrarà un missatge d'error.
*/

int main() {
  int k; //s'usa pel calcul de les distàncies entre les especies
  cin >> k;
  Especie::valor_k(k);

  Cjt_especies cesp; //conjunt d'espècies
  Cjt_clusters cclus; //conjunt de clústers


  string op;
  cin >> op;
  while (op != "fin") {
    if (op == "crea_especie") {
      Especie e;
      e.llegir();
      cout << "# crea_especie " << e.consultar_idn() << ' ' << e.consultar_gen() << endl;
      pair<Especie, bool> p = cesp.existeix_especie(e.consultar_idn());
      if (p.second) cout << "ERROR: La especie " << e.consultar_idn() << " ya existe." << endl;
      else cesp.crea_especie(e);
    }

    else if (op == "obtener_gen") {
      string idn;
      cin >> idn;
      cout << "# obtener_gen " << idn << endl;
      if (cesp.existeix_especie(idn).second)
        cout << (cesp.existeix_especie(idn).first).consultar_gen() << endl;
      else cout << "ERROR: La especie " << idn << " no existe." << endl;
    }

    else if (op == "distancia") {
      string idn1, idn2;
      cin >> idn1 >> idn2;
      cout << "# distancia " << idn1 << ' ' << idn2 << endl;
      pair<Especie, bool> p1 = cesp.existeix_especie(idn1);
      pair<Especie, bool> p2 = cesp.existeix_especie(idn2);
      if (p1.second and p2.second)
        cout << (p1.first).distancia(p2.first) << endl;
      else if (not p1.second and not p2.second)
        cout << "ERROR: La especie " << idn1 << " y la especie " << idn2 << " no existen." << endl;
      else if (not p1.second) cout << "ERROR: La especie " << idn1 << " no existe." << endl;
      else cout << "ERROR: La especie " << idn2 << " no existe." << endl;
    }

    else if (op == "elimina_especie") {
      string idn;
      cin >> idn;
      cout << "# elimina_especie " << idn << endl;
      pair<Especie, bool> p = cesp.existeix_especie(idn);
      if (not p.second) cout << "ERROR: La especie " << idn << " no existe." << endl;
      else cesp.eliminar_especie(idn);
    }

    else if (op == "existe_especie") {
      string idn;
      cin >> idn;
      cout << "# existe_especie " << idn << endl;
      if (cesp.existeix_especie(idn).second)
        cout << "SI" << endl;
      else cout << "NO" << endl;
    }

    else if (op == "lee_cjt_especies") {
      cout << "# lee_cjt_especies" << endl;
      cesp.llegir_cjt_especies();
    }

    else if (op == "imprime_cjt_especies") {
      cout << "# imprime_cjt_especies" << endl;
      cesp.imprimir_cjt_especies();
    }

    else if (op == "tabla_distancias") {
      cout << "# tabla_distancias" << endl;
      cesp.imprimir_taula_distancies();
    }

    else if (op == "inicializa_clusters") {
      cout << "# inicializa_clusters" << endl;
      Cjt_clusters cclus_aux(cesp);
      cclus = cclus_aux;
      cclus.imprimir_taula_distancies();
    }

    else if (op == "ejecuta_paso_wpgma") {
      cout << "# ejecuta_paso_wpgma" << endl;
      if (cclus.mida() > 1) {
        cclus.executa_pas_wpgma();
        cclus.imprimir_taula_distancies();
      }
      else cout << "ERROR: num_clusters <= 1" << endl;
    }

    else if (op == "imprime_cluster") {
      string idn;
      cin >> idn;
      cout << "# imprime_cluster " << idn << endl;
      if (cclus.existeix_cluster(idn)) {
        Cluster c = cclus.consultar_cluster(idn);
        cclus.imprimir_cluster(c);
        cout << endl;
      }
      else cout << "ERROR: El cluster " << idn << " no existe."<< endl;
    }

    else if (op == "imprime_arbol_filogenetico") {
      cout << "# imprime_arbol_filogenetico" << endl;
      Cjt_clusters cclus_aux(cesp);
      cclus = cclus_aux;
      if (cclus.mida() != 0) cclus.imprimir_arbre_filogenetic();
      else cout << "ERROR: El conjunto de clusters es vacio." << endl;
    }

    cout << endl;
    cin >> op;
  }
}
