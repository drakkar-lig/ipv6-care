
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/queue.h>

struct created_socket_entry {
	int socket;
	int af;
	int socktype;
	struct sockaddr sa;
	unsigned int sa_len;
	int initial_socket;
	LIST_ENTRY(created_socket_entry) entries;
};

LIST_HEAD(listhead, created_socket_entry) head;

int list_initialised = 0;

int main()
{
	struct created_socket_entry *n1, *n2, *np;
	if (list_initialised == 0)
	{
		LIST_INIT(&head);
	}

	n1 = malloc(sizeof(struct created_socket_entry));      // Insert at the head. 
	n1->socket = 1;
	LIST_INSERT_HEAD(&head, n1, entries);

	n2 = malloc(sizeof(struct created_socket_entry));      // Insert after. 
	n2->socket = 2;
	LIST_INSERT_AFTER(n1, n2, entries);

	// Forward traversal. 
	for (np = head.lh_first; np != NULL; np = np->entries.le_next)
		printf("%d\n", np->socket);

	while (head.lh_first != NULL)           // Delete. 
	{
		LIST_REMOVE(head.lh_first, entries);
	}

	//free(n1);
	printf("ok\n");
	//free(n2);
	printf("ok\n");
	
	return 0;
}

