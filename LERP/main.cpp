#include <iostream>
#include "polinomio.h"
#include <cmath>
#include <unistd.h>
using namespace std;
#define TAM 50


int main() {

  int xp, opcao;

  do {
    mostrarMenu();
    cin >> opcao;
    realizarOperacao(opcao);
  } while (opcao != 0);

  return 0;
}