/*
 * File: SierpinskiTriangle.cpp
 * ----------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the Sierpinski Triangle problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
using namespace std;

/* Functions */
void sierpinskiTriangle(int edge, int order, GPoint & top, GWindow & gw);

/* Main program */

int main() {
   GWindow gw(600, 500);
   // [TODO: Fill in the necessary code here]
   int edge, order;
   double xCenter = gw.getWidth() / 2;
   double yCenter = gw.getHeight() / 2;
   while(true) {
       cout << "Enter edge length: ";
       cin >> edge;
       cout << "Enter fractal order: ";
       cin >> order;
       if(edge < 0 || order < 0) break;
       gw.clear();
       GPoint top(xCenter, yCenter - (sqrt(3.0) * edge / 4));
       sierpinskiTriangle(edge, order, top, gw);
   }
   return 0;
}

/*
 * Function: sierpinskiTriangle
 * Usage: sierpinskiTriangle(edge, order, top, gw);
 * -----------------------------------------------
 * draw sierpinskiTriangle recursively
 */

void sierpinskiTriangle(int edge, int order, GPoint &top, GWindow &gw) {
    GPoint left = gw.drawPolarLine(top, edge, 240);
    GPoint right = gw.drawPolarLine(left, edge, 0);
    gw.drawPolarLine(right, edge, 120);
    if(order > 0) {
        order--;
        edge /= 2;
        if(edge > 0) {
            sierpinskiTriangle(edge, order, top, gw);
            double leftX = (left.getX() + top.getX()) / 2;
            double leftY = (left.getY() + top.getY()) / 2;
            GPoint lTop(leftX, leftY);
            sierpinskiTriangle(edge, order, lTop, gw);
            double rightX = (right.getX() + top.getX()) / 2;
            double rightY = (right.getY() + top.getY()) / 2;
            GPoint rTop(rightX, rightY);
            sierpinskiTriangle(edge, order, rTop, gw);
        }
    }
}
