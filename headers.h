#ifndef HEADERS_
#define HEADERS_

#include <iostream>
#include <numbers>
#include <filesystem>
#include <vector>
#include <memory>
#include <io.h>
#include <random>
#include <glad/glad.h>
#include <sys/types.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>

#include "MyShader.h"
#include "vertices.h"
#include "Camera.h"

#define VERTEX_BIND_TARGET GL_ARRAY_BUFFER

#endif // !HEADERS_
