#include <Shader.h>
#include <stdio.h>
#include <string>

using namespace std;

void getFileContent(const char* fileName, string* returnedContent) {
	FILE* file;
	fopen_s(&file, fileName, "r");
	if (!file) {
		printf("Failed to open Shader file !\n");
		return;
	}
	char buffer[2000];
	fseek(file, 0, 0);
	string content;
	while (fgets(buffer, 2000, file) != NULL) {
		content += buffer;
	}
	*returnedContent = content;
}

Shader::Shader():ID(0)
{
}

Shader::Shader(const char* VertexShaderName, const char* FragmentShaderName)
{
	ID = LinkProgramShader(CompileShader(VertexShaderName, GL_VERTEX_SHADER), CompileShader(FragmentShaderName, GL_FRAGMENT_SHADER));
}

Shader::~Shader()
{
}


unsigned int Shader::CompileShader(const char* fileName, int type) {
	string Source;
	getFileContent(fileName, &Source);
	const char* ShaderSource = Source.c_str();
	unsigned int Shader = glCreateShader(type);
	glShaderSource(Shader, 1, &ShaderSource, NULL);
	glCompileShader(Shader);
	int  success;
	char infoLog[512];
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		if(type == GL_VERTEX_SHADER)
			printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s\n", infoLog);
		if(type == GL_FRAGMENT_SHADER)
			printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s\n", infoLog);
	}
	return Shader;
}

unsigned int Shader::LinkProgramShader(GLuint vertexShader, GLuint fragmentShader) {
	unsigned int last_shaderProgram = glCreateProgram();
	glAttachShader(last_shaderProgram, vertexShader);
	glAttachShader(last_shaderProgram, fragmentShader);
	glLinkProgram(last_shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(last_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(last_shaderProgram, 512, NULL, infoLog);
		printf("Failed to create shader program:\n %s\n", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return last_shaderProgram;
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::stopUse()
{
	glUseProgram(0);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetColor(Color color)
{
	glUniform3f(glGetUniformLocation(ID, "color"), color.r, color.g, color.b);
}

void Shader::SetVec4f(std::string name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.data()), x, y, z, w);
}

void Shader::SetVec3f(std::string name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.data()), x, y, z);
}

void Shader::SetVec2f(std::string name, float x, float y)
{
	glUniform2f(glGetUniformLocation(ID, name.data()), x, y);
}

void Shader::SetVec2i(std::string name, int x, int y)
{
	glUniform2i(glGetUniformLocation(ID, name.data()), x, y);
}

void Shader::SetMat4(std::string name, glm::mat4 matrix)
{
	// Active la matrice dans le shader
	glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, glm::value_ptr(matrix));
}



ComputeShader::ComputeShader(const char* computePath):Shader()
{
	unsigned int compute;

	string Source;
	getFileContent(computePath, &Source);
	const char* ShaderSource = Source.c_str();
	// compute shader
	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, 1, &ShaderSource, NULL);
	glCompileShader(compute);
	CheckCompileError(compute);
	CreateProgram(compute);

	
}


void ComputeShader::CheckCompileError(GLuint compute) {
	int  success;
	char infoLog[512];
	glGetShaderiv(compute, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(compute, 512, NULL, infoLog);
		printf("ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n %s\n", infoLog);
	}
}

void ComputeShader::CreateProgram(GLuint compute) {
	int  success;
	char infoLog[512];
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, compute);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		printf("Failed to create compute shader program:\n %s\n", infoLog);
	}
	glDeleteShader(ID);
}



ComputeShader::ComputeShader(std::vector<std::string> files) :Shader()
{
	unsigned int compute;
	std::vector<std::string> sources(files.size());
	std::vector<const char*> sources_cstr(files.size());
	for (size_t i = 0; i < files.size(); i++) {
		getFileContent(files[i].c_str(), &sources[i]);
		printf("%s", sources[i].c_str());
		sources_cstr[i] = sources[i].c_str();
	}
	// compute shader
	compute = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(compute, sources_cstr.size(), sources_cstr.data(), NULL);
	glCompileShader(compute);
	CheckCompileError(compute);
	CreateProgram(compute);
}

