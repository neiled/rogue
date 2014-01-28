#ifndef COMMONH
#define COMMONH

#include <fstream>
#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;


class Edge {
public:
  unsigned int src, dst;
	float w;
  Edge():src(-1),dst(-1) {}
  Edge(int a, int b, float wt = 1.0):src(a),dst(b),w(wt) {}
  bool operator()(const Edge &a, const Edge &b)  const {
    return (a.src==b.src)? a.dst<b.dst:a.src<b.src;
  }
};


class CommandLine {
	vector<string> argnames;
  map<string, string> args;
	map<string, string> descriptions;
	vector<string> requiredArgs;
 public:
  CommandLine() {
	}
	void addArgument(string cmd, string defaultValue, string description="", bool required = false) {
		argnames.push_back(cmd);
		if(description!="") descriptions[cmd] = description;
		if(required && find(requiredArgs.begin(), requiredArgs.end(), cmd)==requiredArgs.end()) {
			requiredArgs.push_back(cmd);
		}
		setArgument(cmd, defaultValue);
	}
	void setArgument(string cmd, string value) {
		args[cmd] = value;
	}
	
	bool processArgs(int argc, char *argv[]) {
		int numRequired = 0;
		map<string, int> check;
		for(unsigned int k = 0;k<requiredArgs.size();k++) {
			check[requiredArgs[k]] = 0;
		}
		for(int i=1;i<argc;i+=2) {
			if(i+1<argc) {
				string arg = string(argv[i]);
				string val = string(argv[i+1]);
				setArgument(arg, val);
				if(check.find(arg)!=check.end()) {
					check[arg] = check[arg] + 1;
				}
			}
		}
		bool complete = true;
		for(map<string,int>::const_iterator it = check.begin(); it!=check.end();it++) {
			int n = it->second;
			if(n==0) return false;
		}
		return true;
	}
	void showUsage() {
		for(unsigned int k = 0; k<argnames.size();k++) {
			fprintf(stderr, "\t%s\t\t%s (%s)\n", argnames[k].c_str(), descriptions[argnames[k]].c_str(), args[argnames[k]].c_str());
		}
	}
	float getArgFloat(string arg) {
		string val = args[arg];
		return atof(val.c_str());
	}
														 
  int getArgInt(string arg) {
		string val = args[arg];
		return atoi(val.c_str());
	}
  string getArgString(string arg) {
		string val = args[arg];
		return val;
	}

};

void readPoints(const char *src, vector<float> &readPts, int dims) {
	ifstream inp(src);
  if(!inp.is_open()) {
    fprintf(stderr,"Cannot open file %s\n", src);
    throw runtime_error("Cannot open file");
  }
  string line;
  while(!inp.eof()) {
    getline(inp,line);
    if(line.length()==0) continue;
    const char *sline = line.c_str();
    char *tok = strtok((char*) sline, " \t\r\n");
    if(tok && tok[0]=='#') continue;
    int ndims = 0;
    while(tok && ndims<dims) {
      readPts.push_back(atof(tok));
      tok = strtok(NULL, " \t\r\n");
      ndims++;
    }
    if(ndims<dims) {
      fprintf(stderr, "Error reading input file: num.dims=%d, expecting %d\n", ndims, dims);
      throw runtime_error("Error reading input file");
    }
  }
  inp.close();
}


#endif
