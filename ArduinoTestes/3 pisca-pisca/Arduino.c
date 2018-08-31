/*
    Este programa pisca três leds em ordem a cada click.
    Se houver um click longo (1 segundo), todos os leds são apagados.
    Ele seleciona o led a acender durante o click.
    Quando o botão é solto faz as alterações acontecerem. 
*/
#define TRUE 1
#define FALSE 0

#define RESET -1
#define GREEN 0
#define YELLOW 1
#define RED 2

#define _bit(position) (1 << position)
#define set_bit(bits, position) bits = bits | _bit(position)
#define unset_bit(bits, position) bits = bits & ~_bit(position)
#define is_set_bit(bits, mask) ((bits & mask) == mask)

char leds_states = GREEN; // Estado dos leds.
char light_up = TRUE;     // Posso acender.
char to_press = TRUE;     // Posso precionar.

unsigned long int timer;
unsigned long int limite_timer = 1000;

void turn_off();     // Apaga os leds.
void turn_on_led();  // Acende o led selecionado.
void select_led();   // Seleciona o led a acender.
void turn_off_now(); // Apaga todos os leds na hora.

void setup()
{
    // pinMode(2, INPUT_PULLUP); // 2
    // Para simular a situação acima, deve ser executada as 2 funções abaixo.
    set_bit(PORTD, PD2);  // 2 - Seleciono como saida (Valor inicial).
    set_bit(PIND, PIND2); // 2 - Seleciono como saida (Leitura).

    set_bit(DDRD, DD7);  // 7 - Seleciono como saida (Valor inicial).
    set_bit(DDRB, DDB0); // 8 - Seleciono como saida (Valor inicial).
    set_bit(DDRB, DDB1); // 9 - Seleciono como saida (Valor inicial).
}

void loop()
{
    // Lê a ponta onde o botão está mandando energia.
    // char click = digitalRead(2);
    char click = is_set_bit(PIND, _bit(PIND2));

    if (click == HIGH) // Botão sem precionar.
        turn_on_led(); // Acendo o led selecionado.
    else               // Botão precionado.
    {
        if (to_press) // Se estiver sendo precionado, comece a contar.
        {
            timer = millis();
            to_press = FALSE;
            select_led(); // Seleciono o proximo led a acender.
        }
        else if (millis() - timer > limite_timer) // Manter precionado por mais de 1 segundo, apaga todos os leds na hora.
            turn_off_now();                       // Seleciono para apagar todos os leds.
    }
    delay(5); // Um pequeno delay.
}

void turn_on_led()
{
    // Acende o led selecionado.
    if (light_up) // Se posso acender.
    {
        // Verifico o estado e acendo o selecionado.
        if (leds_states == GREEN)
        {
            unset_bit(PORTD, PD7); // Apago o vermelho
            set_bit(PORTB, PB1);   // Acendo o verde
        }
        else if (leds_states == YELLOW)
        {
            unset_bit(PORTB, PB1); // Apago o verde
            set_bit(PORTB, PB0);   // Acendo o amarelo
        }
        else if (leds_states == RED)
        {
            unset_bit(PORTB, PB0); // Apago o amarelo
            set_bit(PORTD, PD7);   // Acendo o vermelho
        }
        light_up = FALSE; // Não posso acender, pois já acendi
        to_press = TRUE;  // Posso precionar
    }
}
void select_led()
{
    // Seleciona o led a acender.
    if (!light_up) // Se não posso acender, seleciono o led a acender.
    {
        leds_states = (leds_states + 1) % 3; // Faz a seleção.
        light_up = TRUE;                     // Posso acender.
    }
}
void turn_off_now()
{
    // Apaga todos os leds na hora.
    leds_states = RESET; // Reseto os estados dos leds.
    turn_off();          // Desligo todos os leds.
    light_up = TRUE;     // Posso acender.
    to_press = TRUE;     // Posso precionar.
}
void turn_off()
{
    // Apaga todos os leds.
    unset_bit(PORTD, PD7);
    unset_bit(PORTB, PB0);
    unset_bit(PORTB, PB1);
}