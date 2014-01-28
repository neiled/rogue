/***********************************************************************
 * Software License Agreement (BSD License)
 *
 * Copyright 2012  Carlos D. Correa (info@ngraph.org) All rights reserved.
 *
 * THE BSD LICENSE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *************************************************************************/

#include "common.h"
#include "timing.h"
#include <assert.h>

#include <stdlib.h>
#include <unistd.h>

#include <vector>
using namespace std;

#include "timing.h"

int main(int argc, char *argv[]) {
	CommandLine cl;
	cl.addArgument("-i", "input", "Input points", true);
	cl.addArgument("-d", "2", "Number of dimensions", true);
	bool hasArguments = cl.processArgs(argc, argv);
	if(!hasArguments) {
		fprintf(stderr, "Missing arguments\n");
		fprintf(stderr, "Usage:\n\n");
		cl.showUsage();
		exit(1);
	}

  const char *src = cl.getArgString("-i").c_str();
  int dims = cl.getArgInt("-d");
	
	vector<float> inpoints;
	readPoints(src, inpoints, dims);
  int numPts = (int) inpoints.size()/dims;

	int in[2], out[2];
	
	int	commpipe[2];
	if (pipe(in) < 0) fprintf(stderr,"error pipe in");
  if (pipe(out) < 0) fprintf(stderr, "error pipe out");
	
	/* Attempt to fork and check for errors */
	pid_t pid;
	int rv;
	/*
	if( (pid=fork()) == -1){
		fprintf(stderr,"Fork error. Exiting.\n");  
		exit(1);        
	}
	*/
	
	/*
	int     fd[2], nbytes;
	pid_t   childpid;
	char    string[] = "Hello, world!\n";
	char    readbuffer[80];
	
	pipe(fd);
	
	if((childpid = fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	
	if(childpid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		//dup(fd[0]);
		
		//nbytes = read(STDIN_FILENO, readbuffer, sizeof(readbuffer));
		//printf("Received string: [%s]\n", readbuffer);
		int ret=execl("/Users/cdcorrea/Research/ngl/qhull/build/qdelaunay", "qdelaunay", "Qt", "i", "TO", "temp.out", (char*)NULL);//, "Qt", "i");//, "<temp.qhull", ">temp.out");
	}
	else
	{
		close(fd[0]);
		dup2(STDOUT_FILENO,fd[1]);
		
		//fprintf(stdout,"Hello there");
		const char *str = "2\n4\n1 1\n1 0\n0 0 \n0 1\n";
		write(fd[1], str, (strlen(str)+1));
		wait(&rv);
	}
	
	return 0;
*/

	/*
	if(pid==0) {
    close(0);
    close(1);
    close(2);
		//dup2(in[0], STDIN_FILENO);	
    dup2(in[0],STDIN_FILENO);
    dup2(out[1],1);
    dup2(out[1],2);
		close(in[1]);
    close(out[0]);
		
		fprintf(stderr,"Child\n");
		
		
		const char *path = QDELAUNAY_PATH;
		
		//	int ret=execl(path, "qdelaunay", "Qt", "i", "<temp.qhull", ">temp.out");
		int ret=execl("/Users/cdcorrea/Research/ngl/qhull/build/qdelaunay", "qdelaunay", "Qt", "i", "TO", "temp.out", (char*)NULL);//, "Qt", "i");//, "<temp.qhull", ">temp.out");
		//int ret = -1;
		if(ret == -1) {
			fprintf(stderr, "Error: exec failed (%d)\n", ret);
			//return 0;
		}
	}
	 */
	
	// Write input for qdelaunay
	fprintf(stderr,"output\n");
	FILE *fp = fopen("temp.qhull", "w");
	fprintf(fp, "%d\n", dims);
	fprintf(fp, "%d\n", numPts);
	
	for(unsigned int i=0;i<numPts;i++) {
		for(int d = 0;d<dims;d++) {
			fprintf(fp, "%g ", inpoints[dims*i+d]);
			write(in[1], "2", 1);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);	

	timestamp t1 = now();
	system("../qhull/build/qdelaunay Qt i TO temp.out < temp.qhull");
	timestamp t2 = now();
	fprintf(stderr,"Ellapsed %f\n", t2-t1);
	 
	
	// Read output of qdelaunay
	FILE *fpin = fopen("temp.out","r");
	int numTris;
	fscanf(fpin,"%d", &numTris);
	
	bool **edges = new bool*[numPts];
	for(int i=0;i<numPts;i++) {
		edges[i] = new bool[numPts];
		for(int j=0;j<numPts;j++) {
			edges[i][j] = false;
		}
	}
	
	// Output each edge from qdelaunay output
	int D = dims;
	for(int i=0;i<numTris;i++) {
		int simplex[D+1];
		for(int d=0;d<D+1;d++) {
			fscanf(fpin,"%d", &(simplex[d]));
		}
		for(int d=0;d<D+1;d++) {
			for(int d2=d+1;d2<D+1;d2++) {
				int i1 = simplex[d];
				int i2 = simplex[d2];
				if(!edges[i1][i2] && !edges[i2][i1]) {
					edges[i1][i2] = true;
					edges[i2][i1] = true;
					fprintf(stdout, "%d %d\n", i1, i2);
				}
			}
		}
	}
	fclose(fpin);
	delete[] edges;
}
