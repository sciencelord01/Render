#include "Shader.h"
#include "../../utils/FileUtils.h"


namespace ginkgo {

	Shader::Shader()
	{
		program = glCreateProgram();
	}

	Shader::~Shader()
	{
		glDeleteProgram(program);
	}

	void Shader::addVertexShader(const char* file)
	{
		addProgram(file, GL_VERTEX_SHADER);
	}

	void Shader::addGeometryShader(const char* file)
	{
		addProgram(file, GL_GEOMETRY_SHADER);
	}

	void Shader::addFragmentShader(const char* file)
	{
		addProgram(file, GL_FRAGMENT_SHADER);
	}

	void Shader::addProgram(const char* file, GLenum type)
	{
		GLuint shaderID = glCreateShader(type);

		std::string shaderSourceString = FileUtils::read_file(file);
		const char* shaderSource = shaderSourceString.c_str();

		if (shaderID == 0)
		{
			std::cout << "Shader creation failed: Could not find valid memory location when adding shader" << std::endl;
			system("pause");
			return;
		}

		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);

		GLint result;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(shaderID, length, &length, &error[0]);
			std::cout << "Failed to compile shader!\tType of Shader: " << type << std::endl << &error[0] << std::endl;
			glDeleteShader(shaderID);
			system("pause");
			return;
		}

		glAttachShader(program, shaderID);
		shaders.push_back(shaderID);
	}
	
	void Shader::compileShader() const
	{
		glLinkProgram(program);

		GLint success; GLchar infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			system("PAUSE");
		}

		glValidateProgram(program);

		for (unsigned int i = 0; i < shaders.size(); i++)
			glDeleteShader(shaders[i]);
	}


	GLuint Shader::load(const char* vertexShader, const char* fragShader) const
	{
		GLuint program = glCreateProgram();
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

		//use c_str() like this so string is not immediately destroyed and pointer is not able to be found
		std::string vertSourceString = FileUtils::read_file(vertexShader);
		std::string fragSourceString = FileUtils::read_file(fragShader);

		const char* vertSource = vertSourceString.c_str();
		const char* fragSource = fragSourceString.c_str();

		//*********Vertex Shader
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		GLint result;
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertex, length, &length, &error[0]);
			std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(vertex);
			system("pause");
			return EXIT_FAILURE;
		}

		//*********Fragment Shader
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			GLint length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragment, length, &length, &error[0]);
			std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
			glDeleteShader(fragment);
			system("pause");
			return EXIT_FAILURE;
		}
		std::cout << "Program: " << program << std::endl;
		std::cout << "Vertex Shader: " << vertex << std::endl;
		std::cout << "Fragment Shader: " << fragment << std::endl;

		glAttachShader(program, vertex);
		glAttachShader(program, fragment);

		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return program;
	}

	void Shader::bind() const
	{
		glUseProgram(program);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar* name) const
	{
		return glGetUniformLocation(program, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value) const
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar* name, float* value, int count) const
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1iv(const GLchar* name, int* value, int count) const
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar* name, int value) const
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector) const
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}
	void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector) const
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector) const
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

}