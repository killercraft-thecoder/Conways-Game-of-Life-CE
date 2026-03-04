#ifndef FILES_H
#define FILES_H

#include <stdint.h>

void files_scan(void);              // scan VAT for CGLS?? appvars
int  files_count(void);             // number of found files
const char *files_name(int index);  // get filename by index

void files_load(int index);         // load selected file into grid
void files_save(void);              // save current grid to new CGLSXX

#endif