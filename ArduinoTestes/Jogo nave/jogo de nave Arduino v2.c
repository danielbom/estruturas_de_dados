#ifndef _DEF_PRINCIPAIS_H
#define _DEF_PRINCIPAIS_H

#define F_CPU 16000000UL    //define a frequencia do microcontrolador - 16MHz

#include <avr/io.h>         // definições do componente especificado
#include <util/delay.h>     // biblioteca para o uso das rotinas de _delay_ms e _delay_us()
#include <avr/pgmspace.h>   // para o uso do PROGMEM, gravação de dados na memória flash

//Definições de macros para o trabalho com bits

#define set_bit(y,bit)  (y|=(1<<bit))   //coloca em 1 o bit x da variável Y
#define clr_bit(y,bit)  (y&=~(1<<bit))  //coloca em 0 o bit x da variável Y
#define cpl_bit(y,bit)  (y^=(1<<bit))   //troca o estado lógico do bit x da variável Y
#define tst_bit(y,bit)  (y&(1<<bit))    //retorna 0 ou 1 conforme leitura do bit

#endif
/* -------------------------------------------------------------------------------- */
#ifndef MY_DEFS
#define MY_DEFS

#define TRUE  1
#define FALSE 0

#define VAZIO    0
#define NAVE     1
#define EXPLOSAO 2
#define TIRO     3
#define PEDRA    4

#define POS_NAVE_CIMA  0
#define POS_NAVE_BAIXO 1

#define posicao_display(x,y) x == 0 ? 0x80 + y : 0xC0 + y

unsigned char valor = -1;
unsigned long global_time = 1;
unsigned char game_over = 0;

unsigned char posicao_nave = 0;


typedef struct tiro{
    char x;
    char y;
} Tiro;

Tiro tiro = {0, 0};


unsigned char matriz_pedras[2][16] = {0};
unsigned char pedras_time = 0;
unsigned char random_lancer_pedras = 1;

#endif
/* -------------------------------------------------------------------------------- */

#ifndef _LCD_H
#define _LCD_H

//#include "def_principais.h"

//Definições para facilitar a troca dos pinos do hardware e facilitar a re-programação

#define DADOS_LCD      PORTD    //4 bits de dados do LCD no PORTD 
#define nibble_dados  1         //0 para via de dados do LCD nos 4 LSBs do PORT empregado (Px0-D4, Px1-D5, Px2-D6, Px3-D7) 
                //1 para via de dados do LCD nos 4 MSBs do PORT empregado (Px4-D4, Px5-D5, Px6-D6, Px7-D7) 
#define CONTR_LCD     PORTB     //PORT com os pinos de controle do LCD (pino R/W em 0).
#define E         PB1           //pino de habilitação do LCD (enable)
#define RS        PB0           //pino para informar se o dado é uma instrução ou caractere

#define tam_vetor 5   //número de digitos individuais para a conversão por ident_num()   
#define conv_ascii 48   //48 se ident_num() deve retornar um número no formato ASCII (0 para formato normal)

//sinal de habilitação para o LCD
#define pulso_enable()  _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

//protótipo das funções
void cmd_LCD(unsigned char c, char cd);
void inic_LCD_4bits();    
void escreve_LCD(char *c);
void escreve_LCD_Flash(const char *c);

void ident_num(unsigned int valor, unsigned char *disp);

#endif

//--------------------------------------------------------------------------------------------- //
//    AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.                                        //  
//--------------------------------------------------------------------------------------------- //
//============================================================================================= //
//    Sub-rotinas para o trabalho com um LCD 16x2 com via de dados de 4 bits                    //  
//    Controlador HD44780 - Pino R/W aterrado                                                   //
//    A via de dados do LCD deve ser ligado aos 4 bits mais significativos ou                   //
//    aos 4 bits menos significativos do PORT do uC                                             //                                
//============================================================================================= //
// #include "LCD.h"

//---------------------------------------------------------------------------------------------
// Sub-rotina para enviar caracteres e comandos ao LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------
void cmd_LCD(unsigned char c, char cd)        //c é o dado  e cd indica se é instrução ou caractere
{
    if(cd==0)
        clr_bit(CONTR_LCD,RS);
    else
        set_bit(CONTR_LCD,RS);

    //primeiro nibble de dados - 4 MSB
    #if (nibble_dados)                //compila código para os pinos de dados do LCD nos 4 MSB do PORT
        DADOS_LCD = (DADOS_LCD & 0x0F)|(0xF0 & c);    
    #else                             //compila código para os pinos de dados do LCD nos 4 LSB do PORT
        DADOS_LCD = (DADOS_LCD & 0xF0)|(c>>4);  
    #endif
    
    pulso_enable();

    //segundo nibble de dados - 4 LSB
    #if (nibble_dados)                //compila código para os pinos de dados do LCD nos 4 MSB do PORT
        DADOS_LCD = (DADOS_LCD & 0x0F) | (0xF0 & (c<<4));   
    #else                             //compila código para os pinos de dados do LCD nos 4 LSB do PORT
        DADOS_LCD = (DADOS_LCD & 0xF0) | (0x0F & c);
    #endif
    
    pulso_enable();
    
    if((cd==0) && (c<4))        //se for instrução de retorno ou limpeza espera LCD estar pronto
        _delay_ms(2);
}
//---------------------------------------------------------------------------------------------
//Sub-rotina para inicialização do LCD com via de dados de 4 bits
//---------------------------------------------------------------------------------------------
void inic_LCD_4bits()   //sequência ditada pelo fabricando do circuito integrado HD44780
{                       //o LCD será só escrito. Então, R/W é sempre zero.

    clr_bit(CONTR_LCD,RS);  //RS em zero indicando que o dado para o LCD será uma instrução 
    clr_bit(CONTR_LCD,E);   //pino de habilitação em zero
    
    _delay_ms(20);    //tempo para estabilizar a tensão do LCD, após VCC ultrapassar 4.5 V (na prática pode
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
//---------------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD -  dados armazenados na RAM
//---------------------------------------------------------------------------------------------
void escreve_LCD(char *c)
{
   for (; *c!=0;c++) cmd_LCD(*c,1);
}
//---------------------------------------------------------------------------------------------
//Sub-rotina de escrita no LCD - dados armazenados na FLASH
//---------------------------------------------------------------------------------------------
void escreve_LCD_Flash(const char *c)
{
   for (;pgm_read_byte(&(*c))!=0;c++) cmd_LCD(pgm_read_byte(&(*c)),1);
}
//---------------------------------------------------------------------------------------------
//Conversão de um número em seus digitos individuais
//---------------------------------------------------------------------------------------------
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
//---------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------- //
//		AVR e Arduino: Técnicas de Projeto, 2a ed. - 2012.								//	
//------------------------------------------------------------------------------------- //
//=====================================================================================	//
//       			CRIANDO CARACTERES PARA O LCD 16x2	   								//
//																						//
//          			Via de dados de 4 bits											//
//=====================================================================================	//

//#include "def_principais.h"			//inclusão do arquivo com as principais definições 
//#include "LCD.h"

//informação para criar caracteres novos armazenada na memória flash
const unsigned char carac1[] PROGMEM = {0b00000,//Dado 1
                         				0b00000,
                         				0b00000,
                         				0b00100,
                         				0b00000,
                         				0b00000,
                         				0b00000};
										 
const unsigned char carac2[] PROGMEM = {0b00001,//Dado 2
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b10000};

const unsigned char carac3[] PROGMEM = {0b00001,//Dado 3
                         				0b00000,
                         				0b00000,
                         				0b00100,
                         				0b00000,
                         				0b00000,
                         				0b10000};

const unsigned char carac4[] PROGMEM = {0b10001,//Dado 4
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b10001};

const unsigned char carac5[] PROGMEM = {0b10001,//Dado 5
                         				0b00000,
                         				0b00000,
                         				0b00100,
                         				0b00000,
                         				0b00000,
                         				0b10001};

const unsigned char carac6[] PROGMEM = {0b10101,//Dado 6
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b00000,
                         				0b10101};
//--------------------------------------------------------------------------------------
const unsigned char forma_nave[] PROGMEM = {0b11000,
                                      0b10100,
                                      0b10010,
                                      0b01001,
                                      0b10010,
                                      0b10100,
                                      0b11000};

const unsigned char forma_explosao[] PROGMEM = {0b00100,
                                          0b10101,
                                          0b01010,
                                          0b00100,
                                          0b01010,
                                          0b10101,
                                          0b00100};

const unsigned char forma_tiro[] PROGMEM = {0b00000,
                         			  0b00000,
                                      0b00000,
                         			  0b01110,
                         			  0b00000,
                         			  0b00000,
                         			  0b00000};
										 
const unsigned char forma_vazio[] PROGMEM = {0b00000,
                                       0b00000,
                                       0b00000,
                                       0b00000,
                                       0b00000,
                                       0b00000,
                                       0b00000};
const unsigned char forma_pedra[] PROGMEM = {0b01110,
                                       0b11011,
                                       0b10101,
                                       0b11001,
                                       0b10101,
                                       0b11011,
                                       0b01110};
//--------------------------------------------------------------------------------------
void display_apagar(char x, char y)
{
    cmd_LCD(posicao_display(x,y), 0);
    cmd_LCD(VAZIO, 1);
    cmd_LCD(0x14,0);
}

void desloca_nave_para_cima()
{
    if(posicao_nave == POS_NAVE_BAIXO)
    {
        cmd_LCD(posicao_display(1,0),0); // endereça a posição para escrita dos caracteres
        cmd_LCD(VAZIO,1);
        cmd_LCD(posicao_display(0,0),0); // endereça a posição para escrita dos caracteres
        cmd_LCD(NAVE,1);
        posicao_nave = POS_NAVE_CIMA;
    }
}

void desloca_nave_para_baixo()
{
    if(posicao_nave == POS_NAVE_CIMA)
    {
        cmd_LCD(posicao_display(0,0),0); // Definindo a posicao de escrita no display
        cmd_LCD(VAZIO,1);
        cmd_LCD(posicao_display(1,0),0); // Definindo a posicao de escrita no display
        cmd_LCD(NAVE,1);
        posicao_nave = POS_NAVE_BAIXO;
    }
}

void mostrar_tiro(char x, char y)
{
    /* Se y = 1, é a o primeiro tiro, logo, nao preciso apagar o objeto anterior*/   
    if(y == 1)
    {
        /* Primeiro tiro */
        cmd_LCD(posicao_display(x,y), 0);
        cmd_LCD(TIRO, 1);
    }
    else
    {
        /* Apagando o tiro anterior */
        cmd_LCD(posicao_display(x,y-1), 0);
        cmd_LCD(VAZIO, 1);
        /* Se o y = 15, a ultima posição, então não é necessário criar mair tiros */
        if(y != 15)
        {
            /* Criando um novo tiro */
            cmd_LCD(posicao_display(x,y), 0);
            cmd_LCD(TIRO, 1);
        }
    }
}

void atirar()
{
    /* Só atiro se não houver tiros na tela. */
    if(!tiro.y)
    {
        tiro.x = posicao_nave;
        tiro.y = 1;
    }
}

void deslocar_tiro()
{
    /* Só desloco se houver tiros na tela */
    if(tiro.y)
    {
        mostrar_tiro(tiro.x, tiro.y);
        tiro.y++;
        tiro.y %= 16;
    }
}

void gerar_pedras()
{
    /* A geração de pedras acontece a partir de um intervalo. */
    matriz_pedras[random_lancer_pedras % 3 == 0 ? 1 : 0][15] = 1;
    random_lancer_pedras++; // TODO: Tirar intercalação...
}

void mostrar_pedra(char x, char y)
{
    if(matriz_pedras[x][y] == 1)
    {
        /* Mostrando */
        if(y == 15)
        {
            /* Primeira pedra */
            cmd_LCD(posicao_display(x,y), 0);
            cmd_LCD(PEDRA, 1);
        }
        else{
            /* Apagando a pedra anterior */
            display_apagar(x,y+1);

            if(y == 1)
            {
                game_over = TRUE;
                return ;
            }
            else{
                /* Criando uma nova pedra */
                cmd_LCD(posicao_display(x,y), 0);
                cmd_LCD(PEDRA, 1);
            }
        }
        /* Deslocando */
        matriz_pedras[x][y] = 0;
        matriz_pedras[x][y-1] = 1;
    }
}

void deslocar_pedras()
{
    for(char i = 0; i < 2; i++)
    {
        for(char j = 1; j < 16; j++)
        {
            if(i == tiro.x && j == tiro.y)
            {
                if(matriz_pedras[i][j])
                {
                    display_apagar(i,j);
                    matriz_pedras[i][j] = 0;
                    tiro.y = 0;
                }
                else if(matriz_pedras[i][j-1])
                {
                    display_apagar(i, j-1);
                    display_apagar(i, j);
                    matriz_pedras[i][j-1] = 0;
                    tiro.y = 0;
                }
            }

            if(pedras_time % 4 == 0)
                mostrar_pedra(i, j);
        }
    }
}

void init_game()
{
    char k; // Iterador

    /* Armazeno os personagens na memória */
   	// VAZIO = 0 
    cmd_LCD(0x40,0);				//endereço base para gravar novo segmento 0x40
    for(k=0;k<7;k++)
   		cmd_LCD(pgm_read_byte(&forma_vazio[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x40
	cmd_LCD(0x00,1);				//apaga última posição do end. da CGRAM para evitar algum dado espúrio
	
    // NAVE = 1
   	cmd_LCD(0x48,0);				//endereço base para gravar novo segmento  0x48
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&forma_nave[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x48 
   	cmd_LCD(0x00,1);				//apaga última posição do end. da CGRAM para evitar algum dado espúrio
	
    // EXPLOSAO = 2
  	cmd_LCD(0x50,0);				//endereço base para gravar novo segmento  0x50
    for(k=0;k<7;k++)
      	cmd_LCD(pgm_read_byte(&forma_explosao[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x50 
   	cmd_LCD(0x00,1);				//apaga última posição do end. da CGRAM para evitar algum dado espúrio
    
    // TIRO = 3
    cmd_LCD(0x58,0);				        //endereço base para gravar novo segmento  0x58
    for(k=0;k<7;k++)
        cmd_LCD(pgm_read_byte(&forma_tiro[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x58 
    cmd_LCD(0x00,1);				        //apaga última posição do end. da CGRAM para evitar algum dado espúrio

    // PEDRA = 4
    cmd_LCD(0x60,0);				        //endereço base para gravar novo segmento  0x58
    for(k=0;k<7;k++)
        cmd_LCD(pgm_read_byte(&forma_pedra[k]),1);	//grava 8 bytes na DDRAM começando no end. 0x58 
    cmd_LCD(0x00,1);				        //apaga última posição do end. da CGRAM para evitar algum dado espúrio

    cmd_LCD(posicao_display(0,0),0); // endereça a posição para escrita dos caracteres
    cmd_LCD(NAVE,1);			     // Nave
}

char l = 0;
char c = 0;
char r = 0;

void loop()
{

    char button_left   = digitalRead(12); // Verifica se o botão esquerdo esta sendo clicado
    char button_center = digitalRead(11); // Verifica se o botão central esta sendo clicado
    char button_right  = digitalRead(10); // Verifica se o botão direito esta sendo clicado

    if(button_center == LOW)
        c = 1;
    if(button_left == LOW)
        l = 1;
    if(button_right == LOW)
        r = 1;

    if(global_time == 250){
        if(l)
        {    
            l = 0;
            desloca_nave_para_cima();
        }
        if(c)
        {
            atirar();
            c = 0;
        }
        if(r)
        {
            desloca_nave_para_baixo();
            r = 0;
        }
        deslocar_tiro();
        if(pedras_time % 8 == 0) gerar_pedras();
        deslocar_pedras();
        global_time = 0;
        pedras_time++;
    }
    global_time++;
    _delay_ms(1);
}

int main()
{		
	DDRD = 0xFF;					//PORTD como saída
	DDRB = 0xFF;					//PORTB como saída

    /* Configurando os bits para as entradas rodar como pull_up */
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP); 
    pinMode(12, INPUT_PULLUP); 
    //set_bit(PORTB, PB2); // 10 - Seleciono como saida (Valor inicial).
    //set_bit(PORTB, PB3); // 11 - Seleciono como saida (Valor inicial).
    //set_bit(PORTB, PB4); // 12 - Seleciono como saida (Valor inicial).


	inic_LCD_4bits();				//inicializa o LCD

    init_game();
    
    while(!game_over){	//laço infinito
        loop();
    }

}
//=====================================================================================	