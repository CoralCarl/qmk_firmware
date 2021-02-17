#include QMK_KEYBOARD_H

enum unicode_names {
  OE_L,
  OE_U,
  UE_L,
  UE_U,
  AE_L,
  AE_U,
  SZ,
  EUR
};

const uint32_t PROGMEM unicode_map[] = {
  [OE_L] = 0x00F6, // ö
  [OE_U] = 0x00D6, // Ö
  [UE_L] = 0x00FC, // ü
  [UE_U] = 0x00DC, // Ü
  [AE_L] = 0x00E4, // ä
  [AE_U] = 0x00C4, // Ä
  [SZ]  = 0x00DF, // ß
  [EUR] = 0x20AC, // €
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_tkl_ansi(
      KC_ESC,  KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,                      KC_PSCR, KC_SLCK, KC_PAUS,
      KC_GRV,  KC_1,   KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC,            KC_INS,  KC_HOME, KC_PGUP,
      KC_TAB,  KC_Q,   KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC, KC_BSLS,            KC_DEL,  KC_END,  KC_PGDN,
      KC_CAPS, KC_A,   KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,   KC_L,   KC_SCLN,KC_QUOT,          KC_ENT,
      KC_LSFT, KC_Z,   KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,KC_DOT, KC_SLSH,                  KC_RSFT,                     KC_UP,
      KC_LCTL, KC_LGUI,KC_LALT,                     KC_SPC,                      KC_RALT, KC_RGUI, MO(1),  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT   ),
  [1] = LAYOUT_tkl_ansi(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
      UC_MOD, KC_TRNS, KC_TRNS, X(EUR),  KC_TRNS, KC_TRNS, KC_TRNS, XP(UE_L,UE_U), KC_TRNS, XP(OE_L, OE_U), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, XP(AE_L,AE_U), X(SZ), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_VOLD, KC_MUTE,                   KC_TRNS,           KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS,                          KC_MPLY,                              KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS   )
};

uint16_t rsft_timer = 0;
bool rsft_interrupted = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_RSFT:
            if (record->event.pressed) { //keydown
                //start timer
                rsft_timer = timer_read();
                rsft_interrupted = false;
            }
            else { //keyup
                if (!rsft_interrupted && timer_elapsed(rsft_timer) < 200){
                    set_oneshot_layer(1, ONESHOT_START);
                    clear_oneshot_layer_state(ONESHOT_PRESSED);//switch into layer
                }
            }
            break;
        default:
            rsft_interrupted = true;
            break;
    }
    return true;
}
