#include <stdint.h>
#include <stdbool.h>
#include "layers.h"
#include "macros.h"

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
  TD_DOUBLE_COLON,
  TD_TAB_SYM,
  TD_Q_UNDO,
  TD_V_CUT,
  TD_W_COPY,
  TD_D_PASTE
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
    TD_TRIPLE_HOLD,
} td_state_t;



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

	// [ALPHA] = LAYOUT(KC_Q,        KC_W,         KC_F,         KC_P,         KC_B,       KC_J,         KC_L,         KC_U,                    KC_Y, KC_SEMICOLON,
    //                 LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G,       TD(TD_P_NAV), RCTL_T(KC_N), RSFT_T(KC_E),            RALT_T(KC_I),      RGUI_T(KC_O),
    //                 KC_Z, KC_X, KC_C, KC_D, KC_V,                                       KC_K,         TD(TD_H_ESC), KC_COMMA,     TD(TD_DOT_EXC),    TD(TD_X_PROG),
    //                                         TD(TD_TAB_SYM), LT(NUM_FN,KC_ENTER),                        KC_SPC, KC_BSPC),

	[ALPHA] = LAYOUT(KC_Y,        KC_C,         KC_L,         KC_M,         KC_K,       KC_Z,         KC_F,         KC_U,                    TD(TD_COMMA_DASH), KC_QUOTE,
                    LGUI_T(KC_I), LALT_T(KC_S), LSFT_T(KC_R), LCTL_T(KC_T), KC_G,       TD(TD_P_NAV), RCTL_T(KC_N), RSFT_T(KC_E),            RALT_T(KC_A),      RGUI_T(KC_O),
                    TD(TD_Q_UNDO), TD(TD_V_CUT), TD(TD_W_COPY), TD(TD_D_PASTE), KC_J,                                       KC_B,         TD(TD_H_ESC), TD(TD_SLSH_UNDRSCR),     TD(TD_DOT_EXC),    TD(TD_X_PROG),
                                            LT(SYM, KC_TAB), LT(NUM_FN,KC_ENTER),                        LT(NAV, KC_SPC), LT(UTIL, KC_ESC)),


	// [2] = LAYOUT(KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS, KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //                KC_LEFT, KC_UP, KC_DOWN, KC_RGHT, KC_TRNS,                         KC_TRNS, KC_LGUI, KC_NO, LCTL(KC_LALT), LCA(KC_LSFT),
  //                KC_TRNS, KC_HOME, KC_PGDN, KC_END, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //                                           KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

	[SYM] = LAYOUT(KC_AT, KC_HASH, KC_DOLLAR, KC_PERC, KC_UNDS,                         KC_CIRC, KC_AMPR, KC_ASTR, TD(TD_DOUBLE_COLON), KC_SCLN,
                 KC_EQUAL, KC_QUOT,       KC_GRV, KC_NO,   KC_MINUS,                     KC_BACKSLASH, KC_LPRN, KC_RPRN, LSFT(KC_LBRC), LSFT(KC_RBRC),
                 KC_TILD, LSFT(KC_QUOTE), LSFT(KC_GRAVE), KC_TRNS, KC_DQUO,             LSFT(KC_BACKSLASH), KC_LBRC, KC_RBRC, KC_LABK,  KC_RABK,
                                            RGB_RMOD, TO(ALPHA),                         KC_TRNS, KC_TRNS),

	[PROG_SYM] = LAYOUT(M_DOUBLE_EQUAL, M_TRIPLE_EQUAL, M_NOT_EQUAL , M_GT_EQUAL, M_LT_EQUAL,         KC_NO, M_AND_OPERATOR, M_OR_OPERATOR, M_INCLUDE, KC_NO,
                 M_PARENS, M_CURLY, M_BRACKETS, M_ANGLE, KC_NO,                                       KC_NO, M_ARROW_OPERATOR, M_ARROW_FN, KC_DQUO, KC_DLR,
                 M_DECREMENT, M_INCREMENT, KC_NO, KC_NO, KC_NO,                                         KC_NO, M_LEFT_SHIFT, M_RIGHT_SHIFT,  M_UPROPERTY, M_UFUNCTION,
                                            RGB_RMOD, KC_TRNS,                                          KC_TRNS, RGB_MOD),

	// [NAV] = LAYOUT(RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,                       RGB_SPI, KC_HOME, KC_TRNS, KC_BTN2, KC_END,
  //                KC_TRNS, KC_BTN2, KC_NO, KC_BTN1, KC_TRNS,                         KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R,KC_SCLNKC_SCLNKC_SCLN
  //                KC_TRNS, RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,                      RGB_SPD, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS,
  //                                           KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

    [NAV] = LAYOUT(KC_TRNS, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,  KC_ACL0,           RGB_SPI, KC_HOME, KC_TRNS, KC_TRNS, KC_END,
                   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1,                     KC_TRNS, TD(TD_CTRL_LEFT), KC_DOWN, KC_UP, TD(TD_CTRL_RIGHT),
                   KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_ACL2,                     RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                        KC_TRNS, TO(ALPHA),                           KC_TRNS, KC_TRNS),

    [VIM] = LAYOUT(KC_CIRC, KC_7, KC_8, KC_9, KC_DOLLAR,                 RGB_SPI, KC_HOME, KC_TRNS, KC_TRNS, KC_END,
                   KC_NO, KC_4, KC_5, KC_6, KC_NO,                     KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
                   KC_NO, KC_1, KC_2, KC_3, KC_NO,                     RGB_SPD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_0, KC_DOLLAR,                           KC_TRNS, KC_TRNS),

	[NUM_FN] = LAYOUT(KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS,                    KC_SLASH, KC_7, KC_8, KC_9, KC_MINUS,
                 KC_F5, KC_F6, KC_F7, KC_F8, KC_AT,                              KC_ASTR, KC_4, KC_5, KC_6, KC_PLUS,
                 KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS,                            KC_DOT, KC_1, KC_2, KC_3, KC_EQUAL,
                                            KC_VOLD, TG(ALPHA),                       KC_0, KC_TRNS),

	[UTIL] = LAYOUT(KC_NO, KC_NO, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), KC_NO,                             KC_NO, KC_NO, QK_BOOT, LGUI(KC_L),KC_SLEP,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                                    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_LOCKING_CAPS_LOCK, LGUI(LSFT(KC_S)), KC_DEL, KC_NO, KC_NO,                                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                            KC_VOLD, KC_TRNS,                           KC_TRNS, KC_VOLU),

	[11] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10,
                 KC_TRNS, KC_NO, LCTL(KC_LALT), KC_TRNS, KC_TRNS,                   KC_TRNS, KC_F4, KC_F5, KC_F6, KC_F11,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F12,
                                             KC_TRNS, KC_TRNS,                          KC_TRNS, KC_TRNS),

	[12] = LAYOUT(KC_PSLS, KC_7, KC_8, KC_9, KC_PPLS,                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_0, KC_1, KC_2, KC_3, KC_PMNS,                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS,
                 KC_PAST, KC_4, KC_5, KC_6, KC_PEQL,                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS),

	[13] = LAYOUT(KC_TRNS, KC_TRNS, KC_COLN, KC_ESC, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,
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


void double_colon_finished(tap_dance_state_t *state, void *user_data);
void double_colon_reset(tap_dance_state_t *state, void *user_data);

void double_colon_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(LSFT(KC_SEMICOLON));
            break;
        case TD_SINGLE_HOLD:
            send_string("::");
            break;
        default:
            break;
    }
}

void double_colon_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}


void tab_sym_finished(tap_dance_state_t *state, void *user_data);
void tab_sym_reset(tap_dance_state_t *state, void *user_data);

void tab_sym_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_TAB);
            break;
        case TD_SINGLE_HOLD:
            layer_invert(SYM);
            break;
        default:
            break;
    }
}

void q_undo_finished(tap_dance_state_t *state, void *user_data);
void q_undo_reset(tap_dance_state_t *state, void *user_data);

void q_undo_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_Q);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_Z));
            break;
        default:
            break;
    }
}

void q_undo_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}


void v_cut_finished(tap_dance_state_t *state, void *user_data);
void v_cut_reset(tap_dance_state_t *state, void *user_data);

void v_cut_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_V);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_X));
            break;
        default:
            break;
    }
}

void v_cut_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}

void w_copy_finished(tap_dance_state_t *state, void *user_data);
void w_copy_reset(tap_dance_state_t *state, void *user_data);

void w_copy_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_W);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_C));
            break;
        default:
            break;
    }
}
void w_copy_reset(tap_dance_state_t *state, void *user_data) {
    // No need for unregister_code when using tap_code or tap_code16
    tap_state.state = TD_NONE;
}



//   TD_D_PASTE
void d_paste_finished(tap_dance_state_t *state, void *user_data);
void d_paste_reset(tap_dance_state_t *state, void *user_data);

void d_paste_finished(tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_D);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(LCTL(KC_V));
            break;
        default:
            break;
    }
}
void d_paste_reset(tap_dance_state_t *state, void *user_data) {
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
    [TD_DOUBLE_COLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_colon_finished, double_colon_reset),
    [TD_TAB_SYM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_sym_finished, NULL),
    [TD_Q_UNDO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, q_undo_finished, q_undo_reset),
    [TD_V_CUT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, v_cut_finished, v_cut_reset),
    [TD_W_COPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, w_copy_finished, w_copy_reset),
    [TD_D_PASTE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, d_paste_finished, d_paste_reset),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_BRACKETS:
               if (record->event.pressed) {
                     SEND_STRING("[]" SS_TAP(X_LEFT));
                }
        break;

        case M_PARENS:
            if (record->event.pressed) {
                SEND_STRING("()" SS_TAP(X_LEFT));
            }
        break;

        case M_CURLY:
            if (record->event.pressed) {
                SEND_STRING("{}" SS_TAP(X_LEFT));
            }
        break;

        case M_ANGLE:
        if (record->event.pressed) {
            SEND_STRING("<>" SS_TAP(X_LEFT));
        }
        break;

        case M_DOUBLE_EQUAL:
        if (record->event.pressed) {
            SEND_STRING("==");
        }
        break;

        case M_NOT_EQUAL:
        if (record->event.pressed) {
            SEND_STRING("!=");
        }
        break;

        case M_GT_EQUAL:
        if (record->event.pressed) {
            SEND_STRING(">=");
        }
        break;

        case M_LT_EQUAL:
        if (record->event.pressed) {
            SEND_STRING("<=");
        }
        break;

        case M_TRIPLE_EQUAL:
        if (record->event.pressed) {
            SEND_STRING("===");
        }
        break;

        case M_ARROW_OPERATOR:
        if (record->event.pressed) {
            SEND_STRING("->");
        }
        break;

        case M_ARROW_FN:
        if (record->event.pressed) {
            SEND_STRING("=>");
        }
        break;

        case M_INCLUDE:
        if (record->event.pressed) {
              SEND_STRING("#include \"\"" SS_DELAY(500) SS_TAP(X_LEFT));
        }
        break;

        case M_LEFT_SHIFT:
        if (record->event.pressed) {
            SEND_STRING("<<");
        }
        break;

        case M_RIGHT_SHIFT:
        if (record->event.pressed) {
            SEND_STRING(">>");
        }
        break;

        case M_AND_OPERATOR:
        if (record->event.pressed) {
            SEND_STRING("&&");
        }
        break;

        case M_OR_OPERATOR:
        if (record->event.pressed) {
            SEND_STRING("||");
        }
        break;

        case M_INCREMENT:
        if (record->event.pressed) {
            SEND_STRING("++");
        }
        break;

        case M_DECREMENT:
        if (record->event.pressed) {
            SEND_STRING("--");
        }
        break;

        case M_UPROPERTY:
        if (record->event.pressed) {
            SEND_STRING("UPROPERTY()" SS_DELAY(500) SS_TAP(X_LEFT));
        }
        break;

        case M_UFUNCTION:
        if (record->event.pressed) {
            SEND_STRING("UFUNCTION()" SS_DELAY(500) SS_TAP(X_LEFT));
        }
        break;
    };
    return true;
}


// extern rgb_config_t rgb_matrix_config;

// void keyboard_post_init_user(void) {
//   rgb_matrix_enable();
// }

// const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
//     [ALPHA] = {  {201,163,217}, {201,163,217}, {201,163,217}, {110,255,251}, {110,255,251},             {201,163,217}, {0,0,0}, {0,0,0}, {79,113,255}, {79,113,255}, {79,113,255}, {79,113,255}, {79,113,255}, {79,113,255}, {0,202,228}, {139,255,255}, {139,255,255}, {139,255,255}, {0,202,228},  },


// };

// enum combo_events {
//   BSPC,
//   BSPC_LSFT_CLEAR,
// };


const uint16_t PROGMEM bsp_combo[] = { LCTL_T(KC_T), LSFT_T(KC_R), COMBO_END};
const uint16_t PROGMEM bsp_ctrl_combo[] = { RCTL_T(KC_N), RSFT_T(KC_E), COMBO_END};
const uint16_t PROGMEM colon_combo[] = { TD(TD_SLSH_UNDRSCR), TD(TD_DOT_EXC), COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {  TD(TD_DOT_EXC),  TD(TD_X_PROG), COMBO_END};

combo_t key_combos[] = {
  COMBO(bsp_combo, KC_BSPC),
  COMBO(bsp_ctrl_combo, LCTL(KC_BSPC)),
  COMBO(colon_combo, KC_COLON),
  COMBO(semicolon_combo, KC_SEMICOLON),
};
