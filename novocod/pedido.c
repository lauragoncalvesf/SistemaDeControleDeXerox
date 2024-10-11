#include "pedido.h"

int obterOpcaoMenu(){
    char entrada[50]; // Buffer para a entrada do usuário
    int opcao = -1;

    while (1)
    {
        printf("Digite uma opção do menu: ");
        fgets(entrada, 50, stdin);              // Captura a entrada como string
        entrada[strcspn(entrada, "\n")] = '\0'; // Remove o '\n'

        // Verifica se a entrada contém apenas números
        if (apenasNumeros(entrada))
        {
            opcao = atoi(entrada); // Converte a string para inteiro
            break;
        }
        else
        {
            printf("Entrada inválida! Por favor, insira um número.\n");
        }
    }

    return opcao;
}

void obterData(char *data){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int apenasLetras(const char *str){
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
        {
            return 0; // Contém algo que não é letra ou espaço
        }
    }
    return 1; // Apenas letras ou espaços
}

// Função para obter uma entrada apenas com caracteres
void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt) {
    char entradaTemp[tamanho];

    while (1) {
        printf("%s", prompt);
        fgets(entradaTemp, tamanho, stdin);
        entradaTemp[strcspn(entradaTemp, "\n")] = 0; // Remove o '\n'

        // Verifica se a entrada não está vazia e se contém apenas letras
        if (strlen(entradaTemp) > 0 && apenasLetras(entradaTemp)) {
            strcpy(buffer, entradaTemp);
            break;
        } else {
            printf("Entrada inválida! Por favor, insira apenas letras.\n");
        }
    }
}

// Função para obter o tipo de solicitante
void obterTipoSolicitante(Pedido *pedido) {
    int opcao;
    while (1) {
        printf("Tipo de solicitante:\n 1. Aluno\n 2. Professor\n 3. Funcionário\n Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha do buffer

        if (opcao == 1) {
            strcpy(pedido->tipoSolicitante, "Aluno");
            break;
        } else if (opcao == 2) {
            strcpy(pedido->tipoSolicitante, "Professor");
            break;
        } else if (opcao == 3) {
            strcpy(pedido->tipoSolicitante, "Funcionário");
            break;
        } else {
            printf("Opção inválida! Por favor, escolha 1, 2 ou 3.\n");
        }
    }
}

void obterQuantidadePaginas(int *quantidade) {
    char entrada[10];

    while (1) {
        printf("Quantidade de páginas: ");
        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = 0; // Remove o '\n'

        if (apenasNumeros(entrada)) {
            *quantidade = atoi(entrada);
            break; // Saia do loop se a entrada é válida
        } else {
            printf("Entrada inválida! Por favor, insira apenas números.\n");
        }
    }
}

void salvarPedidoNoArquivo(Pedido* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");  // Abre o arquivo no modo de escrita (substitui o conteúdo anterior)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Pedido* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "Numero do Pedido: %d\n", atual->numero);
        fprintf(arquivo, "Nome do Solicitante: %s\n", atual->nomeSolicitante);
        fprintf(arquivo, "Tipo de Solicitante: %s\n", atual->tipoSolicitante);
        fprintf(arquivo, "Quantidade de Páginas: %d\n", atual->quantidadePaginas);
        fprintf(arquivo, "Data do Pedido: %s\n", atual->dataPedido);
        fprintf(arquivo, "Status do Pedido: %s\n", atual->status);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo);
}

Pedido* adicionarPedido(){
    Pedido * novoPedido = (Pedido*)malloc(sizeof(Pedido));
    if (novoPedido == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    obterEntradaApenasCaracteres(novoPedido->nomeSolicitante, sizeof(novoPedido->nomeSolicitante), "Nome do solicitante: ");
    obterTipoSolicitante(novoPedido);
    obterQuantidadePaginas(&novoPedido->quantidadePaginas);
    obterData(novoPedido->dataPedido);
    novoPedido->valorTotal = novoPedido->quantidadePaginas * PRECO_POR_PAGINA;
    if (novoPedido->quantidadePaginas > 50){
        novoPedido->valorTotal *= 0.9;
    }
    strcpy(novoPedido->status, "Pendente");

    novoPedido->proximo = NULL; 
    return novoPedido;
}