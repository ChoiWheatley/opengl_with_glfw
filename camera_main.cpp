/**
* TRANSFORMATION
* - basic understanding of vector and matrices
* - 
* reference: https://learnopengl.com/Getting-started/Transformations
*/
#include "headers.h"

static const GLchar* vertexPath = "vertex.vert";
static const GLchar* fragmentPath = "fragment.frag";
static GLsizei windowWidth;
static GLsizei windowHeight;
static GLfloat deltaTime = .0f; // Time between current frame and last frame
static GLfloat lastFrame = .0f; // Time of last frame
GLfloat cameraYaw = -90.f;
GLfloat cameraPitch = 0.f;


//glm::mat4 transformation;
static glm::mat4 world_trans(1.f), camera_trans(1.f), projection_trans(1.f);
static glm::vec3 cameraPos, cameraFront, cameraUp;
static GLfloat cameraFOV = 45.f; 
static GLfloat cameraAspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
static GLfloat cameraNear = .1f, cameraFar = 100.f;


static const char* textureFileNames[] = {
	"signup.jpg",
	"png_with_alpha_channel.png"
};
static const GLuint textureColorFormats[] = {
	GL_RGB, GL_RGBA
};
static constexpr short polygonCnt = sizeof(MyVert::vertices) / sizeof(float) / 5;

static const std::vector< glm::vec3 > cubePositions = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};


static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void processInput(GLFWwindow* window);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static inline void arcball_roatation(const glm::vec2 & newPos, const glm::vec2 & oldPos, int width, int height);
static inline glm::vec3 get_arcball_vector(float x, float y, int width, int height);
static inline glm::vec3 get_arcball_vector(const glm::vec2 & pos, int width, int height);
static inline void mouse_translation(const glm::vec2& newPos, const glm::vec2& oldPos);
static inline glm::vec3 camera_rotate(const glm::vec2& newPos, const glm::vec2& oldPos);
std::ostream& operator<< (std::ostream& os, const glm::vec2& vec2);
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3);


int main_camera(int argc, char** argv)
{
	GLuint VBO, VAO;
	MyShader* myShader;
	GLint imgWidth[2], imgHeight[2], nrChannels[2];
	unsigned char* imageData[2];
	GLuint texture[2];
	// random rotation generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-180.f, 180.f);
	std::vector< float > angle(cubePositions.size(), 0.f);
	std::vector< glm::vec3 > axis(cubePositions.size(), 
		glm::vec3(0.f,0.f,0.f));
	for (float& i : angle)
		i = dis(gen);
	for (glm::vec3& i : axis)
		i = glm::vec3(dis(gen), dis(gen), dis(gen));















	// image loading 
	// -------------------------------------------------------
	stbi_set_flip_vertically_on_load(true);
	for (int i = 0; i < 2; i++) {
		imageData[i] = stbi_load(textureFileNames[i],
			&imgWidth[i], &imgHeight[i], &nrChannels[i], 0);
		if (!imageData[i]) {
			std::cout << "Failed to load texture (" << textureFileNames[i] << ")\n";
			exit(1);
		}
	}









	//# Initialize and configure )
	//------------------------------------------------------
	// initialize glfw library, configuring with glfw version
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create a glfw window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	// window viewport should be adjusted when window size is changed.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// before call opengl functions, tell GLAD to manage function pointers
	// for OpenGL.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD\n";
		exit(EXIT_FAILURE);
	}
	// before we can start rendering we have to tell OpenGL the size
	// of the rendering window (ViewPort) so OpenGL knows how we want to
	// display the data and coords with respect to the window.
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	framebuffer_size_callback(window, WINDOW_WIDTH, WINDOW_HEIGHT);








	// # Shader
	// ------------------------------------------------
	// shader must be initialized AFTER glfw window has
	// initialized and configured.
	myShader = new MyShader(vertexPath, fragmentPath);

















	//# VAO and VBO
	//-------------------------------------------
	// Create and Bind Vertex Buffer Object and Vertex Array Object.
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	// copy our vertices array in a VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVert::vertices), MyVert::vertices, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret the vertex data.
	glVertexAttribPointer(
		0					/*position*/
		, 3					/*size*/
		, GL_FLOAT			/*type*/
		, GL_FALSE			/*if we want the data to be normalized*/
		, 5 * sizeof(float)	/*stride*/
		, (void*)0			/*offset*/
	);		
	glEnableVertexAttribArray(0);		/*layout (location = 0) in aPos*/
	glVertexAttribPointer(
		1								/*position*/
		, 3								/*size in number of components*/
		, GL_FLOAT						/*type*/
		, GL_FALSE						/*normalized*/
		, 5 * sizeof(float)				/*stride in bytes*/
		, (void*)(3 * sizeof(float))	/*offset in bytes*/
	);
	glEnableVertexAttribArray(1);		/*layout (location = 1) in aTexCoord*/
	// unbind buffers and arrays
	glBindBuffer(VERTEX_BIND_TARGET, 0);
	glBindVertexArray(0);











	// # Textures
	// ------------------------------------------------------
	for (int i = 0; i < 2;  i++) {
		glGenTextures(1, &texture[i]);
		// activate texture before bind texture
		glActiveTexture(GL_TEXTURE0 + i);
		// bind texture object into subsequent texture commands
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		// set the texture wrapping options. it wraps when the canvas is too large
		// that the texture cannot cover it at once. Specifying repeat, mirrored repeat,
		// clamp to edge, or clamp to border options can set the texture wrapping method.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set the texture filtering options. OpenGL must figure out what pixel value
		// to be landing on floating point position of texture coordinate.
		// You can specify those filtering options as nearest pixel value or linearly
		// interpolated value. 
		// Texture filtering can be set for magnifying and minifying operations, so 
		// you have to specify both filtering options each.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// generating a texture using the previously loaded image data.
		glTexImage2D(GL_TEXTURE_2D,
			0,							/*minimap level*/
			GL_RGB, imgWidth[i], imgHeight[i],		/*attribute of texture*/
			0,							/*not used. legacy stuff*/
			textureColorFormats[i], GL_UNSIGNED_BYTE,	/*format of source image file*/
			imageData[i]				/*the actual image data*/
		);
		glGenerateMipmap(GL_TEXTURE_2D);	/*automatically generate minimap levels for
											the currently bound texture image of the
										active texture unit.*/
		// let us free image memory
		stbi_image_free(imageData[i]);
		// tell opengl for sample to which texture unit it belongs to
		myShader->useShaderProgram();
		myShader->setInt("texture"+std::to_string(i), i);
	}
	



















	// Camera Operation
	// --------------------------------------------------------------
	// Camera itself has its own coordinate system, which reverses the entire
	// viewing matrix. Camera need at least two vectors
	// 1. direction axis : camera would see world coord's specific point, reverse
	//		the direction of what it is targeting. It represents as z-axis of 
	//		the camera space.
	// 2. right axis :  right vector that represents the positive x-axis of the 
	//		camera space.
	// How about the last y-axis vector? it is cross producted with z and x axis.
	// Finally, we can make `LookAt` matrix that proves very useful for creating 
	// a camera.
	// Thankfully, glm already made this trivial works for users. We only need to
	// specify three vectors
	// 1. camera position
	// 2. target position
	// 3. up vector
	//
	cameraPos = glm::vec3(0.f, 0.f, 0.f);
	//cameraFront = glm::vec3(0.f, 0.f, -1.f);
	cameraUp = glm::vec3(0.f, 1.f, 0.f);









	//# render loop, let it draw until explicit stop signal
	//-------------------------------------------------
	while (!glfwWindowShouldClose(window)) {
		// every loop == every frame
		// Have to check out delta time between frames
		float currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//** input check
		processInput(window);

		// rendering commands down here
		glClearColor(.2f, .3f, .3f, 1.f);
		// Enabling depth testing and clearing previous depth buffer
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Matrix Multiplication
		// --------------------------------------------------------
		// Homogeneous Coordinate (4x4) matrix which can manipulate 
		// target vector into desired position.
		// Lookout when you gonna imply multiple transformations using
		// matrix multiplications, which takes in a flipped order
		// because of the multiplying order.
		// For example, when you want to make a matrix which scales half
		// and then rotate as 90 degrees, first take rotation and then
		// take scaling is the correct order.
		//
		//projection_trans = glm::mat4(1.f);
		projection_trans = glm::perspective(
			glm::radians(cameraFOV),		/*field of view, width of the 
											perspective frustum*/
			cameraAspectRatio,				/*aspect ratio*/
			cameraNear,						/*nearest view*/
			cameraFar						/*farthest view*/
		);
		camera_trans = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		// 4. register all those matrices into vertex shader's 
		//	  uniform variables
		myShader->setMatrix4fv("world", world_trans);
		myShader->setMatrix4fv("camera", camera_trans);
		myShader->setMatrix4fv("projection", projection_trans);




		//** Let us draw them all
		for (int i = 0; i < 2; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
		}
		myShader->useShaderProgram();
		glBindVertexArray(VAO);
		// draw all cubes
		// render boxes
		for (size_t i = 0; i < cubePositions.size(); i++) {
			// calculate the model matrix for each object and pass it to shader
			// before drawing
			glm::mat4 model(1.f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, 
				glm::radians(angle[i]), 
				axis[i]);
			myShader->setMatrix4fv("model", model);

			glDrawArrays(GL_TRIANGLES, 0, polygonCnt);
		}
		glBindVertexArray(0);	

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//# Program Termination Process
	//	de-allocate all resources once they've outlived their purpose.  
	//-------------------------------------------------------- 
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete myShader;

	// when we exit the render loop, we would like to properly clean
	// and delete of GLFW's resources that were allocated.
	glfwTerminate();

	exit(EXIT_SUCCESS);
}// int main()

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, windowWidth, windowHeight);
	cameraAspectRatio = static_cast<GLfloat>(windowWidth) / static_cast<GLfloat>(windowHeight);
}// void framebuffer_size_callback()

static void processInput(GLFWwindow* window)
{
	GLfloat cameraSpeed = 2.4f * deltaTime;
	glm::vec3 cameraRight = -glm::normalize(glm::cross(cameraFront, cameraUp));

	// Keyboard Escape
	// ------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Keyboard W,A,S,D to move around
	// ------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed *= 3.f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraRight;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraRight;


	// Mouse Capture
	// --------------------------------------------------
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	// Mouse Scroll Capture
	// --------------------------------------------------
	glfwSetScrollCallback(window, scroll_callback);
}
/// <summary>
/// This callback function tells GLFW to listen mouse movement events.
/// left mouse drag = camera yaw and pitch
/// right mouse drag = arcball rotation to world space
/// </summary>
/// <param name="xpos">:current mouse position in x value</param>
/// <param name="ypos">:current mouse position in y value</param>
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static glm::vec2 oldPos = glm::vec2(0.f, 0.f);
	const glm::vec2 newPos = glm::vec2(xpos, ypos);
	static bool firstMouse = true;
	int width, height;

	glfwGetWindowSize(window, &width, &height);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		// when mouse right click was pressed 
		if (firstMouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			oldPos = newPos;
			firstMouse = false;
		}
		arcball_roatation(newPos, oldPos, width, height);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		// when mouse left click was pressed
		if (firstMouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			oldPos = newPos;
			firstMouse = false;
		}
		//mouse_translation(glm::vec2(xpos, ypos), oldPos);
		cameraFront = camera_rotate(newPos, oldPos);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
		// when mouse right click was released
		firstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
		// when mouse left click was released
		firstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	oldPos = newPos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cameraFOV -= (float)yoffset;
	if (cameraFOV < 1.f)
		cameraFOV = 1.f;
	if (cameraFOV >= 90.f)
		cameraFOV = 90.f;
}

/// Rotate WOLRD SPACE by using mouse right click and drag
/// 1. transform screen coord into world coordinate
/// 2. find two vectors `OP1` and `OP2`
/// 3. calc angle between OP1 and OP2 from the center which
///		is defined in camera target
/// 4. get rotation axis using cross product
/// 5. set world coordinate matrix rotate
inline void arcball_roatation(const glm::vec2 & newPos, const glm::vec2 & oldPos, int width, int height)
{
	const static GLfloat rotation_speed = 1.5f;
	if (newPos == oldPos)
		return;
	glm::vec3 vOldDelta, vCurDelta;
	glm::vec3 axis_in_camera_coord;
	GLfloat angle;

	vOldDelta = get_arcball_vector(oldPos, width, height);
	vCurDelta = get_arcball_vector(newPos, width, height);

	angle = glm::acos(fmin(1.f, glm::dot(vOldDelta, vCurDelta)));
	axis_in_camera_coord = glm::cross(vOldDelta, vCurDelta);

	// converting the rotation axis from camera coord to world coordinates.
	// so that the entire world space will rotate, while camera don't
	glm::mat4 camera2World = glm::inverse(world_trans);
	glm::vec4 axis_in_world_coord = camera2World * glm::vec4(axis_in_camera_coord, 0.f);
	world_trans = glm::rotate(world_trans, 
		rotation_speed * angle, 
		glm::vec3(axis_in_world_coord));
}

/// <summary>
/// Map screen coord into sphere coord
/// </summary>
/// <returns>sphere coord</returns>
inline glm::vec3 get_arcball_vector(float x, float y, int width, int height)
{
	glm::vec3 P = glm::vec3(
		x / width * 2 - 1.f,
		y / height * 2 - 1.f,
		0.f
	);
	P.y = -P.y;		
	float OP_squared = P.x * P.x + P.y * P.y;
	if (OP_squared <= 1.f)
		P.z = glm::sqrt(1.f - OP_squared);
	else
		P = glm::normalize(P);
	return P;
}

inline glm::vec3 get_arcball_vector(const glm::vec2 & pos, int width, int height)
{
	return get_arcball_vector(pos.x, pos.y, width, height);
}

inline void mouse_translation(const glm::vec2& newPos, const glm::vec2& oldPos)
{
	static const float translate_speed = 0.01f;
	glm::vec2 mouseDelta = newPos - oldPos;
	//std::cerr << __func__ << "mouseDelta: " << mouseDelta << "\r";

	glm::vec3 translation(mouseDelta.x, -mouseDelta.y, 0.f);

	camera_trans = glm::translate(camera_trans, translation * translate_speed);
}

inline glm::vec3 camera_rotate(const glm::vec2& newPos, const glm::vec2& oldPos)
{
	constexpr GLfloat sensitivity = 0.1f;
	const glm::vec2 mouseDelta = (newPos - oldPos) * sensitivity;
	cameraYaw += mouseDelta.x;
	cameraPitch -= mouseDelta.y;

	if (cameraPitch > 89.f)
		cameraPitch = 89.f;
	if (cameraPitch < -89.f)
		cameraPitch = -89.f;

	return glm::normalize(
		glm::vec3{
		cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch)),
		sin(glm::radians(cameraPitch)),
		sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch))
	});
}

std::ostream& operator<<(std::ostream& os, const glm::vec2& vec2)
{
	os << "(" << vec2.x << ", " << vec2.y << ")";
	return os;
}
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec3)
{
	os << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
	return os;
}
