/**
 ******************************************************************************
 * @file           : ecu.h
 * @author         : Rohan K
 * @brief          : ECU Controls
 ******************************************************************************
 * @details
 * Main ECU functions are wrapped here
 ******************************************************************************
 */

#include <stm32f405xx.h>

#ifndef ECU_H_
#define ECU_H_

/**
 * The GPIO port and pin for the ignition key
 * SW2 (PB3)
 */
#define IGNITION_KEY_PORT GPIOB
#define IGNITION_KEY_PIN 3

/**
 * The GPIO port and pin for the left turn indicator
 * LED4 (PB15)
 */
#define LEFT_TURN_LAMP_PORT GPIOB
#define LEFT_TURN_LAMP_PIN 15

/**
 * The GPIO port and pin for the left turn switch
 * SW3 (PB4)
 */
#define LEFT_TURN_SWITCH_PORT GPIOB
#define LEFT_TURN_SWITCH_PIN 4

/**
 * The GPIO port and pin for the right turn indicator
 * LED3 (PB14)
 */
#define RIGHT_TURN_LAMP_PORT GPIOB
#define RIGHT_TURN_LAMP_PIN 14

/**
 * The GPIO port and pin for the right turn switch
 * SW1 (PB7)
 */
#define RIGHT_TURN_SWITCH_PORT GPIOB
#define RIGHT_TURN_SWITCH_PIN 7

/**
 * The GPIO port and pin for the headlight
 * LED1 (PC6)
 */
#define HEAD_LIGHT_PORT GPIOC
#define HEAD_LIGHT_PIN 6

/**
 * The GPIO port and pin for the headlight switch
 * SW4 (PA15)
 */
#define HEAD_LIGHT_SWITCH_PORT GPIOA
#define HEAD_LIGHT_SWITCH_PIN 15

/**
 * The GPIO port and pin for the fuel indicator
 */
#define FUEL_INDICATOR_PORT GPIOC
#define FUEL_INDICATOR_PORT 0

/**
 * The value to be transmitted via the UART to verify the status of the ECU
 */
#define UART_TRANSMIT_DATA 'j'

/**
 * The statuses available for the engine (ignition)
 * OFF: The engine is turned OFF
 * ON: The engine is turned ON
 */
enum ENGINE_STATUS
{
    ENGINE_OFF,
    ENGINE_ON
};

/**
 * Statuses available for the turn indicator
 * OFF: No turn indicator is working or is turned OFF
 * LEFT: Left turn indicator is turned ON
 * RIGHT: Right turn indicator is turned ON
 */
enum TURN_INDICATOR_STATUS
{
    TURN_INDICATOR_OFF,
    TURN_INDICATOR_LEFT,
    TURN_INDICATOR_RIGHT
};

/**
 * Statuses available for the headlight
 * OFF: Headlights are turned OFF
 * LOW: Headlights are dimmed (Low intensity)
 * HIGH: Headlights are bright (High intensity)
 * PARKING: Parking lights are ON
 */
enum HEAD_LIGHT_STATUS
{
    HEAD_LIGHT_OFF,
    HEAD_LIGHT_LOW_BEAM,
    HEAD_LIGHT_HIGH_BEAM,
    PARKING_LIGHT_ON
};

/**
 * Status of the UART transmission
 * OK: The transferred data is successfully received
 * NOTOK: The transferred data is corrupted or lost
 */
enum UART_STATUS
{
    UART_OK,
    UART_NOT_OK
};

/**
 * Initializes the ECU
 * Sets the GPIO pins for the ignition key, turn indicators, headlight and fuel indicator
 * Sets the UART for communication with the dashboard
 * Sets the ADC for reading the fuel level
 * Sets the timer for the turn indicator
 */
void initialize_ecu(void);

/**
 * Sets the turn indicator status
 * @param status The status of the turn indicator
 * @note If parking mode is ON, the turn indicators are unavailable
 */
void set_turn_indicator(enum TURN_INDICATOR_STATUS);

/**
 * Sets the headlight status
 * @param status The status of the headlight
 * @note If the turn indicators are ON, the parking mode is unavailable
 */
void set_head_light(enum HEAD_LIGHT_STATUS);

/**
 * Sets the fuel indicator status
 * @param status The status of the fuel indicator
 */
void set_ignition(enum ENGINE_STATUS);

/**
 * Transmit and receive data via UART
 */
void uart_signal_check();

#endif /* ECU_H_ */