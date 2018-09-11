#ifndef MESSAGE_H
#define MESSAGE_H

void message_init();

void message_write(char * message);

int message_read(char * buffer, int size);

#endif
