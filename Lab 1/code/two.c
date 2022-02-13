#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h> 

int main (int argc, char* argv[]) {

    // checks if correct arguments are given
    if(2 != argc) {
        printf("\n Usage : \n");
        return 1;
    }

    printf ("\nStarting Program..\n\n");


    /* Task 1.a */

    char* filepath = argv[1];
    int returnval;

    // Check file existence
    returnval = access (filepath, F_OK);
    if (returnval == 0)
        printf ("\b%s file exists.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist.\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible.\n", filepath);
    }


    /* TASK 1.a */    

    // Check read access
    returnval = access (filepath, R_OK);
    if (returnval == 0)
        printf ("\b%s file is readable.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist. Cannot be read from.\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible.\n", filepath);
    }

    // Check write access
    returnval = access (filepath, W_OK);
    if (returnval == 0)
        printf ("\b%s file is writeable.\n", filepath);
    else {
        if (errno == ENOENT)
            printf ("%s does not exist. Cannot be written to.\n", filepath);
        else if (errno == EACCES)
            printf ("%s is not accessible.\n", filepath);
    }


    /* TASK 1.b */

    // Creates new file and opens it
    int fd;

    

    // setting a no problem error value
    errno = 0;

    // opens and creates a file if it DNE
    // Sets file to read and write mode for CURRENT owner/usr
    fd = open(argv[1], O_RDONLY|O_CREAT, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
    
    if(-1 == fd) {
        printf("\nOpen failed with error [%s]\n", strerror(errno));
        return 1;
    }
    else {

        printf("\nFile Opened Successfully.\n");


        char buffer[BUFSIZ]; // Declare an array of char called buffer that has a size of BUFSIZE (a macro constant)
        int length;
        
		while ((length = read(fd, buffer, BUFSIZ)) > 0) {	// rd is assigned the return value of read, # of characters that are read from fd
			write(1, buffer, length);						// This write to the terminal whatever the 'read' syscall reads from the file
		}
    

    }

    close(fd);
    printf("\n\n\bFile Closed Successfully.\n");

    printf ("\nEnding Program..\n\n");
    return 0;
}