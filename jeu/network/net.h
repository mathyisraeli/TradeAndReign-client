#pragma once
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "../perso.h"
#include "parseur.h"
#include <stdlib.h>
#include <string.h>

void recv_order(int socket);
void send_orders(int socket);
int try_connect(char *ip, char *port);
void rec_ground_size(int socket);
void rec_ground_string(int socket);

extern char ordre[999999];
