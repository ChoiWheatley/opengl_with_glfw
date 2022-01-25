#include "headers.h"

static float deltaTime = .0f;
static float lastFrame = .0f;
// 따로 데이터 객체들만 떨어뜨려야 하는 이유: window size가 바뀔 때 콜백함수에서 안전하게 
// 데이터만을 변경할 수 있어야 한다.
static const auto projection = std::make_shared<Projection>(
	Constants::Camera::aspectRatio,
	Constants::Camera::near,
	Constants::Camera::far,
	Constants::Camera::fov
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


static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static int render_loop(Camera* camera, GLFWwindow* window);

int use_camera_class_main(int argc, char** argv)
{
	GLuint VBO, VAO;
	MyShader* myShader;
	Camera* myCamera;
	GLint imgWidth[2], imgHeight[2], nrChannels[2];
	unsigned char* imageData[2];
	GLFWwindow* window;
	GLuint texture[2];

	/*random rotation generator*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-180.f, 180.f);
	std::vector< float > angle(Constants::cubePositions.size(), 0.f);
	std::vector< glm::vec3 > axis(Constants::cubePositions.size(), 
		glm::vec3(0.f,0.f,0.f));
	for (float& i : angle)
		i = dis(gen);
	for (glm::vec3& i : axis)
		i = glm::vec3(dis(gen), dis(gen), dis(gen));

	/*image loading*/
	stbi_set_flip_vertically_on_load(true);
	for (int i = 0; i < 2; i++) {
		const char* filename = Constants::Texture::textureFileNames[i].c_str();
		imageData[i] = stbi_load(filename,&imgWidth[i], &imgHeight[i], &nrChannels[i], 0);
		if (!imageData[i]) {
			std::cout << "Failed to load texture (" << filename << ")\n";
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
	framebuffer_size_callback(window, windowWidth, windowHeight);


	// # Shader
	// ------------------------------------------------
	// shader must be initialized AFTER glfw window has
	// initialized and configured.
	myShader = new MyShader(Constants::Shader::vertexPath, Constants::Shader::fragmentPath);


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
			Constants::Texture::textureColorFormats[i], GL_UNSIGNED_BYTE,	/*format of source image file*/
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



	// # Camera
	// -----------------------------------------------------------------------------
	// Camera 객체가 대부분의 인터페이스만을 남기고 몽땅 추상화했다.
	// 과연 실제 코드에서 사용 시 어떤 변화가 있는지 알아보자.
	//
	myCamera = new Camera(
		projection,
		ViewMatrix(
			CameraPos(
				Constants::Camera::initPosition,
				Constants::Camera::translationSpeed
			),
			CameraFront(
				Constants::Camera::rotationSpeed,
				Constants::Camera::initYaw,
				Constants::Camera::initPitch
			),
			CameraUp(
				Constants::Camera::initUp
			)
		));



	/*Let us draw them all!*/
	return render_loop(myCamera, window);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	projection.aspectRatio = (float)width / (float)height;
}// void framebuffer_size_callback()

int render_loop(Camera* camera, GLFWwindow* window)
{
	while(!glfwWindowShouldClose(window)) {
	}
	return 0;
}
