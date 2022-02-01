#include "headers.h"
#include "MyShader.h"
#include "vertices.h"
#include "Camera.h"
#include "Constants.h"
#include "Structures.h"


namespace Global {
	static float deltaTime = .0f;
	static float lastFrame = .0f;
	static constexpr short polygonCnt = sizeof(MyVert::vertices) / sizeof(float) / 5;
	static glm::mat4 worldMatrix{ 1.f };

	// 따로 데이터 객체들만 떨어뜨려야 하는 이유: 데이터가 바뀔 때 안전하게 
	// 데이터만을 변경할 수 있어야 한다.
	static const auto projection = std::make_shared<Projection>(
		Constants::Camera::aspectRatio,
		Constants::Camera::near,
		Constants::Camera::far,
		Constants::Camera::fov,
		Constants::Camera::fovMin,
		Constants::Camera::fovMax
		);
	static const auto cameraPos = std::make_shared<CameraPos>(
		Constants::Camera::initPosition,
		Constants::Camera::translationSpeed
		);
	static const auto cameraFront = std::make_shared<CameraFront>(
		Constants::Camera::rotationSpeed,
		Constants::Camera::initYaw,
		Constants::Camera::initPitch
		);
	static const auto cameraUp = std::make_shared<CameraUp>(
		Constants::Camera::initUp
		);

}



static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static int render_loop(std::shared_ptr<Camera> camera, std::shared_ptr<MyShader> shader, GLFWwindow* window, const Structure::RenderState& renderState);
static inline const glm::mat4 make_box_matrix(const glm::vec3 pos, const float angle, const glm::vec3 axis);
static void processInput(GLFWwindow* window, std::shared_ptr<Camera> camera);
static void keyboard_state(GLFWwindow* window);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static const glm::mat4 arcball_rotation(const glm::vec2& newPos, const glm::vec2& oldPos, int width, int height);
static inline const glm::vec3 get_arcball_vector(float x, float y, int width, int height);
static inline const glm::vec3 get_arcball_vector(const glm::vec2& pos, int width, int height);
static std::ostream& operator<< (std::ostream& os, const glm::vec2& vec2);
static std::ostream& operator<< (std::ostream& os, const glm::vec3& vec3);



int use_camera_class_main(int argc, char** argv)
{
	GLuint VBO, VAO;
	std::shared_ptr<MyShader> myShader;
	std::shared_ptr<Camera> myCamera;
	std::vector<int> imgWidth(2,0), imgHeight(2,0), nrChannels(2,0);
	std::vector<unsigned char *> imageData(2, nullptr);
	GLFWwindow* window;
	static auto cubePosition = std::vector<glm::vec3>( Constants::cubePositions );
	static auto cubeAngle = std::vector<float>(Constants::cubePositions.size(), 0.f);
	static auto cubeAxis = std::vector<glm::vec3>(Constants::cubePositions.size(), glm::vec3(0.f,0.f,0.f));
	std::vector<unsigned int> texture(2, 0);

	/*random rotation generator*/
	std::cout << "Random Rotation/Axis Generator ...";
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-180.f, 180.f);
	for (float& i : cubeAngle)
		i = dis(gen);
	for (glm::vec3& i : cubeAxis)
		i = glm::vec3(dis(gen), dis(gen), dis(gen));
	std::cout << "Success\n";

	/*image loading*/
	std::cout << "Image Loading ...";
	stbi_set_flip_vertically_on_load(true);
	for (int i = 0; i < Constants::textures.size(); i++) {
		const char* filename = Constants::textures[i].textureFileName.c_str();
		imageData[i] = stbi_load(filename, &imgWidth[i], &imgHeight[i], &nrChannels[i], 0);
		if (!imageData[i]) {
			std::cout << "Failed to load texture (" << filename << ")\n";
			exit(1);
		}
	}
	std::cout << "Success\n";
	//# Initialize and configure )
	//------------------------------------------------------
	// initialize glfw library, configuring with glfw version
	std::cout << "Initialize glfw windowing manager ...";
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// create a glfw window
	window = glfwCreateWindow(Constants::windowWidth, Constants::windowHeight, Constants::windowName.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	// window viewport should be adjusted when window size is changed.
	/// 별개의 콜백함수 안에서 지역변수/객체에 접근할 수 없다. 전역변수
	/// 말고는 답이 없는걸까?
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
	framebuffer_size_callback(window, Constants::windowWidth, Constants::windowHeight);
	std::cout << "Success\n";


	// # Shader
	// ------------------------------------------------
	// shader must be initialized AFTER glfw window has
	// initialized and configured.
	std::cout << "Creating Shader ...";
	myShader = std::make_shared<MyShader>(Constants::Shader::vertexPath, Constants::Shader::fragmentPath);
	std::cout << "Success\n";


	//# VAO and VBO
	//-------------------------------------------
	// Create and Bind Vertex Buffer Object and Vertex Array Object.
	std::cout << "Creating VAO and VBO...";
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
	std::cout << "Success\n";




	// # Textures
	// ------------------------------------------------------
	std::cout << "Textures ...";
	for (int i = 0; i < Constants::textures.size();  i++) {
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
			Constants::textures[i].textureColorFormat, GL_UNSIGNED_BYTE,	/*format of source image file*/
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
	std::cout << "Success\n";



	// # Camera
	// -----------------------------------------------------------------------------
	// Camera 객체가 대부분의 인터페이스만을 남기고 몽땅 추상화했다.
	// 과연 실제 코드에서 사용 시 어떤 변화가 있는지 알아보자.
	// 참고: projection, cameraPos, cameraFront, cameraUp 모두 shared pointer로 들어간다.
	// 즉, 여기서 값을 바꾸면 camera도 바뀐 값으로 처리를 할 거란 얘기다.
	//
	std::cout << "Initializing Camera Object ...";
	myCamera = std::make_shared<Camera>(
		Global::projection,
		std::make_shared<ViewMatrix>(
			Global::cameraPos,
			Global::cameraFront,
			Global::cameraUp
		)
	);
	std::cout << "Success\n";

	/*Let it draw them all!*/
	// 전역변수는 쓰지말자
	Structure::RenderState renderState{
		.cubePositions = cubePosition, 
		.cubeAxis = cubeAxis, 
		.cubeAngles = cubeAngle, 
		.textures = texture, 
		.VAO = VAO
	};
	if (render_loop(myCamera, myShader, window, renderState) == EXIT_SUCCESS) {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		myCamera.reset();
		myShader.reset();
		glfwTerminate();

		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

/**
* 윈도우 사이즈가 변경되는 경우, Projection 객체에 aspect ratio 값을 변경할 것을 요구해야 한다.
*/
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Global::projection->aspectRatio = (float)width / (float)height;
}// void framebuffer_size_callback()

/*
* render loop가 기존에 main 함수로부터 떨어져나왔기 때문에 필요한 데이터를 파라메터로 넣어주어야 하는 수고가 필요하다.
* 그래서 RenderState라는 구조체를 활용했다. 이 구조체 안에는 const 변수만 들어가도록 했다.
*/
static int render_loop(std::shared_ptr<Camera> camera, std::shared_ptr<MyShader> shader, GLFWwindow* window, const Structure::RenderState& renderState)
{
	while(!glfwWindowShouldClose(window)) {
		// check delta time between frames
		float currentFrame = (float)glfwGetTime();
		Global::deltaTime = currentFrame - Global::lastFrame;
		Global::lastFrame = currentFrame;

		// input check
		processInput(window, camera);

		// rendering commands
		glClearColor(.2f, .3f, .3f, 1.f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader->setMatrix4fv("view", camera->getViewMatrix());
		shader->setMatrix4fv("projection", camera->getProjectionMatrix());
		shader->setMatrix4fv("world", Global::worldMatrix);

		// draw boxes
		for (auto i = 0; i < renderState.textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, renderState.textures[i]);
		}
		shader->useShaderProgram();
		glBindVertexArray(renderState.VAO);
		for (size_t i = 0; i < renderState.cubePositions.size(); i++) {
			shader->setMatrix4fv("model", make_box_matrix(
				renderState.cubePositions[i],
				glm::radians(renderState.cubeAngles[i]),
				renderState.cubeAxis[i]
			));
			glDrawArrays(GL_TRIANGLES, 0, Global::polygonCnt);
		}
		glBindVertexArray(0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}
static inline const glm::mat4 make_box_matrix(const glm::vec3 pos, const float angle, const glm::vec3 axis) 
{
	glm::mat4 ret(1.f);
	ret = glm::translate(ret, pos);
	ret = glm::rotate(ret, angle, axis);
	return ret;
}
static void processInput(GLFWwindow* window, std::shared_ptr<Camera> camera)
{
	// Keyboard Escape = close window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Examine keyboard state
	keyboard_state(window);

	// register callback functions specific event from input devices
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}
/*
* CameraPos의 값을 변경한다. qweasd + left shift 조합으로 상하좌우전후 움직일 수 있다.
*/
static inline void keyboard_state(GLFWwindow* window)
{
	using namespace Global;
	const auto front = Global::cameraFront->getVector();
	const auto up = Global::cameraUp->getVector();
	const auto right = glm::normalize(glm::cross(front, up));

	auto offset = glm::vec3{ 0.f, 0.f, 0.f };
	float translationSpeed = cameraPos->speed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) ==  GLFW_PRESS)
		translationSpeed *= 3.f;
	if (glfwGetKey(window, GLFW_KEY_Q) ==  GLFW_PRESS) {
		offset += translationSpeed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_W) ==  GLFW_PRESS) {
		offset += translationSpeed * front;
	}
	if (glfwGetKey(window, GLFW_KEY_E) ==  GLFW_PRESS) {
		offset += translationSpeed * (-up);
	}
	if (glfwGetKey(window, GLFW_KEY_A) ==  GLFW_PRESS) {
		offset += translationSpeed * (-right);
	}
	if (glfwGetKey(window, GLFW_KEY_S) ==  GLFW_PRESS) {
		offset += translationSpeed * (-front);
	}
	if (glfwGetKey(window, GLFW_KEY_D) ==  GLFW_PRESS) {
		offset += translationSpeed * right;
	}

	cameraPos->addVec(offset);
}
/*
* left mouse drag = look around with camera yaw and pitch
* right mouse drag = arcball rotation to world space
*/
static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static glm::vec2 oldPos{ 0.f, 0.f };
	static bool firstMouse = true;
	const glm::vec2 newPos{ xpos, ypos };
	const auto width = std::make_unique<int>(0) ;
	const auto height = std::make_unique<int>(0) ;

	glfwGetWindowSize(window, width.get(), height.get());

	/*left mouse pressed*/
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		if (firstMouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			oldPos = newPos;
			firstMouse = false;
		}
		auto delta = newPos - oldPos;
		Global::cameraFront->addYaw(delta.x);
		Global::cameraFront->addPitch(-delta.y);
	}
	/*right mouse pressed*/
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		if (firstMouse) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			oldPos = newPos;
			firstMouse = false;
		}
		Global::worldMatrix = arcball_rotation(newPos, oldPos, *width, *height);
	}
	/*left mouse released*/
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
		firstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	/*right mouse released*/
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
		firstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	oldPos = newPos;
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Global::projection->addFOV((float)-yoffset);
}
/*
* 윈도우 크기의 가상의 원을 가지고 강체 회전 변환행렬을 생성한다.
* 1. transform view coord into world coordinate
* 2. find two vectors `OP1` and `OP2`
* 3. calculate angle between OP1 and OP2 from the center which
*	 is defined in camera target
* 4. get rotation axis using cross product
* 5. get rotation matrix
*/
static const glm::mat4 arcball_rotation(const glm::vec2& newPos, const glm::vec2& oldPos, int width, int height)
{
	if (newPos == oldPos)
		return Global::worldMatrix;
	const auto vOldDelta = get_arcball_vector(oldPos, width, height);
	const auto vNewDelta = get_arcball_vector(newPos, width, height);
	const float angle = glm::acos(fmin(1.f, glm::dot(vOldDelta, vNewDelta)));
	const glm::vec3 axisInViewCoord = glm::cross(vOldDelta, vNewDelta);

	// converting the rotation axis from view coord to world coords.
	const glm::mat4 viewToWorld = glm::inverse(Global::worldMatrix);
	const glm::vec4 axisInWorldCoord = viewToWorld * glm::vec4(axisInViewCoord, 1.f);

	return glm::rotate(Global::worldMatrix,
		Constants::arcballRotationSpeed * angle,
		glm::vec3(axisInWorldCoord)
	);
}
/*
* Map screen vector into sphere vector
*/
static inline const glm::vec3 get_arcball_vector(float x, float y, int width, int height)
{
	// screen 정중앙을 [0,0,0]으로 두었을 때 [x,y,0] 벡터를 OP 라고 하자.
	// x, y는 screen의 왼쪽 상단을 0으로 두기 때문에 변환과정이 필요함.
	// 원점으로부터의 상대적인 거리를 계산한다. x,y=[-1,1] 구간
	// 원 크기를 두 배로 늘렸다. 스크린 두 배 크기의 원으로 돌리면 정규화할
	// 일이 많지 않을 것이다.
	width *= 2;
	height *= 2;
	glm::vec3 P{
		2 * x / width - .5f,
		2 * y / height - .5f,
		0.f
	};
	P.y = -P.y;
	const float OP_squared = P.x * P.x + P.y * P.y;
	// constraint for imaginary number
	if (OP_squared > 1.f)
		P = glm::normalize(P);
	else
		P.z = glm::sqrt(1.f - OP_squared);
	return P;
}
static inline const glm::vec3 get_arcball_vector(const glm::vec2& pos, int width, int height)
{
	return get_arcball_vector(pos.x, pos.y, width, height);
}
static std::ostream& operator<< (std::ostream& os, const glm::vec2& vec2)
{
	os << "(" << vec2.x << ", " << vec2.y << ")";
	return os;
}
static std::ostream& operator<< (std::ostream& os, const glm::vec3& vec3)
{
	os << "(" << vec3.x << ", " << vec3.y << ", " << vec3.z << ")";
	return os;
}
