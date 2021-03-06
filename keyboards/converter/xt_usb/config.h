/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6512
#define DEVICE_VER      0x0001
#define MANUFACTURER    QMK
#define PRODUCT         XT keyboard converter
#define DESCRIPTION     convert XT keyboard to USB


/* matrix size */
#define MATRIX_ROWS 16  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) || \
    keyboard_report->mods == (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RSHIFT)) \
)


//#define NO_SUSPEND_POWER_DOWN

/*
 * XT Pin interrupt
 */
#define XT_CLOCK_PORT  PORTD
#define XT_CLOCK_PIN   PIND
#define XT_CLOCK_DDR   DDRD
#define XT_CLOCK_BIT   1
#define XT_DATA_PORT   PORTD
#define XT_DATA_PIN    PIND
#define XT_DATA_DDR    DDRD
#define XT_DATA_BIT    0
#define XT_RST_PORT    PORTB
#define XT_RST_PIN     PINB
#define XT_RST_DDR     DDRB
#define XT_RST_BIT     7

/* hard reset: low pulse for 500ms and after that HiZ for safety */
#define XT_RESET() do { \
    XT_RST_PORT &= ~(1<<XT_RST_BIT);  \
    XT_RST_DDR  |=  (1<<XT_RST_BIT);  \
    _delay_ms(500);                   \
    XT_RST_DDR  &= ~(1<<XT_RST_BIT);  \
} while (0)

/* INT1 for falling edge of clock line */
#define XT_INT_INIT()  do {    \
    EICRA |= ((1<<ISC11) |      \
              (0<<ISC10));      \
} while (0)
/* clears flag and enables interrupt */
#define XT_INT_ON()  do {      \
    EIFR  |= (1<<INTF1);        \
    EIMSK |= (1<<INT1);         \
} while (0)
#define XT_INT_OFF() do {      \
    EIMSK &= ~(1<<INT1);        \
} while (0)
#define XT_INT_VECT    INT1_vect
