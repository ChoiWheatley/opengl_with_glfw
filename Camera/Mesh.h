#pragma once
#include <memory>
#include "Node.h"
#include "ShaderI.h"
#include "VertexI.h"
#include "TextureI.h"
#include "Matrix4.h"

/**
 * \brief Mesh defines visible object in the graphics world
 * - ShaderI : encapsulate shader code, mediate uniform variable
 * - TextureI : take care of image and activate-bind texture gl object
 * - VertexI : Vertex Array Object and Vertex Buffer Object
 * Mesh itself has pure abstract interface, which can be implemented by User
 */
class Mesh : public Node
{
public: // interfaces
	virtual glm::mat4 getCoordSpace() override;
	/**
	 * \brief User가 직접 구현하는 인터페이스
	 */
	virtual void draw() const = 0;


public: // constructor
	Mesh(
		std::unique_ptr<ShaderI> shader,
		std::unique_ptr<TextureI> texture,
		std::unique_ptr<VertexI> vertex
	);
	~Mesh() override;

protected: // member
	std::unique_ptr<ShaderI> shader_;
	std::unique_ptr<TextureI> texture_;
	std::unique_ptr<VertexI> vertex_;
	std::unique_ptr<Matrix4> matrix_;

protected: // method
	static glm::mat4 getMatrix(const Matrix4& matrix);

};



