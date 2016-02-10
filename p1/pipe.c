#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// execute the command "cat scores | grep uva"

int main(int argc, char** argv) // same as int main(int argc, char* argv[])
{
  	int pipefd[2];
  	int pid;

  	char* cat_args[] = {"cat", "scores", NULL};
  	char* grep_args[] = {"grep", "uva", NULL};

  	// make a pipe (fds go in pipefd[0] and pipefd[1])

 	pipe(pipefd); 	// create a pipe 
				// a unidirectional data channel used for IPC

  	pid = fork();

  	if (pid == 0)
 	{
    	// child gets here and handles "grep uva"
     	// replace standard input with input part of pipe

     	dup2(pipefd[0], 0); // read (i.e. default input device 0) from pipe

     	// close unused half of pipe (i.e. write)

     	close(pipefd[1]);

     	// execute grep

     	execvp("grep", grep_args);
  	}
  

	else
  	{
     	// parent gets here and handles "cat scores"
     	// replace standard output with output part of pipe

     	dup2(pipefd[1], 1); // write (i.e. default output device 1) to pipe

     	// close unused input half of pipe (i.e. read)

     	close(pipefd[0]);

     	// execute cat

     	execvp("cat", cat_args);
  	}
}
