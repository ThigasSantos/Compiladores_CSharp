#ifndef ID_H
#define ID_H
#include<string>
#include "../Arvore.hpp"

using namespace std;

class ID {
public:
  string nome;
  static ID* extrai_ID(No_arv_parse* no);
};

#endif
