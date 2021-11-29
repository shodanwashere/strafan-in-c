#include <stdio.h>

/**
 * A small little header file I wrote for
 * managing and showing loading bars.
 * Very useful for visualizing complex tasks.
 * 
 * @author nunoDias fc56330
 */

typedef struct{
    int total_perc;
    int curr_status;
} LOADBAR;

/**
 * Takes a LOADBAR struct and initializes it.
 * @param lb - Reference to the loadbar structure
 * @param total - The value that should be == 100% 
 */
void initialize(LOADBAR* lb, int total){
    lb->total_perc = total;
    lb->curr_status = 0;
}

/**
 * Updates the current status
 * @param lb - Reference to the loadbar structure
 * @param new_status - Status update
 */
void update_curr_status(LOADBAR* lb, int new_status){
    lb->curr_status = new_status;
}

/**
 * Gets the current percentage of the loading bar 
 * @param lb - Reference to the loadbar structure
 * @return float 
 */
float get_perc(LOADBAR* lb){
    return ((float)lb->curr_status/(float)lb->total_perc) * 100;
}

/**
 * Shows an instant of the loading bar on screen and
 * returns the carriage. This makes it perfect for constant
 * updates without having to fill the whole terminal with lines.
 * @param lb - Reference to the loadbar structure
 */
void show_loadbar(LOADBAR* lb){
    printf("|");
    for(int i = 1; i <= 10; i++){
        if(i < (get_perc(lb) / 10))
            printf("=");
        else
            printf(" ");
    }
    printf("| %f%%\r", get_perc(lb));
}