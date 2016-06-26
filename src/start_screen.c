#include "start_screen.h"

// Global values.
int duration;
int interval;

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
static void click_configuration_provider(void *context);
static void duration_click_handler(ClickRecognizerRef recognizer, void *context);
static void start_click_handler(ClickRecognizerRef recognizer, void *context);
static void interval_click_handler(ClickRecognizerRef recognizer, void *context);

// Text layer control functions.
void update_duration_text();
void update_interval_text();


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
    // Set initial variables.
    duration = 1;
    interval = 4;
    
    // Add layout elements.
    init_text_layers();
}

void unload_window_start(Window *window) {
    // Destroy layout elements.
    deinit_text_layers();
}

static void click_configuration_provider(void *context) {
    ButtonId duration_button_id = BUTTON_ID_UP;
    ButtonId start_button_id = BUTTON_ID_SELECT;
    ButtonId interval_button_id = BUTTON_ID_DOWN;
    
    window_single_click_subscribe(duration_button_id, duration_click_handler);
    window_single_click_subscribe(start_button_id, start_click_handler);
    window_single_click_subscribe(interval_button_id, interval_click_handler);
}

static void duration_click_handler(ClickRecognizerRef recognizer, void *context) {
    duration = (duration == 5) ? 1 : duration + 1;
    update_duration_text();
}

static void start_click_handler(ClickRecognizerRef recognizer, void *context) {
 
}

static void interval_click_handler(ClickRecognizerRef recognizer, void *context) {
    interval = (interval == 12) ? 1 : interval + 1;
    update_interval_text();
}

void init_text_layers() {
    text_layer_duration = text_layer_create(GRect(50,30,180,30)); 
    text_layer_start = text_layer_create(GRect(110,80,180,30));
    text_layer_interval = text_layer_create(GRect(50,130,180,30));
    
    update_duration_text();
    text_layer_set_text(text_layer_start, TEXT_START);
    update_interval_text();
    
    layer_add_child(window_get_root_layer(window_start), text_layer_get_layer(text_layer_duration));
    layer_add_child(window_get_root_layer(window_start), text_layer_get_layer(text_layer_start));
    layer_add_child(window_get_root_layer(window_start), text_layer_get_layer(text_layer_interval));
}

void update_duration_text() {
    char *min_text = (duration == 1) ? "%d min" : "%d mins";
    char *string_duration_val = malloc(BUF_SIZE_TIME_VAL * sizeof(char));
    char *string_duration = malloc(BUF_SIZE_DURATION * sizeof(char));  
    
    snprintf(string_duration_val, BUF_SIZE_TIME_VAL, min_text, duration);
    snprintf(string_duration, BUF_SIZE_DURATION, TEXT_DURATION, string_duration_val);
    
    text_layer_set_text(text_layer_duration, string_duration);
    
    free(string_duration_val);
}

void update_interval_text() {
    char *hour_text = (interval == 1) ? "%d hour" : "%d hours";
    char *string_interval_val = malloc(BUF_SIZE_TIME_VAL * sizeof(char));
    char *string_interval = malloc(BUF_SIZE_INTERVAL * sizeof(char));
    
    snprintf(string_interval_val, BUF_SIZE_TIME_VAL, hour_text, interval);
    snprintf(string_interval, BUF_SIZE_INTERVAL, TEXT_INTERVAL, string_interval_val);
    
    text_layer_set_text(text_layer_interval, string_interval);
    
    free(string_interval_val);
}

void deinit_text_layers() {
    
    free((void *)text_layer_get_text(text_layer_duration));
    free((void *)text_layer_get_text(text_layer_interval));
    
    text_layer_destroy(text_layer_duration);
    text_layer_destroy(text_layer_start);
    text_layer_destroy(text_layer_interval);
}
