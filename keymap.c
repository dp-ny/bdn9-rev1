/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
// #include "print.h"

;enum encoder_names {
  _ENCODER,
};

enum custom_keycodes {
    FIRST_CODE = SAFE_RANGE,
    KNOB,
};

enum layers {
  DEFAULT,
  NUM_LAYERS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [DEFAULT] = LAYOUT(
        KC_MUTE, KNOB, KC_MPLY,
        MO(1)  , KC_UP  , XXXXXXX,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, _______,
        KC_MPRV, KC_END , KC_MNXT
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KNOB:

        break;
    }
    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
  //   if(IS_LAYER_ON(_RAISE)) { // on Raise layer control volume
  //   if (clockwise){
  //     tap_code(KC_VOLU);
  //   } else{
  //     tap_code(KC_VOLD);
  //   }
  // } else { // on other layers emulate mouse scrollwheel
  //   if (clockwise){
  //     tap_code(KC_MS_WH_DOWN);
  //   } else{
  //     tap_code(KC_MS_WH_UP);
  //   }
  // }
    // int numLayers = NUM_LAYERS;
    // int currLayer = biton32(layer_state);
    if (clockwise) {
        // int nextState = (currLayer + numLayers + 1) % numLayers;
        tap_code(KC_VOLU);
    } else {
        // int nextState = (currLayer + numLayers - 1) % numLayers;
        tap_code(KC_VOLD);
    }
    // MO(nextState);
}

enum nightrider {
  nr_slowest = RGBLIGHT_MODE_KNIGHT,
  nr_slow,
  nr_fast,
  nr_faster,
};

void matrix_init_user() {
    rgblight_mode(nr_slowest);
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  if (layer == DEFAULT) {
    rgblight_sethsv_red();
  } else {
    rgblight_sethsv_cyan();
  }
  return state;
}
