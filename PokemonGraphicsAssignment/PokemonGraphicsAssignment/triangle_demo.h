#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include <cmath>
#include "demo_base.h"
#include "lodepng.h"
#include <vector>
#include <iostream>

#define TEXTURE_COUNT 3

class TriangleDemo : public DemoBase
{
private:
	GLuint mTextureID[TEXTURE_COUNT];


	void loadPNG(const char* path, GLuint textureID)
	{
		//Load file and decode image
		std::vector<unsigned char> image;
		unsigned width, height;
		unsigned error = lodepng::decode(image, width, height, path);

		//If there's an error, display it
		if (error != 0)
		{
			std::cout << "png load error : " << error << ": " << lodepng_error_text(error) << std::endl;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Apply texture wrapping along horizontal part
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //Apply texture wrapping along vertical part

																	  //Bilinear filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Near filtering for texture scaling
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Far filtering for texture scaling

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
	}
public:

	float PI = 3.142;

	void init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
		glEnable(GL_ALPHA_TEST);

		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadPNG("../media/unity_logo.png", mTextureID[0]);
		loadPNG("../media/angry_birds.png", mTextureID[1]);
	}

	void deinit()
	{
	}

	void drawAxis(const Matrix& viewMatrix)
	{
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);

		glColor3f(1.0f, 0.3f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);

		glColor3f(0.3f, 1.0f, 0.3f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		glColor3f(0.3f, 0.3f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);

		glEnd();
	}

	void drawTriangle(const Matrix& viewMatrix)
	{
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_TRIANGLES);							// Drawing Using Triangles

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);					// Top Left
		glVertex3f(1.0f, -1.0f, 0.0f);					// Bottom Left
		glVertex3f(2.0f, -1.0f, 0.0f);					// Bottom Right

		glEnd();										// Finished Drawing The Triangles
	}

	void drawCube(float size = 1.0f)
	{
		size /= 2.0f;
		glBegin(GL_TRIANGLES);

		// Blue
		glColor3f(0.25f, 0.25f, 1.0f);

		// Negative Square
		glVertex3f(-size, size, -size);
		glVertex3f(-size, -size, -size);
		glVertex3f(size, -size, -size);

		glVertex3f(-size, size, -size);
		glVertex3f(size, size, -size);
		glVertex3f(size, -size, -size);

		// Positive Square
		glVertex3f(-size, size, size);
		glVertex3f(-size, -size, size);
		glVertex3f(size, -size, size);

		glVertex3f(-size, size, size);
		glVertex3f(size, size, size);
		glVertex3f(size, -size, size);

		// Green
		glColor3f(0.25f, 1.0f, 0.25f);

		// Negative Square
		glVertex3f(size, -size, -size);
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, -size, size);

		glVertex3f(size, -size, -size);
		glVertex3f(size, -size, size);
		glVertex3f(-size, -size, size);

		// Positive Square
		glVertex3f(size, size, -size);
		glVertex3f(-size, size, -size);
		glVertex3f(-size, size, size);

		glVertex3f(size, size, -size);
		glVertex3f(size, size, size);
		glVertex3f(-size, size, size);

		// Red
		glColor3f(1.0f, 0.25f, 0.25f);

		// Negative Square
		glVertex3f(-size, -size, size);
		glVertex3f(-size, -size, -size);
		glVertex3f(-size, size, -size);

		glVertex3f(-size, -size, size);
		glVertex3f(-size, size, size);
		glVertex3f(-size, size, -size);

		// Positive Square
		glVertex3f(size, -size, size);
		glVertex3f(size, -size, -size);
		glVertex3f(size, size, -size);

		glVertex3f(size, -size, size);
		glVertex3f(size, size, size);
		glVertex3f(size, size, -size);

		glEnd();										// Finished Drawing The Triangles
	}

	void drawTextureCube(float size = 1.0f)
	{
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glBegin(GL_TRIANGLES);

		// Negative Square (back)
		glTexCoord2f(1.0f, 0.0f), glVertex3f(-size, size, -size);
		glTexCoord2f(1.0f, 1.0f), glVertex3f(-size, -size, -size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(size, -size, -size);

		glTexCoord2f(1.0f, 0.0f), glVertex3f(-size, size, -size);
		glTexCoord2f(0.0f, 0.0f), glVertex3f(size, size, -size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(size, -size, -size);

		// Positive Square (front)
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, size, size);
		glTexCoord2f(0.0f, 0.0f), glVertex3f(-size, -size, size);
		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, -size, size);

		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, size, size);
		glTexCoord2f(1.0f, 1.0f), glVertex3f(size, size, size);
		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, -size, size);

		// Negative Square (down)
		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, -size, -size);
		glTexCoord2f(0.0f, 0.0f), glVertex3f(-size, -size, -size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, -size, size);

		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, -size, -size);
		glTexCoord2f(1.0f, 1.0f), glVertex3f(size, -size, size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, -size, size);

		// Positive Square (up)
		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, size, -size);
		glTexCoord2f(0.0f, 0.0f), glVertex3f(-size, size, -size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, size, size);

		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, size, -size);
		glTexCoord2f(1.0f, 1.0f), glVertex3f(size, size, size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, size, size);

		// Negative Square (left)
		glTexCoord2f(1.0f, 0.0f), glVertex3f(-size, -size, size);
		glTexCoord2f(0.0f, 0.0f), glVertex3f(-size, -size, -size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, size, -size);

		glTexCoord2f(1.0f, 0.0f), glVertex3f(-size, -size, size);
		glTexCoord2f(1.0f, 1.0f), glVertex3f(-size, size, size);
		glTexCoord2f(0.0f, 1.0f), glVertex3f(-size, size, -size);

		// Positive Square (right)
		glTexCoord2f(0.0f, 1.0f), glVertex3f(size, -size, size);
		glTexCoord2f(1.0f, 1.0f), glVertex3f(size, -size, -size);
		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, size, -size);

		glTexCoord2f(0.0f, 1.0f), glVertex3f(size, -size, size);
		glTexCoord2f(0.0f, 0.0f), glVertex3f(size, size, size);
		glTexCoord2f(1.0f, 0.0f), glVertex3f(size, size, -size);

		////Front square

		//glTexCoord2f(0.0f, 0.0f), glVertex3f(-3.0f, -3.0f, 0.0f);
		//glTexCoord2f(1.0f, 0.0f), glVertex3f(3.0f, -3.0f, 0.0f);
		//glTexCoord2f(1.0f, 1.0f), glVertex3f(3.0f, 3.0f, 0.0f);

		//glTexCoord2f(1.0f, 1.0f), glVertex3f(3.0f, 3.0f, 0.0f);
		//glTexCoord2f(0.0f, 1.0f), glVertex3f(-3.0f, 3.0f, 0.0f);
		//glTexCoord2f(0.0f, 0.0f), glVertex3f(-3.0f, -3.0f, 0.0f);

		////Back square

		//glTexCoord2f(0.0f, 0.0f), glVertex3f(-3.0f, -3.0f, 3.0f);
		//glTexCoord2f(1.0f, 0.0f), glVertex3f(3.0f, -3.0f, 3.0f);
		//glTexCoord2f(1.0f, 1.0f), glVertex3f(3.0f, 3.0f, 3.0f);

		//glTexCoord2f(1.0f, 1.0f), glVertex3f(3.0f, 3.0f, 3.0f);
		//glTexCoord2f(0.0f, 1.0f), glVertex3f(-3.0f, 3.0f, 3.0f);
		//glTexCoord2f(0.0f, 0.0f), glVertex3f(-3.0f, -3.0f, 3.0f);

		////Left square

		//glTexCoord2f(0.0f, 0.0f), glVertex3f(-3.0f, -3.0f, 0.0f);
		//glTexCoord2f(1.0f, 0.0f), glVertex3f(3.0f, -3.0f, 0.0f);
		//glTexCoord2f(1.0f, 1.0f), glVertex3f(3.0f, 3.0f, 0.0f);

		//glTexCoord2f(1.0f, 1.0f), glVertex3f(3.0f, 3.0f, 0.0f);
		//glTexCoord2f(0.0f, 1.0f), glVertex3f(-3.0f, 3.0f, 0.0f);
		//glTexCoord2f(0.0f, 0.0f), glVertex3f(-3.0f, -3.0f, 0.0f);

		glEnd();
	}

	void drawPyramid(float size = 1.0f)
	{
		size /= 2.0f;
		glBegin(GL_TRIANGLES);							// Drawing Using Triangles

														// Base
		glColor3f(0.25f, 1.0f, 0.25f);
		glVertex3f(size, -size, size);					// Top
		glVertex3f(size, -size, -size);					// Bottom Left
		glVertex3f(-size, -size, size);					// Bottom Right

		glVertex3f(-size, -size, -size);				// Top
		glVertex3f(size, -size, -size);					// Bottom Left
		glVertex3f(-size, -size, size);					// Bottom Right

														// Red Triangles
		glColor3f(1.0f, 0.25f, 0.25f);
		glVertex3f(0.0f, size, 0.0f);					// Top Vertex
		glVertex3f(size, -size, -size);					// Bottom Left
		glVertex3f(size, -size, size);					// Bottom Right

		glVertex3f(0.0f, size, 0.0f);					// Top Vertex
		glVertex3f(-size, -size, -size);				// Bottom Left
		glVertex3f(-size, -size, size);					// Bottom Right

														// Blue Triangles
		glColor3f(0.25f, 0.25f, 1.0f);
		glVertex3f(0.0f, size, 0.0f);					// Top Vertex
		glVertex3f(-size, -size, size);					// Bottom Left
		glVertex3f(size, -size, size);					// Bottom Right

		glVertex3f(0.0f, size, 0.0f);					// Top Vertex
		glVertex3f(-size, -size, -size);				// Bottom Left
		glVertex3f(size, -size, -size);					// Bottom Right

		glEnd();										// Finished Drawing The Triangles
	}

	void drawCylinder(float height, float radius, int iteration = 100) //Change iteration to steps
	{
		//Offset
		float offsetX = 0.0f;
		float offsetY = 0.0f;
		float offsetZ = 0.0f;
		float halfHeight = height / 2.0f;

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);							// Drawing Using Triangles

		float t = 360.0f / iteration;

		for (int i = 0; i < iteration; i++)
		{
			float x1 = radius * cos((i * t) * PI / 180.0);
			float z1 = radius * sin((i * t) * PI / 180.0);

			float x2 = radius * cos(((i + 1) * t) * PI / 180.0);
			float z2 = radius * sin(((i + 1) * t) * PI / 180.0);

			// ---- Upper Circle ----
			glColor3f(1.0f, (i % 2 == 0 ? 0.5f : 1.0f), 0.5f);
			//Center of the circle
			glVertex3f(offsetX, offsetY + halfHeight, offsetZ);

			//First point
			glVertex3f(x1, offsetY + halfHeight, z1);

			//Second point
			glVertex3f(x2, offsetY + halfHeight, z2);

			// ---- Lower Circle ----
			glColor3f(1.0f, (i % 2 == 0 ? 0.5f : 1.0f), 0.5f);
			//Center of the circle
			glVertex3f(offsetX, offsetY - halfHeight, offsetZ);

			//First point
			glVertex3f(x1, offsetY - halfHeight, z1);

			//Second point
			glVertex3f(x2, offsetY - halfHeight, z2);

			// ---- Upper Triangle ----
			glColor3f(0.5f, 1.0f, 0.5f);
			//First point
			glVertex3f(x1, offsetY + halfHeight, z1);

			//Second point
			glVertex3f(x2, offsetY + halfHeight, z2);

			//Third point
			glVertex3f(x1, offsetY - halfHeight, z1);

			// ---- Lower Triangle ----
			glColor3f(0.5f, 0.5f, 1.0f);
			//First point
			glVertex3f(x1, offsetY - halfHeight, z1);

			//Second point
			glVertex3f(x2, offsetY - halfHeight, z2);

			//Third point
			glVertex3f(x2, offsetY + halfHeight, z2);
		}

		glEnd();										// Finished Drawing The Triangles
	}

	void drawCone(float height, float radius, int iteration = 100)
	{
		//Offset
		float offsetX = 0.0f;
		float offsetY = 0.0f;
		float offsetZ = 0.0f;
		float halfHeight = height / 2.0f;

		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);							// Drawing Using Triangles

		float t = 360.0f / iteration;

		for (int i = 0; i < iteration; i++)
		{
			float x1 = radius * cos((i * t) * PI / 180.0);
			float z1 = radius * sin((i * t) * PI / 180.0);

			float x2 = radius * cos(((i + 1) * t) * PI / 180.0);
			float z2 = radius * sin(((i + 1) * t) * PI / 180.0);

			// ---- Circle ----
			glColor3f(1.0f, (i % 2 == 0 ? 0.5f : 1.0f), 0.5f);
			//Center of the circle
			glVertex3f(offsetX, offsetY - halfHeight, offsetZ);

			//First point
			glVertex3f(x1, offsetY - halfHeight, z1);

			//Second point
			glVertex3f(x2, offsetY - halfHeight, z2);

			// ---- Triangle ----
			glColor3f(0.5f, (i % 2 == 0 ? 0.5f : 1.0f), (i % 2 == 0 ? 1.0f : 0.5f));
			//Upper vertex
			glVertex3f(offsetX, offsetY + halfHeight, offsetZ);

			//First point
			glVertex3f(x1, offsetY - halfHeight, z1);

			//Second point
			glVertex3f(x2, offsetY - halfHeight, z2);
		}

		glEnd();										// Finished Drawing The Triangles
	}

	Matrix ovalOrbiter(const Matrix& viewMatrix, float rot1, float rot2, float amplitude, float l1, float l2)
	{
		//Matrix Transformation
		//Matrix translate1 = Matrix::makeTranslationMatrix(Vector(0.0f, amplitude * sin(rot1 * PI / 180.0f), 0.0f));
		//Matrix rotate1 = Matrix::makeRotateMatrix(rot2, Vector(0.0f, 1.0f, 0.0f));
		Matrix translate2 = Matrix::makeTranslationMatrix(Vector(l1 * cos(rot2 * PI / 180.0f), 0.0f, l2 * sin(rot2 * PI / 180.0f)));
		//Matrix scale1 = Matrix::makeScaleMatrix(Vector(2.0f, 1.0f, 3.0f));

		// NOTE on OpenGL Matrix model
		// Screen = Proj * View * Model
		// Model = TransformC(3rd) * TransformB(2nd) * TransformA(1st) (Transform could be Rotate, Scale, Translate, etc)

		//Perform Model Transformation
		Matrix modelMatrix = translate2;

		Matrix viewSpaceMatrix = viewMatrix * modelMatrix;

		return viewSpaceMatrix;
	}

	float rot1 = 0.0f;
	float rot2 = 0.0f;

	float cubeBaseAngle = 0.0f;

	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);

		glLoadMatrixf((GLfloat*)viewMatrix.mVal);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Show Wireframes

		//drawCube();
		//drawPyramid();
		//drawCylinder(2.0f, 1.0f);
		//drawCone(2.0f, 1.0f);

		/*
		// Oval Orbiter
		rot1 += 0.1f;
		rot2 += 0.05f;

		glLoadMatrixf((GLfloat*)ovalOrbiter(viewMatrix, rot2, rot1, 2.0f, 5.0f, 2.5f).mVal);
		drawCube();
		*/

		/*
		// "DNA" Animation
		float radius = 2.0f;
		float offsetY = 0.2f;
		float offsetAngle = 30.0f;
		int cubeAmount = 50;

		for (int i = 0; i < cubeAmount; i++)
		{
			//Method 1 - Translate + Rotation
			Matrix translationCube = Matrix::makeTranslationMatrix(Vector(radius, offsetY * i, 0));
			Matrix rotationCube = Matrix::makeRotateMatrix(cubeBaseAngle - (i * offsetAngle), Vector(0, 1, 0));
			Matrix cubeMatrix = viewMatrix * rotationCube * translationCube;
			//glLoadMatrixf((GLfloat*)cubeMatrix.mVal);

			//Method 2 - Use circle formula
			Matrix magicMatrix = Matrix::makeTranslationMatrix(Vector(cosf((cubeBaseAngle - (i * offsetAngle)) * PI / 180.0f) * radius, offsetY * i, sinf((cubeBaseAngle - (i * offsetAngle)) * PI / 180.0f) * radius));
			glLoadMatrixf((GLfloat*)(viewMatrix * magicMatrix).mVal);

			drawCube(0.5f);
		}

		cubeBaseAngle += 0.05f;
		*/

		/*
		Matrix coneTranslation = Matrix::makeTranslationMatrix(Vector(0.0f, 4.0f, 4.0f));
		Matrix coneRotation = Matrix::makeRotateMatrix(90.0f, Vector(1.0f, 1.0f, 1.0f));
		Matrix coneMatrix = viewMatrix * coneRotation;
		glLoadMatrixf((GLfloat*)coneMatrix.mVal);
		drawCone(1.0f, 0.2f);
		*/

		////drawing both legs
		//for (int j = 0; j < 2; j++)
		//{
		//	//3 main toes on left side
		//	for (int i = 0; i < 3; i++)
		//	{
		//		/*
		//		Matrix coneTranslation1 = Matrix::makeTranslationMatrix(Vector(i, 0.0f, 0.0f));
		//		Matrix coneRotation1 = Matrix::makeRotateMatrix(90.0f, Vector(1.0f, 0.0f, 0.0f));
		//		Matrix coneMatrix1 = viewMatrix * coneTranslation1 * coneRotation1;
		//		glLoadMatrixf((GLfloat*)coneMatrix1.mVal);
		//		drawCone(1.0f, 0.2f);
		//		*/

		//		Matrix feetTranslate1 = Matrix::makeTranslationMatrix(Vector(i * 0.5f + j * 3.0f, 0.0f, 0.0f));
		//		Matrix toeTranslate1 = Matrix::makeTranslationMatrix(Vector(0.0f, 1.5f, 0.0f));
		//		Matrix feetRotate1 = Matrix::makeRotateMatrix(90.0f, Vector(1.0f, 0.0f, 0.0f));
		//		Matrix feetRotate2 = Matrix::makeRotateMatrix((30.0f * i) - 30.0f, Vector(0.0f, 1.0f, 0.0f));

		//		Matrix modelMatrix = feetTranslate1 * feetRotate2 * feetRotate1;
		//		Matrix feetMatrix1 = viewMatrix * modelMatrix;
		//		glLoadMatrixf((GLfloat*)feetMatrix1.mVal);
		//		drawCylinder(2.0f, 0.18f);

		//		modelMatrix = modelMatrix * toeTranslate1;
		//		Matrix feetMatrix2 = viewMatrix * modelMatrix;
		//		glLoadMatrixf((GLfloat*)feetMatrix2.mVal);
		//		drawCone(1.0f, 0.2f);

		//		/*
		//		GLUquadric *quadric;
		//		quadric = gluNewQuadric();
		//		gluSphere(quadric, 0.5, 30, 30);
		//		*/
		//	}

		//	//left lower leg
		//	Matrix leftLowerLegTranslate1 = Matrix::makeTranslationMatrix(Vector(0.5f + j * 3.0f, 1.5f, 1.35f));
		//	Matrix leftLowerLegRotate1 = Matrix::makeRotateMatrix(-15.0f, Vector(1.0f, 0.0f, 0.0f));

		//	Matrix modelMatrixLeftLeg1 = leftLowerLegTranslate1 * leftLowerLegRotate1;
		//	Matrix leftLowerLegMatrix1 = viewMatrix * modelMatrixLeftLeg1;
		//	glLoadMatrixf((GLfloat*)leftLowerLegMatrix1.mVal);
		//	drawCylinder(3.0f, 0.2f);

		//	//left upper leg
		//	Matrix leftUpperLegTranslate1 = Matrix::makeTranslationMatrix(Vector(0.0f, 2.75f, -0.65f));
		//	Matrix leftUpperLegRotate1 = Matrix::makeRotateMatrix(25.0f, Vector(1.0f, 0.0f, 0.0f));

		//	modelMatrixLeftLeg1 = modelMatrixLeftLeg1 * leftUpperLegTranslate1 * leftUpperLegRotate1;
		//	Matrix leftUpperLegMatrix1 = viewMatrix * modelMatrixLeftLeg1;
		//	glLoadMatrixf((GLfloat*)leftUpperLegMatrix1.mVal);
		//	drawCylinder(3.0f, 0.2f);
		//}

		/*
		//3 main toes on right side
		for (int i = 0; i < 3; i++)
		{
			Matrix feetTranslate1 = Matrix::makeTranslationMatrix(Vector(i * 0.5f + 5.0f, 0.0f, 0.0f));
			Matrix toeTranslate1 = Matrix::makeTranslationMatrix(Vector(0.0f, 1.5f, 0.0f));
			Matrix feetRotate1 = Matrix::makeRotateMatrix(90.0f, Vector(1.0f, 0.0f, 0.0f));
			Matrix feetRotate2 = Matrix::makeRotateMatrix((30.0f * i) - 30.0f, Vector(0.0f, 1.0f, 0.0f));

			Matrix modelMatrix = feetTranslate1 * feetRotate2 * feetRotate1;
			Matrix feetMatrix1 = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)feetMatrix1.mVal);
			drawCylinder(2.0f, 0.18f);

			modelMatrix = modelMatrix * toeTranslate1;
			Matrix feetMatrix2 = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)feetMatrix2.mVal);
			drawCone(1.0f, 0.2f);
		}
		*/

		/*
		//Example for sequences of tranforms
		Matrix modelMatrix1;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix1;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		drawCube(); //This cube is affected by the last applied matrix

		Matrix modelMatrix2;
		Matrix viewSpaceMatrix = viewMatrix * modelMatrix2;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		drawCube(); //This cube is affected by the last applied matrix
		*/
		
		drawTextureCube(3.0f);

	}
};

#endif