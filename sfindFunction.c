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

int searchdir(char*,char*,char);


// filter out files/dir based on the type user puts and/or substring.
int whichType( char* filename,char* findme, char type)
{

    char* p;
    struct stat mystat;
    lstat(filename,&mystat);
    char buffer[PATH_MAX];
    // fprintf(stdout,"%s \n",filename);
    switch(type) {
	//checks for regular files
    case 'f':
	if (S_ISREG(mystat.st_mode))
	{
	    if (findme == NULL)
	    {
		p = realpath(filename, buffer);
		fprintf(stdout,"%s\n",p);
	    }
	    else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	    {
		p = realpath(filename, buffer);
		fprintf(stdout,"%s\n",p);
	    }
	} // if
	break;
	//checks for character files
    case 'c':
	if (S_ISCHR(mystat.st_mode))
	{
	     if (findme == NULL)
	    {
		p = realpath(filename, buffer);
		if (p != NULL )
		    fprintf(stdout,"%s\n",p);
		else
		{
		    p = realpath(".",buffer);
		    strcat(p,"/");
		    strcat(p,filename);
		    fprintf(stdout,"%s\n",p);
		}

	    }
	    else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	    {
		p = realpath(filename, buffer);
		if (p != NULL )
		    fprintf(stdout,"%s\n",p);
		else
		{
		    p = realpath(".",buffer);
		    strcat(p,"/");
		    strcat(p,filename);
		    fprintf(stdout,"%s\n",p);
		}
	    }
	}
	break;
	// checks for pipes
    case 'p':
	if (S_ISFIFO(mystat.st_mode))
	{
	    if (findme == NULL)
	    {
		p = realpath(filename, buffer);
		fprintf(stdout,"%s\n",p);
	    }
	    else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	    {
		p = realpath(filename, buffer);
		fprintf(stdout,"%s\n",p);
	    }
	}
	break;
	// checks for directories
    case 'd':
	if (S_ISDIR(mystat.st_mode))
	{
	    if (findme == NULL)
	    {
		p = realpath(filename, buffer);
		fprintf(stdout,"%s\n",p);

	    }
	    else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	    {
		p = realpath(filename, buffer);
		fprintf(stdout,"%s\n",p);
	    }
	}
	break;
	// checks for symbolic links
    case 'l':
	if (S_ISLNK(mystat.st_mode))
	{
	    if (findme == NULL)
	    {
		p = realpath(".",buffer);
		strcat(p,"/");
		strcat(p,filename);
		fprintf(stdout,"%s\n",p);

	    }
	    else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	    {
		p = realpath(".",buffer);
		strcat(p,"/");
		strcat(p,filename);
		fprintf(stdout,"%s\n",p);
	    }

	}
	break;
	// checks for sockets
    case 's':
	if (S_ISSOCK(mystat.st_mode))
	{
	    // checks to see if there is substring there to be checked
	    if (findme == NULL)
	    {
		p = realpath(filename, buffer);
		if (p != NULL )
		    fprintf(stdout,"%s\n",p);
		else
		{
		    p = realpath(".",buffer);
		    strcat(p,"/");
		    strcat(p,filename);
		    fprintf(stdout,"%s\n",p);
		}
	    }
	    // compares the substring and the filename
	    else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	    {
		p = realpath(filename, buffer);
		if (p != NULL )
		    fprintf(stdout,"%s\n",p);
		else
		{
		    p = realpath(".",buffer);
		    strcat(p,"/");
		    strcat(p,filename);
		    fprintf(stdout,"%s\n",p);
		}
	    }
	}
	break;
	//prints every type of files
    case 'x':
	if (findme == NULL)
	{
	    p = realpath(filename, buffer);
	    if (p != NULL )
		fprintf(stdout,"%s\n",p);
	    else
	    {
		p = realpath(".",buffer);
		strcat(p,"/");
		strcat(p,filename);
		fprintf(stdout,"%s\n",p);
	    }
	}
	else if (strstr(filename, findme) != NULL || strcmp(findme,"/0") == 0 )
	{
	    p = realpath(filename, buffer);
	    if (p != NULL )
		fprintf(stdout,"%s\n",p);
	    else
	    {

		p = realpath(".",buffer);
		strcat(p,"/");
		strcat(p,filename);
		fprintf(stdout,"%s\n",p);

	    }
	}
	break;
    default:
	fprintf(stderr,"Invalid Command\n");
	exit(0);
	break;

    }
    if (S_ISDIR(mystat.st_mode))
    {
	if (mystat.st_uid == 1610601687 ) {
	    if ((mystat.st_mode & (S_IRUSR)) != 0 )
	    {
		searchdir(filename,findme,type);
		chdir("..");
	    }

	}  else
	{
	// checks if the current file is directory or not if true go into the directory
	    if ((mystat.st_mode & (S_IROTH)) != 0 )
	    {

		searchdir(filename,findme,type);
		chdir("..");
	    }
	}

    }
      return 0;
}

// opens the directory and checks for everyfile in the directory
int searchdir(char* dirname,char* findme, char type) {

    DIR *dp;
    struct dirent *dir;
    struct stat mystat;
    chdir(dirname);
    char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd));
    // opens the directory
    if( (dp = opendir(cwd)) == NULL )
    {
	fprintf(stderr, "Cannot open dir\n" );
	exit( 0 );
    }

    /* read entries */
    while( (dir = readdir( dp )) != NULL )
    {
	if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
	    whichType(dir->d_name,findme,type);

	}
    } // while
    closedir( dp );
    return 0;

}
