#include "minhasbibliotecas.h"

int comprimento;
int curva_no;
int len;
char tecla;
void gravar();
void carregar();
int vida;
void Atraso(long double);
void Mover();
void Comida();
int Pontuacao();
void Imprimir();
void gotoxy(int x, int y);
void GotoXY(int x, int y);
void Curva();
void Borda();
void Baixo();
void Esquerda();
void Cima();
void Direita();
void SairDoJogo();
int SomentePontuacao();

struct coordenada
{
    int x;
    int y;
    int direcao;
};

typedef struct coordenada coordenada;

coordenada cabeca, curva[500], comida, corpo[30];

int main()
{
#include "minhasbibliotecas.h"
    char tecla;

    Imprimir();

    system("cls");

    carregar();

    comprimento = 5;

    cabeca.x = 25;

    cabeca.y = 20;

    cabeca.direcao = DIREITA;

    Borda();

    Comida(); //para gerar as coordenadas da comida inicialmente

    vida = 3; //número de vidas extras

    curva[0] = cabeca;

    Mover();   //inicializando a coordenada da curva inicial

    return 0;
}

void Mover()
{
    int a, i;

    do
    {

        Comida();
        fflush(stdin);

        len = 0;

        for (i = 0; i < 30; i++)

        {

            corpo[i].x = 0;

            corpo[i].y = 0;

            if (i == comprimento)

                break;
        }

        Atraso(comprimento);

        Borda();

        if (cabeca.direcao == DIREITA)

            Direita();

        else if (cabeca.direcao == ESQUERDA)

            Esquerda();

        else if (cabeca.direcao == BAIXO)

            Baixo();

        else if (cabeca.direcao == CIMA)

            Cima();

        SairDoJogo();

    } while (!kbhit());

    a = getch();

    if (a == 27)

    {

        system("cls");

        exit(0);

    }
    tecla = getch();

    if ((tecla == DIREITA && cabeca.direcao != ESQUERDA && cabeca.direcao != DIREITA) || (tecla == ESQUERDA && cabeca.direcao != DIREITA && cabeca.direcao != ESQUERDA) || (tecla == CIMA && cabeca.direcao != BAIXO && cabeca.direcao != CIMA) || (tecla == BAIXO && cabeca.direcao != CIMA && cabeca.direcao != BAIXO))

    {

        curva_no++;

        curva[curva_no] = cabeca;

        cabeca.direcao = tecla;

        if (tecla == CIMA)

            cabeca.y--;

        if (tecla == BAIXO)

            cabeca.y++;

        if (tecla == DIREITA)

            cabeca.x++;

        if (tecla == ESQUERDA)

            cabeca.x--;

        Mover();
    }

    else if (tecla == 27)

    {

        system("cls");

        exit(0);

    }

    else

    {

        printf("\a");

        Mover();
    }
}

void gotoxy(int x, int y)
{

    COORD coord;

    coord.X = x;

    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a, b);
}

void carregar()
{
    int linha, coluna, r, c, q;
    gotoxy(36, 14);
    printf("CARREGANDO O JOGO...");
    gotoxy(30, 15);
    for (r = 1; r <= 20; r++)
    {
        for (q = 0; q <= 100000000; q++); //para exibir o caractere lentamente
        printf("%c", 177);
    }
    getch();
}

void Baixo()
{
    int i;
    for (i = 0; i <= (cabeca.y - curva[curva_no].y) && len < comprimento; i++)
    {
        GotoXY(cabeca.x, cabeca.y - i);
        {
            if (len == 0)
                printf("v");
            else
                printf("=");
        }
        corpo[len].x = cabeca.x;
        corpo[len].y = cabeca.y - i;
        len++;
    }
    Curva();
    if (!kbhit())
        cabeca.y++;
}

void Atraso(long double k)
{
    Pontuacao();
    long double i;
    for (i = 0; i <= (10000000); i++);
}

void SairDoJogo()
{
    int i, check = 0;
    for (i = 4; i < comprimento; i++)
    {
        if (corpo[0].x == corpo[i].x && corpo[0].y == corpo[i].y)
        {
            check++;
        }
        if (i == comprimento || check != 0)
            break;
    }
    if (cabeca.x <= 10 || cabeca.x >= 70 || cabeca.y <= 10 || cabeca.y >= 30 || check != 0)
    {
        vida--;
        if (vida >= 0)
        {
            cabeca.x = 25;
            cabeca.y = 20;
            curva_no = 0;
            cabeca.direcao = DIREITA;
            Mover();
        }
        else
        {
            system("cls");
            printf("Todas as vidas completas\nMais sorte na próxima vez!!!\nPressione qualquer tecla para sair do jogo\n");
            gravar();
            exit(0);
        }
    }
}

void Comida()
{
    if (cabeca.x == comida.x && cabeca.y == comida.y)
    {
        comprimento++;
        time_t a;
        a = time(0);
        srand(a);
        comida.x = rand() % 70;
        if (comida.x <= 10)
            comida.x += 11;
        comida.y = rand() % 30;
        if (comida.y <= 10)

            comida.y += 11;
    }
    else if (comida.x == 0)
    {
        comida.x = rand() % 70;
        if (comida.x <= 10)
            comida.x += 11;
        comida.y = rand() % 30;
        if (comida.y <= 10)
            comida.y += 11;
    }
}

void Esquerda()
{
    int i;
    for (i = 0; i <= (curva[curva_no].x - cabeca.x) && len < comprimento; i++)
    {
        GotoXY((cabeca.x + i), cabeca.y);
        {
            if (len == 0)
                printf("<");
            else
                printf("=");
        }
        corpo[len].x = cabeca.x + i;
        corpo[len].y = cabeca.y;
        len++;
    }
    Curva();
    if (!kbhit())
        cabeca.x--;

}

void Direita()
{
    int i;
    for (i = 0; i <= (cabeca.x - curva[curva_no].x) && len < comprimento; i++)
    {
        corpo[len].x = cabeca.x - i;
        corpo[len].y = cabeca.y;
        GotoXY(corpo[len].x, corpo[len].y);
        {
            if (len == 0)
                printf(">");
            else
                printf("=");
        }
        len++;
    }
    Curva();
    if (!kbhit())
        cabeca.x++;
}

void Curva()
{
    int i, j, diff;
    for (i = curva_no; i >= 0 && len < comprimento; i--)
    {
        if (curva[i].x == curva[i - 1].x)
        {
            diff = curva[i].y - curva[i - 1].y;
            if (diff < 0)
                for (j = 1; j <= (-diff); j++)
                {
                    corpo[len].x = curva[i].x;
                    corpo[len].y = curva[i].y + j;
                    GotoXY(corpo[len].x, corpo[len].y);
                    printf("*");
                    len++;
                    if (len == comprimento)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff; j++)
                {
                    corpo[len].x = curva[i].x;
                    corpo[len].y = curva[i].y - j;
                    GotoXY(corpo[len].x, corpo[len].y);
                    printf("*");
                    len++;
                    if (len == comprimento)
                        break;
                }
        }
        else if (curva[i].y == curva[i - 1].y)
        {
            diff = curva[i].x - curva[i - 1].x;
            if (diff < 0)
                for (j = 1; j <= (-diff) && len < comprimento; j++)
                {
                    corpo[len].x = curva[i].x + j;
                    corpo[len].y = curva[i].y;
                    GotoXY(corpo[len].x, corpo[len].y);
                    printf("*");
                    len++;
                    if (len == comprimento)
                        break;
                }
            else if (diff > 0)
                for (j = 1; j <= diff && len < comprimento; j++)
                {
                    corpo[len].x = curva[i].x - j;
                    corpo[len].y = curva[i].y;
                    GotoXY(corpo[len].x, corpo[len].y);
                    printf("*");
                    len++;
                    if (len == comprimento)
                        break;
                }
        }
    }
}

void Borda()
{
    system("cls");
    int i;
    GotoXY(comida.x, comida.y);
    printf("X");
    for (i = 10; i < 71; i++)
    {
        GotoXY(i, 10);
        printf("||");
        GotoXY(i, 30);
        printf("||");
    }
    for (i = 10; i < 31; i++)
    {
        GotoXY(10, i);
        printf("||");
        GotoXY(70, i);
        printf("||");
    }
}

void Imprimir()
{
    printf("\tBEM-VINDO AO JOGO DA COBRINHA \n\t\n(pressione qualquer tecla para continuar)\n");
    getch();
    system("cls");
    printf("\tInstruções do jogo:\n");
    printf("\n-> Use as setas do teclado para mover a cobra.\n\n-> Você receberá alimentos (x) em várias coordenadas da tela que você deve comer. Sempre que você come um alimento, o comprimento da cobra aumentará em 1 elemento e, assim, a pontuação.\n\n-> Aqui você tem 3 vidas. Sua vida diminuirá se você bater na parede ou no corpo da cobra.\n\n-> Você também pode pausar o jogo no meio pressionando qualquer tecla e para continuar o jogo pausado, pressione qualquer outra tecla novamente.\n\n-> Se quiser sair, pressione ESC. \n");
    printf("\n\nPressione qualquer tecla para jogar...");
    if (getch() == 27)
        exit(0);
}

void gravar()
{
    char nome_jogador[20], nome_jogador_formatado[20], caractere, c;
    int i, j, px;
    FILE *info;
    info = fopen("record.txt", "a+");
    getch();
    system("cls");
    printf("Digite seu nome\n");
    scanf("%[^\n]", nome_jogador);
    //************************
    for (j = 0; nome_jogador[j] != '\0'; j++)
    {
        nome_jogador_formatado[0] = toupper(nome_jogador[0]);
        if (nome_jogador[j - 1] == ' ')
        {
            nome_jogador_formatado[j] = toupper(nome_jogador[j]);
            nome_jogador_formatado[j - 1] = nome_jogador[j - 1];
        }
        else
            nome_jogador_formatado[j] = nome_jogador[j];
    }
    nome_jogador_formatado[j] = '\0';
    fprintf(info, "Nome do Jogador: %s\n", nome_jogador_formatado);

    time_t mytime;
    mytime = time(NULL);
    fprintf(info, "Data de Jogo: %s", ctime(&mytime));

    fprintf(info, "Pontuação: %d\n", px = SomentePontuacao());
    for (i = 0; i <= 50; i++)
        fprintf(info, "%c", '_');
    fprintf(info, "\n");
    fclose(info);
    printf("Veja os registros de jogos passados!, pressione 'y'\n");
    caractere = getch();
    system("cls");
    if (caractere == 'y' || caractere == 'Y')
    {
        info = fopen("record.txt", "r");
        do
        {
            putchar(c = getc(info));
        } while (c != EOF);
    }
    fclose(info);
}

int Pontuacao()
{
    int pontuacao;
    GotoXY(20, 8);
    pontuacao = comprimento - 5;
    printf("PONTUAÇÃO: %d", (comprimento - 5));
    pontuacao = comprimento - 5;
    GotoXY(50, 8);
    printf("Vida: %d", vida);
    return pontuacao;
}

int SomentePontuacao()
{
    int pontuacao = Pontuacao();
    system("cls");
    return pontuacao;
}

void Cima()
{
    int i;
    for (i = 0; i <= (curva[curva_no].y - cabeca.y) && len < comprimento; i++)
    {
        GotoXY(cabeca.x, cabeca.y + i);
        {
            if (len == 0)
                printf("^");
            else
                printf("=");
        }
        corpo[len].x = cabeca.x;
        corpo[len].y = cabeca.y + i;
        len++;
    }
    Curva();
    if (!kbhit())
        cabeca.y--;
}

