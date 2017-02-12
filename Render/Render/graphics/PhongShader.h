#pragma once

#include <string>

#include "Shader.h"
#include "Texture.h"
#include "LightStructs.h"

namespace ginkgo {

	class PhongShader : public Shader
	{
	private:
		//glm::vec4 ambientLight = glm::vec4(0.1f, 0.1f, 0.1f, 0.1f);
		glm::vec4 ambientLight; //should be static
		//DirectionalLight directionalLight = { .base = {.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .intensity = 0 }, .direction = glm::vec3(1.0f, 1.0f, 1.0f) };
		DirectionalLight directionalLight; //should be static
		const int MAX_POINT_LIGHTS = 4;
		std::vector<PointLight> pointLights;
		
	public:
		PhongShader();
		void updateUniforms(glm::mat4& model, glm::mat4& projectionMatrix, Texture& texture, glm::vec3& cameraPosition);

		inline glm::vec4& getAmbientLight() { return ambientLight; }
		inline void setAmbientLight(const glm::vec4& ambientLight) { this->ambientLight = ambientLight; }

		void setPointLights(const std::vector<PointLight>& pointLights);
				
		inline DirectionalLight& getDirectionalLight() { return directionalLight; }
		void setDirectionalLight(const DirectionalLight& directionalLight);
		
		void setUniform(const std::string& name, DirectionalLight& directionalLight);
		void setUniform(const std::string& name, BaseLight& baseLight);
		void setUniform(const std::string& name, PointLight& pointLight);
	};


}