/** @file Cjt_especies.cc
  @brief Codi de la clase Cjt_especies
*/

#include "Cjt_especies.hh"

//Constructora
Cjt_especies::Cjt_especies(){}

//Destructora
Cjt_especies::~Cjt_especies(){};

//Modificadores
void Cjt_especies::primer() {
  it = mesp.begin();
}

void Cjt_especies::crea_especie(Especie e) {
  string aux_idn = e.consultar_idn();
  mesp[aux_idn] = e;

  //actualitzar taula distàncies
  for (map<string, Especie>::iterator it1 = mesp.begin(); it1 != mesp.end(); it1++) {
    if ((it1->first) < aux_idn) distancies[it1->first][aux_idn] = e.distancia(it1->second);
    else if ((it1->first) > aux_idn) distancies[aux_idn][it1->first] = e.distancia(it1->second);
  }
}

void Cjt_especies::eliminar_especie(string idn) {
  //eliminem del conjunt d'espècies
  mesp.erase(idn);

  //eliminem l'espècie amb identificador "idn" de la taula de distàncies
  distancies.erase(idn);
  map<string, Especie>::const_iterator it = mesp.begin();
  while (it != mesp.end() and it->first < idn) {
    string aux = it->first;
    distancies[aux].erase(idn);
    it++;
  }
}

//Consultores
int Cjt_especies::mida() {
  return mesp.size();
}

string Cjt_especies::proper() {
  string aux = it->first;
  ++it;
  return aux;
}

bool Cjt_especies::final() {
  return it == mesp.end();
}

double Cjt_especies::consultar_distancia(string idn1, string idn2) {
  if (idn1 < idn2) return distancies[idn1][idn2];
  else if (idn1 > idn2) return distancies[idn2][idn1];
  return 0;
}

pair<Especie, bool> Cjt_especies::existeix_especie(string idn) {
  map<string, Especie>::const_iterator it = mesp.find(idn);
  if (it != mesp.end())
    return make_pair(it->second, true);
  Especie e;
  return make_pair(e, false);
}

//Lectura i escriptura
void Cjt_especies::llegir_cjt_especies() {
  int n; cin >> n;
  mesp.clear();
  distancies.clear();
  for (int i = 0; i < n; i++) {
    Especie e;
    e.llegir();
    crea_especie(e);
  }
}

void Cjt_especies::imprimir_cjt_especies() {
  for (map<string, Especie>::const_iterator it = mesp.begin(); it != mesp.end(); it++)
    (it->second).escriure();
}

void Cjt_especies::imprimir_taula_distancies() {
  for (map<string, Especie>::const_iterator it = mesp.begin(); it != mesp.end(); it++) {
    cout << it->first << ":";
    for (map<string, double>::const_iterator it1 = distancies[it->first].begin(); it1 != distancies[it->first].end(); it1++)
      cout << ' ' << it1->first << " (" << it1->second << ')';
    cout << endl;
  }
}
