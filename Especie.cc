/** @file Especie.cc
  @brief Codi de la clase Especie
*/

#include "Especie.hh"

int Especie::K = 0;

void Especie::fer_kmer() {
  int sz = gen.size() - K +1;
  for (int i = 0; i < sz; i++) {
    string subseq = "";
    for (int j = i; j < i+K; j++)
      subseq += gen[j];
    map<string, int>::iterator it = kmer.find(subseq);
    if (it == kmer.end())
      kmer[subseq] = 1;
    else kmer[subseq]++;
  }
}

//Constructores
Especie::Especie() {}

Especie::Especie(string g, string id) {
  gen = g;
  idn = id;
  fer_kmer();
}

//Destructora
Especie::~Especie(){};

//Modificadores
double Especie::distancia(Especie e) {
  //num = intersecció
  //den = unió
  int num = 0, den = 0;
  map<string, int>::const_iterator it1 = kmer.begin();
  map<string, int>::const_iterator it2 = e.kmer.begin();

  while (it1 != kmer.end() and it2 != e.kmer.end()) {
    if (it1->first == it2->first) {
      if (it1->second <= it2->second) {
        num += it1->second;
        den += it2->second;
      }
      else {
        num += it2->second;
        den += it1->second;
      }
      it1++;
      it2++;
    }
    else if (it1->first > it2->first) {
      den += it2->second;
      it2++;
    }
    else {
      den += it1->second;
      it1++;
    }
  }

  while (it1 != kmer.end()) {
    den += it1->second;
    it1++;
  }

  while (it2 != e.kmer.end()) {
    den += it2->second;
    it2++;
  }

  double distancia = (double)num/den;
  return (1-distancia)*100;
}

void Especie::valor_k(int k) {
  Especie::K = k;
}

//Consultores
string Especie::consultar_idn() {
  return idn;
}

string Especie::consultar_gen() {
  return gen;
}

//Lectura i escriptura
void Especie::llegir() {
  cin >> idn >> gen;
  fer_kmer();
}

void Especie::escriure() const {
  cout << idn << ' ' << gen << endl;
}
