#define STB_IMAGE_IMPLEMENTATION
#include "headers.h"
extern int main_camera(int argc, char** argv);
extern int use_camera_class_main(int argc, char** argv);
int main(int argc, char** argv)
{
	return use_camera_class_main(argc, argv);
}