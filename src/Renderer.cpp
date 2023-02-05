#include "Renderer.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace engine
{
	Renderer::Renderer(Camera& camera, Shader& shader) : mActiveCamera(camera), mShader(shader)
	{
        
	}

    void Renderer::Begin(Shader& shader)
    {
        mShader = shader;

        mShader.Bind();

        mShader.SetUniformMat4("view_projection", mActiveCamera.GetViewProjectionMatrix());

        mShader.SetUniformVec3("ambientColor", glm::vec3(0.4, 0.4, 0.4));
        mShader.SetUniformVec3("lightColor", glm::vec3(1.0, 1.0, 1.0));
        mShader.SetUniformVec3("lightDirection", glm::vec3(0, -1, -1));

        mShader.SetSamplerTextureUnit("tex", 0);
    }

    void Renderer::Draw(const Mesh& mesh, const Texture& texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		glm::mat4 model{ 1 };
	    model = glm::translate(model, position);
		model = glm::scale(model, scale);

        model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        mShader.SetUniformMat4("model", model);

        texture.UseTextureUnit(0);

        texture.Bind();
        mesh.Bind();

        glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);

        mesh.Unbind();
        texture.Unbind();
	}

    void Renderer::End()
    {

    }
}

