//i didn't write most of this
#include "Md2.h"
#include "ShaderProgram.h"

float anorms_table[][3] = {
	{ -0.525731f,  0.000000f,  0.850651f },
	{ -0.442863f,  0.238856f,  0.864188f },
	{ -0.295242f,  0.000000f,  0.955423f },
	{ -0.309017f,  0.500000f,  0.809017f },
	{ -0.162460f,  0.262866f,  0.951056f },
	{  0.000000f,  0.000000f,  1.000000f },
	{  0.000000f,  0.850651f,  0.525731f },
	{ -0.147621f,  0.716567f,  0.681718f },
	{  0.147621f,  0.716567f,  0.681718f },
	{  0.000000f,  0.525731f,  0.850651f },
	{  0.309017f,  0.500000f,  0.809017f },
	{  0.525731f,  0.000000f,  0.850651f },
	{  0.295242f,  0.000000f,  0.955423f },
	{  0.442863f,  0.238856f,  0.864188f },
	{  0.162460f,  0.262866f,  0.951056f },
	{ -0.681718f,  0.147621f,  0.716567f },
	{ -0.809017f,  0.309017f,  0.500000f },
	{ -0.587785f,  0.425325f,  0.688191f },
	{ -0.850651f,  0.525731f,  0.000000f },
	{ -0.864188f,  0.442863f,  0.238856f },
	{ -0.716567f,  0.681718f,  0.147621f },
	{ -0.688191f,  0.587785f,  0.425325f },
	{ -0.500000f,  0.809017f,  0.309017f },
	{ -0.238856f,  0.864188f,  0.442863f },
	{ -0.425325f,  0.688191f,  0.587785f },
	{ -0.716567f,  0.681718f, -0.147621f },
	{ -0.500000f,  0.809017f, -0.309017f },
	{ -0.525731f,  0.850651f,  0.000000f },
	{  0.000000f,  0.850651f, -0.525731f },
	{ -0.238856f,  0.864188f, -0.442863f },
	{  0.000000f,  0.955423f, -0.295242f },
	{ -0.262866f,  0.951056f, -0.162460f },
	{  0.000000f,  1.000000f,  0.000000f },
	{  0.000000f,  0.955423f,  0.295242f },
	{ -0.262866f,  0.951056f,  0.162460f },
	{  0.238856f,  0.864188f,  0.442863f },
	{  0.262866f,  0.951056f,  0.162460f },
	{  0.500000f,  0.809017f,  0.309017f },
	{  0.238856f,  0.864188f, -0.442863f },
	{  0.262866f,  0.951056f, -0.162460f },
	{  0.500000f,  0.809017f, -0.309017f },
	{  0.850651f,  0.525731f,  0.000000f },
	{  0.716567f,  0.681718f,  0.147621f },
	{  0.716567f,  0.681718f, -0.147621f },
	{  0.525731f,  0.850651f,  0.000000f },
	{  0.425325f,  0.688191f,  0.587785f },
	{  0.864188f,  0.442863f,  0.238856f },
	{  0.688191f,  0.587785f,  0.425325f },
	{  0.809017f,  0.309017f,  0.500000f },
	{  0.681718f,  0.147621f,  0.716567f },
	{  0.587785f,  0.425325f,  0.688191f },
	{  0.955423f,  0.295242f,  0.000000f },
	{  1.000000f,  0.000000f,  0.000000f },
	{  0.951056f,  0.162460f,  0.262866f },
	{  0.850651f, -0.525731f,  0.000000f },
	{  0.955423f, -0.295242f,  0.000000f },
	{  0.864188f, -0.442863f,  0.238856f },
	{  0.951056f, -0.162460f,  0.262866f },
	{  0.809017f, -0.309017f,  0.500000f },
	{  0.681718f, -0.147621f,  0.716567f },
	{  0.850651f,  0.000000f,  0.525731f },
	{  0.864188f,  0.442863f, -0.238856f },
	{  0.809017f,  0.309017f, -0.500000f },
	{  0.951056f,  0.162460f, -0.262866f },
	{  0.525731f,  0.000000f, -0.850651f },
	{  0.681718f,  0.147621f, -0.716567f },
	{  0.681718f, -0.147621f, -0.716567f },
	{  0.850651f,  0.000000f, -0.525731f },
	{  0.809017f, -0.309017f, -0.500000f },
	{  0.864188f, -0.442863f, -0.238856f },
	{  0.951056f, -0.162460f, -0.262866f },
	{  0.147621f,  0.716567f, -0.681718f },
	{  0.309017f,  0.500000f, -0.809017f },
	{  0.425325f,  0.688191f, -0.587785f },
	{  0.442863f,  0.238856f, -0.864188f },
	{  0.587785f,  0.425325f, -0.688191f },
	{  0.688191f,  0.587785f, -0.425325f },
	{ -0.147621f,  0.716567f, -0.681718f },
	{ -0.309017f,  0.500000f, -0.809017f },
	{  0.000000f,  0.525731f, -0.850651f },
	{ -0.525731f,  0.000000f, -0.850651f },
	{ -0.442863f,  0.238856f, -0.864188f },
	{ -0.295242f,  0.000000f, -0.955423f },
	{ -0.162460f,  0.262866f, -0.951056f },
	{  0.000000f,  0.000000f, -1.000000f },
	{  0.295242f,  0.000000f, -0.955423f },
	{  0.162460f,  0.262866f, -0.951056f },
	{ -0.442863f, -0.238856f, -0.864188f },
	{ -0.309017f, -0.500000f, -0.809017f },
	{ -0.162460f, -0.262866f, -0.951056f },
	{  0.000000f, -0.850651f, -0.525731f },
	{ -0.147621f, -0.716567f, -0.681718f },
	{  0.147621f, -0.716567f, -0.681718f },
	{  0.000000f, -0.525731f, -0.850651f },
	{  0.309017f, -0.500000f, -0.809017f },
	{  0.442863f, -0.238856f, -0.864188f },
	{  0.162460f, -0.262866f, -0.951056f },
	{  0.238856f, -0.864188f, -0.442863f },
	{  0.500000f, -0.809017f, -0.309017f },
	{  0.425325f, -0.688191f, -0.587785f },
	{  0.716567f, -0.681718f, -0.147621f },
	{  0.688191f, -0.587785f, -0.425325f },
	{  0.587785f, -0.425325f, -0.688191f },
	{  0.000000f, -0.955423f, -0.295242f },
	{  0.000000f, -1.000000f,  0.000000f },
	{  0.262866f, -0.951056f, -0.162460f },
	{  0.000000f, -0.850651f,  0.525731f },
	{  0.000000f, -0.955423f,  0.295242f },
	{  0.238856f, -0.864188f,  0.442863f },
	{  0.262866f, -0.951056f,  0.162460f },
	{  0.500000f, -0.809017f,  0.309017f },
	{  0.716567f, -0.681718f,  0.147621f },
	{  0.525731f, -0.850651f,  0.000000f },
	{ -0.238856f, -0.864188f, -0.442863f },
	{ -0.500000f, -0.809017f, -0.309017f },
	{ -0.262866f, -0.951056f, -0.162460f },
	{ -0.850651f, -0.525731f,  0.000000f },
	{ -0.716567f, -0.681718f, -0.147621f },
	{ -0.716567f, -0.681718f,  0.147621f },
	{ -0.525731f, -0.850651f,  0.000000f },
	{ -0.500000f, -0.809017f,  0.309017f },
	{ -0.238856f, -0.864188f,  0.442863f },
	{ -0.262866f, -0.951056f,  0.162460f },
	{ -0.864188f, -0.442863f,  0.238856f },
	{ -0.809017f, -0.309017f,  0.500000f },
	{ -0.688191f, -0.587785f,  0.425325f },
	{ -0.681718f, -0.147621f,  0.716567f },
	{ -0.442863f, -0.238856f,  0.864188f },
	{ -0.587785f, -0.425325f,  0.688191f },
	{ -0.309017f, -0.500000f,  0.809017f },
	{ -0.147621f, -0.716567f,  0.681718f },
	{ -0.425325f, -0.688191f,  0.587785f },
	{ -0.162460f, -0.262866f,  0.951056f },
	{  0.442863f, -0.238856f,  0.864188f },
	{  0.162460f, -0.262866f,  0.951056f },
	{  0.309017f, -0.500000f,  0.809017f },
	{  0.147621f, -0.716567f,  0.681718f },
	{  0.000000f, -0.525731f,  0.850651f },
	{  0.425325f, -0.688191f,  0.587785f },
	{  0.587785f, -0.425325f,  0.688191f },
	{  0.688191f, -0.587785f,  0.425325f },
	{ -0.955423f,  0.295242f,  0.000000f },
	{ -0.951056f,  0.162460f,  0.262866f },
	{ -1.000000f,  0.000000f,  0.000000f },
	{ -0.850651f,  0.000000f,  0.525731f },
	{ -0.955423f, -0.295242f,  0.000000f },
	{ -0.951056f, -0.162460f,  0.262866f },
	{ -0.864188f,  0.442863f, -0.238856f },
	{ -0.951056f,  0.162460f, -0.262866f },
	{ -0.809017f,  0.309017f, -0.500000f },
	{ -0.864188f, -0.442863f, -0.238856f },
	{ -0.951056f, -0.162460f, -0.262866f },
	{ -0.809017f, -0.309017f, -0.500000f },
	{ -0.681718f,  0.147621f, -0.716567f },
	{ -0.681718f, -0.147621f, -0.716567f },
	{ -0.850651f,  0.000000f, -0.525731f },
	{ -0.688191f,  0.587785f, -0.425325f },
	{ -0.587785f,  0.425325f, -0.688191f },
	{ -0.425325f,  0.688191f, -0.587785f },
	{ -0.425325f, -0.688191f, -0.587785f },
	{ -0.587785f, -0.425325f, -0.688191f },
{ -0.688191f, -0.587785f, -0.425325f }
};


md2_model_t::md2_model_t(std::string model,std::string texture, std::string vertexPath, std::string fragmentPath)
{
	ReadMD2Model(model.c_str(), this);
	generateFrameBuffers();
	modelProgramID = LoadShaders(vertexPath.c_str(), fragmentPath.c_str());
	this->texture = loadDDS(texture.c_str());
	textureID = glGetUniformLocation(modelProgramID, "myTextureSampler");
	//glGenVertexArrays(1, &this->VertexArrayID);
	//glBindVertexArray(this->VertexArrayID);
	Model = glm::rotate(Model, glm::radians(-90.f), glm::vec3(1,0,0));
	interpID = glGetUniformLocation(modelProgramID, "interp");
	MatrixID = glGetUniformLocation(modelProgramID, "MVP");
	ModelID = glGetUniformLocation(modelProgramID, "M");
	ViewID = glGetUniformLocation(modelProgramID, "V");
	scaledLocation = glGetUniformLocation(modelProgramID, "scaled");
}
md2_model_t::~md2_model_t()
{
	glDeleteTextures(1, &texture);
	//glDeleteVertexArrays(1, &VertexArrayID);
}
static_md2_model_t::~static_md2_model_t()
{
	glDeleteTextures(1, &texture);
	//glDeleteVertexArrays(1, &VertexArrayID);
}

void md2_model_t::Translate(glm::vec3 direction)
{
	Model = glm::translate(Model, direction);
}

void static_md2_model_t::Translate(glm::vec3 direction)
{
	Model = glm::translate(Model, direction);
}

void md2_model_t::Rotate(float angle,glm::vec3 axis)
{
	Model = glm::rotate(Model, angle,axis);
}

void static_md2_model_t::Rotate(float angle, glm::vec3 axis)
{
	Model = glm::rotate(Model, angle, axis);
}

void md2_model_t::Scale(glm::vec3 scale)
{
	Model = glm::scale(Model, scale);
	if (Model != glm::mat4(1.0f))
	{
		scaled = true;
	}
	else
	{
		scaled = false;
	}
}

void static_md2_model_t::Scale(glm::vec3 scale)
{
	Model = glm::scale(Model, scale);
	if (Model != glm::mat4(1.0f))
	{
		scaled = true;
	}
	else
	{
		scaled = false;
	}
}

int md2_model_t::ReadMD2Model(const char* filename,md2_model_t* mdl)
{
    FILE* fp;
    int i;

    fp = fopen(filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
        return 0;
    }

    /* Read header */
    fread(&mdl->header, 1, sizeof(struct md2_header_t), fp);

    if ((mdl->header.ident != 844121161) ||
        (mdl->header.version != 8))
    {
        /* Error! */
        fprintf(stderr, "Error: bad version or identifier\n");
        fclose(fp);
        return 0;
    }

    /* Memory allocations */
    mdl->skins = (struct md2_skin_t*)
        malloc(sizeof(struct md2_skin_t) * mdl->header.num_skins);
    mdl->texcoords = (struct md2_texCoord_t*)
        malloc(sizeof(struct md2_texCoord_t) * mdl->header.num_st);
    mdl->triangles = (struct md2_triangle_t*)
        malloc(sizeof(struct md2_triangle_t) * mdl->header.num_tris);
    mdl->frames = (struct md2_frame_t*)
        malloc(sizeof(struct md2_frame_t) * mdl->header.num_frames);
    mdl->glcmds = (int*)malloc(sizeof(int) * mdl->header.num_glcmds);

    /* Read model data */
    fseek(fp, mdl->header.offset_skins, SEEK_SET);
    fread(mdl->skins, sizeof(struct md2_skin_t),
        mdl->header.num_skins, fp);

    fseek(fp, mdl->header.offset_st, SEEK_SET);
    fread(mdl->texcoords, sizeof(struct md2_texCoord_t),
        mdl->header.num_st, fp);

    fseek(fp, mdl->header.offset_tris, SEEK_SET);
    fread(mdl->triangles, sizeof(struct md2_triangle_t),
        mdl->header.num_tris, fp);

    fseek(fp, mdl->header.offset_glcmds, SEEK_SET);
    fread(mdl->glcmds, sizeof(int), mdl->header.num_glcmds, fp);

    /* Read frames */
    fseek(fp, mdl->header.offset_frames, SEEK_SET);
    for (i = 0; i < mdl->header.num_frames; ++i)
    {
        /* Memory allocation for vertices of this frame */
        mdl->frames[i].verts = (md2_vertex_t*)
            malloc(sizeof(struct md2_vertex_t) * mdl->header.num_vertices);

        /* Read frame data */
        fread(mdl->frames[i].scale, sizeof(vec3_t), 1, fp);
        fread(mdl->frames[i].translate, sizeof(vec3_t), 1, fp);
        fread(mdl->frames[i].name, sizeof(char), 16, fp);
        fread(mdl->frames[i].verts, sizeof(md2_vertex_t),
            mdl->header.num_vertices, fp);
		printf("%s",mdl->frames[i].name);
    }

    fclose(fp);
    return 1;
}

int static_md2_model_t::ReadMD2Model(const char* filename, static_md2_model_t* mdl)
{
	FILE* fp;
	int i;

	fp = fopen(filename, "rb");
	if (!fp)
	{
		fprintf(stderr, "Error: couldn't open \"%s\"!\n", filename);
		return 0;
	}

	/* Read header */
	fread(&mdl->header, 1, sizeof(struct md2_header_t), fp);

	if ((mdl->header.ident != 844121161) ||
		(mdl->header.version != 8))
	{
		/* Error! */
		fprintf(stderr, "Error: bad version or identifier\n");
		fclose(fp);
		return 0;
	}

	/* Memory allocations */
	mdl->skins = (struct md2_skin_t*)
		malloc(sizeof(struct md2_skin_t) * mdl->header.num_skins);
	mdl->texcoords = (struct md2_texCoord_t*)
		malloc(sizeof(struct md2_texCoord_t) * mdl->header.num_st);
	mdl->triangles = (struct md2_triangle_t*)
		malloc(sizeof(struct md2_triangle_t) * mdl->header.num_tris);
	mdl->frames = (struct md2_frame_t*)
		malloc(sizeof(struct md2_frame_t) * mdl->header.num_frames);
	mdl->glcmds = (int*)malloc(sizeof(int) * mdl->header.num_glcmds);

	/* Read model data */
	fseek(fp, mdl->header.offset_skins, SEEK_SET);
	fread(mdl->skins, sizeof(struct md2_skin_t),
		mdl->header.num_skins, fp);

	fseek(fp, mdl->header.offset_st, SEEK_SET);
	fread(mdl->texcoords, sizeof(struct md2_texCoord_t),
		mdl->header.num_st, fp);

	fseek(fp, mdl->header.offset_tris, SEEK_SET);
	fread(mdl->triangles, sizeof(struct md2_triangle_t),
		mdl->header.num_tris, fp);

	fseek(fp, mdl->header.offset_glcmds, SEEK_SET);
	fread(mdl->glcmds, sizeof(int), mdl->header.num_glcmds, fp);

	/* Read frames */
	fseek(fp, mdl->header.offset_frames, SEEK_SET);
	for (i = 0; i < mdl->header.num_frames; ++i)
	{
		/* Memory allocation for vertices of this frame */
		mdl->frames[i].verts = (md2_vertex_t*)
			malloc(sizeof(struct md2_vertex_t) * mdl->header.num_vertices);

		/* Read frame data */
		fread(mdl->frames[i].scale, sizeof(vec3_t), 1, fp);
		fread(mdl->frames[i].translate, sizeof(vec3_t), 1, fp);
		fread(mdl->frames[i].name, sizeof(char), 16, fp);
		fread(mdl->frames[i].verts, sizeof(md2_vertex_t),
			mdl->header.num_vertices, fp);
		printf("%s", mdl->frames[i].name);
	}

	fclose(fp);
	return 1;
}

void md2_model_t::getAnimBounds(std::string animation)
{
	static int frameBounds[2];//the first and last frame 
	for (int i = 0; i < header.num_frames; i++)
	{
		std::string frameName = std::string(frames[i].name);
		frameName.pop_back();
		size_t found = frameName.find(animation);
		if (found !=std::string::npos)
		{
			frameBounds[0] = i;
			break;
		}
	}
	for (int i = frameBounds[0]+1; i < header.num_frames; i++)
	{
		std::string frameName = std::string(frames[i].name);
		size_t found = frameName.find(animation);
		if (found == std::string::npos)
		{
			frameBounds[1] = i-1;
			break;
		}
	}
	this->start = frameBounds[0];
	this->end = frameBounds[1];
	printf("animation start: %i", this->start);
	printf("animation end: %i", this->end);
}

void md2_model_t::generateFrameBuffers()
{
	float zerointerp = 0.f;
	for (int x = 0; x < header.num_frames;x++)
	{
		RenderFrame(x, x, zerointerp, vertices, uvs, normals,false);
		printf("frame rendered to buffers\n");

		GLuint frameVBO;
		glGenBuffers(1, &frameVBO);
		printf("frameVBO buffer created");
		glBindBuffer(GL_ARRAY_BUFFER, frameVBO);
		printf("frameVBO buffer bound");
		glBufferData(GL_ARRAY_BUFFER, (vertices.size()*sizeof(glm::vec3))+ (uvs.size() * sizeof(glm::vec2)) + (normals.size() * sizeof(glm::vec3)), NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, (vertices.size() * sizeof(glm::vec3)), &vertices[0]);
		glBufferSubData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3)), (uvs.size() * sizeof(glm::vec2)), &uvs[0]);
		glBufferSubData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(glm::vec3)) + (uvs.size() * sizeof(glm::vec2)), (normals.size() * sizeof(glm::vec3)), &normals[0]);
		printf("glBufferData completed");
		vbos.push_back(frameVBO);
		printf("frameVBO pushed to vbos array");
	}
}

void md2_model_t::getBuffers(int start, int end, float& interp, bool loop)
{
	/* Check if current is in a valid range */
	if ((current < 0) || (current > header.num_frames - 1))
		return;

	if ((current < start) || ((current > end) && (loop == false)))
		current = start;

	if (interp >= 1.0f)
	{
		/* Move to next frame */
		interp = 0.0f;
		if (current < end)
			current++;
		else if (loop == true)
			current = start;
	}

	currentVBO = vbos[current];
	if (current < end)
		nextVBO = vbos[current + 1];
	else
		nextVBO = vbos[start];

}

void md2_model_t::RenderFrame(int start, int end, float& interp, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, bool loop)
{
    int i, j;
    GLfloat s, t;
	struct md2_frame_t* pframe1, * pframe2;
	struct md2_vertex_t* pvert1, * pvert2;
	float* n_curr, * n_next;
	vec3_t v_curr, v_next, v, norm;

	out_vertices.clear();
	out_uvs.clear();

    /* Check if current is in a valid range */
    if ((current < 0) || (current > header.num_frames - 1))
        return;

	if ((current < start) || ((current > end)&&(loop == false)) )
		current = start;

	if (interp > 1.0f)
	{
		/* Move to next frame */
		interp = 0.0f;
		if (current < end)
			current++;
		else if(loop == true)
			current = start;
	}



    /* Draw the model */
    /* Draw each triangle */
    for (i = 0; i < header.num_tris; ++i)
    {
        /* Draw each vertex */
        for (j = 0; j < 3; ++j)
        {
			pframe1 = &frames[current];
			if (current < end)
				pframe2 = &frames[current + 1];
			else
				pframe2 = &frames[start];
			pvert1 = &pframe1->verts[triangles[i].vertex[j]];
			pvert2 = &pframe2->verts[triangles[i].vertex[j]];

            /* Compute texture coordinates */
            s = (GLfloat)texcoords[triangles[i].st[j]].s / header.skinwidth;
            t = (GLfloat)texcoords[triangles[i].st[j]].t / header.skinheight;

			out_uvs.push_back(glm::vec2(s, t));

			/* Interpolate normals */
			n_curr = anorms_table[pvert1->normalIndex];
			n_next = anorms_table[pvert2->normalIndex];

			norm[0] = n_curr[0] + interp * (n_next[0] - n_curr[0]);
			norm[1] = n_curr[1] + interp * (n_next[1] - n_curr[1]);
			norm[2] = n_curr[2] + interp * (n_next[2] - n_curr[2]);

			out_normals.push_back(glm::vec3(norm[0],norm[1],norm[2]));

            /* Calculate vertex real position */
			v_curr[0] = ((pframe1->scale[0]/2) * pvert1->v[0]) + pframe1->translate[0];
			v_curr[1] = ((pframe1->scale[1] / 2) * pvert1->v[1]) + pframe1->translate[1];
			v_curr[2] = ((pframe1->scale[2] / 2) * pvert1->v[2]) + pframe1->translate[2];

			v_next[0] = ((pframe2->scale[0] / 2) * pvert2->v[0]) + pframe2->translate[0];
			v_next[1] = ((pframe2->scale[1] / 2) * pvert2->v[1]) + pframe2->translate[1];
			v_next[2] = ((pframe2->scale[2] / 2) * pvert2->v[2]) + pframe2->translate[2];

			v[0] = v_curr[0] + interp * (v_next[0] - v_curr[0]);
			v[1] = v_curr[1] + interp * (v_next[1] - v_curr[1]);
			v[2] = v_curr[2] + interp * (v_next[2] - v_curr[2]);
			
			glm::vec3 v_vec3 = glm::vec3(v[0], v[1], v[2]);

			out_vertices.push_back(v_vec3);
        }
    }
}

static_md2_model_t::static_md2_model_t(std::string model, std::string texture, std::string vertexPath, std::string fragmentPath)
{
	ReadMD2Model(model.c_str(), this);
	RenderFrame(0, 1, fakeinterp, temp_vertices, temp_uvs, temp_normals,false);
	indexVBO(temp_vertices, temp_uvs,temp_normals,indices,indexed_vertices,indexed_uvs,indexed_normals);
	modelProgramID = LoadShaders(vertexPath.c_str(), fragmentPath.c_str());
	this->texture = loadDDS(texture.c_str());
	textureID = glGetUniformLocation(modelProgramID, "myTextureSampler");
	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
	Model = glm::rotate(Model, glm::radians(-90.f), glm::vec3(1, 0, 0));//model matrix
	MatrixID = glGetUniformLocation(modelProgramID, "MVP");
	ModelID = glGetUniformLocation(modelProgramID, "M");
	ViewID = glGetUniformLocation(modelProgramID, "V");
	scaledLocation = glGetUniformLocation(modelProgramID, "scaled");
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3),&indexed_vertices[0],GL_STATIC_DRAW);
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

}

void static_md2_model_t::RenderFrame(int start, int end, float& interp, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals, bool loop)
{
	int i, j;
	GLfloat s, t;
	struct md2_frame_t* pframe1;
	struct md2_vertex_t* pvert1;
	float* n_curr;
	vec3_t v_curr, norm;

	out_vertices.clear();
	out_uvs.clear();

	/* Draw the model */
	/* Draw each triangle */
	for (i = 0; i < header.num_tris; ++i)
	{
		/* Draw each vertex */
		for (j = 0; j < 3; ++j)
		{
			pframe1 = &frames[0];
			pvert1 = &pframe1->verts[triangles[i].vertex[j]];

			/* Compute texture coordinates */
			s = (GLfloat)texcoords[triangles[i].st[j]].s / header.skinwidth;
			t = (GLfloat)texcoords[triangles[i].st[j]].t / header.skinheight;

			out_uvs.push_back(glm::vec2(s, t));

			/* Interpolate normals */
			n_curr = anorms_table[pvert1->normalIndex];

			out_normals.push_back(glm::vec3(n_curr[0], n_curr[1], n_curr[2]));

			/* Calculate vertex real position */
			v_curr[0] = ((pframe1->scale[0]) * pvert1->v[0]) + pframe1->translate[0];
			v_curr[1] = ((pframe1->scale[1]) * pvert1->v[1]) + pframe1->translate[1];
			v_curr[2] = ((pframe1->scale[2]) * pvert1->v[2]) + pframe1->translate[2];


			glm::vec3 v_vec3 = glm::vec3(v_curr[0], v_curr[1], v_curr[2]);

			out_vertices.push_back(v_vec3);
		}
	}
}

void md2_model_t::Draw(Camera camera)
{

	//glBindVertexArray(this->VertexArrayID);
	glUseProgram(modelProgramID);
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = camera.getProjectionMatrix();
	glm::mat4 mvp = projection * view *Model;

	//Send tranformation to shader in MVP transform; done in mainloop because every model has different mvp matrix
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);
	glUniform1f(interpID, interp);
	glUniform1i(scaledLocation,scaled);
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);


	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, currentVBO);
	glVertexAttribPointer(
		0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, currentVBO);
	glVertexAttribPointer(
		1,
		2,//size means size of groups in the array. vertexes have x,y,z so they have size 3. uv's only have x and y (u & v), so size 2
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(vertices.size() * sizeof(glm::vec3))
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, currentVBO);
	glVertexAttribPointer(
		2,
		3,//size means size of groups in the array. vertexes have x,y,z so they have size 3. uv's only have x and y (u & v), so size 2
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)((vertices.size() * sizeof(glm::vec3)) + (uvs.size() * sizeof(glm::vec2)))
	);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, nextVBO);
	glVertexAttribPointer(
		3, // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, nextVBO);
	glVertexAttribPointer(
		4,
		2,//size means size of groups in the array. vertexes have x,y,z so they have size 3. uv's only have x and y (u & v), so size 2
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)(vertices.size() * sizeof(glm::vec3))
	);

	glEnableVertexAttribArray(5);
	glBindBuffer(GL_ARRAY_BUFFER, nextVBO);
	glVertexAttribPointer(
		5,
		3,//size means size of groups in the array. vertexes have x,y,z so they have size 3. uv's only have x and y (u & v), so size 2
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)((vertices.size() * sizeof(glm::vec3)) + (uvs.size() * sizeof(glm::vec2)))
	);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);

}

void static_md2_model_t::Draw(Camera camera)
{

	glUseProgram(modelProgramID);
	glm::mat4 view = camera.getViewMatrix();
	glm::mat4 projection = camera.getProjectionMatrix();
	glm::mat4 mvp = projection * view * Model;

	//Send tranformation to shader in MVP transform; done in mainloop because every model has different mvp matrix
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &Model[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &view[0][0]);
	glUniform1i(scaledLocation,scaled);
	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,
		2,//size means size of groups in the array. vertexes have x,y,z so they have size 3. uv's only have x and y (u & v), so size 2
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,
		3,//size means size of groups in the array. vertexes have x,y,z so they have size 3. uv's only have x and y (u & v), so size 2
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	
	//glBindVertexArray(this->VertexArrayID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

void md2_model_t::Animate(std::string anim, bool loop, float deltaTime,float speed)
{
	if (anim != currentAnim)
	{
		getAnimBounds(anim);
		this->currentAnim = anim;
		this->current = this->start;
	}
	getBuffers(this->start,this->end,this->interp,loop);
	interp += speed*deltaTime;
}