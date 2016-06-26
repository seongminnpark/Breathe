#include <pebble.h>

#define TEXT_DURATION "Duration: %s"
#define TEXT_START "Start!"
#define TEXT_INTERVAL "Interval: %s"

#define BUF_SIZE_TIME_VAL 10
#define BUF_SIZE_DURATION 30
#define BUF_SIZE_START    10
#define BUF_SIZE_INTERVAL 30

// Window creation functions.
void init_window_start();
void deinit_window_start();

