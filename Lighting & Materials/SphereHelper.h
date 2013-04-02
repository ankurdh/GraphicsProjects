#pragma once
#include <GL/glut.h>

//Define constants for display list IDS
static const GLuint FRONT_FACE_DISPLAY_LIST_ID = 1;
static const GLuint RIGHT_FACE_DISPLAY_LIST_ID  = 2;
static const GLuint BACK_FACE_DISPLAY_LIST_ID = 3 ;
static const GLuint BOTTOM_FACE_DISPLAY_LIST_ID = 4;
static const GLuint LEFT_FACE_DISPLAY_LIST_ID = 5;
static const GLuint TOP_FACE_DISPLAY_LIST_ID = 6;

static const GLuint LEFT_FACE_EMISSION_SPHERES_DL_ID = 7;
static const GLuint LEFT_FACE_EMISSION_REACTIVE_SPHERES_DL_ID = 8;

static const GLuint TOP_FACE_ROW_1_DL_ID = 9;
static const GLuint TOP_FACE_ROW_2_DL_ID = 10;
static const GLuint TOP_FACE_ROW_3_DL_ID = 11;
static const GLuint TOP_FACE_ROW_4_DL_ID = 12;

static bool tempFlag = true;

//increasing intensities of specific colors
static GLfloat varyingMaterialProperties[16][4] = {
	    {0.20f, 0.f, 0.f, 1.0f},
	    {0.3f, 0.f, 0.f, 1.0f},
	    {0.6f, 0.f, 0.f, 1.0f},
	    {1.0f, 0.f, 0.f, 1.0f},

	    {0.20f, 0.20f, 0.f, 1.0f},
	    {0.3f, 0.30f, 0.f, 1.0f},
	    {0.5f, 0.50f, 0.f, 1.0f},
	    {1.0f, 1.0f, 0.f, 1.0f},

	    {0.f, 0.10f, 0.20f, 1.0f},
	    {0.f, 0.3f, 0.3f, 1.0f},
	    {0.f, 0.6f, 0.6f, 1.0f},
	    {0.f, 1.0f, 1.0f, 1.0f},

	    {0.20f, 0.0f, 0.20f, 1.0f},
	    {0.30f, 0.0f, 0.30f, 1.0f},
	    {0.60f, 0.0f, 0.60f, 1.0f},
	    {1.0f, 0.0f, 1.0f, 1.0f}
	    };

static GLfloat zeroReflection[] = {0.0f, 0.0f, 0.0f, 1.0f};

class SphereHelper
    {
    private:
	static void renderFrontFaceSpheres();
	static void renderRightFaceSpheres();
	static void renderBackFaceSpheres();
	static void renderBottomFaceSpheres();
	static void renderLeftFaceSpheres();
	static void renderTopFaceSpheres();
	
	static void createFrontFaceDisplayList();
	static void createRightFaceDisplayList();
	static void createBackFaceDisplayList();
	static void createBottomFaceDisplayList();
	static void createLeftFaceDisplayList();
	static void createTopFaceDisplayList();
	static void createLeftFaceEmissiveSpheresDL();
	static void createLeftFaceEmissionReactiveSpheresDL();
	static void createTopFaceRow1DisplayList();
	static void createTopFaceRow2DisplayList();
	static void createTopFaceRow3DisplayList();
	static void createTopFaceRow4DisplayList();

    public:
	static void createDisplayLists();
	SphereHelper(void);
	static void renderSpheres();
	~SphereHelper(void);
    };