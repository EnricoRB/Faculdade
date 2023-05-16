#ifndef POLINOMIO_H
#define POLINOMIO_H
#include <cmath>
#include <iostream>
#include <unistd.h>
using namespace std;

struct No {
  No *elo;    // ponteiro para o próximo nó da lista
  char letra; // letra que representa o coeficiente do termo
  float K;    // coeficiente do termo
  int xp;     // expoente do termo
};

struct LERP {
  No *inicio; // ponteiro para o primeiro nó da lista
  No *fim;    // ponteiro para o último nó da lista
};

void inicializarLERP(
    LERP &lista) { // "LERP = Lista Encadeada Resolvedora de Polinomios"
  lista.inicio = NULL;
  lista.fim = NULL;
}

void inserirLERP(LERP &lista, char letra, float K, int xp) {
  No *novo = new No; // cria um novo nó para inserir na lista
  novo->letra = letra; // 
  novo->K = K;
  novo->xp = xp;
  novo->elo = NULL; // o novo nó não tem próximo

  if (lista.inicio == NULL) { // se a lista estiver vazia
    lista.inicio = novo;
    lista.fim = novo;
  } else { // se a lista já tiver elementos
    lista.fim->elo = novo;
    lista.fim = novo;
  }
}

void mostrarLERP(LERP lista, char frase[]) {
  cout << frase << ": "; // exibe uma mensagem antes de mostrar a lista
  if (lista.inicio == NULL)
    cout << "A Lista está vazia."
         << endl; // se a lista estiver vazia, exibe uma mensagem

  No *aux = lista.inicio; // ponteiro auxiliar para percorrer a lista
  while (aux != NULL) {   // percorre a lista enquanto não chegar ao final
    if (aux == lista.inicio) {
      cout << aux->K << aux->letra << "^" << aux->xp; // primeiro termo, sem sinal
    } else {
      if (aux->K > 0) {
        cout << " + " << aux->K << aux->letra << "^"  << aux->xp; // coeficiente positivo
      } else if (aux->K < 0) {
        cout << " - " << -aux->K << aux->letra << "^" << aux->xp; // coeficiente negativo
      }
    }
    aux = aux->elo; // avança para o próximo nó

    // verifica se o coeficiente do próximo termo é igual a zero e, caso positivo, pula para o próximo termo
    while (aux != NULL && aux->K == 0) {
      aux = aux->elo;
    }
  }
}

void removerLERP(LERP &lista, char letra, float K, int xp) {
  No *ant = NULL;           // ponteiro para o nó anterior
  No *atual = lista.inicio; // ponteiro para o nó atual

  // Percorre a lista até encontrar o elemento a ser removido
  while (atual != NULL && (atual->letra != letra || atual->K != K || atual->xp != xp)) {
    ant = atual;
    atual = atual->elo;
  }

  if (atual == NULL) { // Se não encontrou o elemento, exibe mensagem e retorna
    cout << "Elemento não encontrado na lista." << endl;
    return;
  }

  if (ant == NULL) { // Se o elemento a ser removido é o primeiro da lista
    lista.inicio = atual->elo;
  } else {
    ant->elo = atual->elo;
  }

  if (lista.fim == atual) { // Se o elemento a ser removido é o último da lista
    lista.fim = ant;
  }

  delete atual; // Libera a memória ocupada pelo nó a ser removido
}

void multiplicarPorEscalar(LERP &lista, float escalar) {
  No *aux = lista.inicio;
  while (aux != NULL) { // Enquanto aux for diferente de NULL
    aux->K *= escalar;  // Multiplica o coeficiente pelo escalar
    aux = aux->elo;     // Avança para o próximo nó
  }
}

bool verificarExpoente(LERP lista, int xp) {
  No *aux = lista.inicio;
  while (aux != NULL) { // Enquanto aux for diferente de NULL
    if (aux->xp == xp)
      return true; // Verifica se o termo inserido é o mesmo de algum termo do polinomio
    aux = aux->elo;
  }
  return false; // Caso o termo não exista, retorna falso
}

LERP somarLERP(LERP lista1, LERP lista2) {
  LERP listaResultado;  // cria uma nova LERP para armazenar a soma das duas LERPs de entrada
  inicializarLERP(listaResultado);  // inicializa a nova LERP vazia
  // cria ponteiros para percorrer as listas de entrada
  No *aux1 = lista1.inicio;
  No *aux2 = lista2.inicio;

  // percorre as duas LERPs de entrada
  while (aux1 != NULL || aux2 != NULL) {  // inicializa variáveis para armazenar os valores de cada termo da LERP
    char letra;
    float K;
    int xp;

    // verifica se a primeira lista já acabou
    if (aux1 == NULL) {  // se a primeira lista já acabou, insere o termo atual da segunda lista
      letra = aux2->letra;
      K = aux2->K;
      xp = aux2->xp;
      aux2 = aux2->elo;  // avança o ponteiro da segunda lista para o próximo termo
    } else if (aux2 == NULL) {
      // se a segunda lista já acabou, insere o termo atual da primeira lista
      letra = aux1->letra;
      K = aux1->K;
      xp = aux1->xp;
      aux1 = aux1->elo;  // avança o ponteiro da primeira lista para o próximo termo
    } else if (aux1->xp == aux2->xp) { // se os expoentes dos termos das duas listas são iguais, realiza a soma dos coeficientes
      letra = aux1->letra;
      K = aux1->K + aux2->K;
      xp = aux1->xp;
      aux1 = aux1->elo;  // avança o ponteiro da primeira lista para o próximo termo
      aux2 = aux2->elo;  // avança o ponteiro da segunda lista para o próximo termo
    } else if (aux1->xp > aux2->xp) { // se o expoente do termo atual da primeira lista é maior que o da segunda lista, insere o termo da primeira lista
      letra = aux1->letra;
      K = aux1->K;
      xp = aux1->xp;
      aux1 = aux1->elo;  // avança o ponteiro da primeira lista para o próximo termo
    } else { // caso contrário, insere o termo da segunda lista
      letra = aux2->letra;
      K = aux2->K;
      xp = aux2->xp;
      aux2 = aux2->elo;  // avança o ponteiro da segunda lista para o próximo termo
    }

    // verifica se o coeficiente calculado é diferente de zero
    if (K != 0) {
      // se for diferente de zero, insere o novo termo na lista resultado
      inserirLERP(listaResultado, letra, K, xp);
    }
  }

  // retorna a lista resultado
  return listaResultado;
}

//pk= subtração ajustada, feito igual a soma, porém invertendo o sinal

LERP subtrairLERP(LERP lista1, LERP lista2) {
  LERP listaResultado;  // cria uma nova LERP para armazenar a subtração das duas LERPs de entrada
  inicializarLERP(listaResultado);  // inicializa a nova LERP vazia

  // cria ponteiros para percorrer as listas de entrada
  No *aux1 = lista1.inicio;
  No *aux2 = lista2.inicio;

  // percorre as duas listas até que uma delas chegue ao final
  while (aux1 != NULL && aux2 != NULL) { // verifica qual termo tem expoente maior
    if (aux1->xp > aux2->xp) {
      inserirLERP(listaResultado, aux1->letra, aux1->K, aux1->xp);
      aux1 = aux1->elo;
    } else if (aux1->xp < aux2->xp) {
      inserirLERP(listaResultado, aux2->letra, -aux2->K, aux2->xp);
      aux2 = aux2->elo;
    } else { // se os expoentes forem iguais, subtrai os coeficientes
      float K = aux1->K - aux2->K;
      if (K != 0) { // se o resultado da subtração for diferente de zero, insere na lista
        inserirLERP(listaResultado, aux1->letra, K, aux1->xp);
      }
      aux1 = aux1->elo;
      aux2 = aux2->elo;
    }
  }

  // adiciona os termos restantes da primeira lista (se houver)
  while (aux1 != NULL) {
    inserirLERP(listaResultado, aux1->letra, aux1->K, aux1->xp);
    aux1 = aux1->elo;
  }

  // adiciona os termos restantes da segunda lista (se houver)
  while (aux2 != NULL) {
    inserirLERP(listaResultado, aux2->letra, -aux2->K, aux2->xp);
    aux2 = aux2->elo;
  }

  return listaResultado;
}

LERP multiplicarLERP(LERP lista1, LERP lista2) {
  LERP resultado;
  inicializarLERP(resultado);

  No *aux1 = lista1.inicio;
  while (aux1 != NULL) { // Percorre cada termo do primeiro polinômio
    No *aux2 = lista2.inicio;
    while (aux2 != NULL) {          // Percorre cada termo do segundo polinômio
      float K = aux1->K * aux2->K;  // Multiplica os coeficientes
      int xp = aux1->xp + aux2->xp; // Soma os expoentes
      char letra = aux1->letra;
      if (aux2->letra != '1') {
        letra =
            aux2->letra; // Se o segundo termo não for constante, usa sua letra
      }
      inserirLERP(resultado, letra, K,
                  xp); // Insere o termo resultante no polinômio resultado
      aux2 = aux2->elo;
    }
    aux1 = aux1->elo;
  }

  return resultado;
}

float calcularPolinomio(LERP lista, float x) {
  No *aux = lista.inicio; // ponteiro auxiliar para percorrer a lista
  float resultado = 0.0; // acumulador para o resultado

  while (aux != NULL) { // percorre a lista enquanto não chegar ao final
    float termo = aux->K * pow(x, aux->xp); // calcula o valor do termo
    resultado += termo; // acumula o resultado

    // exibe a representação do termo e o valor parcial do polinômio até aquele momento
    if (aux == lista.inicio) {
      cout << aux->K << aux->letra << "^" << aux->xp << " = " << termo;
    } else {
      if (aux->K > 0) {
        cout << " + " << aux->K << aux->letra << "^" << aux->xp << " = " << termo;
      } else if (aux->K < 0) {
        cout << " - " << -aux->K << aux->letra << "^" << aux->xp << " = " << termo;
      }
    }

    aux = aux->elo; // avança para o próximo nó

    // verifica se o coeficiente do próximo termo é igual a zero e, caso positivo, pula para o próximo termo
    while (aux != NULL && aux->K == 0) {
      aux = aux->elo;
    }
  }

  cout << "\nResultado final: ";

  return resultado;
}


void mostrarMenu() {
  cout << "\nCalculadora de polinômios:" << endl;
  cout << "1. Verificar expoente" << endl;
  cout << "2. Somar polinômios" << endl;
  cout << "3. Multiplicar polinômios" << endl;
  cout << "4. Subtrair polinômios" << endl;
  cout << "5. Multiplicar por escalar (-2)" << endl;
  cout << "6. Determinar o valor númerico" << endl;
  cout << "0. Sair" << endl;
  cout << "\nEscolha uma opção: ";
}


void realizarOperacao(int opcao) {
  system("clear");
  LERP polinomio1, polinomio2, resultado;
  float K, valorVariavel;
  int x, escalar, verificaXP;
  char resposta;

  switch (opcao) {
  case 0:
    cout << "Programa encerrado!" << endl;
    cout << "Creditos: Enrico Belo Ribeiro & Paulo Kunrath" << endl;
    return;

  case 1:
    inicializarLERP(polinomio1);
    inicializarLERP(polinomio2);

    cout << "------------------------------------------------------" << endl;
    cout << "Definiremos por padrão a variavel dos monomios como X. " << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "- Primeiro Polinomio -" << endl << endl;

    // Looping para inserir termos no primeiro polinômio
    do {
    cout << "Deseja inserir um monomio no primeiro polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << "\n Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio1, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "\n Opção inválida! Por favor, escolha S ou N. \n" << endl;
    }
    } while (resposta != 'N' && resposta != 'n');

    mostrarLERP(polinomio1, "\nPolinômio 1");
    cout << endl << "-----------------------------------" << endl;
    cout << "- Segundo Polinomio -" << endl << endl;

    // Looping para inserir termos no segundo polinômio
    do {
    cout << "Deseja inserir um monomio no segundo polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << " Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio2, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "Opção inválida! Por favor, escolha S ou N." << endl;
    }
    } while (resposta != 'N' && resposta != 'n');
    mostrarLERP(polinomio2, "\nPolinômio 2");
    cout << endl << "-----------------------------------" << endl;

    cout << "\nDigite um expoente para verificar se existe no polinomio 1: ";
    cin >> verificaXP;
    if (verificarExpoente(polinomio1, verificaXP)) {
      cout << "Termo existe!\n" << endl;
    } else {
      cout << "Termo não existe!\n" << endl;
    }

    cout << "\nDigite um expoente para verificar se existe no polinomio 2: ";
    cin >> verificaXP;
    if (verificarExpoente(polinomio2, verificaXP)) {
      cout << "Termo existe!\n" << endl;
    } else {
      cout << "Termo não existe!\n" << endl;
    }
    cout << "-----------------------------------" << endl;
    break;

  case 2:
    inicializarLERP(polinomio1);
    inicializarLERP(polinomio2);
    cout << "-----------------------------------" << endl;
    cout << "Definiremos por padrão a variavel dos monomios como X. " << endl;
    cout << "-----------------------------------" << endl;
    cout << "- Primeiro Polinomio -" << endl << endl;

    // Looping para inserir termos no primeiro polinômio
    do {
    cout << "Deseja inserir um monomio no primeiro polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
      cout << "\n Insira o Coeficiente do monomio: ";
      cin >> K;
      cout << endl;
      cout << " Insira o Expoente do monomio: ";
      cin >> x;
      cout << endl;
      inserirLERP(polinomio1, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "\n Opção inválida! Por favor, escolha S ou N. \n" << endl;
    }
    } while (resposta != 'N' && resposta != 'n');

    mostrarLERP(polinomio1, "\nPolinômio 1");
    cout << endl << "-----------------------------------" << endl;
    cout << "- Segundo Polinomio -" << endl << endl;

    // Looping para inserir termos no segundo polinômio
    do {
    cout << "Deseja inserir um monomio no segundo polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << " Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio2, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "Opção inválida! Por favor, escolha S ou N." << endl;
    }
    } while (resposta != 'N' && resposta != 'n');
    mostrarLERP(polinomio2, "\nPolinômio 2");
    cout << endl << "-----------------------------------" << endl;

    resultado = somarLERP(polinomio1, polinomio2);
    mostrarLERP(resultado, "Resultado da soma: ");
    cout << endl << "-----------------------------------" << endl;
    break;
    
  case 3:
    inicializarLERP(polinomio1);
    inicializarLERP(polinomio2);
    cout << "-----------------------------------" << endl;
    cout << "Definiremos por padrão a variavel dos monomios como X. " << endl;
    cout << "-----------------------------------" << endl;
    cout << "- Primeiro Polinomio -" << endl << endl;

    // Looping para inserir termos no primeiro polinômio
    do {
    cout << "Deseja inserir um monomio no primeiro polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << " Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio1, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "\n Opção inválida! Por favor, escolha S ou N. \n" << endl;
    }
    } while (resposta != 'N' && resposta != 'n');

    mostrarLERP(polinomio1, "\nPolinômio 1");
    cout << endl << "-----------------------------------" << endl;
    cout << "- Segundo Polinomio -" << endl << endl;

    // Looping para inserir termos no segundo polinômio
    do {
    cout << "Deseja inserir um monomio no segundo polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << " Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio2, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "Opção inválida! Por favor, escolha S ou N." << endl;
    }
    } while (resposta != 'N' && resposta != 'n');
    mostrarLERP(polinomio2, "\nPolinômio 2");
    cout << endl << "-----------------------------------" << endl;

    resultado = multiplicarLERP(polinomio1, polinomio2);
    mostrarLERP(resultado, "\nResultado da multiplicação: ");
    cout << endl <<"-----------------------------------" << endl;
    break;
    
  case 4:
    inicializarLERP(polinomio1);
    inicializarLERP(polinomio2);
    cout << "-----------------------------------" << endl;
    cout << "Definiremos por padrão a variavel dos monomios como X. " << endl;
    cout << "-----------------------------------" << endl;
    cout << "- Primeiro Polinomio -"<< endl << endl;

    // Looping para inserir termos no primeiro polinômio
    do {
    cout << "Deseja inserir um monomio no primeiro polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << " Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio1, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "\n Opção inválida! Por favor, escolha S ou N. \n" << endl;
    }
    } while (resposta != 'N' && resposta != 'n');

    mostrarLERP(polinomio1, "\nPolinômio 1");
    cout << endl << "-----------------------------------" << endl;
    cout << "- Segundo Polinomio -" << endl << endl;

    // Looping para inserir termos no segundo polinômio
    do {
    cout << "Deseja inserir um monomio no segundo polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << "Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio2, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "Opção inválida! Por favor, escolha S ou N." << endl;
    }
    } while (resposta != 'N' && resposta != 'n');
    mostrarLERP(polinomio2, "\nPolinômio 2");
    cout << endl << "-----------------------------------" << endl;

    resultado = subtrairLERP(polinomio1, polinomio2);
    mostrarLERP(resultado, "Resultado da Subtração: ");
    cout << endl <<"-----------------------------------"<< endl;
    break;

  case 5:
    inicializarLERP(polinomio1);
    cout << "-----------------------------------" << endl;
    cout << "Definiremos por padrão a variavel dos monomios como X. " << endl;
    cout << "-----------------------------------" << endl;
    cout << "- Primeiro Polinomio -" << endl << endl;

    // Looping para inserir termos no primeiro polinômio
    do {
    cout << "Deseja inserir um monomio no primeiro polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << " Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio1, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "\n Opção inválida! Por favor, escolha S ou N. \n" << endl;
    }
    } while (resposta != 'N' && resposta != 'n');

    mostrarLERP(polinomio1, "\nPolinômio 1");
    cout << "\nEscalar que irá multiplicar o polinomio: ";
    cin >> escalar;
    cout << endl<<"-----------------------------------"<< endl;

    multiplicarPorEscalar(polinomio1, escalar);
    mostrarLERP(polinomio1, "\nPolinomio multiplicado por escalar: ");

    cout << endl << "-----------------------------------"<< endl;
    break;

  case 6:
    // introduzir o calculo de valor númerico abaixo
    LERP polinomio;
    inicializarLERP(polinomio);
    cout << "-----------------------------------" << endl;
    cout << "Definiremos por padrão a variavel dos monomios como X. " << endl;
    cout << "-----------------------------------" << endl;
    cout << "- Primeiro Polinomio -"<< endl << endl;

    // Looping para inserir termos no primeiro polinômio
    do {
    cout << "Deseja inserir um monomio no polinomio? (S/N) ";
    cin >> resposta;
    if (resposta == 'S' || resposta == 's') {
        cout << "\n Insira o Coeficiente do monomio: ";
        cin >> K;
        cout << endl;
        cout << "\n Insira o Expoente do monomio: ";
        cin >> x;
        cout << endl;
        inserirLERP(polinomio, 'x', K, x);
    } else if (resposta == 'N' || resposta == 'n') {
        cout << "Lista completa!" << endl;
    } else {
        cout << "\n Opção inválida! Por favor, escolha S ou N. \n" << endl;
    }
    } while (resposta != 'N' && resposta != 'n');
    mostrarLERP(polinomio, "\nPolinômio");
    cout << endl << "-----------------------------------" << endl;
    cout << "Valor da variavel 'x': ";
    cin >> valorVariavel;
    cout << endl <<"-----------------------------------"<< endl;
    cout << "Valor numérico definido para a varival 'x' foi: " << valorVariavel << endl;
    cout << "Valor numérico do polinomio é: " << calcularPolinomio(polinomio, valorVariavel) << endl;
    cout <<"-----------------------------------"<< endl;
    break;

  default:
    cout << "Opção inválida." << endl;
 }
}

#endif