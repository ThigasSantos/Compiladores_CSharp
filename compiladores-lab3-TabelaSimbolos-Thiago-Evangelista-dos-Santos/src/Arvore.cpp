#include "Arvore.hpp"
#include<iostream>
#include "debug-util.hpp"
using namespace std;

No_arv_parse::No_arv_parse() {
  simb = "";
  regra = -1; //terminal
  dado_extra = "";
  filhos.clear();
}

void debug_inicio_no(No_arv_parse * no) {
  if (no == NULL) {
    cerr << "[NO_NULO]";
    return;
  }
  cerr << "[" <<no->simb<<","<< no->regra << ","<<no->dado_extra << ":";
}

void debug_no_tab3(No_arv_parse *no, int tab) {
  tab3(tab);
  debug_inicio_no(no);
  if (no == NULL) {
    cerr << endl;
    return;
  }
  if (no->filhos.size() > 0) cerr << endl;
  for (int i = 0; i < no->filhos.size(); ++i) {
    debug_no_tab3(no->filhos[i], tab+1);
  }
  if (no->filhos.size() > 0) tab3(tab);
  cerr << "]" << endl;
}

void No_arv_parse::debug_no(No_arv_parse *no) {
  debug_no_tab3(no, 0);
}

Arvore_parse::Arvore_parse(No_arv_parse * rr) {
  raiz = rr;
}


void Arvore_parse::imprime(No_arv_parse * no) {
  No_arv_parse::debug_no(no);
}

void Arvore_parse::debug(){
  imprime(raiz);
}



