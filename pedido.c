#include "pedido.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

Pedido **pedidos = NULL; // Ponteiro para ponteiro de Pedido
int contadorPedidos = 0; // Contador de pedidos
int capacidade = 100;    // Capacidade inicial
const char *ARQUIVO_PEDIDOS = "pedido.txt";

void carregarPedidosDoArquivo()
{
    FILE *arquivo = fopen(ARQUIVO_PEDIDOS, "r");

    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de pedidos encontrado. Iniciando com uma lista vazia.\n");
        return;
    }

    pedidos = malloc(capacidade * sizeof(Pedido *));
    if (pedidos == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    while (!feof(arquivo))
    {
        Pedido *novoPedido = (Pedido *)malloc(sizeof(Pedido));
        if (novoPedido == NULL)
        {
            printf("Erro ao alocar memória para o pedido!\n");
            exit(1);
        }

        fscanf(arquivo, "Número: %d\n", &novoPedido->numero);
        fscanf(arquivo, "Nome do Solicitante: %[^\n]\n", novoPedido->nomeSolicitante);
        fscanf(arquivo, "Tipo de Solicitante: %[^\n]\n", novoPedido->tipoSolicitante);
        fscanf(arquivo, "Quantidade de Páginas: %d\n", &novoPedido->quantidadePaginas);
        fscanf(arquivo, "Data do Pedido: %s\n", novoPedido->dataPedido);
        fscanf(arquivo, "Valor Total: %f\n", &novoPedido->valorTotal);
        fscanf(arquivo, "Status: %s\n\n", novoPedido->status);

        if (contadorPedidos >= capacidade)
        {
            redimensionarPedidos();
        }
        pedidos[contadorPedidos++] = novoPedido;
    }
    fclose(arquivo);
}

void salvarPedidosNoArquivo()
{
    FILE *arquivo = fopen(ARQUIVO_PEDIDOS, "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar os pedidos!\n");
        return;
    }

    for (int i = 0; i < contadorPedidos; i++)
    {
        Pedido *p = pedidos[i];
        fprintf(arquivo, "Número: %02d\n", p->numero);
        fprintf(arquivo, "Nome do Solicitante: %s\n", p->nomeSolicitante);
        fprintf(arquivo, "Tipo de Solicitante: %s\n", p->tipoSolicitante);
        fprintf(arquivo, "Quantidade de Páginas: %d\n", p->quantidadePaginas);
        fprintf(arquivo, "Data do Pedido: %s\n", p->dataPedido);
        fprintf(arquivo, "Valor Total: %.2f\n", p->valorTotal);
        fprintf(arquivo, "Status: %s\n\n", p->status);
    }
    fclose(arquivo);
}

void obterData(char *data){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void redimensionarPedidos(){
    capacidade *= 2;
    pedidos = realloc(pedidos, capacidade * sizeof(Pedido *));
    if (pedidos == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
}

int possuiLetra(const char *str){
    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]))
        {
            return 1; // Contém pelo menos uma letra
        }
    }
    return 0; // Não contém letras
}

void obterEntradaValida(char *buffer, int tamanho, const char *prompt)
{
    char entradaTemp[tamanho];

    while (1)
    {
        printf("%s", prompt);
        fgets(entradaTemp, tamanho, stdin);
        entradaTemp[strcspn(entradaTemp, "\n")] = 0; // Remove o '\n'

        // Verifica se o usuário apenas pressionou Enter
        if (strlen(entradaTemp) == 0)
        {
            break;
        }

        // Verifica se a entrada contém ao menos uma letra
        if (strlen(entradaTemp) > 0 && possuiLetra(entradaTemp))
        {
            strcpy(buffer, entradaTemp);
            break;
        }
        else
        {
            printf("Entrada inválida! Por favor, insira um valor.\n");
        }
    }
}

void obterTipoSolicitante(Pedido *pedido)
{
    int opcao;
    while (1)
    {
        printf("Tipo de solicitante:\n 1. Aluno\n 2. Professor\n 3. Funcionário\n Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha do buffer

        if (opcao == 1)
        {
            strcpy(pedido->tipoSolicitante, "Aluno");
            break;
        }
        else if (opcao == 2)
        {
            strcpy(pedido->tipoSolicitante, "Professor");
            break;
        }
        else if (opcao == 3)
        {
            strcpy(pedido->tipoSolicitante, "Funcionário");
            break;
        }
        else
        {
            printf("Opção inválida! Por favor, escolha 1, 2 ou 3.\n");
        }
    }
}

void adicionarPedido()
{
    if (contadorPedidos >= capacidade)
    {
        redimensionarPedidos();
    }

    Pedido *novoPedido = (Pedido *)malloc(sizeof(Pedido));
    if (novoPedido == NULL)
    {
        printf("Erro ao alocar memória!\n");
        return;
    }

    novoPedido->numero = contadorPedidos + 1;
    obterEntradaValida(novoPedido->nomeSolicitante, MAX_NOME, "Nome do solicitante: ");
    obterTipoSolicitante(novoPedido);

    printf("Quantidade de páginas: ");
    while (scanf("%d", &novoPedido->quantidadePaginas) != 1 || novoPedido->quantidadePaginas < 0)
    {
        printf("Entrada inválida! Por favor, insira um número positivo: ");
        while (getchar() != '\n')
            ;
    }
    getchar(); // Limpar buffer

    obterData(novoPedido->dataPedido);
    novoPedido->valorTotal = novoPedido->quantidadePaginas * PRECO_POR_PAGINA;

    if (novoPedido->quantidadePaginas > 50)
    {
        novoPedido->valorTotal *= 0.9;
    }

    strcpy(novoPedido->status, "Pendente");

    int posicao = contadorPedidos;
    for (int i = 0; i < contadorPedidos; i++)
    {
        if (novoPedido->numero < pedidos[i]->numero)
        {
            posicao = i;
            break;
        }
    }

    for (int i = contadorPedidos; i > posicao; i--)
    {
        pedidos[i] = pedidos[i - 1];
    }

    pedidos[posicao] = novoPedido;
    contadorPedidos++;

    salvarPedidosNoArquivo();
    printf("Pedido adicionado com sucesso!\n");
}

void listarPedidos()
{
    if (contadorPedidos == 0)
    {
        printf("Nenhum pedido registrado.\n");
        return;
    }

    for (int i = 0; i < contadorPedidos; i++)
    {
        Pedido *p = pedidos[i];
        printf("\nPedido #%d\n", p->numero);
        printf("Solicitante: %s\n", p->nomeSolicitante);
        printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
        printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
        printf("Data do pedido: %s\n", p->dataPedido);
        printf("Valor total: R$ %.2f\n", p->valorTotal);
        printf("Status: %s\n", p->status);
    }
}

void excluirPedido()
{
    int numero;
    char entrada[50];

    while (1)
    {
        printf("\nDigite o número do pedido que deseja excluir: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (apenasNumeros(entrada))
        {
            numero = atoi(entrada);
            break;
        }
        else
        {
            printf("Entrada inválida! Por favor, insira um número.\n");
        }
    }

    if (numero <= 0 || numero > contadorPedidos)
    {
        printf("Número de pedido inválido.\n");
        return;
    }

    for (int i = 0; i < contadorPedidos; i++)
    {
        if (pedidos[i]->numero == numero)
        {
            free(pedidos[i]);
            for (int j = i; j < contadorPedidos - 1; j++)
            {
                pedidos[j] = pedidos[j + 1];
                pedidos[j]->numero = j + 1;
            }
            contadorPedidos--;
            salvarPedidosNoArquivo();
            printf("Pedido excluído com sucesso!\n");
            return;
        }
    }
    salvarPedidosNoArquivo();
    printf("Pedido não encontrado.\n");
}

void buscarPedido()
{
    if (contadorPedidos == 0)
    {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    char termo[50];
    int encontrado = 0;

    printf("\nDigite o número ou nome do solicitante: ");
    scanf(" %[^\n]", termo);
    getchar();

    // Verifica se a entrada é um número
    if (apenasNumeros(termo))
    {
        int numero = atoi(termo);
        for (int i = 0; i < contadorPedidos; i++)
        {
            if (pedidos[i]->numero == numero)
            {
                Pedido *p = pedidos[i];
                printf("\nPedido #%d\n", p->numero);
                printf("Solicitante: %s\n", p->nomeSolicitante);
                printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
                printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
                printf("Data do pedido: %s\n", p->dataPedido);
                printf("Valor total: R$ %.2f\n", p->valorTotal);
                printf("Status: %s\n", p->status);
                encontrado = 1;
                break; // sai do loop se encontrado
            }
        }
    }
    else
    {
        // Busca pelo nome do solicitante (ignorando maiusculas/minusculas)
        for (int i = 0; i < contadorPedidos; i++)
        {
            char nomeSolicitanteLower[50];
            char termoLower[50];

            // Converte os nomes para minúsculas para busca case-insensitive
            strcpy(nomeSolicitanteLower, pedidos[i]->nomeSolicitante);
            strcpy(termoLower, termo);
            for (int j = 0; nomeSolicitanteLower[j]; j++)
            {
                nomeSolicitanteLower[j] = tolower(nomeSolicitanteLower[j]);
            }
            for (int j = 0; termoLower[j]; j++)
            {
                termoLower[j] = tolower(termoLower[j]);
            }

            if (strstr(nomeSolicitanteLower, termoLower) != NULL)
            {
                Pedido *p = pedidos[i];
                printf("\nPedido #%d\n", p->numero);
                printf("Solicitante: %s\n", p->nomeSolicitante);
                printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
                printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
                printf("Data do pedido: %s\n", p->dataPedido);
                printf("Valor total: R$ %.2f\n", p->valorTotal);
                printf("Status: %s\n", p->status);
                encontrado = 1;
            }
        }
    }
    if (!encontrado)
    {
        printf("Nenhum pedido encontrado.\n");
    }
}

void Status(char *status)
{
    int escolha = 0;

    while (1)
    {
        printf("Escolha o status:\n");
        printf(" 1. Pendente\n");
        printf(" 2. Concluído\n");
        printf(" 3. Cancelado\n");
        printf(" Digite a opção (1-3): ");
        scanf("%d", &escolha);
        getchar(); // Limpa o buffer

        switch (escolha)
        {
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
            printf("\n Escolha inválida! Tente novamente.\n");
            break;
        }
    }
}

void obterNovoStatus(char *status)
{
    int escolha = 0;
    char entrada[3]; // Para capturar o Enter ou uma escolha

    while (1)
    {
        printf("Escolha o status (ou pressione Enter para manter o status atual):\n");
        printf(" 1. Pendente\n");
        printf(" 2. Concluído\n");
        printf(" 3. Cancelado\n");
        printf(" Digite a opção (1-3): ");
        fgets(entrada, sizeof(entrada), stdin); // Captura a entrada

        if (entrada[0] == '\n')
        { // Verifica se o usuário pressionou Enter
            return;
        }

        escolha = atoi(entrada); // Converte para inteiro

        switch (escolha)
        {
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

void editarPedido(){
    int numero;
    printf("Digite o número do pedido que deseja editar: ");
    scanf("%d", &numero);
    getchar(); // Limpar buffer

    for (int i = 0; i < contadorPedidos; i++)
    {
        if (pedidos[i]->numero == numero)
        {
            Pedido *p = pedidos[i];
            printf("Editando pedido #%d\n", p->numero);

            printf("Nome atual: %s\n", p->nomeSolicitante);
            obterEntradaValida(p->nomeSolicitante, MAX_NOME, "Novo nome (ou pressione Enter para manter o atual): ");

            printf("Quantidade de páginas atual: %d\n", p->quantidadePaginas);
            int novasPaginas;
            while (1)
            {
                printf("Digite a nova quantidade de páginas (ou 0 para manter): ");
                if (scanf("%d", &novasPaginas) == 1 && novasPaginas >= 0)
                {
                    break;
                }
                else
                {
                    printf("Entrada inválida! Por favor, insira um número inteiro positivo ou 0.\n");
                    while (getchar() != '\n')
                        ;
                }
            }
            getchar(); // Limpar buffer
            if (novasPaginas > 0)
            {
                p->quantidadePaginas = novasPaginas;
                p->valorTotal = novasPaginas * PRECO_POR_PAGINA;

                if (p->quantidadePaginas > 50)
                {
                    p->valorTotal *= 0.9;
                }
            }

            printf("Status atual: %s\n", p->status);
            obterNovoStatus(p->status);

            salvarPedidosNoArquivo();
            printf("Pedido atualizado com sucesso!\n");
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

void consultarPedidosPorStatus()
{
    if (contadorPedidos == 0)
    {
        printf("Nenhum pedido registrado.\n");
        return;
    }

    char status[MAX_STATUS];
    int encontrado = 0;
    // obterEntradaValida(status, MAX_STATUS, "\nDigite o status (Pendente, Concluído, Cancelado): ");

    Status(status);

    for (int i = 0; i < contadorPedidos; i++)
    {
        if (strcmp(pedidos[i]->status, status) == 0)
        {
            Pedido *p = pedidos[i];
            printf("\nPedido #%d\n", p->numero);
            printf("Solicitante: %s\n", p->nomeSolicitante);
            printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
            printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
            printf("Data do pedido: %s\n", p->dataPedido);
            printf("Valor total: R$ %.2f\n", p->valorTotal);
            printf("Status: %s\n", p->status);
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Nenhum pedido com status %s encontrado.\n", status);
    }
}

void consultarTotalCopiasValor(){
    if (contadorPedidos == 0)
    {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    int totalPaginas = 0;
    float totalValor = 0.0;

    for (int i = 0; i < contadorPedidos; i++)
    {
        totalPaginas += pedidos[i]->quantidadePaginas;
        totalValor += pedidos[i]->valorTotal;
    }

    printf("\nTotal de cópias realizadas: %d\n", totalPaginas);
    printf("Valor total arrecadado: R$ %.2f\n", totalValor);
}

void liberarMemoria(){
    for (int i = 0; i < contadorPedidos; i++)
    {
        free(pedidos[i]);
    }
    free(pedidos);
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