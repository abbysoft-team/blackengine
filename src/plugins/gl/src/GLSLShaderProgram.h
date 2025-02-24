//
// Created by popof on 22.04.2018.
//

#ifndef BLACKENGINE_GLSLSHADERPROGRAM_H
#define BLACKENGINE_GLSLSHADERPROGRAM_H

#include "OpenGLCommonHeaders.h"
#include <shader/ShaderProgram.h>

namespace black {

class Shader;

/**
 * GLSL Shader program
 */
class GLSLShaderProgram : public ShaderProgram {
  static size_t ERROR_BUFFER_LENGTH;

  GLuint program;
public:
  GLSLShaderProgram(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

  virtual ~GLSLShaderProgram();

  void link() override;
  void use() override;

  void setUniformVariable(const std::string &name, int value) override;

  void setUniformVariable(const std::string &name, float value) override;

  void setUniformVariable(const std::string &name, bool value) override;

  void setUniformVariable(const std::string &name, double value) override;

  void setUniformVariable(const std::string &name, std::array<float, 4> value) override;

  void setUniformVariable(const std::string &name, std::array<float, 3> value) override;

  void setUniformVariable(const std::string &name, std::array<float, 2> value) override;

  void setUniformVariable(const std::string &name, glm::mat4 matrix) override;

  void setUniformVariable(const std::string &name, glm::vec3 vector) override;

  void setUniformVariable(const std::string &name, glm::vec4 vector) override;

private:
  bool isLinkedSuccessfully();
  std::string getLinkError();
};
}

#endif //BLACKENGINE_GLSLSHADERPROGRAM_H
