#include "main.h"

int main(void) {
    init_window_start();
    
    app_event_loop();
    
    deinit_window_start();
}

