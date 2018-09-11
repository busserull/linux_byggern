#ifndef UART_H
#define UART_H

void uart_init();

void uart_read_interrupt_enable();

void uart_read_interrupt_disable();

void uart_write(char letter);

char uart_read();

#endif
