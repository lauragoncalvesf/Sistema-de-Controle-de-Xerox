#ifndef PEDIDO_H
#define PEDIDO_H

#define PRECO_POR_PAGINA 0.10
typedef struct{
    int numero;
    char nomeSolicitante[50];
    char tipoSolicitante[20]; // Aluno, Professor, Funcionario
    int quantidadePaginas;
    char dataPedido[11]; // formato: dd/mm/yyyy
    float valorTotal;
    char status[20]; // Pendente, Concluído, Cancelado
} Pedido;

extern Pedido ** pedidos;
extern int contador_pedidos;
extern int capacidade;

void obterData(char * data);
void redimensionar_pedidos();
void adicionar_pedido();
void listar_pedidos();
void excluir_pedido();
void buscar_pedido();
void editar_pedido();
void consultar_pedidos_por_status();
void consultar_total_copias_valor();
void liberar_memoria();

#endif