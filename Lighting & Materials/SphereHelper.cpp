#include "SphereHelper.h"

//Renders all the faces
void SphereHelper::renderSpheres()
    {
    renderFrontFaceSpheres();
    renderRightFaceSpheres();
    renderBackFaceSpheres();
    renderBottomFaceSpheres();
    renderLeftFaceSpheres();
    renderTopFaceSpheres();
    }

#pragma region Display List Creation Region

//Creates all the display lists.
void SphereHelper::createDisplayLists()
    {
    createFrontFaceDisplayList();
    createRightFaceDisplayList();
    createBackFaceDisplayList();
    createBottomFaceDisplayList();
    createLeftFaceDisplayList();
    createTopFaceDisplayList();
    }


#pragma region Front Face Spheres Display List

void SphereHelper::createFrontFaceDisplayList()
    {
    glNewList(FRONT_FACE_DISPLAY_LIST_ID, GL_COMPILE);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, zeroReflection);
    glMaterialfv(GL_FRONT, GL_EMISSION, zeroReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);

    int i = 0, j = 0;
    for(float y = -0.75; y < 1 ; y += 0.5)
	{
	for(float x = -0.75 ; x < 1 ; x += 0.5)
	    {
	    //set different material properties for spheres.
	    glMaterialfv(GL_FRONT, GL_AMBIENT, varyingMaterialProperties[j++]);
	    glPushMatrix();
	    glTranslatef(x, y, 1.25f);
	    glScalef(0.25f, 0.25f, 0.25f);
	    glutSolidSphere(1.0f, 100, 100);
	    glPopMatrix();
	    }
	}
    glEndList();
    }
#pragma endregion

#pragma region Right Face Spheres Display List
void SphereHelper::createRightFaceDisplayList()
    {
    glNewList(RIGHT_FACE_DISPLAY_LIST_ID, GL_COMPILE);

    glMaterialfv(GL_FRONT, GL_AMBIENT, zeroReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    
    int j = 0;
    for(float y = -0.75; y < 1 ; y += 0.5)
	{
	for(float z = 0.75 ; z > -1 ; z -= 0.5)
	    {
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, varyingMaterialProperties[j++]);
	    glPushMatrix();
	    glTranslatef(1.25, y, z);
	    glScalef(0.25f, 0.25f, 0.25f);
	    glutSolidSphere(1.0f, 100, 100);
	    glPopMatrix();
	    }
	}
    glEndList();
    }
#pragma endregion

#pragma region Back Face Spheres Display List
void SphereHelper::createBackFaceDisplayList()
    {
    glNewList(BACK_FACE_DISPLAY_LIST_ID, GL_COMPILE);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    
    GLfloat shades[][4] = {
	{0.2f, 0.0f, 0.3f, 1.0f},
	{0.4f, 0.0f, 0.6f, 1.0f},
	{0.5f, 0.0f, 0.8f, 1.0f},
	{0.7f, 0.0f, 1.0f, 1.0f}
	};

    int p = 0, q = 0;

    for(float y = -0.75; y < 1 ; y += 0.5)
	{
	glMaterialfv(GL_FRONT, GL_AMBIENT, shades[(p++)%4]);
	for(float x = -0.75 ; x < 1 ; x += 0.5)
	    {
	    glMaterialfv(GL_FRONT, GL_DIFFUSE, shades[(q++)%4]);
	    glPushMatrix();
	    glTranslatef(x, y, -1.25f);
	    glScalef(0.25f, 0.25f, 0.25f);
	    glutSolidSphere(1.0f, 100, 100);
	    glPopMatrix();
	    }
	}
    glEndList();
    }
#pragma endregion

#pragma region Bottom Face Spheres Display List
void SphereHelper::createBottomFaceDisplayList()
    {
    glNewList(BOTTOM_FACE_DISPLAY_LIST_ID, GL_COMPILE);
    int i = 0, j = 0;
    GLfloat specularMaterialValues[4][4] = {
	{0.2f, 0.2f, 0.2f, 1.0f},
	{0.5f, 0.5f, 0.5f, 1.0f},
	{0.8f, 0.8f, 0.8f, 1.0f},
	{1.0f, 1.0f, 1.0f, 1.0f}	
	};
    GLfloat lightRed [] = {0.4f, 0.0f, 0.0f, 1.0f};
    const GLfloat shineValues [][4] = { {20.0f}, {50.0f}, {70.0f}, {85.0f}};
    glMaterialfv(GL_FRONT, GL_AMBIENT, lightRed);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, lightRed);

    for(float z = -0.75; z < 1 ; z += 0.5)
	{
	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterialValues[(i++)%4]);
	for(float x = -0.75 ; x < 1 ; x += 0.5)
	    {
	    glMaterialf(GL_FRONT, GL_SHININESS, *(shineValues[(j++)%4]));
	    glPushMatrix();
	    glTranslatef(x, -1.25f, z);
	    glScalef(0.25f, 0.25f, 0.25f);
	    glutSolidSphere(1.0f, 100, 100);
	    glPopMatrix();
	    }
	}
    glEndList();
    }
#pragma endregion

#pragma region Left Face Spheres Display List
void SphereHelper::createLeftFaceEmissiveSpheresDL()
    {
    glNewList(LEFT_FACE_EMISSION_SPHERES_DL_ID, GL_COMPILE);
    for(GLfloat z = -0.75f; z < 1.0f; z += 0.5f)
	{
	glPushMatrix();
	glTranslatef(-1.25f, -0.75, z);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    for(GLfloat z = -0.75f; z < 1.0f; z += 0.5f)
	{
	glPushMatrix();
	glTranslatef(-1.25f, 0.25, z);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    glEndList();
    }

void SphereHelper::createLeftFaceEmissionReactiveSpheresDL()
    {

    glNewList(LEFT_FACE_EMISSION_REACTIVE_SPHERES_DL_ID, GL_COMPILE);
    for(GLfloat z = -0.75f; z < 1.0f; z += 0.5f)
	{
	glPushMatrix();
	glTranslatef(-1.25f, -0.25, z);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    for(GLfloat z = -0.75f; z < 1.0f; z += 0.5f)
	{
	if(z == 0.75f )
	    glMaterialfv(GL_FRONT, GL_EMISSION, zeroReflection);

	glPushMatrix();
	glTranslatef(-1.25f, 0.75, z);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    glEndList();
    }

void SphereHelper::createLeftFaceDisplayList()
    {

    createLeftFaceEmissiveSpheresDL();
    createLeftFaceEmissionReactiveSpheresDL();

    }
#pragma endregion

#pragma region Top Face Spheres Display List

void SphereHelper::createTopFaceRow1DisplayList()
    {
    glNewList(TOP_FACE_ROW_1_DL_ID, GL_COMPILE);
    int p = 0;
    for(GLfloat x = -0.75; x < 1.0f; x += 0.5f)
	{
	glMaterialfv(GL_FRONT, GL_AMBIENT, varyingMaterialProperties[p++]);
	glPushMatrix();
	glTranslatef(x, 1.25f, -0.75);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    glEndList();
    }

void SphereHelper::createTopFaceRow2DisplayList()
    {
    glNewList(TOP_FACE_ROW_2_DL_ID, GL_COMPILE);
    int p = 0;
    for(GLfloat x = -0.75; x < 1.0f; x += 0.5f)
	{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, varyingMaterialProperties[p++]);
	glPushMatrix();
	glTranslatef(x, 1.25f, -0.25);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    glEndList();

    }

void SphereHelper::createTopFaceRow3DisplayList()
    {
    glNewList(TOP_FACE_ROW_3_DL_ID, GL_COMPILE);
    GLfloat brightGray [] = {0.8f, 0.8f, 0.8f, 1.0f};
    int q = 0;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, varyingMaterialProperties[8]);
    GLfloat specularExps [] = { 8.0f, 10.0f, 16.0f, 24.0f };
    for(GLfloat x = -0.75; x < 1.0f; x += 0.5f)
	{
	glMaterialfv(GL_FRONT, GL_SPECULAR, brightGray);
	glMaterialf(GL_FRONT, GL_SHININESS, specularExps[q++]);
	glPushMatrix();
	glTranslatef(x, 1.25f, 0.25);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    glEndList();
    }

void SphereHelper::createTopFaceRow4DisplayList()
    {
    glNewList(TOP_FACE_ROW_4_DL_ID, GL_COMPILE);

    GLfloat lightGray [] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat emissiveColors [][4] = {
	{0.2f, 0.3f, 0.4f, 1.0f},
	{0.3f, 0.5f, 0.5f, 1.0f},
	{0.6f, 0.7f, 0.7f, 1.0f},
	{0.9f, 0.9f, 0.9f, 1.0f}
	};

    int p = 0;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lightGray);

    for(GLfloat x = -0.75; x < 1.0f; x += 0.5f)
	{
	glMaterialfv(GL_FRONT, GL_EMISSION, emissiveColors[p++]);
	glPushMatrix();
	glTranslatef(x, 1.25f, 0.75);
	glScalef(0.25f, 0.25f, 0.25f);
	glutSolidSphere(1.0f, 100, 100);
	glPopMatrix();
	}
    glEndList();
    }

void SphereHelper::createTopFaceDisplayList()
    {

    createTopFaceRow1DisplayList();
    createTopFaceRow2DisplayList();
    createTopFaceRow3DisplayList();
    createTopFaceRow4DisplayList();

    }
#pragma endregion front face

#pragma endregion display list creation region

#pragma region Render Spheres on each of the face

void SphereHelper::renderFrontFaceSpheres()
    {
    glCallList(FRONT_FACE_DISPLAY_LIST_ID);
    }

void SphereHelper::renderRightFaceSpheres()
    {
    glCallList(RIGHT_FACE_DISPLAY_LIST_ID);
    }

void SphereHelper::renderBackFaceSpheres()
    {
    glCallList(BACK_FACE_DISPLAY_LIST_ID);
    }

void SphereHelper::renderBottomFaceSpheres()
    {
    glCallList(BOTTOM_FACE_DISPLAY_LIST_ID);
    }

void SphereHelper::renderLeftFaceSpheres()
    {

    GLfloat brightGray [] = {0.8f, 0.8f, 0.8f, 1.0f};
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brightGray);

    static int l = 0;
    if(tempFlag)
	{
	glMaterialfv(GL_FRONT, GL_EMISSION, varyingMaterialProperties[(l++)%16]);
	tempFlag = false;
	}
    else
	{
	glMaterialfv(GL_FRONT, GL_EMISSION, varyingMaterialProperties[(l++)%16]);
	tempFlag = true;
	}

    glCallList(LEFT_FACE_EMISSION_SPHERES_DL_ID);

    glMaterialfv(GL_FRONT, GL_EMISSION, varyingMaterialProperties[13]);
    glCallList(LEFT_FACE_EMISSION_REACTIVE_SPHERES_DL_ID);    
    }

void SphereHelper::renderTopFaceSpheres()
    {
    //The material properties for every row are different.
    //So reset all properties before calling the display list to render them.
    //The properties specific for each row is handled in the display list.
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, zeroReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, zeroReflection);
    glCallList(TOP_FACE_ROW_1_DL_ID);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, zeroReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, zeroReflection);
    glCallList(TOP_FACE_ROW_2_DL_ID);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, zeroReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, zeroReflection);
    glCallList(TOP_FACE_ROW_3_DL_ID);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, zeroReflection);
    glMaterialfv(GL_FRONT, GL_SPECULAR, zeroReflection);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0f);
    glMaterialfv(GL_FRONT, GL_EMISSION, zeroReflection);
    glCallList(TOP_FACE_ROW_4_DL_ID);
    }

#pragma endregion

SphereHelper::SphereHelper(void)
    {
    }


SphereHelper::~SphereHelper(void)
    {
    }
