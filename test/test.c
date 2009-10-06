
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/queue.h>
#include <ctype.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_BUF 10000

void get_name_of_protocol(int protocol)
{
/*   int buflen, s;
   struct protoent result_buf;
   struct protoent *result;
   char buf[MAX_BUF];
   char **p;

   buflen = 10;

   do {
       s = getprotobynumber_r(protocol, &result_buf,
		    buf, buflen, &result);
       if (s == ERANGE) {
	       printf("ERANGE! Retrying with larger buffer\n");

	   * Increment a byte at a time so we can see exactly
	      what size buffer was required *

	   buflen++;

	   if (buflen > MAX_BUF) {
	       printf("Exceeded buffer limit (%d)\n", MAX_BUF);
	       exit(EXIT_FAILURE);
	   }
       }
   } while (s == ERANGE);

   printf("getprotobynumber_r() returned: %s  (buflen=%d)\n",
	   (s == 0) ? "0 (success)" : (s == ENOENT) ? "ENOENT" :
	   strerror(s), buflen);

   if (s != 0 || result == NULL) {
       printf("Call failed/record not found\n");
       exit(EXIT_FAILURE);
   }

   printf("p_name=%s; p_proto=%d; aliases=",
	       result_buf.p_name, result_buf.p_proto);
   for (p = result_buf.p_aliases; *p != NULL; p++)
       printf("%s ", *p);
   printf("\n");
*/
   printf("%s\n", getprotoent()->p_name);
   printf("%s\n", getprotoent()->p_name);

   exit(EXIT_SUCCESS);
}


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

struct test_struct {
	int a;
	int b;
};

int main()
{
	static __thread struct test_struct hop = { 0, 1 } ;
	struct protoent *proto_data;

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

	printf("%s\n", gethostbyname("localhost")->h_name);

	get_name_of_protocol(0);
	
	return 0;
}

