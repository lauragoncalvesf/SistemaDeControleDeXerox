#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define PRECO_POR_PAGINA 0.10

// Definição da struct de Pedido
typedef struct Pedido{
    int numero;
    char nomeSolicitante[50];
    char tipoSolicitante[20];
    int quantidadePaginas;
    char dataPedido[11];
    float valorTotal;
    char status[15];
    struct Pedido * proximo;
} Pedido;

// Função para obter a data atual dd/mm/yyyy
void obterData(char *data); 

int obterOpcaoMenu();

int apenasLetras(const char *str);

int apenasNumeros(const char *str);

void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt);

void obterTipoSolicitante(Pedido *pedido);

void obterQuantidadePaginas(int *quantidade);

// Carrega os pedidos existentes do arquivo
void carregarPedidosDoArquivo(Pedido** lista, const char* nomeArquivo);

void salvarPedidoNoArquivo(Pedido* lista, const char* nomeArquivo);

// Função para inserir um pedido na lista encadeada
void inserirPedidoNaLista(Pedido** lista, Pedido* novoPedido);

void adicionarPedido(Pedido** listaPedido);

// Função para listar os pedidos
void listarPedidos(Pedido *lista);

// Função para excluir um pedido e atualizar os números
void excluirPedido(Pedido** lista);