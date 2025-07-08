#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "process_file.h"
#include "types.h"

#define PORT "31337" // Port the server will listen on
#define STARTING_CLIENTS 5
#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

int parse_net_header(char *buf, net_header_t *hdr_out)
{
    if(!buf || !hdr_out)
    {
        return -1;
    }

    memcpy(&hdr_out->hdr_len, buf, 4);
    hdr_out->hdr_len = ntohl(hdr_out->hdr_len);

    memcpy(&hdr_out->fname_len, buf + 4, 4);
    hdr_out->fname_len = ntohl(hdr_out->fname_len);

    uint64_t net_pkt_len;
    memcpy(&net_pkt_len, buf + 8, 8);
    hdr_out->pkt_len = be64toh(net_pkt_len);

    memcpy(hdr_out->filename, buf + 16, NET_NAME_FIELD_SZ);
    hdr_out->filename[NET_NAME_FIELD_SZ] = '\0'; // Ensure null termination

    return 0;
}

// Get sockaddr, IPv4 or IPv6
void *get_in_addr(struct sockaddr *sa)
{
    // Get IPv4 sockaddr
    if(sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    // Otherwise get IPv6 sockaddr
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Get a listening socket
int get_listener_socket(void)
{
    int listener; // Listening socket descriptor
    int yes = 1; // For setsockopt() SO_REUSEADDR
    int rv;

    struct addrinfo hints, *ai, *p;

    // Get a socket and bind it
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
    {
        fprintf(stderr, "[-] pollserver: %s\n", gai_strerror(rv));
        exit(1);
    }

    for(p = ai; p != NULL; p = p->ai_next){
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        
        // On error, -1 is returned
        if(listener < 0)
        {
            continue;
        }

        // Set option to keep socket open
        struct timeval timeout = {5, 0};
        setsockopt(listener, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        //setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        // 
        if(bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue;
        }
        
        break;
    }

    // If we arrive here, a bind did not occur
    if(p == NULL)
    {
        fprintf(stderr, "[-] bind() failed.\n");
        return -1;
    }

    // Free the addrinfo
    freeaddrinfo(ai);

    // Listen
    if(listen(listener, MAX_CLIENTS) == -1)
    {
        fprintf(stderr, "[-] listen() failed.\n");
        return -1;
    }

    return listener;
}

// Add a new file descriptor to pfds
void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    // If there isn't enough room, add more space to pfds array
    if(*fd_count == *fd_size)
    {
        // Double fd_size
        *fd_size *= 2; 
        // Realloc space accordingly
        *pfds = realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }

    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN;
    (*pfds)[*fd_count].revents = 0;

    // Increment fd_count
    (*fd_count)++;
}

// Remove an index from pfds
void del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over the one at index i
    pfds[i] = pfds[*fd_count - 1];

    // Decrement fd_count
    (*fd_count)--;
}

int pollserver(void)
{
    // Listening socket descriptor
    int listener;

    // Newly accepted socket descriptor
    int newfd; 

    // Client address
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen;
    
    // Start with room for 5 connections, and later
    // realloc if necessary
    int fd_count = 0;
    int fd_size = STARTING_CLIENTS;
    // Allocate space for poll file descriptors array
    struct pollfd *pfds = malloc(sizeof *pfds * fd_size);

    // Validate malloc
    if(pfds == NULL)
    {
        fprintf(stderr, "[-] Malloc failed.\n");
    }

    // Buffer for client data
    char buf[BUFFER_SIZE];

    // Buffer for client address
    char remoteIP[INET6_ADDRSTRLEN];

    // Set up and get a listening socket
    listener = get_listener_socket();

    // Validate listener
    if(listener == -1)
    {
        fprintf(stderr, "[-] Error getting listening socket.\n");
        exit(1);
    }
    printf("[+] Pollserver listening on port %s\n", PORT);

    // Add the listener to poll file descriptors (pfds)
    pfds[0].fd = listener;
    // Signify there is data ready to read
    pfds[0].events = POLLIN;

    // Set fd_count to 1 for the listener
    fd_count = 1;

    // Main loop
    for(;;)
    {
        // Set timeout = -1 to block until an event occurs
        int poll_count = poll(pfds, fd_count, -1);

        if(poll_count == -1)
        {
            fprintf(stderr, "[-] poll error,\n");
            exit(1);
        }

        // Run through existing connectings looking for data to read
        for(int i = 0; i < fd_count; i++)
        {
            // Check if any fd is ready for reading
            if(pfds[i].revents & (POLLIN | POLLHUP))
            {
                if(pfds[i].fd == listener)
                {
                    // If listener is ready, handle new connection
                    addrlen = sizeof(remoteaddr);
                    newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

                    if(newfd == -1)
                    {
                        fprintf(stderr, "[-] accept error.\n");
                    }
                    else
                    {
                        add_to_pfds(&pfds, newfd, &fd_count, &fd_size);

                        printf("pollserver: new connection from %s on socket %d\n",
                            inet_ntop(remoteaddr.ss_family,
                            get_in_addr((struct sockaddr*)&remoteaddr), 
                            remoteIP, INET6_ADDRSTRLEN), newfd);
                    }
                }
                else
                {
                    // If not the listener, it is a regular client
                    memset(buf, 0, sizeof(buf));
                    // Read in data; header first

                    
                    char hdr_buf[NET_HDR_SZ];
                    int header_bytes = recv(pfds[i].fd, hdr_buf, NET_HDR_SZ, 0);
                    if (header_bytes != NET_HDR_SZ) {
                        fprintf(stderr, "[-] Incomplete header received\n");
                        close(pfds[i].fd);
                        del_from_pfds(pfds, i, &fd_count);
                        continue;
                    }
                    
                    // Try parsing the header
                    net_header_t net_hdr;
                    if (parse_net_header(hdr_buf, &net_hdr) < 0) {
                        fprintf(stderr, "[-] Failed to parse header\n");
                        close(pfds[i].fd);
                        del_from_pfds(pfds, i, &fd_count);
                        continue;
                    }

                    int sender_fd = pfds[i].fd;

                    // Validate the header received
                    if (net_hdr.hdr_len != NET_HDR_SZ || 
                        net_hdr.fname_len > NET_NAME_FIELD_SZ ||
                        net_hdr.pkt_len < NET_HDR_SZ)
                    {
                        fprintf(stderr, "[-] Invalid NET header.\n");
                        printf("header len: %d\n", net_hdr.hdr_len);
                        printf("fname len: %d\n", net_hdr.fname_len);
                        printf("pkt len: %ld\n", net_hdr.pkt_len);

                        net_header_t invalid_hdr_rsp;
                        memset(&invalid_hdr_rsp, 0, sizeof(invalid_hdr_rsp));

                        invalid_hdr_rsp.hdr_len = htonl(NET_HDR_SZ);
                        invalid_hdr_rsp.fname_len = htonl(0);
                        invalid_hdr_rsp.pkt_len = htobe64(NET_HDR_SZ);

                        send(sender_fd, &invalid_hdr_rsp, sizeof(invalid_hdr_rsp), 0);
                        close(sender_fd);
                        continue;
                    }

                    uint64_t payload_size = net_hdr.pkt_len - NET_HDR_SZ;
                    char *data_buf = malloc(payload_size);
                    if (!data_buf) {
                        fprintf(stderr, "[-] Memory allocation failed\n");
                        continue;
                    }

                    size_t total = 0;
                    while (total < payload_size) {
                        int r = recv(pfds[i].fd, data_buf + total, payload_size - total, 0);
                        if (r <= 0) {
                            fprintf(stderr, "[-] Error reading payload data\n");
                            break;
                        }
                        total += r;
                        printf("total = %ld\n", total);
                    }

                    if(total <= 0)
                    {
                        // Got error or closed connection
                        if(total == 0)
                        {
                            // Connection was closed
                            printf("pollserver: socket %d hung up\n", sender_fd);
                        }
                        else
                        {
                            fprintf(stderr, "[-] recv error.\n");
                        }

                        // Close the connection
                        close(pfds[i].fd);

                        // Remove file descriptor from pfds
                        del_from_pfds(pfds, i, &fd_count);

                        // Reconsider the slot that was just removed
                        i--;
                    }

                    // process the data
                    uint8_t *response_buf = NULL;
                    size_t response_size = 0;
                
                    if (process_buffer((uint8_t*) data_buf, payload_size, &response_buf, &response_size) != 0)
                    {
                        fprintf(stderr, "[-] Error processing buffer.\n");
                        close(pfds[i].fd);
                        return 1;
                    }

                    // end the reply

                    // Rebuild header
                    char reply_hdr[NET_HDR_SZ];
                    uint32_t hdr_len = htonl(NET_HDR_SZ);
                    uint32_t fname_len = htonl(net_hdr.fname_len);
                    uint64_t pkt_len = htobe64(NET_HDR_SZ + payload_size);

                    memcpy(reply_hdr, &hdr_len, 4);
                    memcpy(reply_hdr + 4, &fname_len, 4);
                    memcpy(reply_hdr + 8, &pkt_len, 8);
                    memcpy(reply_hdr + 16, net_hdr.filename, NET_NAME_FIELD_SZ);

                    // Send header + data
                    send(pfds[i].fd, reply_hdr, NET_HDR_SZ, 0);
                    send(pfds[i].fd, response_buf, response_size, 0);


                    free(data_buf);
                    close(pfds[i].fd);
                    del_from_pfds(pfds, i, &fd_count);
                    i--; // Adjust loop

                } // handle data from client
            } // got ready-to-read from poll()
        } // looping through file descriptors
    } // main loop

    return 0;
}