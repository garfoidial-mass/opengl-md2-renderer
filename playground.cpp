#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <common/controls.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/camera.hpp>
#include <common/Md2.h>

float TARGET_FPS = 60;

GLFWwindow* window; // rendering window

int main()
{
	glewExperimental = true;
	if (!glfwInit())
	{
		fprintf(stderr, "failed to initialize glfw");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);//4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//set version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macos
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//new opengl
	window = glfwCreateWindow(1920, 1080, "Opengl Tutorial", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open glfw window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//init glew
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to init GLEW");
		return -1;
	}

	int windowWidth = 1920;
	int windowHeight = 1080;
	int renderWidth = 1280;
	int renderHeight = 720;
	// But on MacOS X with a retina screen it'll be 1024*2 and 768*2, so we get the actual framebuffer size:
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//create vertex array object and set it as current
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	//compile and link shaders
	GLuint ProgramID = LoadShaders("standardShadingRTT.vertexshader", "standardShadingRTT.fragmentshader");
	md2_model_t model("data\\pepsi\\tris.md2","data\\pepsi\\pepsi.dds", "standardShadingRTT.vertexshader", "standardShadingRTT.fragmentshader");
	static_md2_model_t model2("data\\room.md2","data\\roomtex.dds", "standardShadingRTTStatic.vertexshader", "standardShadingRTT.fragmentshader");
	//md2_model_t gunmodel("data\\weapons\\v_chain\\tris.md2", "data\\weapons\\v_chain\\skin.dds", "standardShadingRTT.vertexshader", "standardShadingRTT.fragmentshader");
	Camera camera(window,70.0f,float(renderWidth/renderHeight),0.1f,100.0f);
	//get handle for texture sampler
	GLuint textureID = glGetUniformLocation(ProgramID, "myTextureSampler");

	GLuint LightPosID = glGetUniformLocation(ProgramID, "LightPosition_worldspace");
	GLuint LightColorID = glGetUniformLocation(ProgramID, "LightColor");
	GLuint LightPowerID = glGetUniformLocation(ProgramID, "LightPower");
	
	//model.Scale(vec3(0.5f, 0.5f, 0.5f));
	model2.Scale(vec3(7.f,7.f,7.f));
	//gunmodel.Translate(vec3(20, 20, 20));
	//model2.Translate(vec3(40,0,0));

	// ---------------------------------------------
	// Render to Texture - specific code begins here
	// ---------------------------------------------

	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" means "empty" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderWidth, renderHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, renderWidth, renderHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

	//// Alternative : Depth texture. Slower, but you can sample it later in your shader
	//GLuint depthTexture;
	//glGenTextures(1, &depthTexture);
	//glBindTexture(GL_TEXTURE_2D, depthTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	//// Depth texture alternative : 
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);


	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		return false;


	// The fullscreen quad's FBO
	static const GLfloat g_quad_vertex_buffer_data[] = {
		1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,

	};

	GLuint quad_vertexbuffer;
	glGenBuffers(1, &quad_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Create and compile our GLSL program from the shaders
	GLuint quad_programID = LoadShaders("Passthrough.vertexshader", "normaltexture.fragmentshader");
	GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
	GLuint timeID = glGetUniformLocation(quad_programID, "time");
	//model matrix (identity matrix because model is at origin)
	//Model = translate(Model,vec3(-2,0,-2));

	vec3 lightColor = vec3(0.0f, 0.0f, 1.0f);
	float lightPower = 50.0f;
	vec3 lightPos = vec3(20.0f, 0.0f, 0.0f);

	//these variables used to count performance
	double msFrameLast = glfwGetTime();

	do
	{
		// Render to our framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, renderWidth, renderHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static double last_time = glfwGetTime();
		double current_time = glfwGetTime();
		double deltaTime = current_time - last_time;
		printf("%f ", deltaTime * 1000.0);

		//glUniform3f(LightPosID, lightPos.x, lightPos.y, lightPos.z);
		//glUniform3f(LightColorID, lightColor.x, lightColor.y, lightColor.z);
		//glUniform1f(LightPowerID, lightPower);

		camera.computeMatricesFromInputs();
		model.Animate("run", true, (float)deltaTime, 2);
		//gunmodel.Animate("idle", true, (float)deltaTime, 2);
		model.Draw(camera);
		model2.Draw(camera);
		//gunmodel.Draw(camera);

		// Render to the screen
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		if((float)renderWidth/ (float)renderHeight != 16.0f/9.0f)
			glViewport((windowWidth - (renderWidth * (windowHeight / renderHeight))) / 2, 0, renderWidth * (windowHeight / renderHeight), windowHeight);
		else
			glViewport(0,0,1920,1080);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(quad_programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		// Set our "renderedTexture" sampler to use Texture Unit 0
		glUniform1i(texID, 0);

		glUniform1f(timeID, (float)(glfwGetTime() * 10.0f));

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangles !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

		glDisableVertexAttribArray(0);

		//swap buffers
		glfwSwapBuffers(window);
		glfwWaitEvents();
		/*
		while (glfwGetTime() < msFrameLast + 1.0 / TARGET_FPS) {
			// TODO: Put the thread to sleep, yield, or simply do nothing
		}
		msFrameLast += 1.0 / TARGET_FPS;
		*/
		

		last_time = current_time;
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteProgram(ProgramID);
	glDeleteVertexArrays(1, &VertexArrayID);
	glfwTerminate();
}