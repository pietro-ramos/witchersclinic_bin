#include "Bruxo.h"
#include "Tratamento.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* bruxos = NULL;

int InicializarBruxos()
{
    bruxos = fopen("bruxos.bin", "rb+");
    if (!bruxos)
    {
        bruxos = fopen("bruxos.bin", "wb+");
        return 0;
    }
    return 1;
}

int EncerrarBruxos()
{
    if (bruxos != NULL)
    {
        fclose(bruxos);
        bruxos = NULL;
        return 1;
    }
    return 0;
}

int VerificarCodigoBruxo(int codigo)
{
    Bruxo verificaBruxo;
    fseek(bruxos, 0, SEEK_SET); // Move para início do arquivo
    while (fread(&verificaBruxo, sizeof(Bruxo), 1, bruxos) == 1)
    {
        if (verificaBruxo.codigo == codigo)
        {
            return 1; // Código já existe na lista de bruxos
        }
    }
    return 0; // Código não encontrado na lista de bruxos
}

int SalvarBruxo(Bruxo b)
{
    if (!bruxos)
    {
        return 0;
    }

    if (VerificarCodigoBruxo(b.codigo))
    {
        return 0; // Código já existente na lista de bruxos
    }

    fseek(bruxos, 0, SEEK_END);  // Move para o final do arquivo

    // Salva a estrutura Bruxo diretamente
    fwrite(&b, sizeof(Bruxo), 1, bruxos);

    return 1;
}

int QuantidadeBruxos()
{
    if (!bruxos)
    {
        return 0;
    }

    Bruxo countBruxos;
    fseek(bruxos, 0, SEEK_SET);
    int quantidade = 0;

    while (fread(&countBruxos, sizeof(Bruxo), 1, bruxos) == 1)
    {
        quantidade++;
    }

    fseek(bruxos, 0, SEEK_SET); // Reinicia o ponteiro para o início do arquivo

    return quantidade;
}

Bruxo* ObterBruxoPeloIndice(int indice)
{
    if (indice >= 0 && indice < QuantidadeBruxos())
    {
        Bruxo* copiaBruxo = (Bruxo*)malloc(sizeof(Bruxo));
        fseek(bruxos, indice * sizeof(Bruxo), SEEK_SET);  // Move para a posição do registro

        if (!copiaBruxo)
        {
            return NULL;
        }

        fread(copiaBruxo, sizeof(Bruxo), 1, bruxos);

        return copiaBruxo;
    }
    return NULL;
}

void LiberarCopiaBruxo(Bruxo* copiaBruxo)
{
    if (copiaBruxo != NULL)
    {
        free(copiaBruxo);
    }
}

Bruxo* ObterBruxoPeloCodigo(int codigo, Bruxo* bruxo)
{
    fseek(bruxos, 0, SEEK_SET); // Move para início do arquivo.

    while (fread(bruxo, sizeof(Bruxo), 1, bruxos) == 1)
    {
        if (bruxo->codigo == codigo)
        {
            return bruxo;
        }
    }

    return NULL;
}

int AtualizarBruxo(Bruxo b)
{
    if (!bruxos)
    {
        return 0;
    }

    Bruxo bruxoExistente;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(bruxos, 0, SEEK_SET); // Move para início do arquivo

    while (fread(&bruxoExistente, sizeof(Bruxo), 1, bruxos) == 1)
    {
        if (bruxoExistente.codigo != b.codigo)
        {
            fwrite(&bruxoExistente, sizeof(Bruxo), 1, temp);
        }
        else
        {
            // Atualiza o bruxoExistente com os novos dados
            bruxoExistente = b;

            // Escreve o bruxoExistente de volta no arquivo
            fwrite(&bruxoExistente, sizeof(Bruxo), 1, temp);

            verificacao = 1; // Bruxo com o código especificado encontrado
        }
    }

    fclose(bruxos);
    fclose(temp);

    if (remove("bruxos.bin") != 0 || rename("temp.bin", "bruxos.bin") != 0)
    {
        return 0;
    }

    bruxos = fopen("bruxos.bin", "rb+");

    return verificacao;
}

int ModificarBruxoPeloCodigo(int codigo, const char* novoNome, const char* novaEspecialidade)
{
    Bruxo bruxoParaAtualizar;

    if (ObterBruxoPeloCodigo(codigo, &bruxoParaAtualizar))
    {
        // Modifica os campos necessários
        strcpy(bruxoParaAtualizar.nome, novoNome);
        strcpy(bruxoParaAtualizar.especialidade, novaEspecialidade);

        // Atualiza no arquivo
        if (AtualizarBruxo(bruxoParaAtualizar))
        {
            return 1; // Sucesso na atualização
        }
    }

    return 0; // Bruxo com o código especificado não encontrado
}

int ApagarBruxoPeloCodigo(int codigo)
{
    if (!bruxos)
    {
        return 0;
    }

    Bruxo apagadoBruxo;

    FILE* temp = fopen("temp.bin", "wb+");
    if (!temp)
    {
        return 0;
    }

    int verificacao = 0;

    fseek(bruxos, 0, SEEK_SET); // Move para início do arquivo

    while (fread(&apagadoBruxo, sizeof(Bruxo), 1, bruxos) == 1)
    {
        if (apagadoBruxo.codigo != codigo)
        {
            fwrite(&apagadoBruxo, sizeof(Bruxo), 1, temp);
        }
        else
        {
            verificacao = 1; // Bruxo com o código especificado encontrado
        }
    }

    fclose(bruxos);
    fclose(temp);

    if (remove("bruxos.bin") != 0 || rename("temp.bin", "bruxos.bin") != 0)
    {
        return 0;
    }

    bruxos = fopen("bruxos.bin", "rb+");

    return verificacao;
}

