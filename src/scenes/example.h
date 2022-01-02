#pragma once

#include "core/scene.h"

#include "ogl/shader.h"
#include "ogl/vao.h"

#include <memory>

class ExampleScene : public Scene
{
public:
	void start() override;
	void update(const float dt) override;

private:
	std::shared_ptr<Shader> shader;
	std::shared_ptr<VAO> vao;

	float m_Alpha = 0.2f;
};