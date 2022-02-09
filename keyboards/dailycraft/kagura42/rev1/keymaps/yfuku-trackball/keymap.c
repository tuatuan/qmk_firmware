/* Copyright 2020 yfuku
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "yfuku_keymaps.h"
#include "paw3204.h"
#include "pointing_device.h"
bool isScrollMode;

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SCRL
};


// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define TAPPING_LAYER_TERM 230
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GS_S:
      return TAPPING_LAYER_TERM;
    case GS_L:
      return TAPPING_LAYER_TERM;
    case A_D:
      return TAPPING_LAYER_TERM;
    case A_K:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_wrapper(
       __QWERTY_L1__, __QWERTY_R1__,
       __QWERTY_L2__, __QWERTY_R2__,
       __QWERTY_L3__, __QWERTY_R3__,
       __QUERTY_T3__,
       KC_1, KC_2, KC_3
    ),

    [_RAISE] = LAYOUT_wrapper(
       __RAISE_L1__, __RAISE_R1__,
       __RAISE_L2__, __RAISE_R2__,
       __RAISE_L3__, __RAISE_R3__,
       __RAISE_T3__,
       __TRANSx3__
    ),

    [_LOWER] = LAYOUT_wrapper(
       __LOWER_L1__, __LOWER_R1__,
       __LOWER_L2__, __LOWER_R2__,
       __LOWER_L3__, __LOWER_R3__,
       __LOWER_T3__,
       __TRANSx3__
    ),
    [_ADJUST] = LAYOUT_wrapper(
       __TRANSx6__, __TRANSx6__, 
       __TRANSx6__, __TRANSx6__, 
       __TRANSx6__,  __TRANSx6__, 
       __TRANSx3__, __TRANSx3__,
       __TRANSx3__
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SCRL:
      if (record->event.pressed) {
        isScrollMode = true;
        dprint("scroll ON\n");
      }
      else {
        isScrollMode = false;
        dprint("scroll OFF\n");
      }
      return false;
  }
  return true;
}

void matrix_init_user(void) {
    init_paw3204();
}

void matrix_scan_user(void) {
    static int  cnt;
    static bool paw_ready;

    report_mouse_t mouse_rep = pointing_device_get_report();

    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if (paw_ready) {
        uint8_t stat;
        int8_t x, y;
        int8_t r_x, r_y;

        read_paw3204(&stat, &x, &y);

        // 45-degree angle
        int8_t degree = 45;
        r_x =  x * cos(degree) + y * sin(degree);
        r_y = -x * sin(degree) + y * cos(degree);
        /* normal angle
        r_x = y;
        r_y = x;
        */

        if (isScrollMode) {
            if (cnt % 5 == 0) {
                mouse_rep.v = -r_y;
                mouse_rep.h = r_x;
            }
        } else {
            mouse_rep.x = r_x;
            mouse_rep.y = r_y;
        }

        if (cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _LOWER:
        isScrollMode = true;
        break;
    default:
        isScrollMode = false;
        break;
    }
  return state;
}
