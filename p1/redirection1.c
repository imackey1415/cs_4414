#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// execute the command "grep uva < scores > out"

int main(int argc, char** argv) // same as int main(int argc, char* argv[])
{
  int inFile, outFile;
  char* grep_args[] = {"grep", "uva", NULL};

  // open input and output files

  inFile = open("scores", O_RDONLY);
  outFile = open("out", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR |			
			S_IRGRP | S_IWGRP | S_IWUSR);

  // replace standard input with input file (i.e. stdin == inFile)

  dup2(inFile, 0); // fd 0 is default input device (i.e. terminal)

  // replace standard output with output file (i.e. stdout == outFile)

  dup2(outFile, 1); // fd 1 is default output device (i.e. terminal)

  // close unused file descriptors

  close(inFile);
  close(outFile);

  // execute grep

  execvp("grep", grep_args);
}
