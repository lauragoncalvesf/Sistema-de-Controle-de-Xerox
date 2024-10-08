#include "pedido.c"

int main() {
    int opcao = -1;
    pedidos = (Pedido **)malloc(capacidade * sizeof(Pedido *));
    carregarPedidosDoArquivo();

    if (pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    while(1) {
        printf("\n----- | Menu de Pedidos | -----\n\n");
        printf("1. Adicionar pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. Excluir pedido\n");
        printf("4. Buscar pedido por número ou nome\n");
        printf("5. Editar pedido\n");
        printf("6. Consultar pedidos por status\n");
        printf("7. Consultar total de cópias e valor arrecadado\n");
        printf("8. Sair\n\n");
    
        opcao = obterOpcaoMenu();

        switch (opcao) {
            case 1:
                adicionarPedido();
                break;
            case 2:
                listarPedidos();
                break;
            case 3:
                excluirPedido();
                break;
            case 4:
                buscarPedido();
                break;
            case 5:
                editarPedido();
                break;
            case 6:
                consultarPedidosPorStatus();
                break;
            case 7:
                consultarTotalCopiasValor();
                break;
            case 8:
                salvarPedidosNoArquivo();
                liberarMemoria();
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
    return 0;
}