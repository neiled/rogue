#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>

#include <vector>
using namespace std;

#include "ngl.h"
using namespace ngl;

float minx, miny, maxx, maxy;
int width, height;

inline float X(float x) 
{
	return (float) width*(x - minx)/(maxx-minx);
}

inline float Y(float y) 
{
	return (float) height*(1.0 - (y - miny)/(maxy-miny));
}

cairo_t *cr;

void line(float x0, float y0, float x1, float y1) 
{
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
  cairo_set_line_width(cr, 3.0);
	cairo_move_to(cr, X(x0), Y(y0));
	cairo_line_to(cr, X(x1), Y(y1));
	cairo_stroke(cr);
}

void lineseg(float x0, float y0, float x1, float y1)
{
	cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
  cairo_set_line_width(cr, 1.5);
	cairo_move_to(cr, X(x0), Y(y0));
	cairo_line_to(cr, X(x1), Y(y1));
	cairo_stroke(cr);
}

void pointseg(float x, float y) 
{
	cairo_move_to(cr, X(x), Y(y));
	cairo_arc (cr, X(x), Y(y), 1.5/2, 0, 2*M_PI);
	cairo_fill(cr);
}


void point(float x, float y) 
{
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_move_to(cr, X(x), Y(y));
	cairo_arc (cr, X(x), Y(y), 5.0, 0, 2*M_PI);
	cairo_fill(cr);
}

void drawQuad(float x, float y, float r, float g, float b) 
{
	cairo_set_source_rgb (cr, r, g, b);
	cairo_move_to(cr, X(x), Y(y));
	cairo_arc (cr, X(x), Y(y), 1.0, 0, 2*M_PI);
	cairo_fill(cr);
}

typedef NGLPoint<float> pointf;

void drawZeroset(float *field)
{
	double dx = 1.0/(double) width;
	double dy = 1.0/(double) height;
	for(int i = 0; i < width - 1; i++) 
	{
		for(int j = 0; j < height - 1; j++) 
		{
			double x0 = (double) i/(double) width;//*(maxx-minx) + minx;
			double y0 = (double) j/(double) height;//*(maxy-miny) + miny;
			
			int idx00 = j*width + i;
			int idx10 = j*width + i+1;
			int idx11 = (j+1)*width + i+1;
			int idx01 = (j+1)*width + i;
			
			int n = 0;
			double x[4], y[4];
			
			/*
			printf("|-----------------------------|\n");
			printf("|%.4f                     %.4f|\n", field[idx00], field[idx10]);
			printf("|                             |\n");
			printf("|%.4f                     %.4f|\n", field[idx01], field[idx11]);
			printf("|-----------------------------|\n");
			 */
			if(field[idx00]*field[idx10]<=0) 
			{
				double f0 = field[idx00];
				double f1 = field[idx10];
				if(f1-f0!=0) 
				{
					x[n] = x0 + (0 - f0)/(f1-f0)*dx;
					y[n] = y0;
					//printf("Add x0\n");
					n++;
				}
			}
			if(field[idx00]*field[idx01]<=0) 
			{
				double f0 = field[idx00];
				double f1 = field[idx01];
				if(f1-f0!=0)
				{
					x[n] = x0;
					y[n] = y0 + (0 - f0)/(f1-f0)*dy;
					//printf("Add y0\n");
					n++;
				}
			}
			if(field[idx10]*field[idx11]<=0) 
			{
				double f0 = field[idx10];
				double f1 = field[idx11];
				if(f1-f0!=0)
				{
					x[n] = x0 + dx;
					y[n] = y0 + (0 - f0)/(f1-f0)*dy;
					//printf("Add y1\n");
					n++;
				}
			}
			if(field[idx01]*field[idx11]<=0) 
			{
				double f0 = field[idx01];
				double f1 = field[idx11];
				if(f1-f0) 
				{
					x[n] = x0 + (0 - f0)/(f1-f0)*dx;
					y[n] = y0 + dy;
					//printf("Add x1\n");
					n++;
				}
			}
			if(n>=2) 
			{
				x[0] = (x[0]+0.5*dx)*(maxx-minx) + minx;
				x[1] = (x[1]+0.5*dx)*(maxx-minx) + minx;
				y[0] = (y[0]-0.5*dy)*(maxy-miny) + miny;
				y[1] = (y[1]-0.5*dy)*(maxy-miny) + miny;
				//printf("Line %f %f - %f %f\n", x[0], y[0], x[1], y[1]);

				lineseg(x[0], y[0], x[1], y[1]);
			}
			if(n>=3)
			{
				x[2] = (x[2]+0.5*dx)*(maxx-minx) + minx;
				y[2] = (y[2]-0.5*dy)*(maxy-miny) + miny;
				lineseg(x[1], y[1], x[2], y[2]);
			}
		}
	}
}

int main(int argc, char *argv[]) 
{
	string method = argc>1? string(argv[1]):"Gabriel";
	float param = argc>2? atof(argv[2]): 1.0;
	
	minx = -1.5;
	maxx = 2.5;
	miny = -2.0;
	maxy = 2.0;
	
	width = 512;
	height = 512;
	
	const char *output = "out.pdf";
  
  cairo_surface_t *surface;
  
	Geometry<float>::init(2);
	
	pointf p, q, r;
	Geometry<float>::allocate(p);
	Geometry<float>::allocate(q);
	Geometry<float>::allocate(r);
	p[0] = 0.0; p[1] = 0.0;
	q[0] = 1.0; q[1] = 0.0;
	
	EmptyRegionTest<float> *test;
	
	if(method=="Gabriel") test = new Gabriel<float>();
	if(method=="RelativeNeighbor") test = new RelativeNeighbor<float>();
	if(method=="EllipticGabriel") test = new EllipticGabriel<float>(param);
	if(method=="BSkeleton") test = new BSkeleton<float>(param);
	if(method=="Diamond") test = new Diamond<float>(param);

	test->initialize();
	EdgeInfo<float> edge;
	edge.initialize();
	edge.compute(p, q);

	EdgeInfo<float> edge2;
	edge2.initialize();
	//width = height = 100;
	
	unsigned char *data = new unsigned char[width*height*4];
	float * er = new float[width*height];
	float * umbra = new float[width*height];
	for(int i = 0; i < width; i++) 
	{
		for(int j = 0; j < height; j++) 
		{
			float x = (float) i/(float) width*(maxx-minx) + minx;
			float y = (float) j/(float) height*(maxy-miny) + miny;
			int idx = j*width + i;
			
			r[0] = x;
			r[1] = y;
			data[4*idx+0] = (unsigned char) 255;
			data[4*idx+1] = (unsigned char) 255;
			data[4*idx+2] = (unsigned char) 255;
			data[4*idx+3] = 255;
			
			
			if((er[idx] = 1.0*test->contains(edge, r))<0) 
			{
				//drawQuad(x,y,0.7,0.8,1.0);
				data[4*idx+0] = (unsigned char) 255/2 + data[4*idx+0]/2;
				data[4*idx+1] = (unsigned char) 204/2 + data[4*idx+1]/2;
				data[4*idx+2] = (unsigned char) 180/2 + data[4*idx+2]/2;
			}
			
			edge2.compute(p, r);
			
			if((umbra[idx] = 1000.0*test->contains(edge2, q))<0) 
			{
				//drawQuad(x,y,0.9,0.8,0.7);
				data[4*idx+0] = (unsigned char) 180/2 + data[4*idx+0]/2;
				data[4*idx+1] = (unsigned char) 232/2 + data[4*idx+1]/2;
				data[4*idx+2] = (unsigned char) 255/2 + data[4*idx+2]/2;
			}
		}
	}
  surface = cairo_pdf_surface_create (output, width, height);
  cr = cairo_create (surface);
	//cairo_save(cr);
	
	// CC. Oct 21 2012
	// The following works in MAC OS X, but crashes in Fedora
	/*
	cairo_surface_t *image1 = 
	cairo_image_surface_create_for_data(
																			data,
																			CAIRO_FORMAT_ARGB32,
																			width,
																			height,
																			4*width);
	
			
	cairo_rectangle(cr, 0,0,width, height);
	cairo_surface_t *image;
	
	cairo_set_source_surface (cr, image1, 0, 0);
	cairo_paint (cr);
	cairo_surface_destroy (image);
	*/

	cairo_set_source_rgb(cr, 0.6, 0.7, 0.8);
	drawZeroset(er);
	cairo_set_source_rgb(cr, 0.8, 0.75, 0.6);
	drawZeroset(umbra);
	
	line(p[0], p[1], q[0], q[1]);
	point(p[0], p[1]);
	point(q[0], q[1]);
	
	edge.destroy();
	edge2.destroy();
	Geometry<float>::deallocate(p);
	Geometry<float>::deallocate(q);
	Geometry<float>::deallocate(r);
	test->destroy();
	delete test;
	delete data;
	delete er;
	delete umbra;
	
  cairo_show_page(cr);
  cairo_destroy(cr);
  cairo_surface_flush(surface);
  cairo_surface_destroy(surface);
}