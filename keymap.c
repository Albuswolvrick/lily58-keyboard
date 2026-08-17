#include QMK_KEYBOARD_H


char     wpm_str[10];

enum layer_number {
  _STANDARD = 0,
  _GAMING,
  _FN,
  _SYMBOL,
};

// --- Unicode input for German umlauts / euro sign ---------------------
// These no longer depend on the OS keyboard layout (RALT combos) at all.
// QMK sends the actual Unicode codepoint via each OS's own Unicode input
// method, and we pick the right method automatically based on detected OS.
#ifdef UNICODEMAP_ENABLE
enum unicode_names {
    UNI_AE_LOWER,
    UNI_OE_LOWER,
    UNI_UE_LOWER,
    UNI_AE_UPPER,
    UNI_OE_UPPER,
    UNI_UE_UPPER,
    UNI_SZ,
    UNI_EUR,
};

const uint32_t PROGMEM unicode_map[] = {
    [UNI_AE_LOWER] = 0x00E4, // ä
    [UNI_OE_LOWER] = 0x00F6, // ö
    [UNI_UE_LOWER] = 0x00FC, // ü
    [UNI_AE_UPPER] = 0x00C4, // Ä
    [UNI_OE_UPPER] = 0x00D6, // Ö
    [UNI_UE_UPPER] = 0x00DC, // Ü
    [UNI_SZ]       = 0x00DF, // ß
    [UNI_EUR]      = 0x20AC, // €
};
#endif


// Keycode definitions
// Keycode definitions
#define UML_AE UM(UNI_AE_LOWER)
#define UML_OE UM(UNI_OE_LOWER)
#define UML_UE UM(UNI_UE_LOWER)
#define UML_AE_SHIFT UM(UNI_AE_UPPER)
#define UML_OE_SHIFT UM(UNI_OE_UPPER)
#define UML_UE_SHIFT UM(UNI_UE_UPPER)
#define GER_SZ UM(UNI_SZ)
#define EU_EUR UM(UNI_EUR)
#define COPY LCTL(KC_C)
#define PASTE LCTL(KC_V)
#define CUT LCTL(KC_X)
#define UNDO LCTL(KC_Z)

// Tap Dance declarations
enum {
    TD_C,
    TD_V,
    TD_X,
    TD_Z,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_C] = ACTION_TAP_DANCE_DOUBLE(KC_C, COPY),
    [TD_V] = ACTION_TAP_DANCE_DOUBLE(KC_V, PASTE),
    [TD_X] = ACTION_TAP_DANCE_DOUBLE(KC_X, CUT),
    [TD_Z] = ACTION_TAP_DANCE_DOUBLE(KC_Z, UNDO),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_STANDARD] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,         KC_4,         KC_5,                                   KC_6, KC_7,        KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,         KC_R,         KC_T,                                   TD(TD_Z), KC_U,        KC_I,    KC_O,    KC_P,    KC_EQL,
  KC_LCTL,  KC_A,   LCTL_T(KC_S),    LGUI_T(KC_D),    LALT_T(KC_F), KC_G,                        KC_H, RALT_T(KC_J),  RGUI_T(KC_K),    RCTL_T(KC_L),    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Y , TD(TD_X),    TD(TD_C), TD(TD_V), KC_B,  KC_DEL,         KC_BSPC,  KC_N, KC_M,        KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                  KC_ESC, MS_WHLU, MO(_FN), KC_SPC,  LAG_T(KC_ENT),  MO(_SYMBOL), MS_WHLD, KC_PSCR
 ),

 [_GAMING] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,         KC_4,         KC_5,                        KC_6, KC_7,        KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,         KC_R,         KC_T,                        KC_Z, KC_U,        KC_I,    KC_O,    KC_P,    KC_EQL,
  KC_LCTL,  KC_A,   KC_S,    KC_D,         KC_F,         KC_G,                        KC_H, KC_J,        KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Y,   KC_X,    KC_C,         KC_V,         KC_B,  MO(_FN),    KC_BSPC,  KC_N, KC_M,        KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                     KC_LCTL, KC_LGUI, KC_LALT,  KC_SPC,    KC_ENT,  KC_LCTL, KC_LGUI, KC_LALT
 ),

 [_SYMBOL] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX,    XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_QUOTE, KC_LABK, KC_RABK, KC_DQUO, KC_DOT,                   KC_AMPR,  KC_LBRC,   KC_RBRC, KC_PERC, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL, KC_HASH,                    KC_PIPE,  KC_LPRN,   KC_RPRN, KC_QUES,  KC_COLN, XXXXXXX,
  XXXXXXX, KC_CIRC, KC_SLSH, KC_ASTR, KC_BSLS, XXXXXXX, _______, _______, KC_TILD,  KC_LCBR, KC_RCBR, KC_AT,  KC_DLR, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),

 [_FN] = LAYOUT(
  XXXXXXX, DF(_STANDARD),   DF(_GAMING), XXXXXXX, UG_TOGG, UG_HUEU,                   KC_KB_VOLUME_DOWN,           KC_KB_VOLUME_UP,         KC_MPRV, KC_MPLY,    KC_MNXT, XXXXXXX,
  XXXXXXX,  XXXXXXX,    XXXXXXX,   EU_EUR, XXXXXXX, XXXXXXX,                  XXXXXXX,           UML_UE,      XXXXXXX, UML_OE, XXXXXXX, XXXXXXX,
  _______, UML_AE, GER_SZ,   XXXXXXX, XXXXXXX, XXXXXXX,                   KC_LEFT,           KC_DOWN,         KC_UP,   KC_RIGHT,   XXXXXXX, XXXXXXX,
  KC_F1,   KC_F2,      KC_F3,      KC_F4,   KC_F5,   KC_F6, _______, _______, KC_F7,             KC_F8,           KC_F9,   KC_F10,     KC_F11,  KC_F12,
                                 _______, _______, _______, _______, _______, _______, _______, _______
  )
};

// Automatically pick the correct Unicode input method for whichever OS
// this half is currently plugged into. Requires OS_DETECTION_ENABLE = yes
// in rules.mk. UC_WINC uses WinCompose on Windows (install WinCompose and
// this just works, no registry edits needed).
#if defined(UNICODEMAP_ENABLE) && defined(OS_DETECTION_ENABLE)
void keyboard_post_init_user(void) {
    switch (detected_host_os()) {
        case OS_LINUX:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
        case OS_WINDOWS:
            set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            break;
        case OS_MACOS:
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        default:
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
    }
}
#endif


//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) return OLED_ROTATION_270;
    return OLED_ROTATION_180;
}
// When you add source files to SRC in rules.mk, you can use functions.
const char *read_logo(void);
// >>> NEW: fish animation for the slave-side OLED ------------------------
#define FISH_BODY_RX 8
#define FISH_BODY_RY 5
#define FISH_TAIL_LEN 6

// dir: +1 = swimming right (facing right), -1 = swimming left (facing left)
static void draw_fish(uint8_t cx, uint8_t cy, int8_t tail_wag, int8_t dir) {
    // Body: filled ellipse
    for (int8_t dy = -FISH_BODY_RY; dy <= FISH_BODY_RY; dy++) {
        for (int8_t dx = -FISH_BODY_RX; dx <= FISH_BODY_RX; dx++) {
            int32_t val = (int32_t)dx * dx * FISH_BODY_RY * FISH_BODY_RY +
                          (int32_t)dy * dy * FISH_BODY_RX * FISH_BODY_RX;
            int32_t limit = (int32_t)FISH_BODY_RX * FISH_BODY_RX * FISH_BODY_RY * FISH_BODY_RY;
            if (val <= limit) {
                oled_write_pixel((uint8_t)(cx + dx), (uint8_t)(cy + dy), true);
            }
        }
    }

    // Eye: a dark dot near the front of the body (front = facing direction)
    oled_write_pixel((uint8_t)(cx + dir * (FISH_BODY_RX - 3)), (uint8_t)(cy - 2), false);

    // Tail: triangle behind the body (opposite the facing direction), wagging up/down
    for (int8_t i = 0; i < FISH_TAIL_LEN; i++) {
        int8_t spread = i / 2;
        uint8_t tx = (uint8_t)(cx - dir * (FISH_BODY_RX + i));
        oled_write_pixel(tx, (uint8_t)(cy + tail_wag), true);
        oled_write_pixel(tx, (uint8_t)(cy + tail_wag - spread), true);
        oled_write_pixel(tx, (uint8_t)(cy + tail_wag + spread), true);
    }
}

static void animate_fish(void) {
    static uint16_t fish_timer = 0;
    static uint8_t  fish_x     = 20;
    static int8_t   fish_dir   = 1;
    static bool     tail_up    = false;

    if (timer_elapsed(fish_timer) > 150) {
        fish_timer = timer_read();
        fish_x += fish_dir;
        if (fish_x >= 118) fish_dir = -1;
        if (fish_x <= 10)  fish_dir = 1;
        tail_up = !tail_up;
    }

    oled_clear();
    draw_fish(fish_x, 16, tail_up ? -2 : 2, fish_dir);
}
//newe end

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    // WPM
    oled_write_ln_P(PSTR("WPM"), false);
    sprintf(wpm_str, "%03d", get_current_wpm());
    oled_write_ln(wpm_str, false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR(""), false);
    // Base state
    oled_write_ln_P(PSTR("Base"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _GAMING:
            oled_write_P(PSTR("Game\n"), false);
            break;
        case _STANDARD:
            oled_write_P(PSTR("Std\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR(""), false);
    // Layer state
    oled_write_ln_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _SYMBOL:
            oled_write_P(PSTR("Sym\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("-"), false);
    }
} else {
    animate_fish();
  }
    return false;
}
#endif // OLED_ENABLE
