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

int apenasNumeros(const char *str){
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // Contém algo que não é número
        }
    }
    return 1; // Apenas números
}

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

void obterNovoStatus(char *status) {
    int escolha = 0;
    char entrada[3]; // Para capturar o Enter ou uma escolha

    while (1) {
        printf("Escolha o status:\n");
        printf(" 1. Pendente\n");
        printf(" 2. Concluído\n");
        printf(" 3. Cancelado\n");
        printf(" Digite a opção (1-3): ");
        fgets(entrada, sizeof(entrada), stdin); // Captura a entrada

        if (entrada[0] == '\n') { // Verifica se o usuário pressionou Enter
            return;
        }

        escolha = atoi(entrada); // Converte para inteiro

        switch (escolha) {
            case 1:
                strcpy(status, "Pendente");
                return;
            case 2:
                strcpy(status, "Concluído");
                return;
            case 3:
                strcpy(status, "Cancelado");
                return;
            default:
                printf("\nEscolha inválida! Tente novamente.\n");
                break;
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
        fprintf(arquivo, "Numero do pedido: %d\n", atual->numero);
        fprintf(arquivo, "Nome do solicitante: %s\n", atual->nomeSolicitante);
        fprintf(arquivo, "Tipo de solicitante: %s\n", atual->tipoSolicitante);
        fprintf(arquivo, "Quantidade de páginas: %d\n", atual->quantidadePaginas);
        fprintf(arquivo, "Valor total: %.2f\n", atual->valorTotal);
        fprintf(arquivo, "Data do pedido: %s\n", atual->dataPedido);
        fprintf(arquivo, "Status do pedido: %s\n", atual->status);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo); }


void carregarPedidosDoArquivo(Pedido** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Criando um novo arquivo.\n");
        return; 
    }

    Pedido* novoPedido;
    while (1) {
        novoPedido = (Pedido*) malloc(sizeof(Pedido));
        if (fscanf(arquivo, "Numero do Pedido: %d\n", &novoPedido->numero) != 1) {
            free(novoPedido);
            break; // Para caso não conseguir ler o número, sai do loop
        }
        fscanf(arquivo, "Nome do Solicitante: %[^\n]\n", novoPedido->nomeSolicitante);
        fscanf(arquivo, "Tipo de Solicitante: %[^\n]\n", novoPedido->tipoSolicitante);
        fscanf(arquivo, "Quantidade de Páginas: %d\n", &novoPedido->quantidadePaginas);
        fscanf(arquivo, "Valor Total: %f\n", &novoPedido->valorTotal);
        fscanf(arquivo, "Data do Pedido: %[^\n]\n", novoPedido->dataPedido);
        fscanf(arquivo, "Status do Pedido: %[^\n]\n", novoPedido->status);
        fscanf(arquivo, "-----------------------------------\n"); // Ignora a linha separadora

        // Insere o pedido na lista
        novoPedido->proximo = NULL; // Inicializa o próximo como NULL
        inserirPedidoNaLista(lista, novoPedido);
    }

    fclose(arquivo);
}


void inserirPedidoNaLista(Pedido** lista, Pedido* novoPedido) {
    if (*lista == NULL) {
        *lista = novoPedido;  // Se a lista estiver vazia, o novo pedido é o primeiro
    } else {
        Pedido* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;  // Percorre até o final da lista
        }
        atual->proximo = novoPedido;  // Insere o novo pedido no final
    }
}

void adicionarPedido(Pedido ** lista){
    Pedido * novoPedido = (Pedido*)malloc(sizeof(Pedido));
    if (novoPedido == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    obterEntradaApenasCaracteres(novoPedido->nomeSolicitante, sizeof(novoPedido->nomeSolicitante), "\nNome do solicitante: ");
    obterTipoSolicitante(novoPedido);
    obterQuantidadePaginas(&novoPedido->quantidadePaginas);
    strcpy(novoPedido->status, "Pendente");
    novoPedido->valorTotal = novoPedido->quantidadePaginas * PRECO_POR_PAGINA;
    if (novoPedido->quantidadePaginas > 50){
        novoPedido->valorTotal *= 0.9;
    }
    obterData(novoPedido->dataPedido);

    novoPedido->proximo = NULL; 

    if(*lista == NULL){
        novoPedido->numero = 1;
        *lista = novoPedido;
    }else{
        Pedido * atual = *lista;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        novoPedido->numero = atual->numero + 1;
        atual->proximo = novoPedido;
    }

    printf("Pedido criado com sucesso! Número do pedido: %d\n", novoPedido->numero);
}

void exibirPedidos(Pedido *lista) {
    Pedido *atual = lista;
    if (atual == NULL) {
        printf("\nNenhum pedido armazenado.\n");
        return;
    }
    printf("\n-----------------------------\n");
    while (atual != NULL) {
        printf("Pedido: %d\n", atual->numero);
        printf("Nome do solicitante: %s\n", atual->nomeSolicitante);
        printf("Tipo de solicitante: %s\n", atual->tipoSolicitante);
        printf("Quantidade de páginas: %d\n", atual->quantidadePaginas);
        printf("Valor total: %.2f\n", atual->valorTotal);
        printf("Data do pedido: %s\n", atual->dataPedido);
        printf("Status: %s\n", atual->status);
        printf("-----------------------------\n");
        atual = atual->proximo;
    }
}

void excluirPedido(Pedido** lista) {
    char entrada[15];
    int numeroExcluir;

    if(*lista == NULL){
        printf("Nenhum pedido para excluir!\n");
        return;
    }

    Pedido* atual = *lista;
    Pedido* anterior = NULL;
    
    printf("\nDigite o número do pedido que deseja excluir: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = 0; // Remove o '\n'

    if (apenasNumeros(entrada)) {
        numeroExcluir = atoi(entrada);  // Converte para inteiro
    } else {
        printf("Entrada inválida! Digite apenas números.\n");
        return;  // Sai da função se a entrada não for válida
    }

    // Procura pelo pedido a ser excluído
    while (atual != NULL && atual->numero != numeroExcluir) {
        anterior = atual; // Armazena o ponteiro do pedido anterior
        atual = atual->proximo; // Move para o próximo pedido
    }

    // Se o pedido não for encontrado
    if (atual == NULL) {
        printf("Pedido com número %d não encontrado.\n", numeroExcluir);
        return;
    }

    // Se o pedido a ser excluído é o primeiro da lista
    if (anterior == NULL) {
        *lista = atual->proximo; // Atualiza a cabeça da lista
    } else {
        anterior->proximo = atual->proximo; // Atualiza o ponteiro do anterior
    }

    free(atual); // Libera a memória do pedido excluído

    Pedido *aux = *lista;
    int novoNumero = 1;

    while(aux != NULL){
        aux->numero = novoNumero;
        novoNumero ++;
        aux = aux->proximo;
    }
    printf("Pedido com número %d excluído com sucesso.\n", numeroExcluir);
}

void editarPedido(Pedido *lista) {
    char entrada[15];
    int numeroPedido;

    if (lista == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }

    printf("\nDigite o número do pedido que deseja editar: ");
    fgets(entrada, sizeof(entrada), stdin);
    entrada[strcspn(entrada, "\n")] = '\0';    
    if (apenasNumeros(entrada)) {
        numeroPedido = atoi(entrada); // Converte para inteiro
    } else {
        printf("Entrada inválida! Digite apenas números.\n");
        return; // Sai da função se a entrada não for válida
    }

    Pedido *atual = lista;

    // Procura pelo pedido com o número especificado
    while (atual != NULL && atual->numero != numeroPedido) {
        atual = atual->proximo;
    }

    // Verifica se o pedido foi encontrado
    if (atual == NULL) {
        printf("Pedido com o número %d não encontrado.\n", numeroPedido);
        return;
    }

    // Menu de edição
    int opcao;
    do {
        printf("\nEditando pedido #%d:\n", numeroPedido);
        printf(" 1. Editar quantidade de páginas (atual: %d)\n", atual->quantidadePaginas);
        printf(" 2. Editar Status do Pedido (Atual: %s)\n", atual->status);
        printf(" 3. Sair da Edição\n"); 
        printf(" Escolha uma opção: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = 0; // Remove o '\n'

        if (apenasNumeros(entrada)) {
            opcao = atoi(entrada); // Converte para inteiro
        } else {
            printf("Entrada inválida! Digite apenas números.\n");
            continue; // Repete o loop se a entrada for inválida
        }

        switch (opcao) {
            case 1:
                obterQuantidadePaginas(&atual->quantidadePaginas);
                break;
            case 2:
                obterNovoStatus(atual->status); // Atualiza o status do pedido
                break;
            case 3:
                printf("Saindo da edição.\n");
                break;
            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (opcao != 3);

    printf("Edição concluída com sucesso!\n");
}

/*
void buscarPedido(Pedido * lista){
    if(lista == NULL){
        printf("Nenhum pedido encontrado!\n");
        return;
    }

    char entrada[15];
    int numeroPedido, encontrado = 0;
    Pedido *atual = lista;

    printf("\nDigite o número ou nome do solicitante: ");
    if (apenasNumeros(entrada)) {
            opcao = atoi(entrada); // Converte para inteiro
        } else {
            printf("Entrada inválida! Digite apenas números.\n");
            continue; // Repete o loop se a entrada for inválida
        }

}*/