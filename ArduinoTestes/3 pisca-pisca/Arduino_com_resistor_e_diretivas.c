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

char leds_states = GREEN; // Estado dos leds
char light_up = TRUE;     // Posso acender
char to_press = TRUE;     // Posso precionar

unsigned long int timer;
unsigned long int limite_timer = 1000;

void turn_off();     // Apaga os leds.
void turn_on_led();  // Acende o led selecionado.
void select_led();   // Seleciona o led a acender.
void turn_off_now(); // Apaga todos os leds na hora.

void setup()
{
    pinMode(2, INPUT); // DD2 && PD2

    pinMode(7, OUTPUT); // DD7 && PD7
    pinMode(8, OUTPUT); // DDB0 && PB0
    pinMode(9, OUTPUT); // DDB1 && PB1
}

void loop()
{
    char click = digitalRead(2); // Lê a ponta onde o botão está mandando energia.

    if (click == HIGH) // Botão sem precionar
        turn_on_led(); // Seleciono o led que será acesso e digo que não acendi a cor correta.
    else               // Botão precionado
    {
        if (to_press) // Se for precionado, comece a contar
        {
            timer = millis();
            to_press = FALSE;
            select_led();
        }
        else if (millis() - timer > limite_timer) // Manter precionado por mais de 1 segundo, apaga todos os leds na hora.
            turn_off_now();                       // Seleciono para apagar todos os leds.
    }
    delay(5); // Um pequeno delay
}

void turn_on_led()
{
    if (light_up) // Se posso acender
    {

        if (leds_states == GREEN)
        {
            digitalWrite(7, LOW);  // Desligo o vermelho
            digitalWrite(9, HIGH); // Acendo o verde
        }
        else if (leds_states == YELLOW)
        {
            digitalWrite(9, LOW);  // Desligo o verde
            digitalWrite(8, HIGH); // Acendo o amarelo
        }
        else if (leds_states == RED)
        {
            digitalWrite(8, LOW);  // Desligo o amarelo
            digitalWrite(7, HIGH); // Acendo o verde
        }
        light_up = FALSE; // Não posso acender, pois já acendi
        to_press = TRUE;  // Posso precionar
    }
}
void select_led()
{
    if (!light_up) // Se não posso acender, seleciono o led a acender
    {
        leds_states = (leds_states + 1) % 3; // Faz a seleção.
        light_up = TRUE;                     // Posso acender
    }
}
void turn_off_now()
{
    leds_states = RESET; // Reseto os estados dos leds
    turn_off();          // Desligo todos os leds
    light_up = TRUE;     // Posso acender
    to_press = TRUE;     // Posso precionar
}
void turn_off()
{
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
}