/**
 * @date: 11/2024
 * @author: Thiago Pereira de Oliveira
 * @details: Minhas bibliotecas em C.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BIBLIOTECAS

// apenas para funções que não sei fazer

#include <stdlib.h> // para o malloc
#include <stdio.h> // para o printf
#include <time.h> // para clock

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTAR COMPARAÇÕES

// substitui o if para uma versão que conta comparações. Alterações abaixo também, no QOL
#define IF(comp) if(comp && (++comparacoes))
long long int comparacoes = 0.0;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// BOOLEAN & NÚMEROS NATURAIS

typedef unsigned int nat; // numeros naturais

typedef enum { false = 0, true = 1 } boolean;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// QOL

// cria uma linha fácil de ver e remover que printa o número da linha onde está
#define DEBUGLINE_DEBUGLINE_DEBUGLINE_DEBUGLINE_DEBUGLINE \
if (!nao_debugar) printf ("\n\tDebug reached line %d\n", __LINE__)

// for simplificado
#define loop(quantas_vezes,var) for(int var = 0; var < quantas_vezes && (++comparacoes); var++)

// else if
#define elif(comp) else if(comp && (++comparacoes))

// usando o null do java
#define null NULL

// println
#define println(...) printf (__VA_ARGS__); printf ("\n");

// quando true, desativa debugs
boolean nao_debugar = false;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CONTROLE DE MEMÓRIA

// coisas ainda não definidas
void colorir (char* text, char* background);
void murder (char* entrada);

// malloc mais simples/seguro/contabilizado
#define reservar(tipo,quantos) (tipo*) reservar_espaco_funcao (quantos*sizeof (tipo)); 

// Free mais seguro/contabilizado
int reservas_feitas = 0; // Para garantir que tudo foi liberado na memória.
int limpezas_feitas = 0;
#define limpar(val) if(val!=null && limpezas_feitas++){free(val); val = null;}

// Malloc mais seguro
void* reservar_espaco_funcao (size_t Size)
{
    void* try = malloc (Size);
    reservas_feitas++;

    IF (try == null) 
        murder ("Erro ao criar espaco");
    else return try;
}

// Avisa o que tá sobrando de lixo na memória
int quantas_chamadas = 0; // para remover o calculo dos IFs dessa função
void status_da_memoria ()
{
    int razao = reservas_feitas - limpezas_feitas;
    int recomparacoes = comparacoes - 19 * quantas_chamadas++;

    IF    (razao ==  0) colorir ("nao_debugar"   , "preto");
    elif  (razao <= 10) colorir ("amarelo" , "preto");
    else                colorir ("vermelho", "preto");
    
    IF    (nao_debugar ==  0) 
    printf
    (
        "\n\t%s\n\t%s: %d%s\n\t%s: %d%s\n\t%s: %d%s\n\t%s\n\t%s: %d%s\n\t%s\n\n",
        "+---------------------------------------+",
        "|Comparos feitos",recomparacoes, "  \t\t|",
        "|Reservas feitas",reservas_feitas,"\t\t\t|",
        "|Limpezas feitas",limpezas_feitas,"\t\t\t|",
        ">---------------------------------------<",
        "|Lixo de memoria", razao,        "\t\t\t|",
        "+---------------------------------------+"
    );

    colorir ("branco"  , "preto");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE

boolean eh_igual (char* t1, char* t2);

// Texto levemente destacado.
void important (char* entrada)
{
    printf ("\n\n\t%s\n\n", entrada);
}

// Texto mais levemente destacado.
void less_important (char* entrada)
{
    printf ("\t%s\n", entrada);
}

/**
 * Modifica a cor do terminal
 * 
 * Texto Only:
 * negrito
 * sublinhado
 * 
 * Ambos:
 * preto
 * vermelho
 * nao_debugar
 * amarelo
 * azul
 * magenta
 * ciano
 * branco
 */
void colorir (char* text, char* background)
{
    int texto = 37;
    int fundo = 40;

    IF   (eh_igual (text, "negrito"     )) texto =  1;
    elif (eh_igual (text, "sublinhado"  )) texto =  4;
    elif (eh_igual (text, "preto"       )) texto = 30;
    elif (eh_igual (text, "vermelho"    )) texto = 31;
    elif (eh_igual (text, "nao_debugar"       )) texto = 32;
    elif (eh_igual (text, "amarelo"     )) texto = 33;
    elif (eh_igual (text, "azul"        )) texto = 34;
    elif (eh_igual (text, "magenta"     )) texto = 35;
    elif (eh_igual (text, "ciano"       )) texto = 36;
    elif (eh_igual (text, "branco"      )) texto = 37;

    IF   (eh_igual (background, "preto"         )) fundo = 40;
    elif (eh_igual (background, "vermelho"      )) fundo = 41;
    elif (eh_igual (background, "nao_debugar"         )) fundo = 42;
    elif (eh_igual (background, "amarelo"       )) fundo = 43;
    elif (eh_igual (background, "azul"          )) fundo = 44;
    elif (eh_igual (background, "magenta"       )) fundo = 45;
    elif (eh_igual (background, "ciano"         )) fundo = 46;
    elif (eh_igual (background, "branco"        )) fundo = 47;

    printf ("\033[%d;%dm",texto, fundo);
}

// Mensagem colorida
void mensagem_colorida (char* mensagem, char* cor, boolean importante)
{
    colorir (cor, "preto");
    IF (importante) important (mensagem);
    else less_important (mensagem);
    colorir ("branco", "preto");
}

// Mensagem de erro
void murder (char* entrada)
{
    mensagem_colorida (entrada, "vermelho", true);

    exit (-1);
}

// Informação, não aparece se enviado no nao_debugar
void informar (char* entrada, char* cor, boolean importante)
{
    IF (!nao_debugar) mensagem_colorida (entrada, cor, importante);
}

// calloc
char* reservar_string (size_t quantos)
{
    IF (quantos <= 0) murder ("Alocando memoria nula");
    char* tmp = (char*) reservar_espaco_funcao (quantos);

    loop (quantos, x) tmp [x] = '*';

    return tmp;
}

// nextLine
char* proxima_linha (FILE* arquivo)
{
    char *saida = reservar (char, 500);
    IF (arquivo != null)
    {
        IF (fscanf (arquivo, "%[^\n]\n", saida) != 1)
        {murder ("Arquivo lido alem da conta");}
    }
    else   
    IF (scanf ("%[^\n]\n", saida) != 1)
        murder ("Input incorreto do usuario");

    return saida;
}

// nextChar
char proximo_caractere (FILE* arquivo)
{
    char saida = '\0';
    IF (arquivo != null)
    {
        IF (fscanf (arquivo, "%c", &saida) != 1)
        {murder ("Arquivo lido alem da conta");}
    }
    else   
    IF (scanf (" %c", &saida) != 1)
        murder ("Input incorreto do usuario");

    return saida;
}

// nextByte
unsigned char proximo_byte (FILE* arquivo) 
{
    unsigned char saida = 0;

    IF (arquivo != null) 
    { // %hhu lê um byte como número.
        IF ( fscanf (arquivo, "%hhu", &saida) != 1) 
        {murder ("Arquivo lido além do esperado");}
    } 
    else
        IF (scanf("%hhu", &saida) != 1)
            murder ("Entrada do usuário incorreta");

    return saida;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// MATEMÁTICA

// potencia simples de numero inteiro
int potencia (int a, int b)
{
    int resp = 1;
    loop (b, x) resp *= a;

    return resp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXTOS

// Retorna a quantia de caracteres presente em uma string.
int tamanho (char* entrada)
{
    IF (entrada == null) murder ("Impossivel pegar tamanho de string inexistente");
    else
    {
        int resposta = 0;

        while (entrada [resposta] != '\0') resposta++;

        return resposta;
    }
}

// Testa se duas strings são iguais
boolean eh_igual (char* t1, char* t2)
{
    int tam1 = tamanho (t1);
    boolean resposta = true;

    IF (tam1 != tamanho (t2)) resposta = false;
    else
    {
        for (int x = 0; x < tam1 && resposta; x++)
            IF (t1 [x] != t2 [x]) resposta = false;
    }

    return resposta;
}

// Compara duas strings
int comparar (char* t1, char* t2)
{
    int resposta = 0;
    int tam1 = tamanho (t1);
    int tam2 = tamanho (t2);
    int tam  = (tam1 > tam2)?tam2:tam1;

    for (int x = 0; x <= tam && !resposta; x++) resposta = t2 [x] - t1 [x];

    return resposta;
}

// Strcpy. Retorna o tamanho da string (em caracteres) final.
int copiar_texto (char* t1, char* t2)
{
    int x = 0;

    IF (tamanho (t1) >= tamanho (t2))
    {
        char c = '*';

        while (c != '\0')
        {
            c = t2 [x];
            t1 [x] = c;

            x++;
        }
    }
    else
        murder ("Uma tentativa de copiar um texto para uma string menor foi feita!");

    return x - 1;
}

// Quantas vezes um caractere em específico aparece na string
int contar_um_caractere (char* texto, char carac)
{
    IF (texto == null) murder ("Texto inexistente em contar um caractere");
    else
    {
        int tam = tamanho (texto);
        int resposta = 0;

        loop (tam, x) IF (texto [x] == carac) resposta++;

        return resposta;
    }
}

// Split para C
char** separar (char* texto, char carac, int *saida_de_quantos)
{
    IF (texto == null) murder ("Texto inexistente em separar");
    else
    {
        int quantos = contar_um_caractere (texto, carac) + 1;
        int tam     = tamanho (texto);
        int index   = 0;
        int y       = 0;

        char** resposta = reservar (char*, quantos);

        loop (quantos, x)
        {
            resposta [x] = reservar_string (tam + 1);
        }

        loop (tam, x)
        {
            IF (texto [x] == carac)
            {
                resposta [index][y] = '\0';
                index++;
                y = 0;
            }
            else
            {
                resposta [index][y++] = texto [x];
            }
        }

        resposta [index][y] = '\0';

        IF (saida_de_quantos != null) *saida_de_quantos = quantos; 
        return resposta;
    }
}

void imprimir_partes (char* texto, char separador)
{
    int x = 0;
    char** saida = separar (texto, separador, &x);

    loop (x, y)
    {
        printf ("[%d] (size %3d) %s\n", y + 1, tamanho (saida [y]), saida [y]);
    }

    println (null);
}

// parseInt de 1 caractere
unsigned short int char_para_Int (char carac)
{
    IF ('0' <= carac && carac <= '9')
    {
        return carac - '0';
    }
    else
        murder ("Caractere nao numerico nao pode virar numero");
}

// parseInt
int Str_para_Int (char* str)
{
    IF (str == null) murder ("Texto inexistente em Str_para_Int");
    else
    {
        int tam = tamanho (str);
        int resposta = 0;
        int base = potencia (10, tam - 1);

        loop (tam, x) 
        {
            resposta += base * char_para_Int (str [x]);
            base /= 10;
        }

        return resposta;
    }
}

// recebe um digito e o tranforma em char
char Int_para_char (short unsigned int val)
{
    IF (val > 9) murder ("Valor muito grande");
    else
    return '0' + val;
}

// conversão para evitar erros
char* char_para_Str (char in)
{
    char* out = reservar_string (2);
    out [0] =   in;
    out [1] = '\0';

    return out;
}

// recebe uma string e a transforma em double
double Str_para_Dbl (char* str)
{
    IF (str == null) murder ("Texto inexistente em Str_para_Dbl");
    else
    {
        int quantas = 0;
        char** partes = separar (str, '.', &quantas);
        double resposta = 0;

        // casas depois da virgula;
        int casas = tamanho (partes [1]);

        resposta  = Str_para_Int (partes [0]);
        double p2 = Str_para_Int (partes [1]);

        resposta += p2 / (double) potencia (10, casas);

        IF (partes != null && quantas == 2 && partes [0] != null && partes [1] != null)
        {
            loop (quantas, x)
            {
                limpar (partes [x]);
            }
            limpar (partes); // <<<< adicionar essa linha dá um erro em judas perdeu as botas no código
            // não entendi porque, não acho que a eficiência que isso me daria vale realmente a pena 
            // o sofrimento mental que passei por isto, então estou aposentando essa por enquanto.

            //limpezas_feitas++; // <- APENAS PARA SABER QUANTO EU GANHARIA COM ISSO, NÃO TEM UMA LIMPEZA AQUI AINDA!

            // 2400 lixo de memoria -> 880
        }
        else murder ("Algo de errado aconteceu em str para dbl");

        return resposta;
    }
}

// verifica se a string tem um caractere em especifico
boolean contem_caractere (char* entrada, char carac)
{
    IF (entrada == null) murder ("Entrada invalida em contem caractere");
    else
    {
        int tam = tamanho (entrada);
        boolean resposta = false;

        for (int x = 0; x < tam && !resposta; x++) 
            IF (entrada [x] == carac)
                resposta = true;
        
        return resposta;
    }
}

// remove espaços do inicio e do final se existirem
char* trim (char* entrada)
{
    IF (entrada == null) murder ("Trim com entrada invalida");
    else
    {
        int tam = tamanho (entrada);
        char* saida = reservar_string (tam + 1);
        int y = 0;

        loop ((tam - 1), x)
        {
            IF (x == 0)
            {
                IF (entrada [0] != ' ')
                saida [y++] = entrada [x];
            }
            else
            saida [y++] = entrada [x];
        }

        IF (entrada [tam - 1] == ' ')
        saida [y] = '\0';
        else
        {
            saida [y] = entrada [tam - 1];
            saida [y + 1] = '\0';
        }

        return saida;
    }
}

// Remove os caracteres presentes na segunda string de dentro da primeira e retorna
char* remover_caracteres (char* texto, char* remocoes)
{
    IF (texto == null || remocoes == null) murder ("Entradas invalidas em remover caracteres");
    else
    {
        int tam = tamanho (texto);
        char* resposta = reservar_string (tam);
        int index = 0;

        loop (tam, x)
        {
            IF (!contem_caractere (remocoes, texto [x]))
            {
                resposta [index++] = texto [x];
            }
        }

        resposta [index] = '\0';

        return resposta;
    }
}

// Concatenar
char* concatenar (char* t1, char* t2)
{
    IF (t1 == null || t2 == null) murder ("Texto inexistente em concatenar");
    else
    {
        int tam1 = tamanho (t1);
        int tam2 = tamanho (t2);

        int tamfinal = tam1 + tam2 + 1;
        char* tmp = reservar_string (tamfinal);

        copiar_texto (tmp, t1);

        for (int x = tam1; x < tamfinal; x++)
        {
            tmp [x] = t2 [x - tam1];
        }

        tmp [tamfinal] = '\0';

        return tmp;
    }
}
char* conc_3 (char* t1, char* t2, char* t3)
{
    char* a = concatenar (t1, t2);
    char* b = concatenar (a, t3);

    limpar (a);

    return b;
}
char* conc_4 (char* t1, char* t2, char* t3, char* t4)
{
    char* a = conc_3 (t1, t2, t3);
    char* b = concatenar (a, t4);

    limpar (a);

    return b;
}
char* conc_5 (char* t1, char* t2, char* t3, char* t4, char* t5)
{
    char* a = conc_4 (t1, t2, t3, t4);
    char* b = concatenar (a, t5);

    limpar (a);

    return b;
}

// recebe um numero e o transforma em string
char* Int_para_Str (int val)
{
    char* resposta;

    IF (val != 0)  
    {
        char* esquerda = Int_para_Str (val/10);
        char* digito_f = char_para_Str (Int_para_char (val % 10));

        resposta = concatenar (esquerda, digito_f);

        limpar (esquerda);
        limpar (digito_f);
    }
    else
    {
        resposta = reservar_string (1);
        resposta [0] = '\0';
    }

    return resposta;
}

// insere caracteres no inicio se o tamanho nao for o correto
char* garantir_tamanho (char* entrada, int tam, char carac)
{
    IF (entrada == null) murder ("Entrada indefinida em garantir tamanho");
    else
    {
        int tama = tamanho (entrada);
        char* resposta;

        IF (tam > tama)
        {
            resposta = reservar_string (tam - tama);

            loop ((tam - tama), x)
            {
                resposta [x] = carac;
            }
        }
        else
        {
            resposta = "";
        }

        return concatenar (resposta, entrada);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// STRING

// tipo de dado String
typedef struct String
{
    char* texto;
    int tamanho;
}
String;
typedef String* ptr_String;
void free_String (ptr_String str); 

// construtor (duas reservas)
ptr_String novo_String (char* entrada)
{
    ptr_String tmp = reservar (String, 1);

    IF (entrada == null)
    {
        tmp->texto = reservar (char, 1);
        tmp->tamanho = 0;
    }
    else
    {
        int tam = tamanho (entrada);
        tmp->tamanho = tam;
        tmp->texto = reservar_string (tam + 1);

        copiar_texto (tmp->texto, entrada);
    }

    return tmp;
}

// alterar
void alterar_String (ptr_String *str, char* texto)
{
    IF (str == null || texto == null)
        murder ("Valor inexistente em alterar String");
    {
        free_String (*str);
        *str = novo_String (texto);
    }
}

// destrutor
void free_String (ptr_String str)
{
    IF (str != null)
    {
        boolean gambito = (str->texto != null); // sacrifico uma comparação em troca do funcionamento
        
        if (gambito) limpar (str->texto);
        
        if (gambito) limpar (str);
        
    }
    else
        murder ("String sendo deletado nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// LISTA DE STRING ESTÁTICA

// definindo a lista
typedef struct Lista_de_String_Estatica
{
    String **lista;
    int          x;
    int    tamanho;
}
Lista_de_String_Estatica;
typedef Lista_de_String_Estatica* ptr_Lista_de_String_Estatica;

// construtor (2 reservas + string*tamanho reservas) = 2 + 2*tam res
ptr_Lista_de_String_Estatica novo_LdSe (int tamanho)
{
    ptr_Lista_de_String_Estatica tmp = reservar (Lista_de_String_Estatica, 1);

    tmp->tamanho = tamanho;
    tmp->x = 0;

    tmp->lista = reservar (ptr_String, tamanho);

    loop (tamanho, x)
    {
        tmp->lista [x] = novo_String (null);
    }

    return tmp;
}

// adicionar
void adicionar_na_LdSe (ptr_Lista_de_String_Estatica lista, ptr_String valor)
{
    IF (lista == null || valor == null) murder ("Valor inexistente em adicionar na LDSE");
        elif (lista->x >= lista->tamanho) murder ("LdSe muito pequena");
            else
            {
                free_String (lista->lista [lista->x]); // reduziu a produção de lixo para 34k
                lista->lista [lista->x++] = valor;
            }
}

// imprime todos os elementos
void imprimir_LdSe (ptr_Lista_de_String_Estatica lista)
{
    IF (lista == null) murder ("Lista inexistente em impressao");

    loop (lista->x, x)
    {
        println ("[%d] (tam %d) %s", x, lista->lista [x]->tamanho, lista->lista [x]->texto);
    }

    println (null);
}

// destrutor
void free_LdSe (ptr_Lista_de_String_Estatica lista)
{
    IF (lista != null)
    {
        loop (lista->tamanho, x)
        {
            free_String (lista->lista [x]);
        }

        limpar (lista->lista);
        
        limpar (lista);
    }
    else
        murder ("Lista sendo deletada nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// DATA

// tipo de dado Data
typedef struct Data
{
    int dia;
    int mes;
    int ano;
}
Data;
typedef Data* ptr_Data;

// construtor
ptr_Data novo_Data (char* texto)
{
    ptr_Data tmp = reservar (Data, 1);
    tmp->dia = 0;
    tmp->mes = 0;
    tmp->ano = 0;

    IF (texto != null)
    {
        char** cut = separar (texto, '/', null);

        tmp->dia = Str_para_Int (cut [0]);
        tmp->mes = Str_para_Int (cut [1]);
        tmp->ano = Str_para_Int (cut [2]);

        limpar (cut [0]); // reduziu a produção de lixo para 31k 
        limpar (cut [1]);
        limpar (cut [2]);
        limpar (cut    );
    }

    return tmp;
}

// converte data para String
char* Data_para_Str (ptr_Data data)
{
    char* diastr = Int_para_Str (data->dia);
    char* messtr = Int_para_Str (data->mes);
    char* anostr = Int_para_Str (data->ano);

    char* diagrt = garantir_tamanho (diastr, 2, '0');
    char* mesgrt = garantir_tamanho (messtr, 2, '0');
    char* anogrt = garantir_tamanho (anostr, 4, '0');

    char* resposta = conc_5 (diagrt, "/", mesgrt, "/", anogrt);

    limpar (diastr);
    limpar (messtr);
    limpar (anostr);

    limpar (diagrt);
    limpar (mesgrt);
    limpar (anogrt);

    return resposta;
}

// destrutor
void free_Data (ptr_Data data)
{
    IF (data != null)
    {
        limpar (data);
    }
    else
        murder ("Data sendo deletada nao existe");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// CÉLULA DUPLA STRING

// Tipo de dado da célula duplamente encadeada. Tanto para listas quanto para árvores
typedef struct CelulaDuplaStr CelulaDuplaStr;
typedef CelulaDuplaStr* ptr_CelulaDuplaStr;
struct CelulaDuplaStr
{
    ptr_CelulaDuplaStr esq;
    ptr_CelulaDuplaStr dir;
    ptr_String valor;

    int quantidade; // aparicoes do valor na estrutura
};

// construtor
ptr_CelulaDuplaStr novo_CelulaDuplaStr (ptr_String valor)
{
    ptr_CelulaDuplaStr tmp = reservar (CelulaDuplaStr, 1);

    tmp->esq = null;
    tmp->dir = null;
    tmp->valor = valor;
    tmp->quantidade = 1;

    return tmp;
}

// destrutor
void free_CelulaDuplaStr (ptr_CelulaDuplaStr cel)
{
    IF (cel == null) murder ("CelulaDuplastr sendo deletado nao existe");
    else
    {
        free_String (cel->valor);

        limpar (cel);
    }
}

// destrutor completo do tipo de dado
void freeAll_CelulaDuplaStr (ptr_CelulaDuplaStr cel)
{
    IF (cel != null)
    {
        
        freeAll_CelulaDuplaStr (cel->esq);
        
        freeAll_CelulaDuplaStr (cel->dir);
        
        if (cel->valor != null) free_String (cel->valor);
        
        limpar (cel);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// ÁRVORE BINÁRIA DE PESQUISA DE STRING

// Tipo de dado árvore
typedef struct ArvBinPesqStr
{
    ptr_CelulaDuplaStr raiz;
}
ArvBinPesqStr;
typedef ArvBinPesqStr* ptr_ArvBinPesqStr;

// construtor
ptr_ArvBinPesqStr novo_ArvBinPesqStr ()
{
    ptr_ArvBinPesqStr tmp = reservar (ArvBinPesqStr, 1);
    tmp->raiz = null;
    return tmp;
}

// pesquisar
ptr_CelulaDuplaStr pesVerbRec_ArvBinPesqStr (char* valor, ptr_CelulaDuplaStr cel)
{
    ptr_CelulaDuplaStr tmp = null;

    IF (cel == null)
    {
        println (" NAO");
        tmp = null;
    }
    else
    {
        int comparacao = comparar (valor, cel->valor->texto);

        IF (comparacao < 0)
        {
            printf (" dir"); // tá invertido. NÃO SEI PORQUE! SÓ ASSIM FUNCIONA!

            pesVerbRec_ArvBinPesqStr (valor, cel->esq);
        }
        elif (comparacao > 0)
        {
            printf (" esq"); // Quem sou eu pra mexer em time que tá ganhando?
            
            pesVerbRec_ArvBinPesqStr (valor, cel->dir);
        }
        else
        {
            println (" SIM");
            tmp = cel;
        }
    }

    return tmp;
}
ptr_CelulaDuplaStr pesquisarVerbosamente_ArvBinPesqStr (ptr_ArvBinPesqStr arv, char* valor)
{
    printf ("%s\n=>raiz", valor);
    return pesVerbRec_ArvBinPesqStr (valor, arv->raiz);
}

// adicionar
ptr_CelulaDuplaStr adicionarRecursivo_ArvBinPesqStr (ptr_String valor, ptr_CelulaDuplaStr cel)
{
    ptr_CelulaDuplaStr tmp = cel;

    IF (cel == null) tmp = novo_CelulaDuplaStr (valor);
    else
    {
        int comparacao = comparar (valor->texto, cel->valor->texto);
        
        IF   (comparacao < 0) cel->esq = adicionarRecursivo_ArvBinPesqStr (valor, cel->esq);
        elif (comparacao > 0) cel->dir = adicionarRecursivo_ArvBinPesqStr (valor, cel->dir);
        else    
        {
            cel->quantidade++;
            tmp = cel;
        }
    }

    return tmp;
}
void adicionar_ArvBinPesqStr (ptr_ArvBinPesqStr arv, ptr_String valor)
{
    arv->raiz = adicionarRecursivo_ArvBinPesqStr (valor, arv->raiz);
}

// destrutor
void free_ArvBinPesqStr (ptr_ArvBinPesqStr arv)
{
    IF (arv == null) murder ("ArvBinPesqStr sendo deletado nao existe");
    else
    {
        freeAll_CelulaDuplaStr (arv->raiz);

        limpar (arv);
    }
}