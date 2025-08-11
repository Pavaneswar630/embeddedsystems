#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LED_PIN PB5 // Arduino pin 13

void UART_init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);                 // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data
}

void UART_transmit(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void UART_print(char *str) {
    while (*str) {
        UART_transmit(*str++);
    }
}

void ADC_init() {
    ADMUX = (1 << REFS0); // AVcc reference, ADC0
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC, prescaler 128
}

uint16_t ADC_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    return ADC;
}

int main(void) {
    char buffer[20];
    uint16_t adc_value;
    float temperature;

    DDRB |= (1 << LED_PIN); // Set LED pin as output
    UART_init(103); // Baud rate 9600 (F_CPU=16MHz)
    ADC_init();

    while (1) {
        adc_value = ADC_read(0); // LM35 on A0
        temperature = (adc_value * 5.0 * 100.0) / 1024.0; // °C
        sprintf(buffer, "Temp: %.2f C\r\n", temperature);
        UART_print(buffer);

        if (temperature > 30.0) {
            PORTB |= (1 << LED_PIN); // Turn on LED
        } else {
            PORTB &= ~(1 << LED_PIN); // Turn off LED
        }

        _delay_ms(1000);
    }
}
