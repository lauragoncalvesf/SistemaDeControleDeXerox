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

// Função para capturar e validar a entrada
int obterOpcaoMenu();

// Função para obter a data atual dd/mm/yyyy
void obterData(char *data); 

// Função para verificar se a string contém apenas letras
int apenasLetras(const char *str);

// Função para verificar se a string contém apenas números
int apenasNumeros(const char *str);

// Função para obter uma entrada apenas com caracteres
void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt);

// Função para obter o tipo de solicitante
void obterTipoSolicitante(Pedido *pedido);

// Função para obter a quantidade de páginas
void obterQuantidadePaginas(int *quantidade);

// Função para obter o novo status do pedido
void Status(char *status);

// Função para salvar pedidos no arquivo
void salvarPedidoNoArquivo(Pedido* lista, const char* nomeArquivo);

// Carrega os pedidos existentes do arquivo
void carregarPedidosDoArquivo(Pedido** lista, const char* nomeArquivo);

// Função para inserir um pedido na lista encadeada
void inserirPedidoNaLista(Pedido** lista, Pedido* novoPedido);

// Função para adicionar um pedido
void adicionarPedido(Pedido** lista);

// Função para listar os pedidos
void exibirPedidos(Pedido *lista);

// Função para excluir um pedido e atualizar os números
void excluirPedido(Pedido** lista);

// Função para editar um pedido 
void editarPedido(Pedido *lista);

// Função para buscar pedido por número ou nome
void buscarPedido(Pedido * lista);

// Função para consultar pedidos por status
void consultarPedidoPorStatus(Pedido * lista);

// Função para consultar total de copias realizadas e o valor arrecado 
void consultarTotalCopiasValor(Pedido *lista);
