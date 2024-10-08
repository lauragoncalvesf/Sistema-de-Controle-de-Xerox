#ifndef PEDIDO_H
#define PEDIDO_H

#define MAX_NOME 50
#define MAX_STATUS 50
#define PRECO_POR_PAGINA 0.20
typedef struct{
    int numero;
    char nomeSolicitante[MAX_NOME];
    char tipoSolicitante[MAX_NOME]; // Aluno, Professor, Funcionario
    int quantidadePaginas;
    char dataPedido[11]; // formato: dd/mm/yyyy
    float valorTotal;
    char status[MAX_STATUS]; // Pendente, Concluído, Cancelado
} Pedido;

extern Pedido ** pedidos;
extern int contador_pedidos;
extern int capacidade;

// Função para obter a data atual
void obterData(char * data);

// Função para redimensionar o array de pedidos
void redimensionarPedidos();

// Função para adicionar um pedido
void adicionarPedido();

// Função para listar todos os pedidos
void listarPedidos();

// Função para excluir um pedido
void excluirPedido();

// Função para buscar pedido por número ou nome
void buscarPedido();

// Função para editar um pedido
void editarPedido();

// Função para consultar pedidos por status
void consultarPedidosPorStatus();

// Função para calcular total de cópias realizadas e valor arrecadado
void consultarTotalCopiasValor();

// Função para liberar memória alocada para os pedidos
void liberarMemoria();

// Função para verificar se a string contém apenas números
int apenasNumeros(const char *str);

// Função para verificar se a string contém apenas letras
int apenasLetras(const char *str); 

// Função para verificar se a string contém pelo menos uma letra
int possuiLetra(const char *str);

// Função para capturar e validar a entrada
int obterOpcaoMenu();

// Função para obter o novo status do pedido
void obterNovoStatus(char *status);

// Função para obter tipo de solicitante como número
void obterTipoSolicitante(Pedido *pedido);

// Função para obter entrada de string com validação
void obterEntradaValida(char *buffer, int tamanho, const char *prompt);

// Função para carregar pedidos do arquivo
void carregarPedidosDoArquivo();

// Função para salvar pedidos no arquivo
void salvarPedidosNoArquivo();

#endif