#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Defs.h>

class Shader
{
public:
	Shader();
	Shader(const char* VertexShaderName, const char* FragmentShaderName);
	~Shader();
	// Active le Shader pour le rendu
	void use();
	// D�sactive le Shader pour le rendu
	void stopUse();

	// Fonctions utilitaires pour la gestions des variables de Shader, �quivoques.
	// name est le nom de la variable dans le Shader
	// Envoie un bool�en au shader
	void SetBool(const std::string& name, bool value) const;
	// Envoie un int au shader
	void SetInt(const std::string& name, int value) const;
	// Envoie un float au shader
	void SetFloat(const std::string& name, float value) const;
	// Envoie la couleur au shader
	void SetColor(Color color);
	// Envoie un vec4 de float au shader
	void SetVec4f(std::string name, float x, float y, float z, float w);
	// Envoie un vec3 de float au shader
	void SetVec3f(std::string name, float x, float y, float z);
	// Envoie un vec2 de float au shader
	void SetVec2f(std::string name, float x, float y);
	// Envoie un ivec2(int) au shader
	void SetVec2i(std::string name, int x, int y);
	// Envoie une mat4 de float au shader
	void SetMat4(std::string name, glm::mat4 matrix);

	unsigned int ID;
protected:
	//Compile un Shader
	unsigned int CompileShader(const char* fileName, int type);
	//Lie un shader � son identifiant
	unsigned int LinkProgramShader(GLuint vertexShader, GLuint fragmentShader);
};



class ComputeShader: public Shader
{
public:
	ComputeShader(std::vector<std::string> );
	ComputeShader(const char* );

	void CheckCompileError(GLuint compute);
	void CreateProgram(GLuint compute);
};

