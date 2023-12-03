#include "Tratamento.h"
#include "Bruxo.h"
#include "Paciente.h"
#include "Pocao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tratamento* tratamentos = NULL;
int MAX_TRATAMENTOS = 5;
int qtdTratamentos = 0;

int InicializarTratamentos()
{
    tratamentos = (Tratamento*)calloc(MAX_TRATAMENTOS, sizeof(Tratamento));
    if (tratamentos == NULL)
	{
        return 0;
    }
    return 1;
}

int EncerrarTratamentos()
{
    if (tratamentos != NULL)
	{
        free(tratamentos);
        tratamentos = NULL;
        MAX_TRATAMENTOS = 0;
        qtdTratamentos = 0;
        return 1;
    }
    return 0;
}

int CodigoPacienteValido(int codigo)
{
    for (int i = 0; i < QuantidadePacientes(); i++)
	{
        if (pacientes[i].codigo == codigo)
		{
            return 1;  // C�digo de paciente v�lido
        }
    }
    return 0;  // C�digo de paciente inv�lido
}

int CodigoBruxoValido(int codigo)
{
    for (int i = 0; i < QuantidadeBruxos(); i++)
	{
        if (bruxos[i].codigo == codigo)
		{
            return 1;  // C�digo de bruxo v�lido
        }
    }
    return 0;  // C�digo de bruxo inv�lido
}

int CodigoPocaoValido(int codigo)
{
    for (int i = 0; i < QuantidadePocoes(); i++)
	{
        if (pocoes[i].codigo == codigo)
		{
            return 1;  // C�digo de bruxo v�lido
        }
    }
    return 0;  // C�digo de bruxo inv�lido
}

int SalvarTratamento(Tratamento t)
{
    if (tratamentos == NULL)
	{
        return 0;
    }

    if (qtdTratamentos == MAX_TRATAMENTOS)
	{
        // Amplia o array usando realloc
        MAX_TRATAMENTOS += 5;
        Tratamento* temp = (Tratamento*)realloc(tratamentos, MAX_TRATAMENTOS * sizeof(Tratamento));
        if (temp == NULL)
		{
			MAX_TRATAMENTOS -= 5;
            return 0; // N�o foi poss�vel ampliar o array
        }
        tratamentos = temp;
    }

    tratamentos[qtdTratamentos] = t;
    qtdTratamentos++;
    return 1;
}

Tratamento* ObterTratamentoPeloIndice(int indice)
{
    if (indice >= 0 && indice < qtdTratamentos)
	{
        Tratamento* copiaTratamento = (Tratamento*)malloc(sizeof(Tratamento));

        if (copiaTratamento == NULL)
		{
            return NULL;
        }

        *copiaTratamento = tratamentos[indice]; // Copia todos os campos do tratamento

        return copiaTratamento;
    }
    return NULL;
}

void LiberarCopiaTratamento(Tratamento* copiaTratamento) {
    if (copiaTratamento != NULL) {
        free(copiaTratamento);
    }
}


Tratamento* ObterTratamentoPeloCodigo(int codigo)
{
    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoTratamento == codigo)
		{
            return &tratamentos[i];
        }
    }
    return NULL;
}

int AtualizarTratamento(Tratamento t)
{
    Tratamento* tratamentoExistente = ObterTratamentoPeloCodigo(t.codigoTratamento);

    if (tratamentoExistente != NULL)
	{
        *tratamentoExistente = t; // Atualiza todos os campos do tratamento

        return 1;
    }
    return 0; // Tratamento com o c�digo especificado n�o encontrado
}

int ObterNomeBruxo(int codigo, char *nomeBruxo)
{
    for (int i = 0; i < QuantidadeBruxos(); i++)
	{
        if (bruxos[i].codigo == codigo)
		{
            strcpy(nomeBruxo, bruxos[i].nome);
            return 1;  // Encontrou o bruxo
        }
    }
    return 0;  // C�digo de bruxo inv�lido
}

int ObterNomePocao(int codigo, char *nomePocao)
{
    for (int i = 0; i < QuantidadePocoes(); i++)
	{
        if (pocoes[i].codigo == codigo)
		{
            strcpy(nomePocao, pocoes[i].nome);
            return 1;  // Encontrou a po��o
        }
    }
    return 0;  // C�digo de po��o inv�lido
}

int ObterNomePaciente(int codigo, char *nomePaciente)
{
    for (int i = 0; i < QuantidadePacientes(); i++)
	{
        if (pacientes[i].codigo == codigo)
		{
            strcpy(nomePaciente, pacientes[i].nome);
            return 1;  // Encontrou o paciente
        }
    }
    return 0;  // C�digo de paciente inv�lido
}


int ListarTratamentosPaciente(int codigoPaciente, int** tratamentosPaciente)
{
    int count = 0;
    *tratamentosPaciente = (int*)malloc(qtdTratamentos * sizeof(int)); // Aloca mem�ria para armazenar os �ndices dos tratamentos

    if (*tratamentosPaciente == NULL)
	{
        return 0; // Falha na aloca��o de mem�ria
    }

    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoPaciente == codigoPaciente)
		{
            (*tratamentosPaciente)[count] = i;
            count++;
        }
    }

    return count;
}

int ListarTratamentosBruxo(int codigoBruxo, int** tratamentosBruxo)
{
    int count = 0;
    *tratamentosBruxo = (int*)malloc(qtdTratamentos * sizeof(int)); // Aloca mem�ria para armazenar os �ndices dos tratamentos

    if (*tratamentosBruxo == NULL)
	{
        return 0; // Falha na aloca��o de mem�ria
    }

    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoBruxo == codigoBruxo)
		{
            (*tratamentosBruxo)[count] = i;
            count++;
        }
    }

    return count;
}

int AmpliarTratamento(int codigoTratamento, int duracaoAdicional, int dosagemAdicional)
{
    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoTratamento == codigoTratamento)
		{
			tratamentos[i].dosagem += dosagemAdicional;
            tratamentos[i].duracao += duracaoAdicional;
            return 1;
        }
    }
    return 0; // Tratamento n�o encontrado
}

int VerificarTratamentosVinculadosAoBruxo(int codigoBruxo)
{
    for (int i = 0; i < qtdTratamentos; i++)
    {
        if (tratamentos[i].codigoBruxo == codigoBruxo)
        {
            return 1; // Existe pelo menos um tratamento vinculado ao bruxo
        }
    }
    return 0; // N�o h� tratamentos vinculados ao bruxo
}

int VerificarTratamentosVinculadosAoPaciente(int codigoPaciente)
{
    for (int i = 0; i < qtdTratamentos; i++)
    {
        if (tratamentos[i].codigoPaciente == codigoPaciente)
        {
            return 1; // Existe pelo menos um tratamento vinculado ao bruxo
        }
    }
    return 0; // N�o h� tratamentos vinculados ao bruxo
}

int VerificarTratamentosVinculadosAPocao(int codigoPocao)
{
    for (int i = 0; i < qtdTratamentos; i++)
    {
        if (tratamentos[i].codigoPocao == codigoPocao)
        {
            return 1; // Existe pelo menos um tratamento vinculado ao bruxo
        }
    }
    return 0; // N�o h� tratamentos vinculados ao bruxo
}

int ExcluirTratamento(int codigoTratamento)
{
    int indiceParaRemover = -1;
    for (int i = 0; i < qtdTratamentos; i++)
	{
        if (tratamentos[i].codigoTratamento == codigoTratamento)
		{
            indiceParaRemover = i;
            break;
        }
    }

    if (indiceParaRemover != -1)
	{
        // Movendo os tratamentos � direita do �ndice para preencher a lacuna
        for (int i = indiceParaRemover; i < qtdTratamentos - 1; i++)
		{
            tratamentos[i] = tratamentos[i + 1];
        }

        qtdTratamentos--;

        // Verificar a ocupa��o e reduzir o array se necess�rio
        if (qtdTratamentos < MAX_TRATAMENTOS / 2.5)
		{
			int temp_MAX_TRATAMENTOS = MAX_TRATAMENTOS;
            MAX_TRATAMENTOS /= 2.5;
            Tratamento* temp = (Tratamento*)realloc(tratamentos, MAX_TRATAMENTOS * sizeof(Tratamento));
            if (temp != NULL)
			{
                tratamentos = temp;
            } else {
            	MAX_TRATAMENTOS = temp_MAX_TRATAMENTOS;
			}
        }
        return 1;
    }
    return 0; // Tratamento com o c�digo especificado n�o encontrado
}

