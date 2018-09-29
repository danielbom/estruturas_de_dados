#ifndef _DEF_PRINCIPAIS_H
#define _DEF_PRINCIPAIS_H

#define F_CPU 16000000UL  //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>       //definições do componente especificado
#include <util/delay.h>   //biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h>   //para o uso do PROGMEM, gravação de dados na memória flash

//Definições de macros para o trabalho com bits
#define set_bit(y,bit)  (y|=(1<<bit)) //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit)  (y&=~(1<<bit))  //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit)  (y^=(1<<bit)) //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit)  (y&(1<<bit))  //retorna 0 ou 1 conforme leitura do bit

#endif


#ifndef _LCD_H
#define _LCD_H

//#include "def_principais.h"

//Definições para facilitar a troca dos pinos do hardware e facilitar a re-programação

#define DADOS_LCD      PORTD   //4 bits de dados do LCD no PORTD 
#define nibble_dados  1   //0 para via de dados do LCD nos 4 LSBs do PORT empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7) 
                //1 para via de dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7) 
#define CONTR_LCD     PORTB   //PORT com os pinos de controle do LCD (pino R/W em 0).
#define E         PB1     //pino de habilitação do LCD (enable)
#define RS        PB0     //pino para informar se o dado é uma instrução ou caractere

#define tam_vetor 5 //número de digitos individuais para a conversão por ident_num()   
#define conv_ascii  48  //48 se ident_num() deve retornar um número no formato ASCII (0 para formato normal)

//sinal de habilitação para o LCD
#define pulso_enable()  _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

//protótipo das funções
void cmd_LCD(unsigned char c, char cd);
void inic_LCD_4bits();    
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);

void ident_num(unsigned int valor, unsigned char *disp);

#endif

//--------------------------------------------------- //
//    AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.                    //  
//--------------------------------------------------- //
//=================================================== //
//    Sub-rotinas para o trabalho com um LCD 16x2 com via de dados de 4 bits          //  
//    Controlador HD44780 - Pino R/W aterrado                         //
//    A via de dados do LCD deve ser ligado aos 4 bits mais significativos ou         //
//    aos 4 bits menos significativos do PORT do uC                     //                                
//=================================================== //
// #include "LCD.h"

//---------------------------------------------------
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//---------------------------------------------------
void cmd_LCD(unsigned char c, char cd)        //c é o dado  e cd indica se é instrução ou caractere
{
  if(cd==0)
    clr_bit(CONTR_LCD,RS);
  else
    set_bit(CONTR_LCD,RS);

  //primeiro nibble de dados - 4 MSB
  #if (nibble_dados)                //compila código para os pinos de dados do LCD nos 4 MSB do PORT
    DADOS_LCD = (DADOS_LCD & 0x0F)|(0xF0 & c);    
  #else                     //compila código para os pinos de dados do LCD nos 4 LSB do PORT
    DADOS_LCD = (DADOS_LCD & 0xF0)|(c>>4);  
  #endif
  
  pulso_enable();

  //segundo nibble de dados - 4 LSB
  #if (nibble_dados)                //compila código para os pinos de dados do LCD nos 4 MSB do PORT
    DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c<<4));   
  #else                     //compila código para os pinos de dados do LCD nos 4 LSB do PORT
    DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
  #endif
  
  pulso_enable();
  
  if((cd==0) && (c<4))        //se for instrução de retorno ou limpeza espera LCD estar pronto
    _delay_ms(2);
}
//---------------------------------------------------
//Sub-rotina para inicialização do LCD com via de dados de 4 bits
//---------------------------------------------------
void inic_LCD_4bits()   //sequência ditada pelo fabricando do circuito integrado HD44780
{             //o LCD será só escrito. Então, R/W é sempre zero.

  clr_bit(CONTR_LCD,RS);  //RS em zero indicando que o dado para o LCD será uma instrução 
  clr_bit(CONTR_LCD,E); //pino de habilitação em zero
  
  _delay_ms(20);      //tempo para estabilizar a tensão do LCD, após VCC ultrapassar 4.5 V (na prática pode
              //ser maior). 
  //interface de 8 bits           
  #if (nibble_dados)
    DADOS_LCD = (DADOS_LCD & 0x0F) | 0x30;    
  #else   
    DADOS_LCD = (DADOS_LCD & 0xF0) | 0x03;    
  #endif            
              
  pulso_enable();     //habilitação respeitando os tempos de resposta do LCD
  _delay_ms(5);   
  pulso_enable();
  _delay_us(200);
  pulso_enable(); /*até aqui ainda é uma interface de 8 bits.
          Muitos programadores desprezam os comandos acima, respeitando apenas o tempo de
          estabilização da tensão (geralmente funciona). Se o LCD não for inicializado primeiro no 
          modo de 8 bits, haverá problemas se o microcontrolador for inicializado e o display já o tiver sido.*/
  
  //interface de 4 bits, deve ser enviado duas vezes (a outra está abaixo)
  #if (nibble_dados) 
    DADOS_LCD = (DADOS_LCD & 0x0F) | 0x20;    
  #else   
    DADOS_LCD = (DADOS_LCD & 0xF0) | 0x02;
  #endif
  
  pulso_enable();   
    cmd_LCD(0x28,0);    //interface de 4 bits 2 linhas (aqui se habilita as 2 linhas) 
              //são enviados os 2 nibbles (0x2 e 0x8)
    cmd_LCD(0x08,0);    //desliga o display
    cmd_LCD(0x01,0);    //limpa todo o display
    cmd_LCD(0x0C,0);    //mensagem aparente cursor inativo não piscando   
    cmd_LCD(0x80,0);    //inicializa cursor na primeira posição a esquerda - 1a linha
}
//---------------------------------------------------
//Sub-rotina de escrita no LCD -  dados armazenados na RAM
//---------------------------------------------------
void escreve_LCD(char *c)
{
   for (; *c!=0;c++) cmd_LCD(*c,1);
}
//---------------------------------------------------
//Sub-rotina de escrita no LCD - dados armazenados na FLASH
//---------------------------------------------------
void escreve_LCD_Flash(const char *c)
{
   for (;pgm_read_byte(&(*c))!=0;c++) cmd_LCD(pgm_read_byte(&(*c)),1);
}
//---------------------------------------------------
//Conversão de um número em seus digitos individuais
//---------------------------------------------------
void ident_num(unsigned int valor, unsigned char *disp)
{   
  unsigned char n;

  for(n=0; n<tam_vetor; n++)
    disp[n] = 0 + conv_ascii;   //limpa vetor para armazenagem do digitos 

  do
  {
       *disp = (valor%10) + conv_ascii; //pega o resto da divisao por 10 
     valor /=10;            //pega o inteiro da divisão por 10
     disp++;

  }while (valor!=0);
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
const unsigned char shape_little_rock[] PROGMEM = {0b01110,
                                                   0b11011,
                                                   0b10101,
                                                   0b11001,
                                                   0b10101,
                                                   0b11011,
                                                   0b01110};

// ---------------------------------------------------------------- 

// CONTROLE GLOBAL
#define TRUE 1
#define FALSE 2

#define line_0 0x80
#define line_1 0xC0

#define UP line_0
#define DOWN line_1

int timer = 0;
int points = 0;
char running = 1;
char difficulty = 0;

void clear_cursor(unsigned char position)
{
    cmd_LCD(position, 0);
    cmd_LCD(iNULL, 1);
}

// NAVE
typedef struct {
    unsigned char position;
} Ship;

Ship ship = {UP};

void draw_ship_up()
{
    // Limpo o curso, onde esta a nave
    clear_cursor(line_1);
    // Desenho uma nova nave
    cmd_LCD(line_0, 0);
    cmd_LCD(iSHIP, 1);
    // Informo a nova posicao que a nave esta
    ship.position = UP;
}

void draw_ship_down()
{
    // Limpo o curso, onde esta a nave
    clear_cursor(line_0);
    // Desenho uma nova nave
    cmd_LCD(line_1, 0);
    cmd_LCD(iSHIP, 1);
    // Informo a nova posicao que a nave esta
    ship.position = DOWN;
}

void move_up_ship()
{
    if(ship.position == DOWN)
        draw_ship_up();
}

void move_down_ship()
{
    if(ship.position == UP)
        draw_ship_down();
}

// TIRO
typedef struct {
    unsigned char position;
    unsigned char limite;
} Bullet;

Bullet bullet = {0};

void draw_bullet()
{
    cmd_LCD(bullet.position, 0);
    cmd_LCD(iBULLET, 1);
}

void shoot()
{
    if(bullet.position == 0)
    {
        bullet.position = ship.position + 0x01;
        bullet.limite   = ship.position + 0x10;
        draw_bullet();
    }
}

void move_bullet()
{
    if(bullet.position != 0)
    {
        clear_cursor(bullet.position);     // Apaga a bala atual
        bullet.position++;
        bullet.position %= bullet.limite;
        draw_bullet();    // Desenha uma nova bala
    }
}

// PEDRAS
typedef struct {
    unsigned char position;
    unsigned char limite;
} Rock;

Rock rock = {0};

void draw_rock()
{
    cmd_LCD(rock.position, 0);
    cmd_LCD(iBIG_ROCK, 1);
}

void spawn_rock()
{
    static unsigned char time_spawn = 0;
    time_spawn++;
    if(time_spawn % 4 == 0){
        if(rock.position == 0)
        {
            time_spawn = 0;
            rock.limite   = random(0, 2) == 0 ? line_0 : line_1;
            rock.position = rock.limite + 0x0F;
            draw_rock();
        }
    }
}

void move_rock()
{
    static unsigned char time_move = 0;
    time_move++;
    char lim = 3 - difficulty;
    if(time_move % (lim > 1 ? lim : 1) == 0) {
        if(rock.position != 0)
        {
            time_move = 0;
            clear_cursor(rock.position);
            rock.position--;
            if(rock.position == rock.limite)
            {
                rock.position = 0;
                return;
            }
            draw_rock();
        }
    }
}

// COLISAO
typedef struct {
    unsigned char position;
} Explosion;

Explosion explosion = {0};

void draw_explosion()
{
    cmd_LCD(explosion.position, 0);
    cmd_LCD(iEXPLOSION, 1);
}

void dissipate_explosion()
{
    static unsigned char time_dissipate = 0;

    if(explosion.position != 0){
        time_dissipate++;
        if(time_dissipate % 2 == 0)
        {
            points++;
            difficulty += (points % 5 == 0);
            clear_cursor(explosion.position);
            explosion.position = 0;
            time_dissipate == 0;
        }
    }
}

void bullet_test_hit()
{
    if(rock.position != 0 && bullet.position != 0)
    {
        if(rock.position == bullet.position)
        {
            clear_cursor(bullet.position);
            explosion.position = rock.position + 0x01;
            draw_explosion();
            rock.position = 0;
            bullet.position = 0;
        }
        else if(rock.position - 0x01 == bullet.position)
        {
            clear_cursor(bullet.position);
            explosion.position = rock.position;
            draw_explosion();
            rock.position = 0;
            bullet.position = 0;
        }
    }
}

// GAME OVER
void game_over_test()
{
    if(ship.position + 0x01 == rock.position)
        running = FALSE;
}

void draw_game_over()
{
    cmd_LCD(0x01, 0);
    cmd_LCD(line_0, 0);
    escreve_LCD("GAME OVER...");
    cmd_LCD(line_1, 0);
    char buffer[16] ;
    snprintf(buffer, 16, "POINTS %d", points);
    escreve_LCD(buffer);
}

// SETUP
void init_game()
{
    char k;
    // VAZIO
    cmd_LCD(0x40,0);
    for(k=0;k<7;k++)
   		cmd_LCD(pgm_read_byte(&shape_null[k]),1);
	cmd_LCD(0x00,1);
	
    // NAVE
   	cmd_LCD(0x48,0);
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&shape_ship[k]),1);
   	cmd_LCD(0x00,1);
	
    // EXPLOSAO
  	cmd_LCD(0x50,0);
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&shape_explosion[k]),1);
   	cmd_LCD(0x00,1);
  
    // TIRO
  	cmd_LCD(0x58,0);
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&shape_bullet[k]),1);
   	cmd_LCD(0x00,1);
  
    // PEDRA GRANDE
  	cmd_LCD(0x60,0);
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&shape_big_rock[k]),1);
   	cmd_LCD(0x00,1);	
  
    // PEDRA PEQUENA
  	cmd_LCD(0x68,0);
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&shape_little_rock[k]),1);
   	cmd_LCD(0x00,1);

    // Inicialmente a nave esta posicionada na posicao [0,0]
    draw_ship_up();
}

void __setup__()
{	
	DDRD = 0xFF;					//PORTD como saída
	DDRB = 0xFF;					//PORTB como saída

    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP); 
    pinMode(12, INPUT_PULLUP);

	inic_LCD_4bits();				//inicializa o LCD
	
   	init_game();
}

// BOTOES
char click_left = 0;
char click_center = 0;
char click_right = 0;

void read_buttons()
{
    // Função auxiliar para agrupar todas as funções de leitura de botões
    char button_left   = digitalRead(12); // Verifica se o botão esquerdo esta sendo clicado
    char button_center = digitalRead(11); // Verifica se o botão central esta sendo clicado
    char button_right  = digitalRead(10); // Verifica se o botão direito esta sendo clicado

    // Armazena o botao precionado em uma variável global
    if(button_center == LOW)
        click_center = 1;
    if(button_left == LOW)
        click_left = 1;
    if(button_right == LOW)
        click_right = 1;
}

// LOOP
void __loop__()
{
    read_buttons(); // Le os botões do jogo
    timer++;
    if(timer == 200)
    {
        if(click_left)
        {
            click_left = 0;
            move_up_ship();
        }
        if(click_center)
        {
            click_center = 0;
            shoot();
        }
        if(click_right)
        {
            click_right = 0;
            move_down_ship();
        }
        game_over_test();
        move_bullet();
        bullet_test_hit();
        dissipate_explosion();
        move_rock();
        spawn_rock();
        timer = 0;
    }
    
    _delay_ms(1); // Delay para melhorar a performance
}

int main()
{	
    __setup__();
    while(running == TRUE) __loop__();
    draw_game_over();
    return 0;
}	