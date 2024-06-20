#include <stdio.h>
#include "grid.h"

int main(int argc, char *argv[]){
	int width = 640;
	int height = 480;
    char grid[NBL][NBC+1] = {
        "bwrwbw",
        "wrwbwr",
        "bwrwbw",
        "wrwbwr",
        "bwrwbw",
        "wrwbwr",
        "bwrwbw",
        "wrwbwr"
    };

	MLV_create_window( "SNAKE", "SNAKE", width, height );
	draw_grid(grid,NBL,NBC);
	
	MLV_actualise_window();

	while (MLV_get_keyboard_state( MLV_KEYBOARD_ESCAPE ) != MLV_PRESSED){
        MLV_wait_milliseconds(10);
    }
	MLV_free_window();
    return 0;
}
