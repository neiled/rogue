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

	
	// Write input for qdelaunay
	FILE *fp = fopen("temp.qhull", "w");
	fprintf(fp, "%d\n", dims);
	fprintf(fp, "%d\n", numPts);
	
	for(unsigned int i=0;i<numPts;i++) {
		for(int d = 0;d<dims;d++) {
			fprintf(fp, "%g ", inpoints[dims*i+d]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);	

	timestamp t1 = now();
	char cmd[1024];
	sprintf(cmd, "%s/qdelaunay Qt i TO temp.out < temp.qhull", QDELAUNAY_PATH);
	system(cmd);
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
