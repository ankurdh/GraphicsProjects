/**
Copyright 2007, All Rights Reserved: Zachary Wartell, University of North Carolina at Charlotte
\file Main.cpp
\author Zachary Wartell
\brief Main.cpp file
*/
#include <iostream>
#include <assert.h>
#include <Math2D/Matrix3x3.h>

using namespace std;
using namespace ITCS4120;


void test()
    {    
    /** ITCS4120: Once you get all methods implemented replace 0 with 1 to compile the test function
    */
   #if 1     
    Vector2 v1,v2,v3;
    Point2 p1,p2,p3;
    Matrix3x3 m1, m2, m3;

    v1 [0] = 1.0f; v1 [1] = 5.0f;
    v2 [0] = 6.0f; v2 [1] = 10.0f;
    v3 = v1 + v2;
    assert (v3 == Vector2(7.0,15.0));
    v3 = v1 - v2;
    assert (v3 == Vector2(-5.0,-5.0));
    assert(v1.length() == 5.0990195135927848300282241090228f);

    v3 += v3;
    assert (v3 == Vector2(-10.0,-10.0));
    v3 *= 5.0;
    assert (v3 == Vector2(-50.0,-50.0));

    m1.assign(5,6,4,
	1,2,3,
	3,5,9);
    m2=m1.inverse();
    m3.assign(3/11,-34/11,10/11,
	0,33/11,-11/11,
	-1/11,-7/11,4/11);
    m1.assignInverse(m2);
    assert(m1 == (m2.inverse()));
    m1.assign(3/11,0,-1/11,
	-34/11,33/11,-7/11,
	10/11,-11/11,4/11);
    assert(m1 == (m3.transpose()));

    m1.assign(5,6,4,
	1,2,3,
	3,5,9);
    m2.assign(2,6,1,
	      9,6,5,
	      3,4,5);
    m3.assign(76,82,55,
	      29,30,26,
	      78,84,73);
    m1.postMultiply(m2);
    assert(m1==m3);
    
    m1.assign(5,6,4,
	1,2,3,
	3,5,9);
    m2.assign(2,6,1,
	      9,6,5,
	      3,4,5);
    m3.assign(19,29,35,
	      66,91,99,
	      34,51,69);
    m1.preMultiply(m2);
    assert(m1==m3);

    cout << "Test passed!\n";
   #endif
    }

void testPointClass()
    {

    Vector2 v1,v2,v3;
    // test the point class functions here. 
    Point2 p1(1.0f, 2.0f);
    //test the overloaded [] operators
    assert (1.0f == p1[0]);

    p1[1] = 3.0f;
    assert (3.0f == p1[1]);

    Point2 p2(1.0f, 3.0f), p3(1.0f, 2.0f), p4(4.0f, 3.0f), p5(4.0f, 5.0f);
    //check overloaded == and != operators
    assert(p1 == p2);
    assert(p1 != p3);
    assert(p1 != p4);
    assert(p1 != p5);

    //test the overloaded += and -= methods
    v1 [0] = 1.0f; v1 [1] = 5.0f;
    v2 [0] = 6.0f; v2 [1] = 10.0f;
    p1[0] = 1.0f, p1[1] = 1.0f;
    p2[0] = 1.0f, p2[1] = 1.0f;

    //first for the point class methods.
    p1 += v1;
    p2 -= v2;

    assert(p1[0] == 2.0f);
    assert(p1[1] == 6.0f);
    assert(p2[0] == -5.0f);
    assert(p2[1] == -9.0f);

    //test the assignCombination and combine methods
    p1[0] = 2.0f, p1[1] = 2.0f;
    p2[0] = 2.0f, p2[1] = 2.0f;
    p3[0] = 0.0f, p3[1] = 0.0f;

    p3.assignCombination(p1, p2, 0.5f);
    assert(p3 == Point2(2.0f,2.0f));

    p3[0] = 0.0f, p3[1] = 0.0f;

    p3 = Point2::combine(p1, p2, 0.5);
    assert(p3 == Point2(2.0f,2.0f));

    //Point class friend functions.
    p2[0] = 1.0f, p2[1] =1.0f;
    v1 = p3 - p2;
    assert(v1 == Vector2(1.0f, 1.0f));

    p1 = p3 - v1;
    assert(p1 == Point2(1.0f,1.0f));

    p1 = p3 + v1;
    assert(p1 == Point2(3.0f, 3.0f));

    Matrix3x3 m(2.0f, 0.0f, 0.0f, 
	0.0f, 2.0f, 0.0f, 
	0.0f, 0.0f, 1.0f);

    p2 = m * p1;
    assert(p2 == Point2(6.0f, 6.0f));

    }

void testVectorClass()
    {
    //test the overloaded [] operator
    Vector2 v1, v2, v3;

    v1[0] = 1.0f;
    assert(v1[0] == 1.0f);

    v1[1] = 1.0f;
    assert(v1 == Vector2(1.0f, 1.0f)); //this would also test the overloaded == operator

    v2[0] = 1.0f, v2[1] = 2.0f;
    v3[0] = 2.0f, v3[1] = 2.0f;

    assert(v1 != v3);

    v1 [0] = 1.0f; v1 [1] = 5.0f;

    //test the normalize function
    v1.normalize();
    assert(v1 == Vector2(1.0f/5.0990195135927848300282241090228f, 5.0f/5.0990195135927848300282241090228f));

    //test the normal function
    v1 [0] = 1.0f; v1 [1] = 5.0f;
    v2 = v1.normal();
    assert(v2 == Vector2(v1[0]/5.0990195135927848300282241090228f, v1[1]/5.0990195135927848300282241090228f));

    //test the *= operator
    v1 *= 2.0f;
    assert(v1 == Vector2(2.0f, 10.0f));

    //test the - operator
    Point2 p1(1.0f, 1.0f), p2(2.0f, 2.0f);
    v1 = p2 - p1;
    assert(v1 == Vector2(1.0f, 1.0f));

    //test the - operator
    v1 [0] = 2.0f; v1 [1] = 10.0f;
    p2 = p1 - v1;
    assert(p2 == Point2(-1.0f, -9.0f));

    //test the + operator
    p2 = p1 + v1;
    assert(p2 == Point2(3.0f, 11.0f));

    Matrix3x3 m(2.0f, 0.0f, 0.0f, 
	0.0f, 2.0f, 0.0f, 
	0.0f, 0.0f, 1.0f);

    //test the overloaded * operator
    v2 = m * v1;
    assert(v2 == Vector2(4.0f, 20.0f));

    }

void testMatrixClass()
    {
    Matrix3x3 m, p;
    //test assignIdentity, assignInverse
    m.assignIdentity();
    p.assign(1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 1.0f);
    assert(m == p);

    //test the copy constructor
    m.assignIdentity();

    Matrix3x3 n(m);

    assert(m == n);

    //test the overloaded [] operator
    m[0][1] = 5.0f;
    m[0][2] = 6.3f;

    n.assign(1.0f, 5.0f, 6.3f, 
	0.0f, 1.0f, 0.0f, 
	0.0f, 0.0f, 1.0f);

    assert(m == n);

    n.assign(1.0f, 5.0f, 6.3f, 
	0.0f, 1.0f, 8.0f, 
	0.0f, 0.0f, 5.0f);

    assert(n[1][2] == 8.0f);
    assert(n[2][2] == 5.0f);

    //test the assign method that takes another matrix as parameter
    m.assign(n);
    Matrix3x3 o(1.0f, 5.0f, 6.3f, 
	0.0f, 1.0f, 8.0f, 
	0.0f, 0.0f, 5.0f);
    assert(m == o);

    //test assignTranslate, assignRotate, assignScale
    m.assignIdentity();
    m.assignTranslate(2.0f, 3.0f);
    n.assign(1.0f, 0.0f, 2.0f,
	0.0f, 1.0f, 3.0f, 
	0.0f, 0.0f, 1.0f);

    assert(m == n);

    m.assignIdentity();
    m.assignRotate(45);
    n.assign(1/sqrt((float)2.0), -1/sqrt((float)2.0), 0.0f,
	1/sqrt((float)2.0), 1/sqrt((float)2.0), 0.0f, 
	0.0f, 0.0f, 1.0f);

    assert(m == n);

    m.assignIdentity();
    m.assignScale(2.0f, 4.0f);
    n.assign(2.0f, 0.0f, 0.0f, 
	0.0f, 4.0f, 0.0f, 
	0.0f, 0.0f, 1.0f);

    assert(m == n);

    //test assignInverse overloads
    n.assign(0.5f, 0.0f, 0.0f, 
	0.0f, 0.25f, 0.0f, 
	0.0f, 0.0f, 1.0f);

    m.assignInverse();
    assert(m == n);

    m.assignInverse(n);
    n.assignScale(2.0f, 4.0f);
    assert(m == n);

    //test operator !=
    m.assignIdentity();
    assert(m != n);

    //test det()
    m.assign(2.0f, -2.0f, 0.0f, 
	-1.0f, 5.0f, 1.0f, 
	3.0f, 4.0f, 5.0f);

    assert(26 == m.det());

    //test the static det() for 2x2 matrix
    assert(10 == Matrix3x3::det(6, 2, 1, 2));

    //\todo test preTranslate, preRotate and preScale
    m.assign(1.0f, 2.0f, 3.0f,
	1.0f, 2.0f, 3.0f, 
	1.0f, 2.0f, 3.0f);

    m.preTranslate(2.0f, 2.0f);
    n.assign(3.0f, 6.0f, 9.0f, 
	3.0f, 6.0f, 9.0f, 
	1.0f, 2.0f, 3.0f);
    
    assert(m == n);

    m.assign(1.0f, 2.0f, 3.0f,
	1.0f, 2.0f, 3.0f, 
	1.0f, 2.0f, 3.0f);
    m.preScale(2.0f, 2.0f);
    n.assign(2.0f, 4.0f, 6.0f,
	2.0f, 4.0f, 6.0f,
	1.0f, 2.0f, 3.0f);
    
    assert(m == n);

    m.assign(1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 
	0.0f, 0.0f, 1.0f);
    m.preRotate(45);
    n.assign(1/sqrt((float)2), -1/sqrt((float)2), 0,
	1/sqrt((float)2), 1/sqrt((float)2), sqrt((float)2),
	0.0f, 0.0f, 1.0f);
    assert(m == n);

    p.assign(1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 3.0f, 
	3.0f, 1.0f, 2.0f);
    m.assign(0.0f, 1.0f, 0.0f, 
	1.0f, 1.0f, 1.0f, 
	2.0f, 1.0f, 2.0f);
    m.preMultiply(p);
    p.assign(2.0f, 2.0f, 2.0f, 
	6.0f, 4.0f, 6.0f, 
	5.0f, 6.0f, 5.0f);
    assert(p == m);

    //test postTranslate, postRotate and postScale
    p.assign(0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 
	2.0f, 1.0f, 2.0f);
    m.assign(1.0f, 0.0f, 1.0f, 
	0.0f, 1.0f, 1.0f, 
	0.0f, 0.0f, 1.0f);
    m.postMultiply(p);
    p.assign(2.0f, 2.0f, 2.0f, 
	3.0f, 2.0f, 3.0f, 
	2.0f, 1.0f, 2.0f);
    assert(m == p);

    m.assign(1.0f, 0.0f, 1.0f, 
	0.0f, 1.0f, 1.0f, 
	0.0f, 0.0f, 1.0f);
    m.postRotate(45);
    p.assign(1/sqrt((float)2), -1/sqrt((float)2), 1.0f,
	1/sqrt((float)2), 1/sqrt((float)2), 1.0f,
	0.0f, 0.0f, 1.0f);
    assert(m == p);

    m.assign(1.0f, 2.0f, 1.0f, 
	1.0f, 1.0f, 1.0f, 
	1.0f, 1.0f, 2.0f);
    m.postScale(2.0f, 2.0f);
    p.assign(2.0f, 4.0f, 1.0f, 
	2.0f, 2.0f, 1.0f, 
	2.0f, 2.0f, 2.0f);
    assert(m == p);

    m.assign(1.0f, 2.0f, 1.0f, 
	1.0f, 1.0f, 1.0f, 
	1.0f, 1.0f, 2.0f);
    m.postTranslate(2.0f, 2.0f);
    p.assign(1.0f, 2.0f, 7.0f, 
	1.0f, 1.0f, 5.0f, 
	1.0f, 1.0f, 6.0f);
    assert(m == p);

    }

/**
\brief 'main' is the standard C/C++ main function where execution starts
*/
int main (int argc, char** argv)
    {    
    //additional test methods.
    testPointClass();
    testVectorClass();
    testMatrixClass();
    
    test();
    return 0;
    }
