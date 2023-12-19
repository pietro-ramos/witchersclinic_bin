#ifndef BRUXO_H
#define BRUXO_H

#define MAX_STRING 100

typedef struct {
    int codigo;
    char nome[MAX_STRING];
    char especialidade[MAX_STRING];
} Bruxo;

int InicializarBruxos();
int EncerrarBruxos();
int VerificarCodigoBruxo(int codigo);
int SalvarBruxo(Bruxo b);
int QuantidadeBruxos();
Bruxo* ObterBruxoPeloIndice(int indice);
void LiberarCopiaBruxo(Bruxo* copiaBruxo);
Bruxo* ObterBruxoPeloCodigo(int codigo, Bruxo* bruxo);
int ModificarBruxoPeloCodigo(int codigo, const char* novoNome, const char* novaEspecialidade);
int AtualizarBruxo(Bruxo b);
int ApagarBruxoPeloCodigo(int codigo);

#endif

