/** @file Cjt_clusters.cc
  @brief Codi de la clase Cjt_clusters
*/

#include "Cjt_clusters.hh"

void Cjt_clusters::recalcular_dist_min() {
  //li tornem a donar el valor 101 per a evitar errors
  dist_min = 101;

  map<string, map<string, double> >::const_iterator it = distancies.begin();
  while (it != distancies.end() and dist_min != 0) {
    //si dist_min = 0 vol dir que no hi haura cap distància menor
    map<string, double>::const_iterator it2 = (it->second).begin();
    while (it2 != (it->second).end() and dist_min != 0) {
      if ((it2->second) < dist_min) {
        idn_min1 = it->first;
        idn_min2 = it2->first;
        dist_min = it2->second;
      }
      it2++;
    }
    it++;
  }
}

//Constructores
Cjt_clusters::Cjt_clusters(){}

Cjt_clusters::Cjt_clusters(Cjt_especies cesp) {
  //inicialitzem el conjunt de clústers
  cesp.primer();
  while (not cesp.final()) {
    string idn = cesp.proper();
    pair<string, double> p = make_pair(idn, 0);
    Cluster c(p);
    mclust[idn] = c;
  }

  //inicialitzem la taula de distàncies
  for (map<string, Cluster>::const_iterator it = mclust.begin(); it != mclust.end(); it++) {
    map<string, Cluster>::const_iterator it1 = it;
    ++it1;
    while (it1 != mclust.end()) {
      distancies[it->first][it1->first] = cesp.consultar_distancia(it->first, it1->first);

      //busquem els dos clústers a distància mínima
      if (cesp.consultar_distancia(it->first, it1->first) < dist_min) {
        dist_min = cesp.consultar_distancia(it->first, it1->first);
        idn_min1 = it->first;
        idn_min2 = it1->first;
      }
      ++it1;
    }
  }
}

//Destructora
Cjt_clusters::~Cjt_clusters(){};

//Modificadores
void Cjt_clusters::executa_pas_wpgma() {
  //concatenació de strings
  string conc = idn_min1 + idn_min2;

  //calculem la distància del nou node del arbre i creem el nou clúster
  pair<string, double> p = make_pair(conc, distancies[idn_min1][idn_min2]/2);
  BinTree< pair<string, double> > btree(p, mclust[idn_min1], mclust[idn_min2]);

  //afegim el nou clúster i eliminem els antics
  mclust[conc] = btree;
  mclust.erase(idn_min1);
  mclust.erase(idn_min2);

  //calculem les noves distàncies
  for (map<string, Cluster>::const_iterator it = mclust.begin(); it != mclust.end(); it++) {
    double dist = 0;
    if (it->first > idn_min1) dist += distancies[idn_min1][it->first];
    else if (it-> first < idn_min1) {
      dist += distancies[it->first][idn_min1];

      //eliminem la distància amb el clúster antic perquè ja no ens interessa
      distancies[it->first].erase(idn_min1);
    }

    if (it->first > idn_min2) dist += distancies[idn_min2][it->first];
    else if (it->first < idn_min2) {
      dist += distancies[it->first][idn_min2];

      //eliminem la distància amb el clúster antic perquè ja no ens interessa
      distancies[it->first].erase(idn_min2);
    }

    dist /= 2;
    if (it->first > conc) distancies[conc][it->first] = dist;
    else if (it->first < conc) distancies[it->first][conc] = dist;
  }

  //eliminem les distàncies dels clústers antics
  distancies.erase(idn_min1);
  distancies.erase(idn_min2);

  //busquem els dos clústers a menor distancia
  recalcular_dist_min();
}

//Consultores
int Cjt_clusters::mida() {
  return mclust.size();
}

bool Cjt_clusters::existeix_cluster(string idn) {
  map<string, Cluster>::const_iterator it = mclust.find(idn);
  return it != mclust.end();
}

Cluster Cjt_clusters::consultar_cluster(string idn) {
  return mclust[idn];
}

//Lectura i escriptura
void Cjt_clusters::imprimir_cluster(const Cluster &clust) {
  if (clust.empty()) return;
  cout << '[';
  if (clust.left().empty() and clust.right().empty()) cout << clust.value().first << ']';
  else {
    cout << '(' << clust.value().first << ", " << clust.value().second << ") ";
    imprimir_cluster(clust.left());
    imprimir_cluster(clust.right());
    cout << ']';
  }
}

void Cjt_clusters::imprimir_arbre_filogenetic() {
  while (mclust.size() != 1)
    executa_pas_wpgma();
  imprimir_cluster((mclust.begin())->second);
  cout << endl;
}

void Cjt_clusters::imprimir_taula_distancies() {
  for (map<string, Cluster>::const_iterator it = mclust.begin(); it != mclust.end(); it++) {
    cout << it->first << ":";
    for (map<string, double>::const_iterator it1 = distancies[it->first].begin(); it1 != distancies[it->first].end(); it1++)
      cout << ' ' << it1->first << " (" << it1->second << ')';
    cout << endl;
  }
}
