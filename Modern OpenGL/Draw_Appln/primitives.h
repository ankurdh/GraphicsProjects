#ifndef  PRIMITIVES_H

#define PRIMITIVES_H
#include <vector>

using namespace std;

struct Point {
	float x, y, size;

	Point() {
		x = y = 0; 
	}
	Point (float xx, float yy) {
		x = xx; y = yy; 
	}

	void setPoint(float xx, float yy) {
		x = xx; y = yy;
	}
};

struct Line {
	Point v1, v2;
	float line_width;

	Line() {
		v1 = Point (0., 0.);
		v2 = Point (0., 0.);
	}
	Line(Point p1, Point p2) {
		v1 = p1; v2 = p2;
		line_width = 3.0;
	}

	Point getPoint1 () {
		return v1;
	}
	Point getPoint2 () {
		return v2;
	}

	void setPoints (Point p1, Point p2) {
		v1 = p1; v2 = p2;
	}
	int getLineWidth() {
		return line_width;
	}
	void setLineWidth(float w) {
		line_width = w;
	}
};

struct PolyLine {
		
	vector<Point> vertices;

	float line_width;

	PolyLine() {
		line_width = 3.0;
	}

	~PolyLine() {
	}

	vector<Point> getVertices() {
		return vertices;
	}
	void  setVertices(vector<Point> v) {
		vertices  = v;
	}

	float getLineWidth() {
		return line_width;
	}	
	void setLineWidth(float w) {
		line_width = w;
	}

	int getNumVertices() {
		return vertices.size(); 
	}
	int addPoint (Point p) {
		vertices.push_back(p);
	}

	void clear() {
		vertices.clear();
	}
};

struct FreeHandCurve {
		
	vector<Point> vertices;

	float line_width;

	FreeHandCurve() {
		line_width = 3.0;
	}
	~FreeHandCurve() {
	}

	vector<Point> getVertices() {
		return vertices;
	}

	void  setVertices(vector<Point> v) {
		vertices  = v;
	}

	float getLineWidth() {
		return line_width;
	}	

	void setLineWidth(float w) {
		line_width = w;
	}

	int getNumVertices() {
		return vertices.size(); 
	}
	int addPoint (Point p) {
		vertices.push_back(p);
	}
	void clear() {
		vertices.clear();
	}
};

#endif
