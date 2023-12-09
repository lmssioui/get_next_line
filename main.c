#include "get_next_line.h"

int main()
{
    int fd;
	 char *line;
	// char *max 

    fd = open("example", O_RDONLY);
	 /*while((line = get_next_line(fd)) != NULL)
	 		{
 			printf("%s\n",line);
	 		free (line);
	 		}*/
	printf("%s\n",get_next_line(fd));
	//printf("%ld",sizeof(char *));
//	 printf("%s\n",get_next_line(fd));
//	printf("%s\n",get_next_line(fd));
//	printf("%s\n",get_next_line(fd));
//	printf("%s\n",get_next_line(fd));
///	printf("%s\n",get_next_line(fd));
//	printf("%s\n",get_next_line(fd));
//	printf("%s\n",get_next_line(fd));
//	printf("%s\n",get_next_line(fd));
	
}
