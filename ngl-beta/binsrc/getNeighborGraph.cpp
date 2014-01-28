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

#include "ngl.h"
#include "common.h"
#include "timing.h"

#include <map>
using namespace ngl;

typedef void (*fn)(NGLPointSet<float> &points, IndexType **indices, int &numEdges, NGLParams<float> params);

std::map<string, fn> methods;

void listMethods() {
	fprintf(stderr,"Available methods: \n");
	for(map<string,fn>::const_iterator it = methods.begin();it!=methods.end();it++ ){
		fprintf(stderr,"\t\t%s\n", it->first.c_str());
	}
}

int main(int argc, char *argv[]) {
	// Initialize available methods
	methods["RelativeNeighbor"] = getRelativeNeighborGraph;
	methods["Gabriel"] = getGabrielGraph;
	methods["BSkeleton"] = getBSkeleton;
	methods["RelaxedRelativeNeighbor"] = getRelaxedRelativeNeighborGraph;
	methods["RelaxedGabriel"] = getRelaxedGabrielGraph;
	methods["RelaxedBSkeleton"] = getRelaxedBSkeleton;
	
	CommandLine cl;
	cl.addArgument("-i", "input", "Input points", true);
	cl.addArgument("-d", "2", "Number of dimensions", true);
	cl.addArgument("-m", "BSkeleton", "Neighborhood Method", false);
	cl.addArgument("-b", "1.0", "Beta", false);
	cl.addArgument("-k", "-1", "K max", false);
	bool hasArguments = cl.processArgs(argc, argv);
	if(!hasArguments) {
		fprintf(stderr, "Missing arguments\n");
		fprintf(stderr, "Usage:\n\n");
		cl.showUsage();
		listMethods();
		exit(1);
	}
	
	string method = cl.getArgString("-m");
	
	// Check if the method exists
	if(methods.find(method)==methods.end()) 
	{
		fprintf(stderr, "Method does not exist\n");
		listMethods();
		return 0;
	}
	
	
	const char *src = cl.getArgString("-i").c_str();
	int dims = cl.getArgInt("-d");
	float param = cl.getArgFloat("-b");
	int kmax = cl.getArgInt("-k");
	vector<float> inpoints;
	readPoints(src, inpoints, dims);

	float *pts = new float[(int) inpoints.size()];
	for(unsigned int i = 0;i<inpoints.size();i++) {
		pts[i] = inpoints[i];
	}
	
	Geometry<float>::init(dims);

  timestamp t1 = now();

	int n = (int) inpoints.size()/dims;
	if(kmax<0) kmax = n-1;

	ANNPointSet<float> P(pts, n);
	NGLParams<float> params;
	params.param1 = param;
	params.iparam0 = kmax;
	IndexType *indices;
	int numEdges;
	methods[method](P, &indices, numEdges, params);

  timestamp t2 = now();


	for(unsigned int i=0;i<numEdges;i++) {
		fprintf(stdout,"%d %d\n", indices[2*i+0],indices[2*i+1]);
	}
	
	delete pts;
  fprintf(stderr, "Ellapsed time: %f s.\n", t2-t1);

}
