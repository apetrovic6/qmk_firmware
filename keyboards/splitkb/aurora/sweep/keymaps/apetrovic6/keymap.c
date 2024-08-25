#include <stdint.h>
#include <stdbool.h>
#include "layers.h"

#include QMK_KEYBOARD_H


enum tap_dance_codes {
  TD_DOT_EXC,
  TD_SLSH_UNDRSCR,
  TD_COMMA_DASH,
  TD_X_PROG, // For switching to PROG_SYM layer
  TD_H_ESC, // H and ESCAPE
  TD_P_NAV,
  TD_CTRL_LEFT,
  TD_CTRL_RIGHT,
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

enum macros  {
    M_PARENS = 0,
};

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

static td_tap_t tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[ALPHA] = LAYOUT(KC_Y,        KC_C,         KC_L,         KC_M,         KC_K,       KC_Z,         KC_F,         KC_U,                    TD(TD_COMMA_DASH), KC_QUOTE,
                    LGUI_T(KC_I), LALT_T(KC_S), LSFT_T(KC_R), LCTL_T(KC_T), KC_G,       TD(TD_P_NAV), RCTL_T(KC_N), RSFT_T(KC_E),            RALT_T(KC_A),      RGUI_T(KC_O),
                    KC_Q, KC_V, KC_W, KC_D, KC_J,                                       KC_B,         TD(TD_H_ESC), TD(TD_SLSH_UNDRSCR),     TD(TD_DOT_EXC),    TD(TD_X_PROG),
                                            KC_TAB, KC_ENTER,                        KC_SPC, KC_BSPC),


	// [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //                KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_TRNS,                         KC_TRNS, KC_LGUI, KC_NO, LCTL(KC_LALT), LCA(KC_LSFT),
  //                KC_TRNS, KC_HOME, KC_PGDN, KC_END, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //                                           KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),
	[SYM] = LAYOUT(KC_AT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_UNDS, KC_PIPE, QK_BOOT, KC_SLASH,
                 KC_CIRC, KC_ASTR, KC_AMPR, KC_NO,   KC_TRNS,                       KC_HASH, KC_TILD, KC_SLSH, KC_DQUO, KC_DLR,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_MINS, KC_BSLS, KC_GRV,  KC_TRNS,
                                            RGB_RMOD, KC_TRNS,                          KC_TRNS, RGB_MOD),

	[PROG_SYM] = LAYOUT(KC_AT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_UNDS, KC_PIPE, QK_BOOT, KC_SLASH,
                 KC_CIRC, KC_ASTR, KC_AMPR, KC_NO,   KC_TRNS,                       KC_HASH, KC_TILD, KC_SLSH, KC_DQUO, KC_DLR,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_MINS, KC_BSLS, KC_GRV,  KC_TRNS,
                                            RGB_RMOD, KC_TRNS,                          KC_TRNS, RGB_MOD),

	// [NAV] = LAYOUT(RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,                       RGB_SPI, KC_HOME, KC_TRNS, KC_BTN2, KC_END,
  //                KC_TRNS, KC_BTN2, KC_NO, KC_BTN1, KC_TRNS,                         KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,
  //                KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,                      RGB_SPD, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS,
  //                                           KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

    [NAV] = LAYOUT(KC_TRNS, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,  KC_ACL0,           RGB_SPI, KC_HOME, KC_TRNS, KC_TRNS, KC_END,
                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1,                     KC_TRNS, TD(TD_CTRL_LEFT), KC_DOWN, KC_UP, TD(TD_CTRL_RIGHT),
                   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_ACL2,                     RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, TG(ALPHA),                           TO(ALPHA), KC_TRNS),

    [VIM] = LAYOUT(KC_CIRC, KC_7, KC_8, KC_9, KC_DOLLAR,                 RGB_SPI, KC_HOME, KC_TRNS, KC_TRNS, KC_END,
                   KC_NO, KC_4, KC_5, KC_6, KC_NO,                     KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
                   KC_NO, KC_1, KC_2, KC_3, KC_NO,                     RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_0, KC_DOLLAR,                           KC_TRNS, KC_TRNS),

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

// #ifdef RGBLIGHT_ENABLE
// void keyboard_post_init_user(void) {
//   rgblight_enable_noeeprom(); // enables RGB, without saving settings
//   rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
//   rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
// }
// #endif

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// Define tap dance states
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_DOUBLE_HOLD;
    }
    return TD_UNKNOWN;
}

void dot_exc_finished(tap_dance_state_t *state, void *user_data);
void dot_exc_reset(tap_dance_state_t *state, void *user_data);

void dot_exc_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_DOT);  // Single tap outputs '.'
            break;
        case TD_SINGLE_HOLD:
            tap_code16(S(KC_1));  // Use tap_code16 for Shifted '1' which is '!'
            break;
        default:
            break;
    }
}

void dot_exc_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}

void slash_underscore_finished(tap_dance_state_t *state, void *user_data);
void slash_underscore_reset(tap_dance_state_t *state, void *user_data);

void slash_underscore_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SLASH);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(S(KC_MINUS));
            break;
        default:
            break;
    }
}

void slash_underscore_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}

void comma_dash_finished(tap_dance_state_t *state, void *user_data);
void comma_dash_reset(tap_dance_state_t *state, void *user_data);

void comma_dash_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_COMMA);  // Single tap outputs '.'
            break;
        case TD_SINGLE_HOLD:
            tap_code16(KC_MINUS);  // Use tap_code16 for Shifted '1' which is '!'
            break;
        default:
            break;
    }
}

void comma_dash_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}

void x_prog_finished(tap_dance_state_t *state, void *user_data);
void x_prog_reset(tap_dance_state_t *state, void *user_data);

void x_prog_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_X);
            break;
        case TD_SINGLE_HOLD:
            layer_on(PROG_SYM);
            break;
        default:
            break;
    }
}

void x_prog_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    // tap_state.state = TD_NONE;
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
        set_oneshot_layer(PROG_SYM, ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
        default:
            break;
    }
}

void h_escape_finished(tap_dance_state_t *state, void *user_data);
void h_escape_reset(tap_dance_state_t *state, void *user_data);

void h_escape_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_H);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(KC_ESC);
            break;
        default:
            break;
    }
}

void h_escape_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}


void p_nav_prog_finished(tap_dance_state_t *state, void *user_data);
void p_nav_reset(tap_dance_state_t *state, void *user_data);

void p_nav_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_P);
            break;
        case TD_SINGLE_HOLD:
            layer_invert(NAV);
            break;
        default:
            break;
    }
}

void ctrl_left_finished(tap_dance_state_t *state, void *user_data);
void ctrl_left_reset(tap_dance_state_t *state, void *user_data);

void ctrl_left_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_LEFT);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_LEFT));
            break;
        default:
            break;
    }
}

void ctrl_left_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}

void ctrl_right_finished(tap_dance_state_t *state, void *user_data);
void ctrl_right_reset(tap_dance_state_t *state, void *user_data);

void ctrl_right_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_RIGHT);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_RIGHT));
            break;
        default:
            break;
    }
}

void ctrl_right_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}

// Tap Dance definition
tap_dance_action_t tap_dance_actions[] = {
    [TD_DOT_EXC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dot_exc_finished, dot_exc_reset),
    [TD_SLSH_UNDRSCR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, slash_underscore_finished, slash_underscore_reset),
    [TD_COMMA_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, comma_dash_finished, comma_dash_reset),
    [TD_X_PROG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_prog_finished, x_prog_reset),
    [TD_H_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, h_escape_finished, h_escape_reset),
    [TD_P_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, p_nav_finished, NULL),
    [TD_CTRL_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_left_finished, ctrl_left_reset),
    [TD_CTRL_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_right_finished, ctrl_right_reset),
};
