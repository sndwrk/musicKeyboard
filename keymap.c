/* Copyright 2020 Boardsource
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

enum layers {
    _MAIN,
    _RAISE,
    _LOWER,
    _MIDICONTROL,
};

// Readability keycodes
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT_ortho_4x12(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    RGB_TOG, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,   LOWER,  TG(3),  KC_SPC,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

  [_RAISE] = LAYOUT_ortho_4x12(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
  RESET,   _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
  ),

  [_LOWER] = LAYOUT_ortho_4x12(
 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
 KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
 _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
 RGB_MOD, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
  ),

  [_MIDICONTROL] = LAYOUT_ortho_4x12(
  MI_G_2, MI_Gs_2, MI_A_2,  MI_As_2, MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3, MI_Ds_3, MI_E_3,  MI_F_3,  MI_Fs_3,
  MI_D_2, MI_Ds_2, MI_E_2,  MI_F_2,  MI_Fs_2, MI_G_2,  MI_Gs_2, MI_A_2, MI_As_2, MI_B_2,  MI_C_3,  MI_Cs_3,
  MI_A_1, MI_As_1, MI_B_1,  MI_C_2,  MI_Cs_2, MI_D_2,  MI_Ds_2, MI_E_2, MI_F_2,  MI_Fs_2, MI_G_2,  MI_Gs_2,
  MI_E_1, MI_F_1,  MI_Fs_1, MI_G_1,  MI_Gs_1, MI_A_1,  MI_As_1, MI_B_1, MI_C_2,  MI_OCTD, MI_OCTU, TG(3)
  )


};

// Light indices when in MIDI mode
int MLIGHTS_A[] = {10, 22, 34, 46, 25, 37,27, 39, 29, 41, 31, 43};
int MLIGHTS_B[] = {55, 56};

//Light indices when in Keyboard mode
int KLIGHTS_A[] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44};

// Find sizes of the arrays using a method described here: https://www.geeksforgeeks.org/how-to-find-size-of-array-in-cc-without-using-sizeof-operator/
int MLIGHTS_A_SIZE = *(&MLIGHTS_A + 1) - MLIGHTS_A;
int MLIGHTS_B_SIZE = *(&MLIGHTS_B + 1) - MLIGHTS_B;

int KLIGHTS_A_SIZE = *(&KLIGHTS_A + 1) - KLIGHTS_A;


// These shorthands are used below to set led colors on each matrix cycle
void loop_colorset(int *indices, int array_size, int r, int g, int b) {
  for (int i = 0; i < array_size; i++) { 
  rgb_matrix_set_color(indices[i], r, g, b); // Set color A here
  }
}



void rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            rgb_matrix_set_color_all(80,0,0);
            loop_colorset(KLIGHTS_A,KLIGHTS_A_SIZE,0,40,80);
            rgb_matrix_set_color(50, 0, 100, 0);
            rgb_matrix_set_color(53, 0, 100, 0);
            break;
        case _RAISE:
            rgb_matrix_set_color_all(0,0,0);
            break;
        case _LOWER:
            rgb_matrix_set_color_all(0,0,0);
            break;
        case _MIDICONTROL: 
            rgb_matrix_set_color_all(0, 0, 0);
            loop_colorset(MLIGHTS_A, MLIGHTS_A_SIZE,70,70,70);
            loop_colorset(MLIGHTS_B, MLIGHTS_B_SIZE, 0, 100, 0);
            rgb_matrix_set_color(57, 100, 0, 0);

            break;
        default:
            break;
    }
}

