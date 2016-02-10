#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// This program runs the command "cat < redirect.c | wc > out"

int main(int argc, char** argv) // same as int main(int argc, char* argv[])
{
  	int inFile, outFile, pipefd[2]; // file descriptors
  	char* cat_args[] = {"cat", NULL}; // arguments for cat command
  	char* wc_args[] = {"wc", NULL}; // arguments for wc command
  	int status, i;
  	pid_t first, second; // process ids

  	// open the input file

  	inFile = open("redirect.c", O_RDONLY);

  	if (inFile < 0)
  	{
      	fprintf(stderr, "Error opening input file\n");
      	exit(1);
  	}

  	// open the output file

  	outFile = open("out", O_CREAT | O_WRONLY);

  	if (outFile < 0)
  	{
      	fprintf(stderr, "Error opening output file\n");
      	exit(1);
  	}





  	// create the pipe

  	if (pipe(pipefd) != 0)
  	{
      	fprintf(stderr, "Error creating pipe.\n");
      	exit(1);
  	}

  	// spawn the processes

  	first = fork();
  
  	if (first == 0)
  	{
      	// the child gets here

      	dup2(inFile, 0); // replace stdin with the input file
      	dup2(pipefd[1], 1); // replace stdout with output part of pipe
      	close(pipefd[0]); // don't need other end of the pipe

      	execvp("cat", cat_args);

      	fprintf(stderr, "execvp for cat failed");
      	exit(1);
  	}
  	else if (first > 0)
  	{
      	// the parent gets here

      	second = fork();

      	if (second == 0)
	{
	 // the second child gets here

	 dup2(pipefd[0], 0); // replace stdin with input part of pipe
	 dup2(outFile, 1); // replace stdout with the output file
	 close(pipefd[1]); // don't need other end of the pipe

	 execvp("wc", wc_args);
	  
	 fprintf(stderr, "execvp for wc failed");
	 exit(1);
	}
     	else if (second > 0)
	{
	 // the parent gets here

	 close(inFile);
	 close(outFile);
	 close(pipefd[0]);
	 close(pipefd[1]);
	  
	 for (i = 0; i < 2; i++)
	 {
	      			wait(&status);
	  	}

	  	printf("All done\n");
	}
     	 else
	{
	  	fprintf(stderr, "Could not fork second child\n");
	  	wait(&status);
	  	exit(1);
	}
  		}
  	else
  	{
      	fprintf(stderr, "Could not fork first child\n");
      	exit(1);
  	}
}
