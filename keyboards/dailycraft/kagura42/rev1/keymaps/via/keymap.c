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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE
};

#define L_SPC LT(_LOWER, KC_SPC)
#define R_ENT LT(_RAISE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_RSFT,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                                   KC_LGUI, KC_LANG2,L_SPC,            R_ENT,   KC_LANG1,KC_RALT,
        KC_1,    KC_2,    KC_3
    ),
    [_LOWER] = LAYOUT(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_EQL,  KC_PLUS, KC_ASTR, KC_PERC, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, _______, _______, _______, _______,
                                   _______, _______, _______,          KC_DEL,  _______, _______,
        KC_1,    KC_2,    KC_3
    ),
    [_RAISE] = LAYOUT(
        _______, KC_BSLS, KC_EXLM, KC_AMPR, KC_PIPE, XXXXXXX,          XXXXXXX, KC_EQL,  KC_PLUS, KC_ASTR, KC_PERC, _______,
        _______, KC_HASH, KC_GRV,  KC_DQT,  KC_QUOT, KC_TILD,          KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DLR,  _______,
        _______, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN,          KC_RPRN, KC_RBRC, KC_RCBR, KC_AT,   KC_CIRC, _______,
                                   _______, _______, KC_BSPC,          _______, _______, _______,
        KC_1,    KC_2,    KC_3
   ),
};

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 4, .col = 0},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 4, .col = 1},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 4, .col = 2},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 4, .col = 3},
    .pressed = false
};

keyevent_t encoder3_ccw = {
    .key = (keypos_t){.row = 4, .col = 4},
    .pressed = false
};

keyevent_t encoder3_cw = {
    .key = (keypos_t){.row = 4, .col = 5},
    .pressed = false
};

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

    if (IS_PRESSED(encoder2_ccw)) {
        encoder2_ccw.pressed = false;
        encoder2_ccw.time = (timer_read() | 1);
        action_exec(encoder2_ccw);
    }

    if (IS_PRESSED(encoder2_cw)) {
        encoder2_cw.pressed = false;
        encoder2_cw.time = (timer_read() | 1);
        action_exec(encoder2_cw);
    }

    if (IS_PRESSED(encoder3_ccw)) {
        encoder3_ccw.pressed = false;
        encoder3_ccw.time = (timer_read() | 1);
        action_exec(encoder3_ccw);
    }

    if (IS_PRESSED(encoder3_cw)) {
        encoder3_cw.pressed = false;
        encoder3_cw.time = (timer_read() | 1);
        action_exec(encoder3_cw);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
        }
    } else if (index == 2) {
        if (clockwise) {
            encoder3_cw.pressed = true;
            encoder3_cw.time = (timer_read() | 1);
            action_exec(encoder3_cw);
        } else {
            encoder3_ccw.pressed = true;
            encoder3_ccw.time = (timer_read() | 1);
            action_exec(encoder3_ccw);
        }
    }

    return true;
}
