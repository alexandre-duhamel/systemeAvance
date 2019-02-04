# include <stdio.h>
# include <string.h>
int main (int argc , char **argv )
{


	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,2), &WSAData);

/* Arnold Robbins in the LJ of February ’95 , describing RCS */
	if (argc > 1 && strcmp(argv[1], "-advice" ) == 0) {
		printf ( "Don ’t Panic !\n ");
	WSACleanup();
	return 42;
	}
	printf ("Need an advice ?\n");
	WSACleanup();
	return 0;
}
