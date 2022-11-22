#include "RenderComponent.h"

RenderComponent::RenderComponent(GameObject* _gameObject, Simple3DShader* _shader):Component(_gameObject, "render")
{
	shader = _shader;
}
RenderComponent::RenderComponent(GameObject* _gameObject, Simple3DShader* _shader, const char* modelPath) : Component(_gameObject, "render")
{
	shader = _shader;
	model = new Model(modelPath);
}

void RenderComponent::render(Camera* cam)
{
	if (!enable)return;
	glm::mat4 projectionMatrix = cam->GetProjectionMatrix();
	glm::mat4 viewMatrix = cam->GetViewMatrix();

	shader->setProjectionMatrix(projectionMatrix);
	shader->setViewMatrix(viewMatrix);
	shader->setModelMatrix(gameObject->getLocalToGlobalMatrix());
	shader->Use();

	model->Draw(*shader);
	glUseProgram(0);
}