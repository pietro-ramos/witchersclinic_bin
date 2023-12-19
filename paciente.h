#ifndef PACIENTE_H
#define PACIENTE_H

#define MAX_STRING 100

typedef struct {
    int codigo;
    char nome[MAX_STRING];
    int idade;
    float altura;
} Paciente;

int InicializarPacientes();
int EncerrarPacientes();
int VerificarCodigoPaciente(int codigo);
int SalvarPaciente(Paciente p);
int QuantidadePacientes();
Paciente* ObterPacientePeloIndice(int indice);
void LiberarCopiaPaciente(Paciente* copiaPaciente);
Paciente* ObterPacientePeloCodigo(int codigo, Paciente* paciente);
int AtualizarPaciente(Paciente p);
int ModificarPacientePeloCodigo(int codigo, const char* novoNome, int novaIdade, float novaAltura);
int ApagarPacientePeloCodigo(int codigo);

#endif

