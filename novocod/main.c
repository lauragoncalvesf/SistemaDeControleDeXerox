#include "pedido.h"

int main(){
    Pedido * listaPedidos = NULL;
    const char* nomeArquivo = "pedidos.txt";

    carregarPedidosDoArquivo(&listaPedidos, nomeArquivo);

    int quantidadePaginas, opcao, numeroPedido = 1;
    char nomeSolicitante[50], tipoSolicitante[20], status[15];

    do{
        printf("\n----- | Menu de Pedidos | -----\n\n");
        printf("1. Adicionar pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. Excluir pedido\n");
        printf("4. Editar pedido\n");
        printf("5. Buscar pedido por número ou nome\n");
        printf("6. Consultar pedidos por status\n");
        printf("7. Consultar total de cópias e valor arrecadado\n");
        printf("8. Sair\n\n");

        opcao = obterOpcaoMenu();

        switch(opcao){
            case 1:
                adicionarPedido(&listaPedidos);
                salvarPedidoNoArquivo(listaPedidos, nomeArquivo);
                break;
            case 2:
                exibirPedidos(listaPedidos);
                break;
            case 3:
                excluirPedido(&listaPedidos);
                salvarPedidoNoArquivo(listaPedidos, nomeArquivo);
                break;
            case 4: 
                editarPedido(listaPedidos);
                salvarPedidoNoArquivo(listaPedidos, nomeArquivo);
                break;
            default:
                printf("Opção inválida!\n");
        }
    }while(opcao != 8);
    return 0;
}