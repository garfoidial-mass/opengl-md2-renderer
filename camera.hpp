#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(GLFWwindow* window,float fov,float aspectRatio,float nearPlane,float farPlane);
	~Camera();

	float fov;
	float aspectRatio;
	float nearPlane;
	float farPlane;
	GLFWwindow* window;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;

	//camera Position
	glm::vec3 position = glm::vec3(0, 0, 0);
	//horizontal angle towards -Z
	float horizontalAngle = 3.14f;
	//vertical angle : look at horizon
	float verticalAngle = 0.f;
	glm::vec3 direction;
	glm::vec3 right;
	float speed = 20.0f;//camera movement speed
	float mouseSpeed = 3.0f; //mouse sensitivity

	void computeMatricesFromInputs();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};

#endif