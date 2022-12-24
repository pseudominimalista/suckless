#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include "event_handler.c"
void						/*	Just a simple event handler to catch Ctrl+C	*/
event_handler(int signum);	/*	We only need this so we can restore the 	*/
#endif						/*	terminal cursor when the program exits.		*/
