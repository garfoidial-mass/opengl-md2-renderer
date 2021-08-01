//include glm

#include "camera.hpp"
using namespace glm;

//projection and view matrices

mat4 Camera::getViewMatrix()
{
	return ViewMatrix;
}
mat4 Camera::getProjectionMatrix()
{
	return ProjectionMatrix;
}

//up in world coordinates
vec3 worldUp(0, 1, 0);

Camera::Camera(GLFWwindow* window, float fov, float aspectRatio, float nearPlane, float farPlane)
{
	this->window = window;
	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	ProjectionMatrix = perspective(radians(this->fov), this->aspectRatio, this->nearPlane, this->farPlane);
}

Camera::~Camera()
{

}

void Camera::computeMatricesFromInputs()
{
	//time between last and current frame
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	//calculate fov based on scroll wheel

	double xpos, ypos;
	//get mouse position on screen
	glfwGetCursorPos(window, &xpos, &ypos);
	//center mouse
	glfwSetCursorPos(window, width / 2, height / 2);

	//compute orientation
	horizontalAngle += mouseSpeed * deltaTime/5 * float(width/2 - xpos);
	verticalAngle += mouseSpeed * deltaTime/5 * float(height / 2 - ypos);
	verticalAngle = clamp(verticalAngle,30.0f,33.0f);

	direction = vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	//right vector
	right = vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14/2.0f)
	);
	//up vector in camera's local coords: perpendicular to right and front
	vec3 up = cross(right, direction);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += direction * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= direction * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += right * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= right * deltaTime * speed;
	}


	ViewMatrix = lookAt(
		position,
		position + direction,
		up
	);

	lastTime = currentTime;
}