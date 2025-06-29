#ifndef _ARVORE_HPP_
#define _ARVORE_HPP_
#include<vector>
#include<string>
using namespace std;

class No_arv_parse {
public:
  string simb;
  int regra; // -1 = terminal
  string dado_extra;
  vector<No_arv_parse *> filhos;
  No_arv_parse();
  static void debug_no(No_arv_parse * no);
};

class Arvore_parse {
public:
  No_arv_parse * raiz;
  Arvore_parse(No_arv_parse * rr);
  void imprime(No_arv_parse * no);
  void debug();
};

#endif
