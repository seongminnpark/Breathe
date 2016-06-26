#include "start_screen.h"

// Layout elements.
Window *window_start;
TextLayer *text_layer_duration; // Exercize duration.
TextLayer *text_layer_start;    // Start exersize.
TextLayer *text_layer_interval; // Reminder interval.

// Window creation functions.
void load_window_start(Window *window);
void unload_window_start(Window *window);

// Layout setup functions.
void init_text_layers(void);
void deinit_text_layers(void);

// Button configuration functions.
static void select_click_handler(ClickRecognizerRef recognizer, void *context);
static void click_configuration_provider(void *context);


void init_window_start() {
    window_start = window_create();
    window_set_window_handlers(window_start, (WindowHandlers) {
        .load = load_window_start,
        .unload = unload_window_start,
    });
    
    window_set_click_config_provider(window_start, click_configuration_provider);
    
    // Show window
    window_stack_push(window_start, true);
}

void deinit_window_start() {
    window_destroy(window_start);
} 

void load_window_start(Window *window) {
    // Add layout elements.
    init_text_layers();
}

void unload_window_start(Window *window) {
    // Destroy layout elements.
    deinit_text_layers();
}

static void click_configuration_provider(void *context) {
    ButtonId select_button_id = BUTTON_ID_SELECT;
    window_single_click_subscribe(select_button_id, select_click_handler);
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    
}

void init_text_layers() {
    text_layer_duration = text_layer_create(GRect(50,30,180,30)); 
    text_layer_start = text_layer_create(GRect(110,80,180,30));
    text_layer_interval = text_layer_create(GRect(50,130,180,30));
    
    char *string_duration_val = malloc(BUF_SIZE_TIME_VAL * sizeof(char));
    char *string_duration = malloc(BUF_SIZE_DURATION * sizeof(char));
    char *string_interval_val = malloc(BUF_SIZE_TIME_VAL * sizeof(char));
    char *string_interval = malloc(BUF_SIZE_INTERVAL * sizeof(char));
    snprintf(string_duration_val, BUF_SIZE_TIME_VAL, "%d min", 1);
    snprintf(string_duration, BUF_SIZE_DURATION, TEXT_DURATION, string_duration_val);
    snprintf(string_interval_val, BUF_SIZE_TIME_VAL, "%d hour", 1);
    snprintf(string_interval, BUF_SIZE_INTERVAL, TEXT_INTERVAL, string_interval_val);
    text_layer_set_text(text_layer_duration, string_duration);
    text_layer_set_text(text_layer_start, TEXT_START);
    text_layer_set_text(text_layer_interval, string_interval);
    free(string_duration_val);
    free(string_interval_val);
    
    layer_add_child(window_get_root_layer(window_start), text_layer_get_layer(text_layer_duration));
    layer_add_child(window_get_root_layer(window_start), text_layer_get_layer(text_layer_start));
    layer_add_child(window_get_root_layer(window_start), text_layer_get_layer(text_layer_interval));
}

void deinit_text_layers() {
    
    free((void *)text_layer_get_text(text_layer_duration));
    free((void *)text_layer_get_text(text_layer_interval));
    
    text_layer_destroy(text_layer_duration);
    text_layer_destroy(text_layer_start);
    text_layer_destroy(text_layer_interval);
}
