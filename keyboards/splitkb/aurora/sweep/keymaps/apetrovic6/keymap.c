#include <stdint.h>
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_Y, KC_C, KC_L, KC_M, KC_K,                                     KC_Z, KC_F, KC_U, KC_COMMA, KC_QUOTE,
                 LGUI_T(KC_I), LALT_T(KC_S), LSFT_T(KC_R), LCTL_T(KC_T), KC_G,     KC_P, RCTL_T(KC_N), RSFT_T(KC_E), RALT_T(KC_A), RGUI_T(KC_O),
                 KC_Q, LCTL_T(KC_V), LALT_T(KC_W), KC_D, KC_J,                     KC_B, KC_H, LALT_T(KC_SLASH), LCTL_T(KC_DOT), KC_X,
                                            KC_TAB, KC_ENTER,                             KC_SPC, KC_BSPC),

	[1] = LAYOUT(RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,                       RGB_SPI, KC_BTN1, KC_WH_U, KC_BTN2, KC_TRNS,
                 KC_TRNS, KC_BTN2, KC_NO, KC_BTN1, KC_TRNS,                         KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
                 KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,                      RGB_SPD, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

	[2] = LAYOUT(KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_TRNS,                         KC_TRNS, KC_LGUI, KC_NO, LCTL(KC_LALT), LCA(KC_LSFT),
                 KC_TRNS, KC_HOME, KC_PGDN, KC_END, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

	[3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_UNDS, KC_PIPE, KC_QUOT, KC_TRNS,
                 KC_CIRC, KC_ASTR, KC_AMPR, KC_NO,   KC_TRNS,                       KC_HASH, KC_TILD, KC_SLSH, KC_DQUO, KC_DLR,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_MINS, KC_BSLS, KC_GRV,  KC_TRNS,
                                            RGB_RMOD, KC_TRNS,                          KC_TRNS, RGB_MOD),


	[4] = LAYOUT(KC_TRNS, KC_COLN, KC_LT, KC_GT, KC_SCLN,                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, KC_AT,                         KC_TRNS, KC_NO, KC_EQL, KC_PLUS, KC_PERC,
                 KC_TRNS, KC_EXLM, KC_LBRC, KC_RBRC, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_VOLD, KC_TRNS,                           KC_TRNS, KC_VOLU),

	[5] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10,
                 KC_TRNS, KC_NO, LCTL(KC_LALT), KC_TRNS, KC_TRNS,                   KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12,
                                             KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS),

	[6] = LAYOUT(KC_PSLS, KC_7, KC_8, KC_9, KC_PPLS,                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_0, KC_1, KC_2, KC_3, KC_PMNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS,
                 KC_PAST, KC_4, KC_5, KC_6, KC_PEQL,                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

	[7] = LAYOUT(KC_TRNS, KC_TRNS, KC_COLN, KC_ESC, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
                 KC_TRNS, KC_PERC, KC_SLSH, KC_ENT, KC_TRNS,                        DF(1), KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_EXLM, KC_TRNS,                       DF(0), KC_TRNS, RALT_T(KC_COMM), RCTL_T(KC_DOT),
                                            QK_BOOT, KC_TRNS,                            KC_TAB, KC_NO, KC_TRNS),
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
