#ifndef POLLSERVER_H
#define POLLSERVER_H

#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>

/**
 * @brief Get the in addr object
 * 
 * @param sa generic sockaddr structure
 * @return void* Pointer to sockaddr structure
 */
void *get_in_addr(struct sockaddr *sa);

int get_listener_socket(void);

void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);

int pollserver(void);

#endif