#include "net.h"
#include "../shared_var.h"
#include <time.h>
#include <sys/time.h>

char ordre[999999];

int try_connect(char *ip, char *port) // Connecter
{
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);
	//specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(port));
	server_address.sin_addr.s_addr = inet_addr(ip);
	if (connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == 0)
		return network_socket;
	return -1;
}

void rec_ground_size(int socket)
{
	char ground_string[20];
	recv(socket, ground_string, 20, 0);
	sscanf (ground_string, "%d %d", &max_x, &max_y);
	building_id = calloc(max_x*max_y, sizeof(int));
	for (int i = 0; i < max_x*max_y;i++)
		building_id[i] = -1;
}

void rec_ground_string(int socket)
{
	recv(socket, ground_buffer, 2, 0);
	uint16_t nb_to_res;
	memcpy(&nb_to_res, ground_buffer, sizeof(nb_to_res));
	nb_to_res = ntohs(nb_to_res);
	int res = 0;
	while (res < nb_to_res)
		res += recv(socket, ground_buffer+res+2, nb_to_res - res, 0);
}

void recv_order(int socket)
{
	char skin[4]; int id;
	int res = 0;
	while  (res < 10)
		res += recv(socket, recv_order_string + res, 10- res, 0);
	if (recv_order_string[0] == '0')
		return;
	res = 0;
	int nb_to_res  = atoi(recv_order_string);
	if (recv_order_string_size<nb_to_res)
	{
		recv_order_string = realloc(recv_order_string, nb_to_res+3);
		recv_order_string_size = nb_to_res + 3;
	}
		while (res < nb_to_res)
		{
			int w = recv(socket, recv_order_string+res, nb_to_res - res, 0);
			res += w;
		}
		res = 0;

	while (res < nb_to_res)
	{
		//printf ("(((%.300s)))\n",recv_order_string + res);
		sscanf(recv_order_string + res	, "%s %d", skin, &id);
		if (skin[0] == '1')
		{
			struct building *yalist = get_building_from_id(id);
			if (yalist != NULL)
			{
				remove_building_altitude(yalist);
				res += parse_building(yalist, &recv_order_string[res]);
				actualise_stat_building(yalist);
				actualise_building_altitude(yalist);
			}
			else
			{
				res += append_building(&recv_order_string[res]);
			}
		}
		else
		{
			struct personnages *yalist = get_ptr_from_id(id);
			if (yalist != NULL)
			{
				free_linked_enemie(yalist->e_list);
				if (yalist == moi)
				{
					struct building *oldinside = find_building_by_id(moi->inside);
					res += parse_order(yalist, &recv_order_string[res]);
					struct building *newinside = find_building_by_id(moi->inside);
					if (newinside != NULL)
						actualise_stat_building(newinside);
					if (oldinside != NULL)
						actualise_stat_building(oldinside);
				}
				else
				{
					res += parse_order(yalist, &recv_order_string[res]);
				}

				actualise_stat(yalist);	
			}
			else
				res += append_perso(&recv_order_string[res]);
		}
	}
}


void send_orders(int socket)
{
	char tmp[20] =  {0};
	int size_ordre = strlen(ordre);
	if (size_ordre > 0)
	{
		strcat(tmp, "ordre");
		sprintf (tmp + 5, "%d", size_ordre);
		//printf ("[[[%s]]]\n\n\n", ordre);
		send(socket, ordre, size_ordre, MSG_NOSIGNAL);
	}
	ordre[0] = 0;
}
