#include <iostream>
#include <new>
#include <string>
#include <stdlib.h>

using namespace std;

//Estrutura para adicionar as informações do livro.
struct livro
{
    string autor;               //define a variavel autor como uma string.
    string titulo;              //define a variavel titulo como uma string.
    int pag;                    //define a variavel pag como um inteiro.
};

//Função de limpar a tela.
void limpatela()
{
    system("clear");
}

/* Função que ao adicionar um livro no inicio da lista sequenial, Ao adicionar um novo livro, a lista 
é atualizada e o novo livro é inserido no inicio, com as informações anteriores sendo deslocadas*/
void adcComecoSequencial(livro *&ponteiroSequencial, int *tamanhoDaLista, string autor, string titulo, int pag)
{
    if(*tamanhoDaLista == 0) // se o tamanhoDaLista for igual a 0.
    {
        livro *novaListaSequencial = new livro[1]; /*atualiza a lista e adiciona as informações para    
                                                     para o proximo espaco de memória disponivel.*/

        novaListaSequencial[0].autor = autor;
        novaListaSequencial[0].titulo = titulo;  //adiciona as informações to topo da pilha.
        novaListaSequencial[0].pag = pag;

        ponteiroSequencial = novaListaSequencial; //atualiza a lista com as novas informações.

    }

    else // se o tamanho da lista for diferente de 0
    {
        livro * novaListaSequencial = new livro[*tamanhoDaLista + 1]; // aumenta o tamanho da lista.
        novaListaSequencial[0].autor = autor;
        novaListaSequencial[0].titulo = titulo; // adiciona as informações no topo da pilha.
        novaListaSequencial[0].pag =  pag;

        int cont; // percorre a lista antiga passando todas as informações para a nova lista.
        for(cont =0; cont < *tamanhoDaLista; cont++)
        {
            novaListaSequencial[cont + 1].autor = ponteiroSequencial[cont].autor;
            novaListaSequencial[cont + 1].titulo = ponteiroSequencial[cont].titulo; 
            novaListaSequencial[cont + 1].pag = ponteiroSequencial[cont].pag;
        }

        ponteiroSequencial = novaListaSequencial;
    }
       *tamanhoDaLista = *tamanhoDaLista + 1;
}
/*   função para deletar um livro pelo titulo. O programa percorre a lista e, se encontrar um titulo
compativel, deleta o livro e atualiza a lista, liberando espaço na memória */

void removePorTitulo(livro *&ponteiroSequencial, int *tamanhoDaLista, const string &titulo) {
    int posicao = -1;

    // Encontrar a posição do livro pelo título
    for (int i = 0; i < *tamanhoDaLista; i++) {
        if (ponteiroSequencial[i].titulo == titulo) {
            posicao = i;
            break;
        }
    }
    // Se não ouver titulo compativel com a pesquisa.
    if (posicao == -1) {
        cout << "Livro não encontrado!" << endl;
        return;
    }

    livro *novaListaSequencial = new livro[*tamanhoDaLista - 1];

    for (int cont = 0; cont < *tamanhoDaLista - 1; cont++) {
        if (cont < posicao) {
            novaListaSequencial[cont] = ponteiroSequencial[cont];
        } else {
            novaListaSequencial[cont] = ponteiroSequencial[cont + 1];
        }
    }
    //Atualiza a lista diminuindo o tamanho do vetor em -1.
    delete[] ponteiroSequencial;
    ponteiroSequencial = novaListaSequencial;
    *tamanhoDaLista = *tamanhoDaLista - 1;
}


/*Função para procurar um livro pelo título. Percorre a lista e, se encontrar um título compatível, 
retorna o título do livro.*/
string procuraPorTitulo(livro *&ponteiroSequencial, int *tamanhoDaLista,string &titulo)
{
    int cont;
    for(cont = 0;cont < *tamanhoDaLista; cont++)    //Percorre a lista procurando um titulo compativel
    {
        if(ponteiroSequencial[cont].titulo == titulo) // se o titulo procurado for igual da lista.
        {
            titulo = ponteiroSequencial[cont].titulo; // define a variavel "titulo" como a informação 
        }                                             // dentro do endereço de memória apontado.
    }
    return titulo;
    //se encontrar retorna o nome do livro.
}


//Função que procura o livro pelo Autor.
string procuraPorAutor(livro *&ponteiroSequencial, int *tamanhoDaLista, const string &autor) 
{
    string resultados = "";
    bool encontrado = false; // define a variavel boleana pra falso.

    for (int cont = 0; cont < *tamanhoDaLista; cont++) //Percorre a lista procurando um autor compativel 
    {
        if (ponteiroSequencial[cont].autor == autor) //se autor da lista for igual autor procurado.
        {
            if (encontrado) //se autor encontrado.
            {
                resultados += "\n";  // Adiciona uma nova linha antes de cada título adicional
            }
            resultados += ponteiroSequencial[cont].titulo; // pega todos os titulos no nome do autor.
            encontrado = true; // muda a variavel boleana para verdadeiro
        }
    }    
    if (!encontrado) //se autor nao encontrado
    {
        return "Autor não encontrado!";
    }
        return resultados;   // retorna a mensagem dependendo se encontrou ou nao
}

int main()
{
    int pergunta2;

    int funcaoDesejada = 1;

    livro *ponteiroSequencial;

    int tamanhoDaLista = 0;

// enquanto o usuario escolher uma função entre 1 e 3.
    while(funcaoDesejada < 3 && funcaoDesejada > 0)
    {
        cout << "--------------BEM VINDO A BIBLIOTECA DIGITAL -------------------" << endl;   
        cout << "\n";
        cout << "Escolha uma das opções abaixo para continuar." << endl;
        cout << "    ( 1 )  INSERIR um livro." << endl;
        cout << "    ( 2 )  DELETAR um livro." << endl;
        cout << "    ( 3 )  PESQUISAR um livro." << endl;
        cout << "----------------------------------------------------------------" << endl;
        cin >> funcaoDesejada;
    
        cin.ignore();

        limpatela();

        string autor;
        string titulo;
        int pag;

        switch(funcaoDesejada) //após o usuario escolher uma opção
        {

            case 1:   //se ele escolher a opção 1.
                cout << "---------------------------------------------" << endl;
                cout << "O usuario escolheu adicionar um livro." << endl;

                cout << "Digite o nome do autor:" << endl;
                getline(cin, autor);
                cout << "Digite o titulo do livro:" << endl;
                getline(cin, titulo);
                cout << "Digite a quantidade de paginas:" << endl;;
                cin >> pag;
                
                cin.ignore();

                adcComecoSequencial(ponteiroSequencial, &tamanhoDaLista, autor, titulo, pag);
                //adiciona as informações solicitadas ao topo da lista.

                break;
            case 2: // se ele escolher a opção 2
            if (tamanhoDaLista == 0)
            {
                cout << "----------------------------------------";
                cout << "biblioteca esta vazia." << endl;
            }
            else
            { //se o tamanho da lista for > 0.
                cout << "------------------------------------------------------------";
                cout << "Insira o titulo do livro que deseja deletar:" << endl;
                getline(cin, titulo);

                removePorTitulo(ponteiroSequencial, &tamanhoDaLista, titulo);   
            } // ira solicitar o titulo do livro, ira remover e atualizar o tamanho da lista.
                break;
            case 3: // se o usuario escolher a 3 opção.
                if (tamanhoDaLista == 0) // se o tamanho da lista for 0.
                {
                    cout << "----------------------------------------" << endl;
                    cout << "biblioteca esta vazia." << endl;
                }
            else
                { // se o tamanho da lista for > 0
                    cout << "------------------------------------------------------------" << endl;
                    cout << "1 - procura por Titulo." << endl;
                    cout << "2 - procura por autor." << endl;
                    cin >> pergunta2;
                // ira perguntar se o usuario deseja procurar pelo titulo ou autor.
                    cin.ignore();

                if(pergunta2 == 1) // se ele escolher pelo titulo.
                {
                    cout << "Insira o livro que deseja encontrar:" << endl;
                    getline(cin, titulo);

                    cout << "Resultado da pesquisa: " << procuraPorTitulo(ponteiroSequencial, &tamanhoDaLista, titulo);
                } // imprime o titulo que o usuario escolheu.
                else if(pergunta2 == 2) // se escolher pelo autor.
                {
                    cout << "insira o nome do Autor." << endl;
                    getline(cin, autor);

                    cout << "Resultado da pesquisa: " << procuraPorAutor(ponteiroSequencial, &tamanhoDaLista, autor);
                } // imprime todos os livros que estão salvos no nome do autor escolhido.
            break;
            }
        }
    }
}