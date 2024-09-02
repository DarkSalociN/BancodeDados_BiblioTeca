#include <iostream>
#include <new>
#include <string>
#include <stdlib.h>

using namespace std;

// Função para limpar a tela (específica para Windows)
void limparTela() {
    system("CLS"); // Use "clear" se estiver no Linux
}

// Estrutura do nó da árvore binária de busca
typedef struct Nodo{
    int valor;                    // Valor armazenado no nó
    struct Nodo *direita, *esquerda; // Ponteiros para os filhos da direita e esquerda
} NodoArvore;

// Função para inserir um novo nó na árvore binária de busca
NodoArvore* inserirNodo(NodoArvore *raiz, int numeroInserir) {
    // Se a raiz está vazia, cria um novo nó e o retorna
    if (raiz == NULL) {
        NodoArvore *novoNodo = new NodoArvore;
        novoNodo->valor = numeroInserir;
        novoNodo->esquerda = NULL;
        novoNodo->direita = NULL;
        return novoNodo;
    } else {
        // Insere recursivamente na sub-árvore esquerda ou direita, dependendo do valor
        if (numeroInserir < raiz->valor)
            raiz->esquerda = inserirNodo(raiz->esquerda, numeroInserir);
        else
            raiz->direita = inserirNodo(raiz->direita, numeroInserir);
        return raiz;
    }
}

// Função para imprimir os valores inseridos na árvore (pré-ordem)
void imprimirPreOrdem(NodoArvore *raiz) {
    if (raiz) {
        cout << raiz->valor << " ";  // Imprime o valor do nó
        imprimirPreOrdem(raiz->esquerda); // Recursivamente imprime a subárvore esquerda
        imprimirPreOrdem(raiz->direita);  // Recursivamente imprime a subárvore direita
    }
}

// Função para imprimir a árvore em ordem (em-ordem)
void imprimirEmOrdem(NodoArvore *raiz) {
    if (raiz) {
        imprimirEmOrdem(raiz->esquerda); // Recursivamente imprime a subárvore esquerda
        cout << raiz->valor << " ";  // Imprime o valor do nó
        imprimirEmOrdem(raiz->direita);  // Recursivamente imprime a subárvore direita
    }
}

// Função para buscar um valor na árvore binária de busca
NodoArvore* buscar(NodoArvore *raiz, int chave) {
    if (raiz) {
        if (chave == raiz->valor)
            return raiz;  // Retorna o nó se o valor for encontrado
        else if (chave < raiz->valor)
            return buscar(raiz->esquerda, chave); // Busca na subárvore esquerda
        else    
            return buscar(raiz->direita, chave);  // Busca na subárvore direita
    }
    return NULL;  // Retorna NULL se o valor não for encontrado
}

// Função para remover um nó da árvore binária de busca
NodoArvore* removerNodo(NodoArvore *raiz, int chave) {
    if (raiz == NULL) {
        cout << "Valor Não Encontrado" << endl;
        return NULL;
    } else {
        if (raiz->valor == chave) {
            // Caso 1: O nó é uma folha (não tem filhos)
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                delete raiz;  // Libera o nó
                cout << "Elemento folha removido: " << chave << endl;
                return NULL;
            }
            // Caso 2: O nó tem dois filhos
            else if (raiz->esquerda != NULL && raiz->direita != NULL) {
                NodoArvore *aux = raiz->esquerda;
                // Encontrar o maior valor da subárvore esquerda
                while (aux->direita != NULL)
                    aux = aux->direita;
                // Substituir o valor do nó a ser removido pelo maior valor encontrado
                raiz->valor = aux->valor;
                // Remover o nó duplicado na subárvore esquerda
                raiz->esquerda = removerNodo(raiz->esquerda, aux->valor);
                cout << "Removido nó com 2 filhos: " << chave << endl;
                return raiz;
            }
            // Caso 3: O nó tem um filho
            else {
                NodoArvore *aux = (raiz->esquerda != NULL) ? raiz->esquerda : raiz->direita; // Escolhe o filho que não é NULL
                delete raiz;  // Libera o nó
                cout << "Elemento com 1 filho removido: " << chave << endl;
                return aux;
            }
        } else {
            // Percorrer a árvore para encontrar o nó a ser removido
            if (chave < raiz->valor)
                raiz->esquerda = removerNodo(raiz->esquerda, chave); // Remove recursivamente da subárvore esquerda
            else
                raiz->direita = removerNodo(raiz->direita, chave);  // Remove recursivamente da subárvore direita
            return raiz;
        }
    }
}

int main() {
    NodoArvore *nodoEncontrado, *raiz = NULL;
    int opcao, chave;

    do {
        // Menu de interface para o usuário
        cout << "           LóguiTéchi" << endl;
        cout << "Sistema de armazenamento de Arquivos\n" << endl;
        cout << "Escolha uma opção abaixo." << endl; 
        cout << "\t1 - Inserir o ID do Produto\n\t2 - Imprimir pelo ID do produto\n\t3 - Buscar pelo ID do Produto\n\t4 - Remover pelo ID do Produto\n\t0 - Sair" << endl;
        cin >> opcao;

        switch (opcao) {
        case 1:
            // Inserção de um novo valor na árvore
            cout << "Digite o ID do produto:" << endl;
            cin >> chave;
            raiz = inserirNodo(raiz, chave);
            break;
        case 2:
            // Impressão dos valores da árvore
            cout << "Valores Inseridos:" << endl; //(Pré-Ordem)
            imprimirPreOrdem(raiz);
            cout << "\n";
            cout << "Árvore Ordenada:" << endl; //(Em-Ordem)
            imprimirEmOrdem(raiz);
            cout << "\n";
            break;
        case 3:
            // Busca de um valor na árvore
            cout << "Digite um ID a ser procurado:" << endl;
            cin >> chave;
            nodoEncontrado = buscar(raiz, chave);
            if (nodoEncontrado)
                cout << "\nValor Encontrado: " << nodoEncontrado->valor << endl;
            else
                cout << "Valor Não Encontrado." << endl;

            break;
        case 4:
            // Remoção de um valor da árvore
            cout << "Digite um ID para ser removido:" << endl;
            cin >> chave;
            raiz = removerNodo(raiz, chave);
            break;
        default:
            if (opcao != 0)
                cout << "\n\tOpção Inválida!!!" << endl; // Mensagem para opção inválida
            break;
        }
    } while (opcao != 0); // Continua até o usuário escolher sair

    return 0;
}
