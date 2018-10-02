/**
 * Este arquivo define um jogo de naves para um arduino UNO com uma tela LCD de 2 linhas.
 * 
 * O jogo possui 4 nivel de dificuldade, determinados pela quantidade de pontos.
 * [0:4]: O jogo e facil. E possivel desviar das rochas e as rochas se movimentam lentamente.
 * [5:9]: O jogo e medio. E possivel desviar das rochas ainda, mas elas estao um pouco mais rapidas.
 * [10:19]: O jogo e dicifil. Ainda é possivel desviar das rochas, porem elas estao bem rapidas.
 * [20:-]: Modo final. Nao e mais possivel desviar das rochas, se alguma passar voce perde, e elas estao rapidas como no modo dificil.
 * 
 * https://www.tinkercad.com/things/8chOaQJiOSz-copy-of-lcd4bitsdado/editel?sharecode=YzhPdXUwrSgqJd_ABXsH5O3jNikug5tqCqCE7_Ks9IE=
*/

#ifndef _DEF_PRINCIPAIS_H
#define _DEF_PRINCIPAIS_H

#define F_CPU 16000000UL //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>       // Definicoes do componente especificado
#include <util/delay.h>   // Biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h> // Para o uso do PROGMEM, gravacao de dados na memoria flash

//Definicoes de macros para o trabalho com bits
#define set_bit(y, bit) (y |= (1 << bit))  //coloca em 1 o bit x da variavel Y
#define clr_bit(y, bit) (y &= ~(1 << bit)) //coloca em 0 o bit x da variavel Y
#define cpl_bit(y, bit) (y ^= (1 << bit))  //troca o estado logico do bit x da variavel Y
#define tst_bit(y, bit) (y & (1 << bit))   //retorna 0 ou 1 conforme leitura do bit

#endif

#ifndef _LCD_H
#define _LCD_H

//#include "def_principais.h"

// Definicoes para facilitar a troca dos pinos do hardware e facilitar a re-programacao

// 0 para via de dados do LCD nos 4 LSBs do PORT empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7)
// 1 para via de dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7)
#define nibble_dados 1
#define DADOS_LCD PORTD // 4 bits de dados do LCD no PORTD
#define CONTR_LCD PORTB // PORT com os pinos de controle do LCD (pino R/W em 0).
#define E PB1           // Pino de habilitacao do LCD (enable)
#define RS PB0          // Pino para informar se o dado e uma instrucao ou caractere

#define tam_vetor 5   // numero de digitos individuais para a conversao por ident_num()
#define conv_ascii 48 // 48 se ident_num() deve retornar um numero no formato ASCII (0 para formato normal)

//sinal de habilitacao para o LCD
#define pulso_enable()     \
    _delay_us(1);          \
    set_bit(CONTR_LCD, E); \
    _delay_us(1);          \
    clr_bit(CONTR_LCD, E); \
    _delay_us(45)

//prototipo das funcoes
void cmd_LCD(unsigned char c, char cd);
void inic_LCD_4bits();
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);

void ident_num(unsigned int valor, unsigned char *disp);

#endif

//----------------------------------------------------------------------------------- //
//    AVR e Arduino: Tecnicas de Projeto, 2a ed. - 2012.                              //
//----------------------------------------------------------------------------------- //
//=================================================================================== //
//    Sub-rotinas para o trabalho com um LCD 16x2 com via de dados de 4 bits          //
//    Controlador HD44780 - Pino R/W aterrado                                         //
//    A via de dados do LCD deve ser ligado aos 4 bits mais significativos ou         //
//    aos 4 bits menos significativos do PORT do uC                                   //
//=================================================================================== //
// #include "LCD.h"

//----------------------------------------------------------------------------------- //
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits     //
//----------------------------------------------------------------------------------- //
// c e o dado e cd indica se e instrucao ou caractere
// Se cd == 0, entao c e uma instrucao. Caso contrario, c e um caracter.
void cmd_LCD(unsigned char c, char cd)
{
    if (cd == 0)
        clr_bit(CONTR_LCD, RS);
    else
        set_bit(CONTR_LCD, RS);

// primeiro nibble de dados - 4 MSB
#if (nibble_dados) // compila codigo para os pinos de dados do LCD nos 4 MSB do PORT
    DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & c);
#else // compila codigo para os pinos de dados do LCD nos 4 LSB do PORT
    DADOS_LCD = (DADOS_LCD & 0xF0) | (c >> 4);
#endif

    pulso_enable();

//segundo nibble de dados - 4 LSB
#if (nibble_dados) // compila codigo para os pinos de dados do LCD nos 4 MSB do PORT
    DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c << 4));
#else // compila codigo para os pinos de dados do LCD nos 4 LSB do PORT
    DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
#endif

    pulso_enable();

    if ((cd == 0) && (c < 4)) // se for instrucao de retorno ou limpeza espera LCD estar pronto
        _delay_ms(2);
}
//----------------------------------------------------------------------------------- //
// Sub-rotina para inicializacao do LCD com via de dados de 4 bits                    //
//----------------------------------------------------------------------------------- //

// Sequência ditada pelo fabricando do circuito integrado HD44780
// o LCD sera so escrito. Entao, R/W e sempre zero.
void inic_LCD_4bits()
{
    clr_bit(CONTR_LCD, RS); // RS em zero indicando que o dado para o LCD sera uma instrucao
    clr_bit(CONTR_LCD, E);  // pino de habilitacao em zero

    // Tempo para estabilizar a tensao do LCD, apos VCC ultrapassar 4.5 V (na pratica pode
    // ser maior).
    _delay_ms(20);

//interface de 8 bits
#if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;
#else
    DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;
#endif

    pulso_enable(); //habilitacao respeitando os tempos de resposta do LCD
    _delay_ms(5);
    pulso_enable();
    _delay_us(200);
    pulso_enable();
/*
    * Ate aqui ainda e uma interface de 8 bits. Muitos programadores desprezam os comandos
    * acima, respeitando apenas o tempo de estabilizacao da tensao (geralmente funciona).
    * Se o LCD nao for inicializado primeiro no modo de 8 bits, havera problemas se o
    * microcontrolador for inicializado e o display ja o tiver sido.
    */

//interface de 4 bits, deve ser enviado duas vezes (a outra esta abaixo)
#if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;
#else
    DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
#endif

    pulso_enable();
    // Interface de 4 bits 2 linhas (aqui se habilita as 2 linhas)
    // sao enviados os 2 nibbles (0x2 e 0x8)
    cmd_LCD(0x28, 0);
    cmd_LCD(0x08, 0); // Desliga o display
    cmd_LCD(0x01, 0); // Limpa todo o display
    cmd_LCD(0x0C, 0); // Mensagem aparente cursor inativo nao piscando
    cmd_LCD(0x80, 0); // Inicializa cursor na primeira posicao a esquerda - 1a linha
}
//----------------------------------------------------------------------------------- //
// Sub-rotina de escrita no LCD -  dados armazenados na RAM                           //
//----------------------------------------------------------------------------------- //
void escreve_LCD(char *c)
{
    for (; *c != 0; c++)
        cmd_LCD(*c, 1);
}
//----------------------------------------------------------------------------------- //
// Sub-rotina de escrita no LCD - dados armazenados na FLASH                          //
//----------------------------------------------------------------------------------- //
void escreve_LCD_Flash(const char *c)
{
    for (; pgm_read_byte(&(*c)) != 0; c++)
        cmd_LCD(pgm_read_byte(&(*c)), 1);
}
//----------------------------------------------------------------------------------- //
// Conversao de um numero em seus digitos individuais                                 //
//----------------------------------------------------------------------------------- //
void ident_num(unsigned int valor, unsigned char *disp)
{
    unsigned char n;

    for (n = 0; n < tam_vetor; n++)
        disp[n] = 0 + conv_ascii; //limpa vetor para armazenagem do digitos

    do
    {
        *disp = (valor % 10) + conv_ascii; // Pega o resto da divisao por 10
        valor /= 10;                       // Pega o inteiro da divisao por 10
        disp++;
    } while (valor != 0);
}
//---------------------------------------------------

// FORMAS
#define iNULL 0
#define iSHIP 1
#define iEXPLOSION 2
#define iBULLET 3
#define iBIG_ROCK 4
#define iLITTLE_ROCK 5

const unsigned char shape_null[] PROGMEM = {0b00000,
                                            0b00000,
                                            0b00000,
                                            0b00000,
                                            0b00000,
                                            0b00000,
                                            0b00000};
const unsigned char shape_ship[] PROGMEM = {0b11000,
                                            0b10100,
                                            0b10010,
                                            0b01001,
                                            0b10010,
                                            0b10100,
                                            0b11000};
const unsigned char shape_explosion[] PROGMEM = {0b00100,
                                                 0b10101,
                                                 0b01010,
                                                 0b00100,
                                                 0b01010,
                                                 0b10101,
                                                 0b00100};
const unsigned char shape_bullet[] PROGMEM = {0b00000,
                                              0b00000,
                                              0b00000,
                                              0b01110,
                                              0b00000,
                                              0b00000,
                                              0b00000};
const unsigned char shape_big_rock[] PROGMEM = {0b01110,
                                                0b11011,
                                                0b10101,
                                                0b11001,
                                                0b10101,
                                                0b11011,
                                                0b01110};
const unsigned char shape_little_rock[] PROGMEM = {0b00000,
                                                   0b00000,
                                                   0b01111,
                                                   0b11001,
                                                   0b10111,
                                                   0b11100,
                                                   0b00000};

// ----------------------------------------------------------------

// CONTROLE GLOBAL
// Definicao de booleanos para tornar o codigo mais facil de ler
#define TRUE 1
#define FALSE 0

// Definicao das posicoes iniciais de cada linha como constantes
#define line_0 0x80
#define line_1 0xC0

// Defino constantes para definir a posicao de cima e a de baixo
// para tornar a compreencao da posicao da nave melhor.
#define UP line_0
#define DOWN line_1

int timer = 0;       // Temporizador para cada modificacao da tela do jogo
int points = 0;      // Pontos do jogador
char running = 1;    // Indicador para marcar se o jogo esta rodando
char difficulty = 0; // Indicador da dificuldade do jogo

void clear_cursor(unsigned char position)
{
    // Esta funcao limpa a posicao do LCD recebida.
    cmd_LCD(position, 0); // No modo de instrucao, envio a posicao
    cmd_LCD(iNULL, 1);    // No modo de caracter, envio o identificar do formato limpo (vazio)
}

// NAVE
typedef struct
{
    unsigned char position;
} Ship;

Ship ship = {UP};

void draw_ship_up()
{
    // Esta funcao desenha a nave na posicao de cima (primeira linha, primeira coluna)
    // Limpando o curso, na posicao de baixo
    clear_cursor(DOWN);
    // Desenhando uma nova nave
    cmd_LCD(UP, 0);    // No modo de instrucao, envio a posicao de cima
    cmd_LCD(iSHIP, 1); // No modo de caracter, envio o identificador do formato da nave
    // Informando a nova posicao que a nave esta
    ship.position = UP;
}

void draw_ship_down()
{
    // Esta funcao desenha a nave na posicao de baixo (segunda linha, primeira coluna)
    // Limpando o curso, na posicao de cima
    clear_cursor(UP);
    // Desenho uma nova nave
    cmd_LCD(DOWN, 0);  // No modo de instrucao, envio a posicao de baixo
    cmd_LCD(iSHIP, 1); // No modo de caracter, envio o identificador do formato da nave
    // Informando a nova posicao que a nave esta
    ship.position = DOWN;
}

void move_up_ship()
{
    // Esta funcao movimenta a nave para cima, se ela estiver embaixo
    if (ship.position == DOWN) // Se a posicao da nave e baixo
        draw_ship_up();        // Desenho a nave emcima
}

void move_down_ship()
{
    // Esta funcao movimenta a nava para baixo, se ela estiver emcima
    if (ship.position == UP) // Se a posicao da nave e cima
        draw_ship_down();    // Desenho a nave embaixo
}

// TIRO
typedef struct
{
    unsigned char position;
    unsigned char limite;
} Bullet;

Bullet bullet = {0};

void draw_bullet()
{
    // Esta funcao desenha a bala na posicao que a bala deve estar
    cmd_LCD(bullet.position, 0); // No modo de instrucao, envio a posicao da bala
    cmd_LCD(iBULLET, 1);         // No modo de caracter, envio o identificador do formato da bala
}

void shoot()
{
    // Esta funcao faz a nave atirar se nao ouver balas na tela
    if (bullet.position == 0)
    {
        bullet.position = ship.position + 0x01; // Defino a posicao inicial da bala a partir da posicao da nave
        bullet.limite = ship.position + 0x10;   // Defino o limite que a bala pode alcancar ate ser 'destruida'
        draw_bullet();                          // Desenho a bala
    }
}

void move_bullet()
{
    // Esta funcao movimenta a bala pela tela.
    if (bullet.position != 0) // Se existe uma bala
    {
        clear_cursor(bullet.position);    // Apago a bala atual
        bullet.position++;                // Incremento a posicao da bala
        bullet.position %= bullet.limite; // Faco o calculo do limite, para destruir a bala
        draw_bullet();                    // Desenho uma nova bala
    }
}

// PEDRAS
typedef struct
{
    unsigned char position;
    unsigned char limite;
    unsigned char shape;
} Rock;

Rock rock = {0};

void draw_rock()
{
    // Esta funcao desenha uma rocha na posicao que a rocha deve estar
    cmd_LCD(rock.position, 0); // No modo de instrucao, envio a posicao da bala
    cmd_LCD(rock.shape, 1);    // No modo de caracter, envio o identificar do formato da rocha
    // O formato da rocha pode ser pequena ou grande, por isso que existe esse
    // atributo em rocha.
}

void spawn_rock()
{
    // Essa funcao realiza o spawn de pedras quando nao existem pedras
    // A variavel time_spawn foi criada na esperanca de em algum momento
    // existir mais de uma pedra na tela.
    static unsigned char time_spawn = 0;
    time_spawn++;
    if (time_spawn % 4 == 0)
    {
        if (rock.position == 0) // Se nao existem pedras
        {
            time_spawn = 0;
            rock.limite = random(0, 2) == 0 ? line_0 : line_1;         // Defino a posicao inicial da pedra de forma aleatoria
            rock.position = rock.limite + 0x0F;                        // O limite da rocha e pre-determinado
            rock.shape = random(0, 2) == 0 ? iBIG_ROCK : iLITTLE_ROCK; // Defino o formato da rocha de forma aleatoria
            draw_rock();                                               // Desenho a rocha
        }
    }
}

void move_rock()
{
    // Essa funcao movimenta a pedra pela tela
    // A variavel time_move determina a velocidade da pedra
    // Quanto maior esse valor pode alcancar, mais devagar a
    // pedra vai se movimentar
    static unsigned char time_move = 0;
    time_move++;
    // A partir da dificuldade, aumento a velocidade da pedra
    // Se essa diferenca for menor que 1, defino como 1
    char lim = 3 - difficulty;
    if (time_move % (lim > 1 ? lim : 1) == 0)
    {                           // Se o intervalo de tempo para movimentar for alcancado
        if (rock.position != 0) // Se a pedra existe
        {
            time_move = 0;
            clear_cursor(rock.position); // Apago a posicao onde a pedra esta
            rock.position--;             // Decremento a posicao da pedra

            if (rock.position == rock.limite) // Se a rocha alcancar o limite, destroi a rocha
            {
                rock.position = 0;
                return;
            }

            draw_rock(); // Se a rocha nao alcancou seu limite, desenha a rocha
        }
    }
}

// COLISAO
typedef struct
{
    unsigned char position;
} Explosion;

Explosion explosion = {0};

void draw_explosion()
{
    // Esta funcao desenha uma explosao na posicao que a explosao deve estar
    cmd_LCD(explosion.position, 0); // No modo de instrucao, envio a posicao da explosao
    cmd_LCD(iEXPLOSION, 1);         // No modo de caracter, envio o identificador do formato da explosao
}

void dissipate_explosion()
{
    // Esta funcao dissipa a explosao criada
    // Quando essa funcao e executada os pontos sao incrementados em 1
    // A dificuldade e incrementada a cada 5 pontos
    static unsigned char time_dissipate = 0;
    // A variavel time_dissipate e utilizada para que a explosao nao suma
    // muito rapidamente
    if (explosion.position != 0)
    {                                // Se existe uma explosao
        time_dissipate++;            // Incremento o tempo de dissipacao
        if (time_dissipate % 2 == 0) // Se o tempo de dissipacao for o suficiente
        {
            points++;                         // Incremento os pontos do jogador
            difficulty += (points % 5 == 0);  // Incremento a dificuldade quando a pontuacao incrementa em 5
            clear_cursor(explosion.position); // Limpo a posicao da explosao
            explosion.position = 0;           // Destruo a explosao
            time_dissipate == 0;              // Reseto o tempo de dissipacao
        }
    }
}

void bullet_test_hit()
{
    // Esta funcao determina se uma bala acertou uma pedra
    if (rock.position != 0 && bullet.position != 0) // Se bala e rocha existem
    {
        if (rock.position == bullet.position) // Se as posicoes sao iguais
        {
            clear_cursor(bullet.position);             // Limpo a posicao que a bala esta
            explosion.position = rock.position + 0x01; // Defino a posicao que a explosao deve ser criada
            draw_explosion();                          // Desenho a explosao
            rock.position = 0;                         // Destruo a pedra
            bullet.position = 0;                       // Destruo a bala
        }
        else if (rock.position - 0x01 == bullet.position) // Se a rocha ultrapassou a bala
        {
            clear_cursor(bullet.position);      // Limpo a posicao que a bala esta
            explosion.position = rock.position; // Defino a posicao da rocha para a explosao ser criada
            draw_explosion();                   // Desenho a explosao em cima do desenho da rocha
            rock.position = 0;                  // Destruo a rocha
            bullet.position = 0;                // Destruo a bala
        }
    }
}

// GAME OVER
void game_over_test()
{
    // Esta funcao identifica se o jogo terminou

    // Se a pontuacao for menor que 20, posso desviar das pedras
    if (points < 20)
    {
        if (ship.position + 0x01 == rock.position) // Teste para identificar que nao estou na frente da pedra
            running = FALSE;
    }
    else // Para pontuacoes maiores que 20, nao posso desviar das pedras
    {
        if (line_0 + 0x01 == rock.position ||
            line_1 + 0x01 == rock.position) // Teste para identificar se a pedra alcancou a nave
            running = FALSE;
    }
}

void draw_game_over()
{
    // Esta funcao finaliza o jogo informando a pontuacao do jogador
    cmd_LCD(0x01, 0);                          // No modo de instrucao, limpo a tela
    cmd_LCD(line_0, 0);                        // No modo de instrucao, posiciono o cursor no comeco da primeira linha
    escreve_LCD("GAME OVER...");               // Escrevo "GAME OVER..."
    cmd_LCD(line_1, 0);                        // Na modo de instrucao, posiciono o cursor no comeco da segunda linha
    char buffer[16];                           // Crio um buffer para converter os pontos em string
    snprintf(buffer, 16, "POINTS %d", points); // Converto os pontos em string
    escreve_LCD(buffer);                       // Escrevo a pontuacao do jogador
}

// SETUP
void init_game()
{
    // Esta funcao inicia o jogo, gravando os formatos dos objetos do jogo na memoria DDRAM
    // comecando a partir do endereco 0x40
    char k; // Iterador para as instrucoes for a seguir
    // VAZIO
    cmd_LCD(0x40, 0); // Endereco para gravar no segmento
    for (k = 0; k < 7; k++)
        cmd_LCD(pgm_read_byte(&shape_null[k]), 1); // Grava 7 bytes na DDRAM
    cmd_LCD(0x00, 1);                              // Grava um valor null na ultima posicao

    // (***) Todas as instrucoes for seguintes agem da mesma forma

    // NAVE
    cmd_LCD(0x48, 0);
    for (k = 0; k < 7; k++)
        cmd_LCD(pgm_read_byte(&shape_ship[k]), 1);
    cmd_LCD(0x00, 1);

    // EXPLOSAO
    cmd_LCD(0x50, 0);
    for (k = 0; k < 7; k++)
        cmd_LCD(pgm_read_byte(&shape_explosion[k]), 1);
    cmd_LCD(0x00, 1);

    // TIRO
    cmd_LCD(0x58, 0);
    for (k = 0; k < 7; k++)
        cmd_LCD(pgm_read_byte(&shape_bullet[k]), 1);
    cmd_LCD(0x00, 1);

    // PEDRA GRANDE
    cmd_LCD(0x60, 0);
    for (k = 0; k < 7; k++)
        cmd_LCD(pgm_read_byte(&shape_big_rock[k]), 1);
    cmd_LCD(0x00, 1);

    // PEDRA PEQUENA
    cmd_LCD(0x68, 0);
    for (k = 0; k < 7; k++)
        cmd_LCD(pgm_read_byte(&shape_little_rock[k]), 1);
    cmd_LCD(0x00, 1);

    // Inicialmente a nave esta posicionada na posicao [0,0]
    draw_ship_up();
}

void __setup__()
{
    // Esta funcao define a configuracao do arduino
    DDRD = 0xFF; //PORTD como saida
    DDRB = 0xFF; //PORTB como saida

    // Determinando os pinos 10, 11 e 12 input_pullup
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    pinMode(12, INPUT_PULLUP);

    inic_LCD_4bits(); // Inicializando o LCD

    init_game(); // Inicializando o jogo
}

// BOTOES
char click_left = 0;
char click_center = 0;
char click_right = 0;

void read_buttons()
{
    // Funcao auxiliar para agrupar todas as funcoes de leitura de botoes
    char button_left = digitalRead(12);   // Verifica se o botao esquerdo esta sendo clicado
    char button_center = digitalRead(11); // Verifica se o botao central esta sendo clicado
    char button_right = digitalRead(10);  // Verifica se o botao direito esta sendo clicado

    // Armazena o botao precionado em uma variavel global
    if (button_center == LOW)
        click_center = 1;
    if (button_left == LOW)
        click_left = 1;
    if (button_right == LOW)
        click_right = 1;
}

// LOOP
void __loop__()
{
    // Esta funcao executa a logica do jogo.
    // Ela e executada em um loop, que so finaliza quando o jogo acaba
    read_buttons();   // Leitura dos botoes do jogo
    timer++;          // Incremento do temporizador global
    if (timer == 200) // A cada 200 ticks o jogo executa uma mudanca na tela
    {
        if (click_left) // Verifico se o botao esquerdo foi precionado
        {
            click_left = 0; // Desmarco o botao
            move_up_ship(); // Movimento a nave para cima
        }
        if (click_center) // Verifico se o botao centrao foi precionado
        {
            click_center = 0; // Desmarco o botao
            shoot();          // Atiro com a nave
        }
        if (click_right) // Verifico se o botao direito foi precionado
        {
            click_right = 0;  // Desmarco o botao
            move_down_ship(); // Movimento a nave para baixo
        }
        game_over_test();      // Realizo o teste de fim de jogo
        move_bullet();         // Movimento a bala
        bullet_test_hit();     // Testo se a bala colidiu com uma rocha
        dissipate_explosion(); // Dissipa a explosao
        move_rock();           // Movimento a rocha
        spawn_rock();          // Crio rochas
        timer = 0;             // Zero o contador de tempo
    }

    _delay_ms(1); // Delay para melhorar a performance
}

int main()
{
    // Funcao principa que chama todas as funcoes necessarias para rodar o jogo
    __setup__();
    while (running)
        __loop__();
    draw_game_over();
    return 0;
}