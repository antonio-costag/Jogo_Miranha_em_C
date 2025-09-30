#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <wchar.h>

#define LARGURA_TELA 80
#define ALTURA_TELA 17
#define ALTURA_JOGO_PRINCIPAL 15
#define ALTURA_HUD_SINGULAR 1
#define ESPACO_VAZIO ' '
#define ATRASO_TIQUE 100

#define ALTURA_MIRANHA 2
#define LARGURA_MIRANHA 4
#define ALTURA_DOENTE 3
#define LARGURA_DOENTE 6
#define ALTURA_INIMIGO_JANELA 2
#define LARGURA_INIMIGO_JANELA 5

#define INICIO_TEIA_X 2
#define MIRANHA_CENTRALIZADO_Y 7

#define MAX_INIMIGOS_INICIAL 4
#define MAX_BOMBAS_INICIAL 4
#define PROBABILIDADE_INIMIGOS_INICIAL 5
#define PROBABILIDADE_BOMBAS_INICIAL 2
#define MAX_INIMIGOS_TOTAL 24
#define MAX_BOMBAS_TOTAL 16

#define MIRANHA_CAINDO "|_/o"

#define ALTURA_PREDIO 65
#define LARGURA_PREDIO 58

#define TEMPO_MAXIMO 20
#define TEMPO_MINIMO 10
#define DECREMENTO_TEMPO 2000

#define ALTURA_LOGO_INICIO 12
#define LARGURA_LOGO_INICIO 18

#define ALTURA_LOGO_PAUSA 12
#define LARGURA_LOGO_PAUSA 21

#define NOME_ARQUIVO_RECORDE "recorde.txt"

const wchar_t *PREDIO[ALTURA_PREDIO] = {
    L"                 ||||||||||||||||||||||||                 ",
    L"                 |||||||||||##|||||||||||                 ",
    L"                 |||||||||||##|||||||||||                 ",
    L"         ||||||||||||||||||||||||||||||||||||||||         ",
    L"         ||||||          ||||||||          ||||||         ",
    L"         ||  ||||      ||||    ||||      ||||  ||         ",
    L"         ||    ||||  ||||        ||||  ||||    ||         ",
    L"         ||      ||||||            ||||||      ||         ",
    L"         ||      ||||||            ||||||      ||         ",
    L"         ||    ||||  ||||        ||||  ||||    ||         ",
    L"         ||  ||||      ||||    ||||      ||||  ||         ",
    L"         ||||||          ||||||||          ||||||         ",
    L"     ||||||||||||||||||||||||||||||||||||||||||||||||     ",
    L"     ||||||              ||||||||              ||||||     ",
    L"     ||  ||||          ||||    ||||          ||||  ||     ",
    L"     ||    ||||      ||||        ||||      ||||    ||     ",
    L"     ||      ||||  ||||            ||||  ||||      ||     ",
    L"     ||        ||||||                ||||||        ||     ",
    L"     ||        ||||||                ||||||        ||     ",
    L"     ||      ||||  ||||            ||||  ||||      ||     ",
    L"     ||    ||||      ||||        ||||      ||||    ||     ",
    L"     ||  ||||          ||||    ||||          ||||  ||     ",
    L"     |||||              ||||||||||             ||||||     ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||        ||||||        ||||||        ||||||        ||  ",
    L"  ||||||||||||||||||||||||||||||||||||||||||||||||||||||  ",
    L"  ||       ||||       ||          ||       ||||       ||  ",
    L"  ||       ||||       ||          ||       ||||       ||  ",
    L"  ||       ||||       ||          ||       ||||       ||  ",
    L"  ||       ||||       ||          ||       ||||       ||  ",
    L"  ||||||||||||||||||||||          ||||||||||||||||||||||  ",
    L"  ||||||||||||||||||||||          ||||||||||||||||||||||  ",
};

const wchar_t *LOGO_INICIO[ALTURA_LOGO_INICIO] = {
    L"⠀⢀⡄⠛⠛⢋⣉⣤⣴⡆⣦⣬⣉⣉⠁⢠  ",
    L"⢠⠟⣰⡎⣿⣿⣿⣿⣿⡇⣿⣿⣿⡟⣰⡌⢷⡀",
    L"⣃⠐⢾⣿⣿⡘⣿⣿⡿⠟⠃⠿⣿⡿⢱⣿⣿⣦",
    L"⠀⠀⠻⣿⠇⠀⣀⣤⣴⡇⣷⣦⢀⡘⣿⣿⡿⠋",
    L"⢰⣄⡀⠀⠺⣧⢻⣿⣿⣇⣿⢇⣾⣿⠎⢉⣴⠇",
    L"⠀⣿⣿⣦⡀⠘⢧⢻⣿⢸⢇⣾⠟⢁⣴⣿⣿⠀",
    L"⡀⠸⣿⣿⣿⣶⣄⠑⢻⢨⠛⢁⣴⣿⣿⣿⠇ ",
    L"⢰⡀⠙⠿⣿⠿⠋⠀⠴⠄⠀⠙⠿⣿⡿⠋⣴⠃",
    L"⠈⣿⣷⠖⣠⣄⡂⠸⠿⠃⠛⣢⣄⢲⡎⢸⡟⠀",
    L"⠀⠈⣥⡈⢻⡿⢰⣶⣿⣿⢸⣿⣿⠗⡀⠿⠁ ",
    L"⠀⠀⠹⣿⣆⠁⠟⠛⠛⠛⠆⠛⣵⣿⣿⠂  ",
    L"⠀⠀⠀⠙⡿⣰⣿⣿⣿⣿⣇⢸⣿⡿⠁   ",
};

const wchar_t *LOGO_PAUSA[ALTURA_LOGO_PAUSA] = {
    L"⠀⠀⠀⡠⠀⡌⠀⠀⠀⠀⠀⠀⠀⠀⢡⠀⢄⠀⠀⠀ ",
    L"⠀⠀⣰⠃⣸⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⣇⠘⣆⠀⠀ ",
    L"⠀⢀⡏⢠⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡄ ⢹⡀⠀",
    L"⠀⣸⡇⠘⠷⢖⣒⡲⣤⣤⣤⣤⢖⣒⡲⠾⠃ ⢸⣇ ",
    L"⠀⠻⠷⠚⠋⣩⡭⢭⣿⣿⣿⣿⡭⢭⣍⠙⠓⠾⠟  ",
    L"⠀⠀⢀⣠⠞⢉⣴⠏⣽⣿⣿⣯⠹⣦⡍⠳⣄⡀   ",
    L"⣤⡴⠋⠁⠀⢸⣿⠀⢸⣿⣿⡏⠀⣿⡇⠀⠈⠙⢶⣤ ",
    L"⢹⡇⠀⠀⠀⢸⣿⠀⠈⣿⣿⠁⠀⣿⡇⠀⠀⠀⢸⡟ ",
    L"⠸⡇⠀⠀⠀⠀⣿⠀⠀⠘⠃⠀⠀⣿⠁⠀⠀⠀⢸⡇ ",
    L"⠀⢷⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⡾⠀ ",
    L"⠀⠘⡄ ⠀⢸⠀⠀⠀  ⠀⠀⡇⠀⠀⢠⠃   ",
    L"⠀⠀⠀⠀⠀⠈⠇⠀⠀  ⠀⠀⢸⠁⠀⠀    ",
};

typedef enum {
    NENHUMA,
    CIMA,
    DIAGONAL_ESQUERDA,
    DIAGONAL_DIREITA,
    ANCORA_LOCAL
} DirecaoTeia;

DirecaoTeia direcaoAtualTeia = NENHUMA;
bool soltandoTeia = false;
bool teiaAncorada = false;
int teiaAncoradaNoPredioX = 0;
int teiaAncoradaNoPredioY = 0;
int tempoSegurandoEspaco = 0;
int tamanhoTeiaDisparando = 0;
int tamanhoTeiaAncorada = 0;

bool quedaComum = false;
bool quedaFatal = false;
int scrollCamera = 0;
int scrollDoente = 0;

int tempoMaximoAtual = TEMPO_MAXIMO;
int tempoRestante;
int contadorTempo;
int pontuacao;
int vidas;

int predioCor = 1;

int maxInimigoAtual = MAX_INIMIGOS_INICIAL;
int maxBombaAtual = MAX_BOMBAS_INICIAL;
int probabilidadeInimigo = PROBABILIDADE_INIMIGOS_INICIAL;
int probabilidadeBomba = PROBABILIDADE_BOMBAS_INICIAL;

int recorde = 0;

bool pausado = false;

bool fim_som_disparo = false;
bool som_colidir_inimigo = false;
bool som_colidir_bomba = false;
bool som_colidir_doente = false;
bool musica = false;
bool game_over_musica = false;
bool inicio_game = true;

const wchar_t *CORPO_MIRANHA[ALTURA_MIRANHA] = {
    L"|o /",
    L"/ | "
};

const wchar_t *DOENTE_VERDE[ALTURA_DOENTE] = {
    L"=- V-=",
    L"  | | ",
    L" /--\\ "
};

const wchar_t *INIMIGO_JANELA_SPRITE[ALTURA_INIMIGO_JANELA] = {
    L"| o |",
    L" / \\ "
};

typedef struct {
    int x, y;
    WORD cor;
} MIRANHA;

typedef struct {
    int x, y;
    WORD cor;
    bool esquerda;
    bool direita;
} DOENTE;

typedef struct {
    int x, y;
    bool ativo;
    int tempoNoLugar;
} INIMIGO_JANELA;

typedef struct {
    int x, y;
    bool ativo;
    int tempoNoLugar;
} BOMBA;

MIRANHA miranha;
DOENTE doente;
INIMIGO_JANELA inimigos[MAX_INIMIGOS_TOTAL];
BOMBA bombas[MAX_BOMBAS_TOTAL];

const COORD posicoesJanelas[24] = {
    {4, 24}, {18, 24}, {32, 24}, {46, 24},
    {4, 30}, {18, 30}, {32, 30}, {46, 30},
    {4, 36}, {18, 36}, {32, 36}, {46, 36},
    {4, 42}, {18, 42}, {32, 42}, {46, 42},
    {4, 48}, {18, 48}, {32, 48}, {46, 48},
    {4, 54}, {18, 54}, {32, 54}, {46, 54},
};
const int NUM_POSICOES_JANELAS = 24;

HANDLE console;
CHAR_INFO bufferConsole[LARGURA_TELA * ALTURA_TELA];
COORD tamanhoBuffer = {LARGURA_TELA, ALTURA_TELA};
COORD posicaoCaractere = {0, 0};
SMALL_RECT areaEscritaConsole = {0, 0, LARGURA_TELA - 1, ALTURA_TELA - 1};

void InicializarMiranha(){
    miranha.x = 38;
    miranha.y = MIRANHA_CENTRALIZADO_Y;

    quedaComum = false;
    quedaFatal = false;

    soltandoTeia = false;

    scrollCamera = 50;

    direcaoAtualTeia = NENHUMA;
    teiaAncorada = false;
    tamanhoTeiaAncorada = 0;

    tempoSegurandoEspaco = 0;

    tamanhoTeiaDisparando = 0;

    tempoRestante = tempoMaximoAtual;
    contadorTempo = 0;
}

void InicializarDoente(){
    doente.x = 38;
    doente.y = 0;

    doente.direita = true;
    doente.esquerda = false;

    scrollDoente = 3;
}

void InicializarInimigos() {
    for (int i = 0; i < maxInimigoAtual; i++) {
        inimigos[i].ativo = false;
        inimigos[i].tempoNoLugar = 0;
    }
}

void InicializarBombas() {
    for (int i = 0; i < maxBombaAtual; i++) {
        bombas[i].ativo = false;
        bombas[i].tempoNoLugar = 0;
    }
}

void InicializarNivel() {
    InicializarMiranha();
    InicializarDoente();
    InicializarInimigos();
    InicializarBombas();
}

void LimparBuffer(){
    for(int i = 0; i < ALTURA_TELA * LARGURA_TELA; i++){
        bufferConsole[i].Char.UnicodeChar = ESPACO_VAZIO;
        bufferConsole[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}

void DesenharBuffer(){
    WriteConsoleOutputW(console, bufferConsole, tamanhoBuffer, posicaoCaractere, &areaEscritaConsole);
}

void SalvarRecorde(int numero) {
    HANDLE arquivo;
    DWORD bytesEscritos = 0;
    char buffer_arquivo[32];
    char nomeArquivo[] = NOME_ARQUIVO_RECORDE;

    int chars_escritos = sprintf_s(buffer_arquivo, sizeof(buffer_arquivo), "%d", numero);

    arquivo = CreateFileA(
        nomeArquivo,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    WriteFile(
        arquivo,
        buffer_arquivo,
        chars_escritos,
        &bytesEscritos,
        NULL
    );

    CloseHandle(arquivo);
}

int LerRecorde() {
    HANDLE arquivo;
    DWORD bytesLidos = 0;
    char buffer_arquivo[32] = {0};
    int numero = 0;
    char nomeArquivo[] = NOME_ARQUIVO_RECORDE;

    arquivo = CreateFileA(
        nomeArquivo,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    ReadFile(arquivo, buffer_arquivo, sizeof(buffer_arquivo) - 1, &bytesLidos, NULL);

    buffer_arquivo[bytesLidos] = '\0';
    
    numero = atoi(buffer_arquivo);

    CloseHandle(arquivo);

    return numero;
}

enum {
    SETA_CIMA,
    SETA_BAIXO
};

int direcaoSetinha;
bool mostrarMenu = true;
int selecionado = 1;
void MudarSelecionado(int direcao){
    if(selecionado == 1){
        switch (direcao){
            case SETA_CIMA: selecionado = 4; break;
            case SETA_BAIXO: selecionado = 2; break;
            default: break;
        }
    } else if(selecionado == 2){
        switch (direcao){
            case SETA_CIMA: selecionado = 1; break;
            case SETA_BAIXO: selecionado = 3; break;
            default: break;
        }
    } else if(selecionado == 3){
        switch (direcao){
            case SETA_CIMA: selecionado = 2; break;
            case SETA_BAIXO: selecionado = 4; break;
            default: break;
        }
    }
    else{
        switch (direcao){
            case SETA_CIMA: selecionado = 3; break;
            case SETA_BAIXO: selecionado = 1; break;
            default: break;
        }
    }
}

void MenuRecorde(){
    char textoRecorde[34];
    char textoPontos[50];
    sprintf(textoRecorde, "Sua pontuacao recorde nesse jogo:");
    sprintf(textoPontos, "%d", recorde);

    int indiceTextoRecorde = ALTURA_TELA/2 * LARGURA_TELA + (LARGURA_TELA - strlen(textoRecorde))/2;
    int indiceTextoPontos = (ALTURA_TELA/2 + 1) * LARGURA_TELA + (LARGURA_TELA - strlen(textoPontos))/2;

    LimparBuffer();

    for(int i = 0; i < strlen(textoRecorde); i++){
        bufferConsole[indiceTextoRecorde + i].Char.UnicodeChar = textoRecorde[i];
        bufferConsole[indiceTextoRecorde + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }

    for(int i = 0; i < strlen(textoPontos); i++){
        bufferConsole[indiceTextoPontos + i].Char.UnicodeChar = textoPontos[i];
        bufferConsole[indiceTextoPontos + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }

    DesenharBuffer();

    Sleep(5000);

    LimparBuffer();
    DesenharBuffer();
}

void MenuComoJogar(){
    char textoComoJogar[61];
    char texto2[73];
    sprintf(textoComoJogar, "Segure Espaco + Direcao das Setinhas para disparar sua teia!");
    sprintf(texto2, "Quanto mais tempo voce segurar a barra de espaco, mais longe a teia vai!");

    int indiceComoJogar = ALTURA_TELA/2 * LARGURA_TELA + (LARGURA_TELA - strlen(textoComoJogar))/2;
    int indiceTexto2 = (ALTURA_TELA/2 + 1) * LARGURA_TELA + (LARGURA_TELA - strlen(texto2))/2;

    LimparBuffer();

    for(int i = 0; i < strlen(textoComoJogar); i++){
        bufferConsole[indiceComoJogar + i].Char.UnicodeChar = textoComoJogar[i];
        bufferConsole[indiceComoJogar + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }

    for(int i = 0; i < strlen(texto2); i++){
        bufferConsole[indiceTexto2 + i].Char.UnicodeChar = texto2[i];
        bufferConsole[indiceTexto2+ i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }

    DesenharBuffer();

    Sleep(5000);

    LimparBuffer();
    DesenharBuffer();
}

void SelecionarMenu(){
    if(selecionado == 1){
        mostrarMenu = false;
    } else if(selecionado == 2){
        MenuComoJogar();
    } else if(selecionado == 3){
        MenuRecorde();
    } else{
        exit(0);
    }
}

void CarregarJogo(){
    char textoCarregando[15];
    sprintf(textoCarregando, "Carregando...");

    int indiceCarregando = ALTURA_TELA/2 * LARGURA_TELA + (LARGURA_TELA - strlen(textoCarregando))/2;

    
    while (musica)
    {
        LimparBuffer();

        if(inicio_game){
            for(int i = 0; i < strlen(textoCarregando); i++){
                bufferConsole[indiceCarregando + i].Char.UnicodeChar = textoCarregando[i];
                bufferConsole[indiceCarregando + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            }
        }
        
        DesenharBuffer(); 
    }

    if(inicio_game){
        Sleep(1000);
        musica = true;
    }
}

void DesenharLogo(){
    if(!pausado){
        for(int i = 0; i < ALTURA_LOGO_INICIO; i++){
            for(int j = 0; j < LARGURA_LOGO_INICIO; j++){
                int indice = i * LARGURA_TELA + (((LARGURA_TELA - LARGURA_LOGO_INICIO) / 2) + j);
                bufferConsole[indice].Char.UnicodeChar = LOGO_INICIO[i][j];
                bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            }
        }
    }
    else{
        for(int i = 0; i < ALTURA_LOGO_PAUSA; i++){
            for(int j = 0; j < LARGURA_LOGO_PAUSA; j++){
                int indice = i * LARGURA_TELA + (((LARGURA_TELA - LARGURA_LOGO_PAUSA) / 2) + j + 1);
                bufferConsole[indice].Char.UnicodeChar = LOGO_PAUSA[i][j];
                bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            }
        }
    }
}

void ResetarGame(){
    pontuacao = 0;
    vidas = 3;
    tempoMaximoAtual = TEMPO_MAXIMO;
    predioCor = 1;
    maxInimigoAtual = MAX_INIMIGOS_INICIAL;
    maxBombaAtual = MAX_BOMBAS_INICIAL;
    probabilidadeInimigo = PROBABILIDADE_INIMIGOS_INICIAL;
    probabilidadeBomba = PROBABILIDADE_BOMBAS_INICIAL;
}

void MenuInicial(){
    while(mostrarMenu){
        DesenharLogo();

        char jogar[10];

        if(pausado){
            sprintf(jogar, "CONTINUAR");
        } else {
            sprintf(jogar, "JOGAR");
        }

        int indiceJogar = 13 * LARGURA_TELA + (LARGURA_TELA - strlen(jogar)) / 2;

        for (int i = 0; i < strlen(jogar); i++) {
            bufferConsole[indiceJogar + i].Char.UnicodeChar = jogar[i];
            if(selecionado == 1){
                bufferConsole[indiceJogar + i].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            } else {
                bufferConsole[indiceJogar + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            }
        }

        char comoJogar[11];
        sprintf(comoJogar, "COMO JOGAR");

        int indiceComoJogar = 14 * LARGURA_TELA + (LARGURA_TELA - strlen(comoJogar)) / 2;

        for(int i = 0; i < strlen(comoJogar); i++){
            bufferConsole[indiceComoJogar + i].Char.UnicodeChar = comoJogar[i];
            if(selecionado == 2){
                bufferConsole[indiceComoJogar + i].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            } else {
                bufferConsole[indiceComoJogar + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; 
            }
        }

        char pontuacaoRecorde[18];
        sprintf(pontuacaoRecorde, "PONTUACAO RECORDE");

        int indicePontuacaoRecorde = 15 * LARGURA_TELA + (LARGURA_TELA - strlen(pontuacaoRecorde))/2;

        for(int i = 0; i < strlen(pontuacaoRecorde); i++){
            bufferConsole[indicePontuacaoRecorde + i].Char.UnicodeChar = pontuacaoRecorde[i];
            if(selecionado == 3){
                bufferConsole[indicePontuacaoRecorde + i].Attributes = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            } else {
                bufferConsole[indicePontuacaoRecorde + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            }
        }

        char sair[5];
        sprintf(sair, "SAIR");

        int indiceSair = 16 * LARGURA_TELA + ((LARGURA_TELA - strlen(sair))/2);

        for(int i = 0; i < strlen(sair); i++){
            bufferConsole[indiceSair + i].Char.UnicodeChar = sair[i];
            if(selecionado == 4){
                bufferConsole[indiceSair + i].Attributes = BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            } else {
                bufferConsole[indiceSair + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
            }
        }
        

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            MudarSelecionado(SETA_CIMA);
        } else if (GetAsyncKeyState(VK_DOWN) & 0x8000){
            MudarSelecionado(SETA_BAIXO);
        } else if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
            SelecionarMenu();
        }

        DesenharBuffer();

        Sleep(ATRASO_TIQUE + 25);
    }

    CarregarJogo();
    if(!pausado){
        ResetarGame();
        InicializarNivel();
    } else{
        pausado = false;
    }
}

void GameOver(){
    game_over_musica = true;
    quedaComum = false;
    quedaFatal = false;
    
    
    char gameOver[10];
    char pontosTotais[50];
    sprintf(gameOver, "GAME OVER");
    sprintf(pontosTotais, "SUA PONTUACAO FINAL FOI: %d", pontuacao);

    int indiceGameOver = (ALTURA_TELA/2)*LARGURA_TELA + (LARGURA_TELA - strlen(gameOver))/2;
    int indicePontosTotais = (ALTURA_TELA/2 + 1)*LARGURA_TELA + (LARGURA_TELA - strlen(pontosTotais))/2;

    LimparBuffer();

    for(int i = 0; i < strlen(gameOver); i++){
        bufferConsole[indiceGameOver + i].Char.UnicodeChar = gameOver[i];
        bufferConsole[indiceGameOver + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }

    for(int i = 0; i < strlen(pontosTotais); i++){
        bufferConsole[indicePontosTotais + i].Char.UnicodeChar = pontosTotais[i];
        bufferConsole[indicePontosTotais + i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }

    DesenharBuffer();

    if(pontuacao > recorde){
        SalvarRecorde(pontuacao);
        recorde = LerRecorde();
    }

    ResetarGame();

    Sleep(5000);

    LimparBuffer();
    DesenharBuffer();

    mostrarMenu = true;
    inicio_game = true;
    MenuInicial();
}

void PerderVida() {
    vidas--;
    if (vidas <= 0) {
        GameOver();
    }
    InicializarNivel();
}

void VencerNivel() {
    Sleep(3000);
    
    pontuacao *= 2;

    if(maxInimigoAtual + 2 <= MAX_INIMIGOS_TOTAL){
        maxInimigoAtual = maxInimigoAtual + 2;
    }

    if(maxBombaAtual + 2 <= MAX_BOMBAS_TOTAL){
        maxBombaAtual = maxBombaAtual + 2;
    }

    if(probabilidadeInimigo < 100){
        probabilidadeInimigo = probabilidadeInimigo + 5;
    }

    if(probabilidadeBomba < 100){
        probabilidadeBomba = probabilidadeBomba + 2;
    }

    switch (predioCor)
    {
    case 1:
        predioCor = 2; break;
    case 2:
        predioCor = 3; break;
    case 3:
        predioCor = 4; break;
    case 4:
        predioCor = 5; break;
    case 5:
        predioCor = 6; break;
    case 6:
        predioCor = 7; break;
    case 7:
        predioCor = 1; break;
    default: break;
    }

    if((tempoMaximoAtual - 1) >= TEMPO_MINIMO){
        tempoMaximoAtual--;
    }

    InicializarNivel();
}

void EsconderCursorConsole() {
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

void DesenharPredio(){
    for(int i = scrollCamera; i < ALTURA_JOGO_PRINCIPAL + scrollCamera; i++){
        for(int j = 0; j < LARGURA_PREDIO; j++){
            int indice = (i - scrollCamera + ALTURA_HUD_SINGULAR) * LARGURA_TELA + (((LARGURA_TELA - LARGURA_PREDIO) / 2) + j);
            if (i >= 0 && i < ALTURA_PREDIO) {
                bufferConsole[indice].Char.UnicodeChar = PREDIO[i][j];
                if(PREDIO[i][j] == '#'){
                    bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                }
                else{
                    switch (predioCor) {
                        case 1:
                            bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                        case 2:
                            bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
                        case 3:
                            bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
                        case 4:
                            bufferConsole[indice].Attributes = FOREGROUND_BLUE; break;
                        case 5:
                            bufferConsole[indice].Attributes = FOREGROUND_GREEN; break;
                        case 6:
                            bufferConsole[indice].Attributes = FOREGROUND_RED; break;
                        case 7:
                            bufferConsole[indice].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                        
                        default: break;
                    }
                }
            }
        }
    }
}
void DesenharMiranha(){
    if(quedaComum == false){
        for(int i = 0; i < ALTURA_MIRANHA; ++i){
            for(int j = 0; j < LARGURA_MIRANHA; ++j){
                if (CORPO_MIRANHA[i][j] != ' ' || (i == 0 && j == 2) || (i == 1 && j == 1)) {
                    int indice = (miranha.y + i + ALTURA_HUD_SINGULAR) * LARGURA_TELA + (miranha.x + j);
                    if ( (miranha.y + i) < ALTURA_JOGO_PRINCIPAL) {
                        bufferConsole[indice].Char.UnicodeChar = CORPO_MIRANHA[i][j];

                        if(CORPO_MIRANHA[i][j] == 'o'){
                            bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
                        }
                        else{
                            bufferConsole[indice].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        }
                    }
                }
            }
        }
    }
    else{
        for(int i = 0; i < LARGURA_MIRANHA; i++){
            int indice = (miranha.y + ALTURA_HUD_SINGULAR) * LARGURA_TELA + miranha.x;
             if (miranha.y < ALTURA_JOGO_PRINCIPAL) {
                bufferConsole[indice + i].Char.UnicodeChar = MIRANHA_CAINDO[i];
                
                if(MIRANHA_CAINDO[i] == 'o' || MIRANHA_CAINDO[i] == '_'){
                    bufferConsole[indice + i].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
                }
                else{
                    bufferConsole[indice + i].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                }
             }
        }
    }
}

void DesenharDoente(){
    for(int i = scrollDoente; i < ALTURA_DOENTE; ++i){
        for(int j = 0; j < LARGURA_DOENTE; ++j){
            if (DOENTE_VERDE[i][j] != ' ' || (i == 1 && j == 3) || (i == 0 && j == 2)) {
                int indice = (doente.y + (i - scrollDoente) + ALTURA_HUD_SINGULAR) * LARGURA_TELA + (doente.x + j);
                if ( (doente.y + (i- scrollDoente)) < ALTURA_JOGO_PRINCIPAL){
                    bufferConsole[indice].Char.UnicodeChar = DOENTE_VERDE[i][j];

                    if(i == 0){
                        bufferConsole[indice].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                    }
                    else if(i == 1){

                        bufferConsole[indice].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;
                    }
                    else{
                        bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
                    }
                }
            }
        }
    }
}

void DesenharInimigos() {
    for (int i = 0; i < maxInimigoAtual; i++) {
        if (inimigos[i].ativo) {
            int inimigoTelaY = inimigos[i].y - scrollCamera;
            int inimigoTelaX = inimigos[i].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);

            for (int linha = 0; linha < ALTURA_INIMIGO_JANELA; linha++) {
                for (int coluna = 0; coluna < LARGURA_INIMIGO_JANELA; coluna++) {
                    int finalY = inimigoTelaY + linha + ALTURA_HUD_SINGULAR;
                    int finalX = inimigoTelaX + coluna;
                    if (finalY >= ALTURA_HUD_SINGULAR && finalY < ALTURA_JOGO_PRINCIPAL + ALTURA_HUD_SINGULAR && finalX >= 0 && finalX < LARGURA_TELA) {
                        int indice = finalY * LARGURA_TELA + finalX;
                        bufferConsole[indice].Char.UnicodeChar = INIMIGO_JANELA_SPRITE[linha][coluna];

                        if(INIMIGO_JANELA_SPRITE[linha][coluna] == 'o'){
                            bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE;
                        }
                        else{
                            bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
                        }
                    }
                }
            }
        }
    }
}

void DesenharBombas() {
    for (int i = 0; i < maxBombaAtual; i++) {
        if (bombas[i].ativo) {
            int bombaTelaY = bombas[i].y - scrollCamera + ALTURA_HUD_SINGULAR;
            int bombaTelaX = bombas[i].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
            if (bombaTelaY >= ALTURA_HUD_SINGULAR && bombaTelaY < ALTURA_JOGO_PRINCIPAL + ALTURA_HUD_SINGULAR && bombaTelaX >= 0 && bombaTelaX < LARGURA_TELA) {
                int indice = bombaTelaY * LARGURA_TELA + bombaTelaX;
                bufferConsole[indice].Char.UnicodeChar = '@';
                bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
            }
        }
    }
}

void DesenharTeia() {
    if (soltandoTeia && direcaoAtualTeia != ANCORA_LOCAL) {
        switch (direcaoAtualTeia) {
            case CIMA:
                for (int i = 1; i <= tamanhoTeiaDisparando; i++){
                    if (miranha.y - i >= 0){
                        int indice = (miranha.y - i + ALTURA_HUD_SINGULAR) * LARGURA_TELA + (miranha.x + INICIO_TEIA_X);
                        bufferConsole[indice].Char.UnicodeChar = '0';
                        bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                    }
                }
                break;
            case DIAGONAL_ESQUERDA:
                for (int i = 1; i <= tamanhoTeiaDisparando; i++){
                    if (miranha.y - i >= 0 && miranha.x + 1 - i >= 0){
                        int indice = (miranha.y - i + ALTURA_HUD_SINGULAR) * LARGURA_TELA + (miranha.x + 1 - i);
                        bufferConsole[indice].Char.UnicodeChar = '0';
                        bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                    }
                }
                break;
            case DIAGONAL_DIREITA:
                for (int i = 1; i <= tamanhoTeiaDisparando; i++){
                    if (miranha.y - i >= 0 && miranha.x + INICIO_TEIA_X + i < LARGURA_TELA){
                        int indice = (miranha.y - i + ALTURA_HUD_SINGULAR) * LARGURA_TELA + (miranha.x + INICIO_TEIA_X + i);
                        bufferConsole[indice].Char.UnicodeChar = '0';
                        bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                    }
                }
                break;
            default: break;
        }
    }
    else if (teiaAncorada) {
        int ancoraTelaY = teiaAncoradaNoPredioY - scrollCamera;
        int ancoraTelaX = teiaAncoradaNoPredioX + ((LARGURA_TELA - LARGURA_PREDIO) / 2);

        int x0 = miranha.x + INICIO_TEIA_X;
        int y0 = miranha.y;
        int x1 = ancoraTelaX;
        int y1 = ancoraTelaY;

        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy, e2;

        while (true) {
            if (y0 >= 0 && y0 < ALTURA_JOGO_PRINCIPAL && x0 >= 0 && x0 < LARGURA_TELA) {
                int indice = (y0 + ALTURA_HUD_SINGULAR) * LARGURA_TELA + x0;
                bufferConsole[indice].Char.UnicodeChar = '.';
                bufferConsole[indice].Attributes = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
            }
                if (x0 == x1 && y0 == y1){
                    break;
                }
            e2 = 2 * err;

            if (e2 >= dy){ 
                err += dy; 
                x0 += sx; 
            }

            if (e2 <= dx) { 
                err += dx; 
                y0 += sy; 
            }
        }
    }
}

void DesenharHUD() {
    char textoPontos[30];
    sprintf(textoPontos, "PONTOS: %d", pontuacao);
    int indiceTextoPontos = (LARGURA_TELA - strlen(textoPontos)) / 2;

    for (int i = 0; i < strlen(textoPontos); i++) {
        bufferConsole[i + indiceTextoPontos].Char.UnicodeChar = textoPontos[i];
    }

    int linhaInferiorY = ALTURA_JOGO_PRINCIPAL + ALTURA_HUD_SINGULAR;

    char textoVidas[9];
    sprintf(textoVidas, "VIDAS: %d", vidas);
    for (int i = 0; i < strlen(textoVidas); i++) {
        int indiceTextoVidas = linhaInferiorY * LARGURA_TELA + i;
        bufferConsole[indiceTextoVidas].Char.UnicodeChar = textoVidas[i];
        if(vidas == 1 && i == strlen(textoVidas) - 1){
            bufferConsole[indiceTextoVidas].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
        }
    }

    for (int i = 0; i < tempoRestante; i++) {
        int x = LARGURA_TELA - TEMPO_MAXIMO - 1 + i;
        int indiceTempoRestante = linhaInferiorY * LARGURA_TELA + x;
        bufferConsole[indiceTempoRestante].Char.UnicodeChar = '#';
        if(tempoRestante > 4){
            bufferConsole[indiceTempoRestante].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        } else{
            bufferConsole[indiceTempoRestante].Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;
        }
    }
}

void DesenharTela(){
    LimparBuffer();
    
    DesenharHUD();
    DesenharPredio();
    DesenharBombas();
    DesenharInimigos();

    if (soltandoTeia || teiaAncorada) {
        DesenharTeia();
    }
    DesenharDoente();
    DesenharMiranha();
 
    DesenharBuffer();
}

void ControlarTeia() {
    if (!soltandoTeia && !quedaFatal) {
        teiaAncorada = false;
        direcaoAtualTeia = NENHUMA;

        if (GetAsyncKeyState(VK_UP) & 0x8000){
            direcaoAtualTeia = CIMA;
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000){
            direcaoAtualTeia = DIAGONAL_ESQUERDA;   
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000){
            direcaoAtualTeia = DIAGONAL_DIREITA;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000){
            direcaoAtualTeia = ANCORA_LOCAL;
        }

        if (direcaoAtualTeia != NENHUMA) {
            soltandoTeia = true;
            tempoSegurandoEspaco = 0;
            tamanhoTeiaDisparando = 1;
        }
    }
    else {
        if (direcaoAtualTeia != ANCORA_LOCAL) {
            tempoSegurandoEspaco += ATRASO_TIQUE;
            if (tempoSegurandoEspaco > 150 && tamanhoTeiaDisparando == 1) {
                tamanhoTeiaDisparando = 2;
            } else if (tempoSegurandoEspaco > 300 && tamanhoTeiaDisparando == 2) {
                tamanhoTeiaDisparando = 3;
            } else if (tempoSegurandoEspaco > 450 && tamanhoTeiaDisparando == 3) {
                tamanhoTeiaDisparando = 4;
            } else if (tempoSegurandoEspaco > 600 && tamanhoTeiaDisparando == 4) {
                tamanhoTeiaDisparando = 5;
            }
        }
    }
}

void ControlarTeia2(){
    soltandoTeia = false;

    int teia_x_final_tela = -1, teia_y_final_tela = -1;
    bool colidiu = false;

    for (int i = 1; i <= tamanhoTeiaDisparando; i++) {
        int teia_x_tela = -1, teia_y_tela = -1;
        switch (direcaoAtualTeia) {
            case CIMA: teia_y_tela = miranha.y - i; teia_x_tela = miranha.x + INICIO_TEIA_X; break;
            case DIAGONAL_ESQUERDA: teia_y_tela = miranha.y - i; teia_x_tela = miranha.x + 1 - i; break;
            case DIAGONAL_DIREITA: teia_y_tela = miranha.y - i; teia_x_tela = miranha.x + INICIO_TEIA_X + i; break;
            default: break;
        }

        if (i == tamanhoTeiaDisparando) {
            teia_x_final_tela = teia_x_tela;
            teia_y_final_tela = teia_y_tela;
        }

        if(teia_x_tela != -1) {
            for (int j = 0; j < maxInimigoAtual; j++) {
                if(inimigos[j].ativo) {
                    int inimigoTelaY = inimigos[j].y - scrollCamera, inimigoTelaX = inimigos[j].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                    if(teia_x_tela >= inimigoTelaX && teia_x_tela < inimigoTelaX + LARGURA_INIMIGO_JANELA && teia_y_tela >= inimigoTelaY && teia_y_tela < inimigoTelaY + ALTURA_INIMIGO_JANELA) {
                        colidiu = true;
                        inimigos[j].ativo = false;
                        break;
                    }
                }
            }
            if(colidiu) break;
            for (int j = 0; j < maxBombaAtual; j++) {
                if(bombas[j].ativo) {
                    int bombaTelaY = bombas[j].y - scrollCamera, bombaTelaX = bombas[j].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                    if(teia_x_tela == bombaTelaX && teia_y_tela == bombaTelaY) {
                        colidiu = true;
                        bombas[j].ativo = false;
                        break;
                    }
                }
            }
            if(colidiu) break;
        }
    }

    if (colidiu) {
        quedaComum = true;
    } else if (direcaoAtualTeia == ANCORA_LOCAL) {
        int teiaTelaY = miranha.y;
        int teiaTelaX = miranha.x + INICIO_TEIA_X;
        int predioY = teiaTelaY + scrollCamera;
        int predioX = teiaTelaX - ((LARGURA_TELA - LARGURA_PREDIO) / 2);

        if (predioY >= 0 && predioY < ALTURA_PREDIO && predioX >= 0 && predioX < LARGURA_PREDIO && PREDIO[predioY][predioX] == '|') {
            teiaAncorada = true;
            teiaAncoradaNoPredioX = predioX;
            teiaAncoradaNoPredioY = predioY;
            tamanhoTeiaAncorada = 0;
            if (quedaComum) {
                scrollCamera = scrollCamera + (miranha.y - MIRANHA_CENTRALIZADO_Y);
                if (scrollCamera > (ALTURA_PREDIO - ALTURA_JOGO_PRINCIPAL)) {
                    scrollCamera = ALTURA_PREDIO - ALTURA_JOGO_PRINCIPAL;
                }
                if (scrollCamera < 0) {
                    scrollCamera = 0;
                }
                miranha.y = MIRANHA_CENTRALIZADO_Y;
                quedaComum = false;
            }
        } else {
            quedaComum = true;
        }
    } else {
        int predioY = teia_y_final_tela + scrollCamera;
        int predioX = teia_x_final_tela - ((LARGURA_TELA - LARGURA_PREDIO) / 2);

        if (direcaoAtualTeia != NENHUMA && predioY >= 0 && predioY < ALTURA_PREDIO && predioX >= 0 && predioX < LARGURA_PREDIO && PREDIO[predioY][predioX] == '|') {
            teiaAncorada = true;
            teiaAncoradaNoPredioX = predioX;
            teiaAncoradaNoPredioY = predioY;
            tamanhoTeiaAncorada = tamanhoTeiaDisparando;
            if (quedaComum) {
                scrollCamera = scrollCamera + (miranha.y - MIRANHA_CENTRALIZADO_Y);
                if (scrollCamera > (ALTURA_PREDIO - ALTURA_JOGO_PRINCIPAL)) scrollCamera = ALTURA_PREDIO - ALTURA_JOGO_PRINCIPAL;
                if (scrollCamera < 0) scrollCamera = 0;
                miranha.y = MIRANHA_CENTRALIZADO_Y;
                quedaComum = false;
            }
        } else {
            quedaComum = true;
        }
    }
    direcaoAtualTeia = NENHUMA;
    tempoSegurandoEspaco = 0;
    tamanhoTeiaDisparando = 0;

}

void EscolherControleTeia() {
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        ControlarTeia();
    } else if (soltandoTeia) {
        ControlarTeia2();
    }
}

void MovimentarMiranha() {  
    if (teiaAncorada) {
        int ancoraTelaY = teiaAncoradaNoPredioY - scrollCamera;
        int ancoraTelaX = teiaAncoradaNoPredioX + ((LARGURA_TELA - LARGURA_PREDIO) / 2);

        if ((GetAsyncKeyState(VK_UP) & 0x8000) && tamanhoTeiaAncorada > 0) {
            if (miranha.y > MIRANHA_CENTRALIZADO_Y) {
                miranha.y--;
            }
            else if (scrollCamera > 0) {
                scrollCamera--;
            }
            else {
                miranha.y--;
            }


            if (miranha.x + INICIO_TEIA_X < ancoraTelaX) {
                miranha.x++;
            }
            if (miranha.x + INICIO_TEIA_X > ancoraTelaX) {
                miranha.x--;
            }

            tamanhoTeiaAncorada--;
            if (tamanhoTeiaAncorada == 0) {
                teiaAncorada = false;
            }
        }
        else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && tamanhoTeiaAncorada < 5 && miranha.y <= MIRANHA_CENTRALIZADO_Y) {
            if (miranha.y < MIRANHA_CENTRALIZADO_Y) {
                miranha.y++;
            } else if ((scrollCamera + ALTURA_JOGO_PRINCIPAL) < ALTURA_PREDIO) {
                scrollCamera++;
            } else if (miranha.y < ALTURA_JOGO_PRINCIPAL - ALTURA_MIRANHA) {
                miranha.y++;
            }

            if (miranha.x > 0 && miranha.x + INICIO_TEIA_X > ancoraTelaX) {
                miranha.x--;
            }
            if (miranha.x < LARGURA_TELA - LARGURA_MIRANHA && miranha.x + INICIO_TEIA_X < ancoraTelaX) {
                miranha.x++;
            }

            tamanhoTeiaAncorada++;
        }
    }
}

void MovimentarDoente(){
    if(scrollCamera == 0){ scrollDoente = 0; doente.y = 4; }
    else if(scrollCamera == 1){ scrollDoente = 0; doente.y = 3;}
    else if(scrollCamera == 2){ scrollDoente = 0; doente.y = 2; }
    else if(scrollCamera == 3){ scrollDoente = 0; doente.y = 1; }
    else if(scrollCamera == 4){ scrollDoente = 0; doente.y = 0; }
    else if(scrollCamera == 5){ scrollDoente = 1; doente.y = 0; }
    else if(scrollCamera == 6){ scrollDoente = 2; doente.y = 0; }
    else if(scrollCamera == 7){ scrollDoente = 3; doente.y = 0; }

    if(doente.x < 65 && doente.direita == true){
        doente.x++;
        doente.esquerda = false;
        doente.direita = true;
    }
    else{
        doente.direita = false;
        doente.esquerda = true;
    }

    if(doente.x > 10 && doente.esquerda == true){
        doente.x--;
        doente.esquerda = true;
        doente.direita = false;
    }
    else{
        doente.esquerda = false;
        doente.direita = true;
    }
}

void SpawnInimigos() {
    if (rand() % 100 >= probabilidadeInimigo) {
        return;
    }

    int inimigosAtivos = 0;
    for (int i = 0; i < maxInimigoAtual; i++) {
        if (inimigos[i].ativo) {
            inimigosAtivos++;
        }
    }

    if (inimigosAtivos < maxInimigoAtual) {
        int slotVazio = -1;
        for (int i = 0; i < maxInimigoAtual; i++) {
            if (!inimigos[i].ativo) {
                slotVazio = i;
                break;
            }
        }

    int miranha_x1 = miranha.x, miranha_y1 = miranha.y, miranha_x2 = miranha.x + LARGURA_MIRANHA, miranha_y2 = miranha.y + ALTURA_MIRANHA;
    
        if (slotVazio != -1) {
            COORD janelasDisponiveis[NUM_POSICOES_JANELAS];
            int countDisponiveis = 0;

            for (int i = 0; i < NUM_POSICOES_JANELAS; i++) {
                bool naTela = posicoesJanelas[i].Y >= scrollCamera && posicoesJanelas[i].Y < scrollCamera + ALTURA_JOGO_PRINCIPAL;
                if (naTela) {
                    bool posicaoOcupada = false;
                    bool miranhaOcupa = false;
                    for (int j = 0; j < maxInimigoAtual; j++) {
                        int inimigoTelaY = inimigos[j].y - scrollCamera, inimigoTelaX = inimigos[j].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                        int inimigo_x1 = inimigoTelaX, inimigo_y1 = inimigoTelaY, inimigo_x2 = inimigoTelaX + LARGURA_INIMIGO_JANELA, inimigo_y2 = inimigoTelaY + ALTURA_INIMIGO_JANELA;
                        if (inimigos[j].ativo && inimigos[j].x == posicoesJanelas[i].X + 1 && inimigos[j].y == posicoesJanelas[i].Y + 2) {
                            posicaoOcupada = true;
                            break;
                        }

                        if (miranha_x1 < inimigo_x2 && miranha_x2 > inimigo_x1 && miranha_y1 < inimigo_y2 && miranha_y2 > inimigo_y1) {
                            miranhaOcupa = true;
                            break;     
                        }
                    }                       
            
                    if (!posicaoOcupada && !miranhaOcupa) {
                        janelasDisponiveis[countDisponiveis] = posicoesJanelas[i];
                        countDisponiveis++;
                    }
                }
            }

            if (countDisponiveis > 0) {
                int posIndex = rand() % countDisponiveis;
                inimigos[slotVazio].ativo = true;
                inimigos[slotVazio].x = janelasDisponiveis[posIndex].X + 1;
                inimigos[slotVazio].y = janelasDisponiveis[posIndex].Y + 2;
                inimigos[slotVazio].tempoNoLugar = 0;
            }
        }
    }
}

void SpawnBombas() {
    if (rand() % 100 >= probabilidadeBomba) {
        return;
    }
    int bombasAtivas = 0;
    for(int i = 0; i < maxBombaAtual; i++) {
        if(bombas[i].ativo) {
            bombasAtivas++;
        }
    }

    if(bombasAtivas < maxBombaAtual) {
        int slotVazio = -1;
        for(int i = 0; i < maxBombaAtual; i++) {
            if(!bombas[i].ativo) {
                slotVazio = i;
                break;
            }
        }

        if(slotVazio != -1) {
            COORD bombasDisponiveis[LARGURA_PREDIO * ALTURA_PREDIO];
            int countDisponiveis = 0;

            for (int y = 4; y <= 22; y++) {

                for (int x = 0; x < LARGURA_PREDIO; x++) {
                    if (PREDIO[y][x] == '|') {
                        bool naTela = y >= scrollCamera && y < scrollCamera + ALTURA_JOGO_PRINCIPAL;
                        if (naTela) {
                            bool ocupada = false;
                            for(int j = 0; j < maxBombaAtual; j++) {
                                if(bombas[j].ativo && bombas[j].x == x && bombas[j].y == y) {
                                    ocupada = true;
                                    break;
                                }
                            }
                            bool ocupadaPeloMiranha = false;
                            int bombaTelaX = x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                            int bombaTelaY = y - scrollCamera;
                            if(bombaTelaX >= miranha.x && bombaTelaX < miranha.x + LARGURA_MIRANHA &&
                               bombaTelaY >= miranha.y && bombaTelaY < miranha.y + ALTURA_MIRANHA) {
                                ocupadaPeloMiranha = true;
                            }

                            if(!ocupada && !ocupadaPeloMiranha) {
                                bombasDisponiveis[countDisponiveis].X = x;
                                bombasDisponiveis[countDisponiveis].Y = y;
                                countDisponiveis++;
                            }
                        }
                    }
                }
            }

            if(countDisponiveis > 0) {
                int posIndex = rand() % countDisponiveis;
                bombas[slotVazio].ativo = true;
                bombas[slotVazio].x = bombasDisponiveis[posIndex].X;
                bombas[slotVazio].y = bombasDisponiveis[posIndex].Y;
                bombas[slotVazio].tempoNoLugar = 0;
            }
        }
    }
}

void AtualizarInimigos() {
    int miranha_x1 = miranha.x, miranha_y1 = miranha.y, miranha_x2 = miranha.x + LARGURA_MIRANHA, miranha_y2 = miranha.y + ALTURA_MIRANHA;
    for (int i = 0; i < maxInimigoAtual; i++) {
        
        if (inimigos[i].ativo) {
            inimigos[i].tempoNoLugar += ATRASO_TIQUE;
            if (inimigos[i].tempoNoLugar >= 4000) {
                int tentativas = 0;
                while (tentativas < NUM_POSICOES_JANELAS) {
                    int posIndex = rand() % NUM_POSICOES_JANELAS;
                    bool posicaoOcupada = false;
                    bool miranhaOcupa = false;
                    for (int j = 0; j < maxInimigoAtual; j++) {
                        int inimigoTelaY = inimigos[j].y - scrollCamera, inimigoTelaX = inimigos[j].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                        int inimigo_x1 = inimigoTelaX, inimigo_y1 = inimigoTelaY, inimigo_x2 = inimigoTelaX + LARGURA_INIMIGO_JANELA, inimigo_y2 = inimigoTelaY + ALTURA_INIMIGO_JANELA;
                        if (i != j && inimigos[j].ativo && inimigos[j].x == posicoesJanelas[posIndex].X + 1 && inimigos[j].y == posicoesJanelas[posIndex].Y + 2) {
                            posicaoOcupada = true;
                            break;
                        }
                        if (miranha_x1 < inimigo_x2 && miranha_x2 > inimigo_x1 && miranha_y1 < inimigo_y2 && miranha_y2 > inimigo_y1) {
                            miranhaOcupa = true;
                            break;     
                        }
                    }
                    if (!posicaoOcupada && !miranhaOcupa) {
                        inimigos[i].x = posicoesJanelas[posIndex].X + 1;
                        inimigos[i].y = posicoesJanelas[posIndex].Y + 2;
                        inimigos[i].tempoNoLugar = 0;
                        break;
                    }
                    tentativas++;
                }
            }
        }
    }
}

void AtualizarBombas() {
    for (int i = 0; i < maxBombaAtual; i++) {
        if (bombas[i].ativo) {
            bombas[i].tempoNoLugar += ATRASO_TIQUE;
            if (bombas[i].tempoNoLugar >= 4000) {
                bombas[i].ativo = false;
            }
        }
    }
}

void VerificarQuedaMiranha(){
    if(miranha.x <= (((LARGURA_TELA - LARGURA_PREDIO) / 2) - 1) || miranha.x >= (LARGURA_PREDIO + ((LARGURA_TELA - LARGURA_PREDIO) / 2)) - LARGURA_MIRANHA){
        quedaComum = true;
    }
    if (!teiaAncorada && !soltandoTeia && !quedaComum) {
        bool tocandoPredio = false;
        for (int i = 0; i < ALTURA_MIRANHA; i++) {
            for (int j = 0; j < LARGURA_MIRANHA; j++) {
                if (CORPO_MIRANHA[i][j] == ' ') { continue; }
                int predioY = (miranha.y + i) + scrollCamera;
                int predioX = (miranha.x + j) - ((LARGURA_TELA - LARGURA_PREDIO) / 2);

                if (predioY >= 0 && predioY < ALTURA_PREDIO && predioX >= 0 && predioX < LARGURA_PREDIO) {
                    if (PREDIO[predioY][predioX] == '|') {
                        tocandoPredio = true;
                        break;
                    }
                }
            }
            if (tocandoPredio) { break; }
        }

        if (!tocandoPredio) {
            quedaComum = true;
        }
    }
    if (quedaComum) {
        teiaAncorada = false;
        if((ALTURA_JOGO_PRINCIPAL + scrollCamera) < 65){
            scrollCamera++;
        }
    }
}

void VerificarMiranhaCaiuChao(){
    if(quedaComum == true && (ALTURA_JOGO_PRINCIPAL + scrollCamera) == 65){
        miranha.y++;
        if(miranha.y >= ALTURA_JOGO_PRINCIPAL - ALTURA_MIRANHA){
            PerderVida();
        }
    }
}

void CorrigirPosicaoMiranha(){
    if(miranha.x <= 0) {
        miranha.x = 1;
    } else if(miranha.x >= LARGURA_TELA - LARGURA_MIRANHA) {
        miranha.x = LARGURA_TELA - LARGURA_MIRANHA - 1;
    }

    if(miranha.y <= 0) {
        miranha.y = 1;
    }
}

void VerificarColisoes() {
    if (quedaComum || quedaFatal) {
        return;
    }

    int doente_x1 = doente.x, doente_y1 = doente.y, doente_x2 = doente.x + LARGURA_DOENTE, doente_y2 = doente.y + ALTURA_DOENTE;
    int miranha_x1 = miranha.x, miranha_y1 = miranha.y, miranha_x2 = miranha.x + LARGURA_MIRANHA, miranha_y2 = miranha.y + ALTURA_MIRANHA;

    if (miranha_x1 < doente_x2 && miranha_x2 > doente_x1 && miranha_y1 < doente_y2 && miranha_y2 > doente_y1) {
        som_colidir_doente = true;
        quedaComum = true;
        return;
    }

    for (int i = 0; i < maxInimigoAtual; i++) {
        if (inimigos[i].ativo) {
            int inimigoTelaY = inimigos[i].y - scrollCamera, inimigoTelaX = inimigos[i].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
            int inimigo_x1 = inimigoTelaX, inimigo_y1 = inimigoTelaY, inimigo_x2 = inimigoTelaX + LARGURA_INIMIGO_JANELA, inimigo_y2 = inimigoTelaY + ALTURA_INIMIGO_JANELA;
            if (miranha_x1 < inimigo_x2 && miranha_x2 > inimigo_x1 && miranha_y1 < inimigo_y2 && miranha_y2 > inimigo_y1) {
                pontuacao += 30;
                som_colidir_inimigo = true;
                inimigos[i].ativo = false;
                if(tempoRestante < TEMPO_MAXIMO){
                    tempoRestante++;
                }
                return;
            }
        }
    }

    for(int i = 0; i < maxBombaAtual; i++) {
        if(bombas[i].ativo) {
            int bombaTelaY = bombas[i].y - scrollCamera;
            int bombaTelaX = bombas[i].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
            if(miranha_x1 < bombaTelaX + 1 && miranha_x2 > bombaTelaX && miranha_y1 < bombaTelaY + 1 && miranha_y2 > bombaTelaY) {
                pontuacao += 80;
                som_colidir_bomba = true;
                bombas[i].ativo = false;
                if(tempoRestante < TEMPO_MAXIMO){
                    tempoRestante++;
                }
                return;
            }
        }
    }

    if (teiaAncorada) {
        int ancoraTelaY = teiaAncoradaNoPredioY - scrollCamera, ancoraTelaX = teiaAncoradaNoPredioX + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
        int x0 = miranha.x + INICIO_TEIA_X, y0 = miranha.y;
        int x1 = ancoraTelaX, y1 = ancoraTelaY;
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = dx + dy, e2;
        while (true) {
            if (scrollCamera <= 4) {
                if (x0 >= doente_x1 && x0 < doente_x2 && y0 >= doente_y1 && y0 < doente_y2) {
                    quedaComum = true;
                    return;

                }
            }
            for (int j = 0; j < maxInimigoAtual; j++) {
                if(inimigos[j].ativo) {
                    int inimigoTelaY = inimigos[j].y - scrollCamera, inimigoTelaX = inimigos[j].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                    if(x0 >= inimigoTelaX && x0 < inimigoTelaX + LARGURA_INIMIGO_JANELA && y0 >= inimigoTelaY && y0 < inimigoTelaY + ALTURA_INIMIGO_JANELA) {
                        quedaComum = true;
                        inimigos[j].ativo = false;
                        return;
                    }
                }
            }
            for (int j = 0; j < maxBombaAtual; j++) {
                if(bombas[j].ativo) {
                    int bombaTelaY = bombas[j].y - scrollCamera, bombaTelaX = bombas[j].x + ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                    if(x0 == bombaTelaX && y0 == bombaTelaY) {
                        quedaComum = true;
                        bombas[j].ativo = false;
                        return;
                    }
                }
            }

            if (x0 == x1 && y0 == y1) {
                break;
            }

            e2 = 2 * err;

            if (e2 >= dy) {
                err += dy;
                x0 += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y0 += sy;
            }
        }
    }

    for (int i = 0; i < ALTURA_MIRANHA; ++i) {
        for (int j = 0; j < LARGURA_MIRANHA; ++j) {
            if (CORPO_MIRANHA[i][j] != ' ') {
                int miranhaTelaX = miranha.x + j, miranhaTelaY = miranha.y + i;
                int predioY = miranhaTelaY + scrollCamera, predioX = miranhaTelaX - ((LARGURA_TELA - LARGURA_PREDIO) / 2);
                if (predioY >= 0 && predioY < ALTURA_PREDIO && predioX >= 0 && predioX < LARGURA_PREDIO) {
                    if (PREDIO[predioY][predioX] == '#') { 
                        musica = true;

                        VencerNivel();
                        return;
                    }
                }
            }
        }
    }
}

void AtualizarTempo() {
    contadorTempo += ATRASO_TIQUE;
    if (contadorTempo >= DECREMENTO_TEMPO) {
        tempoRestante--;
        contadorTempo = 0;
    }
    if (tempoRestante <= 0) {
        quedaComum = true;
        quedaFatal = true;
    }
}

void VoltarMenu(){
    if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
        inicio_game = false;
        pausado = true;

        LimparBuffer();
        DesenharBuffer();

        mostrarMenu = true;
        MenuInicial();
    }
}

DWORD WINAPI Jogo(LPVOID lpParam){
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8);

    console = GetStdHandle(STD_OUTPUT_HANDLE);

    EsconderCursorConsole();

    recorde = LerRecorde();

    MenuInicial();
    while (true)
    {
        SpawnInimigos();
        SpawnBombas();

        AtualizarInimigos();
        AtualizarBombas();
        AtualizarTempo();

        EscolherControleTeia();

        VerificarQuedaMiranha();
        MovimentarMiranha();

        MovimentarDoente();

        VerificarColisoes();

        CorrigirPosicaoMiranha();
        VerificarMiranhaCaiuChao();

        DesenharTela();

        VoltarMenu();

        Sleep(ATRASO_TIQUE);
    }

    return 0;
}

void SomDisparoTeia(){
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !quedaFatal){
        if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000){
            if(tamanhoTeiaDisparando < 5){
                Beep(349, 150);
                Sleep(100);
            }
            else if(tamanhoTeiaDisparando == 5 && !fim_som_disparo){
                Beep(349, 150);
                Sleep(100);
                fim_som_disparo = true;
            }
        }
    }   
        
    if(tamanhoTeiaDisparando == 0){
        fim_som_disparo = false;
    }
}

void SomTeiaAncorada(){
    if(teiaAncorada){
        if(GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000){
            if(tamanhoTeiaAncorada < 5){
                Beep(261, 150);
                Sleep(100);
            } 
        }
    }
}

void SomQuedaMiranha(){
    if(quedaComum || quedaFatal){
        if(!som_colidir_doente){
            Beep(392, 150);
            Sleep(50);
            Beep(261, 150);
            Sleep(50);
            Beep(329, 150);
            Sleep(50);
        }
    } 
}

void SomColodirElementos(bool colisao, int frequncia){
    if(colisao == true){
        Beep(frequncia, 150);
        Sleep(50);

        som_colidir_inimigo = false;
        som_colidir_bomba = false;
        som_colidir_doente = false;
    }
}  

void Musica(){
    musica = true;

    Beep(294, 225);
    Beep(294, 75);
    Beep(440, 300);
    Sleep(150);

    Beep(294, 225);
    Beep(294, 75);
    Beep(440, 300);
    Sleep(150);

    Beep(440, 150);
    Beep(392, 150);
    Beep(349, 150);
    Beep(330, 150);
    Beep(294, 150);
    Beep(330, 150);
    Beep(349, 150);
    Beep(294, 300);
    Sleep(1000);

    musica = false;
}

void GameOverMusica(){
    Sleep(500);
    Beep(440, 150);
    Sleep(50);

    Beep(392, 200);
    Beep(349, 200);
    Beep(330, 200);
    Beep(294, 400);

    Sleep(300);

    Beep(261, 500);
    Sleep(150);
    Beep(196, 1000);

    game_over_musica = false;
}                                        
                                 
DWORD WINAPI EfeitosSonoros(LPVOID lpParam){
    while(true){
        if(game_over_musica){
            musica = false;
            GameOverMusica();
        }
        else if(musica || mostrarMenu){
            Musica();
        }
        else{
            SomDisparoTeia();
            SomTeiaAncorada();
            SomColodirElementos(som_colidir_doente, 493);
            SomQuedaMiranha();
            SomColodirElementos(som_colidir_inimigo, 392);
            SomColodirElementos(som_colidir_bomba, 440);
        }
    }

    return 0;
}

int main(){
    HANDLE thread1;
    HANDLE thread2;

    thread1 = CreateThread(NULL, 0, Jogo, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, EfeitosSonoros, NULL, 0, NULL);

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    return 0;
}
