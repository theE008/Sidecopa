#include "libs.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECA SIDECOPA 

// verifíca existência do arquivo
boolean arquivo_existe (char* caminho)
{
    FILE* arq = fopen (caminho, "rt");
    boolean resposta = true;

    IF (arq == null) resposta = false;

    fclose (arq);
    return resposta;
}

// retorna uma linha em específico de um arquivo
char* linha (char* caminho, int linha)
{
    char* resposta = reservar_string (500);
    linha++;

    IF (!arquivo_existe (caminho)) resposta = null;
    else
    {
        FILE* arquivo = fopen (caminho, "rt");

        loop (linha, x)
        {
            fscanf (arquivo, "%[^\n]\n", resposta);
        }

        fclose (arquivo);
    }

    return resposta;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN

int main (void)
{
    // para começar, abra o arquivo metafísica/quarto_inicial.txt para saber qual é o room inicial.
    char* path_rom_ini = "Sistema/Metafisica/quarto_inicial.txt";

    char* rom_ini = linha (path_rom_ini, 0);

    if (rom_ini == null) 
    // se o arquivo quarto_inicial.txt não existe (erro metafisico)
    {

    }

    limpar (rom_ini);

    status_da_memoria ();
    getchar ();

    return 0;
}