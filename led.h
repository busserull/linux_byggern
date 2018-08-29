/**
 * @file
 * Sample LED module provided for testing the microcontroller
 *
 * This module assumes there is an LED connected to PC0
 * on the ATmega 162 (pin 21), in a sinking configuration;
 * this means that the current flows into the chip
 */
#ifndef LED_H
#define LED_H

/**
 * @brief Initialize LED; necessary to call only once.
 */
void led_init();

/**
 * @brief Turn LED on.
 */
void led_turn_on();

/**
 * @brief Turn LED off.
 */
void led_turn_off();

#endif
