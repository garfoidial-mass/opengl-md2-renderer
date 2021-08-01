#pragma once

#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include "GL/glew.h"

#include "GLFW/glfw3.h"


#include <cstdio>
#include <cstdlib>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <map>
#include <memory>
#include <string>
#include "vboindexer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"

struct md2_header_t
{
	int ident;                  /* magic number: "IDP2" */
	int version;                /* version: must be 8 */

	int skinwidth;              /* texture width */
	int skinheight;             /* texture height */

	int framesize;              /* size in bytes of a frame */

	int num_skins;              /* number of skins */
	int num_vertices;           /* number of vertices per frame */
	int num_st;                 /* number of texture coordinates */
	int num_tris;               /* number of triangles */
	int num_glcmds;             /* number of opengl commands */
	int num_frames;             /* number of frames */

	int offset_skins;           /* offset skin data */
	int offset_st;              /* offset texture coordinate data */
	int offset_tris;            /* offset triangle data */
	int offset_frames;          /* offset frame data */
	int offset_glcmds;          /* offset OpenGL command data */
	int offset_end;             /* offset end of file */
};

/* Vector */
typedef float vec3_t[3];

/* Texture name */
struct md2_skin_t
{
	char name[64];              /* texture file name */
};

/* Texture coords */
struct md2_texCoord_t
{
	short s;
	short t;
};

struct allVectors {
	glm::vec3 vertices;
	glm::vec2 uvs;
	glm::vec3 normals;
};

/* Triangle info */
struct md2_triangle_t
{
	unsigned short vertex[3];   /* vertex indices of the triangle */
	unsigned short st[3];       /* tex. coord. indices */
};

/* Compressed vertex */
struct md2_vertex_t
{
	unsigned char v[3];         /* position */
	unsigned char normalIndex;  /* normal vector index */
};

/* Model frame */
struct md2_frame_t
{
	vec3_t scale;               /* scale factor */
	vec3_t translate;           /* translation vector */
	char name[16];              /* frame name */
	struct md2_vertex_t* verts; /* list of frame's vertices */
};

class md2_model_t
{
public:
	md2_model_t( std::string model,std::string texture,std::string vertexPath,std::string fragmentPath);
	~md2_model_t();
	struct md2_header_t header;
	struct md2_skin_t* skins;
	struct md2_texCoord_t* texcoords;
	struct md2_triangle_t* triangles;
	struct md2_frame_t* frames;
	int* glcmds; // opengl commands
	GLuint tex_id;
	float interp;
	bool scaled = false;

	GLuint currentVBO;
	GLuint nextVBO;
	GLuint modelProgramID;
	GLuint texture;
	GLuint textureID;
	GLuint scaledLocation;

	GLuint VertexArrayID;

	GLuint MatrixID;
	GLuint ModelID;
	GLuint ViewID;
	GLuint interpID;

	glm::mat4 Model = glm::mat4(1.0f);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> vbos;

	short uvOffset = 0;
	short normalOffset = 0;
private:
	std::string currentAnim = "";
	int start, end, current = 0;
	int ReadMD2Model(const char* filename, md2_model_t* mdl);
	void RenderFrame(int start, int end, float& interp, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, bool loop);
	void getAnimBounds(std::string animation);
	void generateFrameBuffers(); // generates vbo's for each frame
	void getBuffers(int start, int end, float& interp,bool loop);
public:
	void Animate(std::string anim, bool loop, float deltaTime, float speed);
	void Draw(Camera camera);
	void Translate(glm::vec3 direction);
	void Scale(glm::vec3 scale);
	void Rotate(float angle, glm::vec3 axis);
};

class static_md2_model_t
{
public:
	static_md2_model_t(std::string model, std::string texture, std::string vertexPath, std::string fragmentPath);
	~static_md2_model_t();
	struct md2_header_t header;
	struct md2_skin_t* skins;
	struct md2_texCoord_t* texcoords;
	struct md2_triangle_t* triangles;
	struct md2_frame_t* frames;
	int* glcmds; // opengl commands
	GLuint tex_id;
	bool scaled = false;

	GLuint modelProgramID;
	GLuint texture;
	GLuint textureID;
	GLuint scaledLocation;

	GLuint VertexArrayID;

	GLuint MatrixID;
	GLuint ModelID;
	GLuint ViewID;

	glm::mat4 Model = glm::mat4(1.0f);

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint indexbuffer;
private:
	float fakeinterp = 0;
	int ReadMD2Model(const char* filename, static_md2_model_t* mdl);
	void RenderFrame(int start, int end, float& interp, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, bool loop);
public:
	void Draw(Camera camera);
	void Translate(glm::vec3 direction);
	void Scale(glm::vec3 scale);
	void Rotate(float angle, glm::vec3 axis);
};