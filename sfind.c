#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#include "sfindFunction.h"

//global
char* dirname = NULL;
char type = 'x';
char* findMe = NULL;

// parse command line arguments
void getArguments(int argc,char** argv)
{
    int ch;
    while ((ch = getopt(argc,argv,":s:n:t:"))!= -1 )
    {
	switch (ch)
	{
	case 's':
	    dirname = optarg;
	    break;
	case 'n':
	    findMe = optarg;
	    break;
	case 't':
	    if ((strlen(optarg)) >1)
	    {
		errno = EINVAL;
		perror("Type arguement is too long, must be single character \n");
		exit(0);
	    }
	    type = optarg[0];
	    break;
	case '?':
	default:
	    fprintf(stderr,"Invaild argument \n");
	    exit(0);
	    break;
	} // switch
    } // while
} // getArguemt

int main( int argc, char* argv[] )
{
    struct stat mystat;
// checks if the user had input more than 2 arguments
    if (argc > 2)
    {
	// calls the parsing method
	getArguments(argc,argv);
	DIR* dir = opendir(dirname);
	if (ENOENT == errno) {
	    fprintf(stderr,"%s does not exist\n",dirname);
	    exit(0);
	}
	// checks the input dir permissions
	lstat(dirname,&mystat);
	if ((mystat.st_mode & S_IRUSR) == 0) {
	    fprintf(stderr,"Cannot access directory or file \n");
	    exit(0);
	}
	// calls the filter mechanism
	whichType(dirname,findMe,type);
    } else {
	fprintf(stderr,"Invalid Command\n");
	exit(0);
    }

    return 1;
}
