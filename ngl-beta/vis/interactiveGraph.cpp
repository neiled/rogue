#include "glheaders.h"
#include "GLUT/glut.h"
#include <vector>

#include "ngl.h"

using namespace ngl;

const float PointRadius = 10.0;
int w, h;

int selected = -1;

using namespace std;
struct pt{
	float x[2];
	pt(float x0, float x1) {
		x[0] = x0;
		x[1] = x1;
	}
	float &operator[](const int i) {
		return x[i];
	}
};
std::vector<int> edges;
std::vector<pt> points;

const char *methodNames[] = {
	"Relative Neighbor",
	"Relative Neighbor-r",
	"Gabriel",
	"Gabriel-r",
	"Elliptic Gabriel",
	"Elliptic Gabriel-r",
	"Diamond",
	"Diamond-r",
	"BSkeleton",
	"BSkeleton-r"
};

int numMethods = 10;
int method = 0;
float param = .7;

void computeGraph() {
	int d = 2;
	Geometry<float>::init(2);
	edges.clear();
	int n = (int) points.size();
	if(n==0) return;
	float *pts = new float[n*d];
	for(int i = 0;i<n;i++) {
		for(int k=0;k<d;k++) {
			pts[i*d + k] = points[i][k];
		}
	}

	ANNPointSet<float> P(pts, n);
	NGLParams<float> params;
	params.param1 = param;
	params.iparam0 = n-1;
	IndexType *indices;
	int numEdges;
	if(method==0) ngl::getRelativeNeighborGraph(P, &indices, numEdges, params);
	if(method==1) ngl::getRelaxedRelativeNeighborGraph(P, &indices, numEdges, params);
	if(method==2) ngl::getGabrielGraph(P, &indices, numEdges, params);
	if(method==3) ngl::getRelaxedGabrielGraph(P, &indices, numEdges, params);
	if(method==4) ngl::getEllipticGabrielGraph(P, &indices, numEdges, params);
	if(method==5) ngl::getRelaxedEllipticGabrielGraph(P, &indices, numEdges, params);
	if(method==6) ngl::getDiamondGraph(P, &indices, numEdges, params);
	if(method==7) ngl::getRelaxedDiamondGraph(P, &indices, numEdges, params);
	if(method==8) ngl::getBSkeleton(P, &indices, numEdges, params);
	if(method==9) ngl::getRelaxedBSkeleton(P, &indices, numEdges, params);
	
	for(unsigned int i=0;i<numEdges;i++) {
		edges.push_back(indices[2*i+0]);
		edges.push_back(indices[2*i+1]);
	}
	
	delete indices;
	P.destroy();
}

inline float sqr(float x) {
	return x*x;
}

void deletePoint(int idx) {
	if(idx<0 || idx>=points.size()) return;
	points.erase(points.begin()+idx);	
}
void addPoint(float x, float y) {
	points.push_back(pt(x,y));
	computeGraph();
}

void setPosition(int idx, float x, float y) {
	if(idx<0 || idx>=points.size()) return;
	points[idx][0] = x;
	points[idx][1] = y;
	computeGraph();
}

int findPoint(float x, float y) {
	float D = PointRadius/(float) w;
	float D2 = D*D;
	for(unsigned int i=0;i<points.size();i++) {
		float d2 = sqr(x - points[i][0]) + sqr(y - points[i][1]);
		if(d2 < D2) {
			return i;
		}
	}
	return -1;
}

void resetPoints() {
	selected = -1;
	points.clear();
}

inline void text(const char *str) {
	for(int i=0;i<strlen(str);i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
	}
}

void drawHelp() {
	char text1[200];
	sprintf(text1, "Method['m','M']: %s", methodNames[method]);
	char text2[200];
	sprintf(text2, "Param['p','P']: %f", param);
	const char *text3 = "Click to add point";
	const char *text4 = "'x' to delete selected point";
	const char *text5 = "'r' to clear all points";
	
	glColor4f(0,0,0,0.95);
	glRasterPos2f(0.03, 0.95);
	text(text1);
	glRasterPos2f(0.03, 0.90);
	text(text2);
	glRasterPos2f(0.03, 0.85);
	text(text3);
	glRasterPos2f(0.03, 0.80);
	text(text4);
	glRasterPos2f(0.03, 0.75);
	text(text5);
}

void displayCall() {
	glClearColor(1,1,1,1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
	
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 100.0);
	
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	glLineWidth(3.0);
	glColor4f(0,0,0, 0.95);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(0,0);
		glVertex2f(0,1);
		glVertex2f(1,1);
		glVertex2f(1,0);
	}
	glEnd();
	
	glPointSize(PointRadius);
	glBegin(GL_POINTS);
	{
		for(unsigned int i=0;i<points.size();i++) {
			if(i==selected) {
				glColor3f(0.3,0.5,1.0);
			} else {
				glColor3f(0,0,0);
			}
			glVertex2f(points[i][0], points[i][1]);
		}
	}
	glEnd();
	glColor4f(0,0,0, 0.95);
	glBegin(GL_LINES);
	{
		for(unsigned int i=0;i<edges.size();i+=2) {
			IndexType idx1 = edges[i+0]; 
			IndexType idx2 = edges[i+1];
			glVertex2f(points[idx1][0], points[idx1][1]);
			glVertex2f(points[idx2][0], points[idx2][1]);
		}
	}
	glEnd();
	
	drawHelp();
	
  glutSwapBuffers();
} /* end func displayCall */

void toWorld(int ix, int iy, float &x, float &y) {
	x = (float) ix/(float) w;
	y = 1.0 - (float) iy/(float) h;
}

void mousemove(int ix, int iy) 
{
	float x, y;
	toWorld(ix, iy, x, y);
	if(selected>=0) {
		setPosition(selected, x, y);
		glutPostRedisplay();
	}
}

void mouse(int btn, int state, int ix, int iy)
{
	float x, y;
	toWorld(ix, iy, x, y);
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)   
	{
		int idx = findPoint(x,y);
		if(idx<0) {
			addPoint(x,y);
			selected=(int) points.size()-1;
		} else {
			selected = idx;
		}
		glutPostRedisplay();
	}
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)   
	{
		exit(1);
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch(key) {
		case 'm':
			method++;
			method=method%numMethods;
			printf("Method = %s\n", methodNames[method]);
			break;
		case 'M':
			method--;
			if(method<0) method=numMethods-1;
			method=method%numMethods;
			printf("Method = %s\n", methodNames[method]);
			break;
		case 'p':
			param+=0.01;
			printf("Param = %f\n", param);
			break;
		case 'P':
			param-=0.01;
			printf("Param = %f\n", param);
			break;
		case 'x':
			deletePoint(selected);
			break;
		case 'r':
			resetPoints();
			break;
	}
	computeGraph();
	glutPostRedisplay();
}

void resize(int wd, int ht) 
{
	w = wd;
	h = ht;
	glViewport(0,0,w,h);
}

int main(int argc, char *argv[]) {
	w = 512;
	h = 512;
	glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
  glutInitWindowSize(w, h);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("NGL Demo");
  glutDisplayFunc(displayCall);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
