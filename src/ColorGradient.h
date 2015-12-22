#include <stdlib.h>
#include <vector>
#include <cmath>

#pragma once

class ColorGradient
{
private:
  struct ColorPoint  // Internal class used to store colors at different points in the gradient.
  {
    float r,g,b;      // Red, green and blue values of our color.
    float val;        // Position of our color along the gradient (between 0 and 1).
    ColorPoint(float red, float green, float blue, float value)
      : r(red), g(green), b(blue), val(value) {}
  };
  std::vector<ColorPoint> color;      // An array of color points in ascending value.
 
public:
  //-- Default constructor:
  ColorGradient()  {  createDefaultHeatMapGradient();  }
 
  //-- Inserts a new color point into its correct position:
  void addColorPoint(float red, float green, float blue, float value)
  {
    for(int i=0; i<color.size(); i++)  {
      if(value < color[i].val) {
        color.insert(color.begin()+i, ColorPoint(red,green,blue, value));
        return;  }}
    color.push_back(ColorPoint(red,green,blue, value));
  }
 
  //-- Inserts a new color point into its correct position:
  void clearGradient() { color.clear(); }
 
  //-- Places a 5 color heapmap gradient into the "color" vector:
  void createDefaultHeatMapGradient()
  {
    color.clear();
    color.push_back(ColorPoint(0, 0, 128,   -1.0f));      // deeps.
    color.push_back(ColorPoint(0, 0, 255,   -0.25f));     // shallow.
    color.push_back(ColorPoint(0, 128, 255,   0.0f));      // shore
    color.push_back(ColorPoint(240, 240, 64,   0.0625f));     // sand.
    color.push_back(ColorPoint(32, 160, 0,   0.1250f));     // grass.
    color.push_back(ColorPoint(224, 224, 0,   0.375f));     // dirt.
    color.push_back(ColorPoint(128, 128, 128,   0.75f));     // rock.
    color.push_back(ColorPoint(255, 255, 255,   1.00f));     // snow.
    
    
  }
 
  //-- Inputs a (value) between 0 and 1 and outputs the (red), (green) and (blue)
  //-- values representing that position in the gradient.
  void getColorAtValue(const float value, float &red, float &green, float &blue)
  {
    if(color.size()==0)
      return;
 
    for(int i=0; i<color.size(); i++)
    {
      ColorPoint &currC = color[i];
      if(value < currC.val)
      {
        ColorPoint &prevC  = color[ std::max(0,i-1) ];
        float valueDiff    = prevC.val - currC.val;
        float fractBetween = (valueDiff==0) ? 0 : (value - currC.val) / valueDiff;
        red   = (prevC.r - currC.r)*fractBetween + currC.r;
        green = (prevC.g - currC.g)*fractBetween + currC.g;
        blue  = (prevC.b - currC.b)*fractBetween + currC.b;
        return;
      }
    }
    red   = color.back().r;
    green = color.back().g;
    blue  = color.back().b;
    return;
  }
};
