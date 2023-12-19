#include "Paciente.h"
#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* pacientes = NULL;

int InicializarPacientes()
{
    pacientes = fopen("pacientes.bin", "rb+");
    if (!pacientes)
    {
        pacientes = fopen("pacientes.bin", "wb+");
        return 0;
    }
    return 1;
}

int EncerrarPacientes()
{
    if (pacientes != NULL)
    {
        fclose(pacientes);
        pacientes = NULL;
        return 1;
    }
    return 0;
}

int VerificarCodigoPaciente(int codigo)
{
    Paciente verificaPaciente;
    fseek(pacientes, 0, SEEK_SET); // Move para o in�cio do arquivo
    while (fread(&verificaPaciente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (verificaPaciente.codigo == codigo)
        {
            return 1; // C�digo j� existe na lista de pacientes
        }
    }
    return 0; // C�digo n�o encontrado na lista de pacientes
}

int SalvarPaciente(Paciente p)
{
    if (!pacientes)
    {
        return 0;
    }

    if (VerificarCodigoPaciente(p.codigo))
    {
        return 0; // C�digo j� existente na lista de pacientes
    }

    fseek(pacientes, 0, SEEK_END); // Move para o final do arquivo

    fwrite(&p, sizeof(Paciente), 1, pacientes);

    return 1;
}

int QuantidadePacientes()
{
    if (!pacientes)
    {
        return 0;
    }

    Paciente countPacientes;
    fseek(pacientes, 0, SEEK_SET); // Move para o in�cio do arquivo
    int quantidade = 0;

    while (fread(&countPacientes, sizeof(Paciente), 1, pacientes) == 1)
    {
        quantidade++;
    }

    fseek(pacientes, 0, SEEK_SET); // Reinicia o ponteiro para o in�cio do arquivo

    return quantidade;
}

Paciente* ObterPacientePeloIndice(int indice)
{
    if (indice >= 0 && indice < QuantidadePacientes())
    {
        Paciente* copiaPaciente = (Paciente*)malloc(sizeof(Paciente));
        fseek(pacientes, indice * sizeof(Paciente), SEEK_SET); // Move para a posi��o do registro

        if (!copiaPaciente)
        {
            return NULL;
        }

        fread(copiaPaciente, sizeof(Paciente), 1, pacientes);

        return copiaPaciente;
    }
    return NULL;
}

void LiberarCopiaPaciente(Paciente* copiaPaciente)
{
    if (copiaPaciente != NULL)
    {
        free(copiaPaciente);
    }
}

Paciente* ObterPacientePeloCodigo(int codigo, Paciente* paciente)
{
    fseek(pacientes, 0, SEEK_SET); // Move para in�cio do arquivo.

    while (fread(paciente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (paciente->codigo == codigo)
        {
            return paciente;
        }
    }

    return NULL;
}

int AtualizarPaciente(Paciente p)
{
    if (!pacientes)
    {
        return 0;
    }

    Paciente pacienteExistente;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(pacientes, 0, SEEK_SET); // Move para o in�cio do arquivo

    while (fread(&pacienteExistente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (pacienteExistente.codigo != p.codigo)
        {
            fwrite(&pacienteExistente, sizeof(Paciente), 1, temp);
        }
        else
        {
            // Atualiza o pacienteExistente com os novos dados
            pacienteExistente = p;

            // Escreve o pacienteExistente de volta no arquivo
            fwrite(&pacienteExistente, sizeof(Paciente), 1, temp);

            verificacao = 1; // Paciente com o c�digo especificado encontrado
        }
    }

    fclose(pacientes);
    fclose(temp);

    if (remove("pacientes.bin") != 0 || rename("temp.bin", "pacientes.bin") != 0)
    {
        return 0;
    }

    pacientes = fopen("pacientes.bin", "rb+");

    return verificacao;
}

int ModificarPacientePeloCodigo(int codigo, const char* novoNome, int novaIdade, float novaAltura)
{
    Paciente pacienteParaAtualizar;

    if (ObterPacientePeloCodigo(codigo, &pacienteParaAtualizar))
    {
        // Modifica os campos necess�rios
        strcpy(pacienteParaAtualizar.nome, novoNome);
        pacienteParaAtualizar.idade = novaIdade;
        pacienteParaAtualizar.altura = novaAltura;

        // Atualiza no arquivo
        if (AtualizarPaciente(pacienteParaAtualizar))
        {
            return 1; // Sucesso na atualiza��o
        }
    }

    return 0; // Paciente com o c�digo especificado n�o encontrado
}

int ApagarPacientePeloCodigo(int codigo)
{
    if (!pacientes)
    {
        return 0;
    }

    Paciente apagadoPaciente;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(pacientes, 0, SEEK_SET); // Move para o in�cio do arquivo

    while (fread(&apagadoPaciente, sizeof(Paciente), 1, pacientes) == 1)
    {
        if (apagadoPaciente.codigo != codigo)
        {
            fwrite(&apagadoPaciente, sizeof(Paciente), 1, temp);
        }
        else
        {
            verificacao = 1; // Paciente com o c�digo especificado encontrado
        }
    }

    fclose(pacientes);
    fclose(temp);

    if (remove("pacientes.bin") != 0 || rename("temp.bin", "pacientes.bin") != 0)
    {
        return 0;
    }

    pacientes = fopen("pacientes.bin", "rb+");

    return verificacao;
}

