#ifndef POCAO_H
#define POCAO_H

#define MAX_STRING 100

typedef struct {
    int codigo;
    char nome[MAX_STRING];
    char tipo[MAX_STRING];
} Pocao;

int InicializarPocoes();
int EncerrarPocoes();
int VerificarCodigoPocao(int codigo);
int SalvarPocao(Pocao p);
int QuantidadePocoes();
Pocao* ObterPocaoPeloIndice(int indice);
void LiberarCopiaPocao(Pocao* copiaPocao);
Pocao* ObterPocaoPeloCodigo(int codigo);
int AtualizarPocao(Pocao p);
int ModificarPocaoPeloCodigo(int codigo, const char* novoNome, const char* novoTipo);
int ApagarPocaoPeloCodigo(int codigo);

#endif

