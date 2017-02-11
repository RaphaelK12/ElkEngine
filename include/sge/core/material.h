#pragma once

#include "sge/core/texture.h"

#include <memory>

namespace sge { namespace core {

class Material
{
public:
  Material(
    std::shared_ptr<Texture> albedo_texture     = nullptr,
    std::shared_ptr<Texture> roughness_texture  = nullptr,
    std::shared_ptr<Texture> R0_texture        = nullptr,
    std::shared_ptr<Texture> metalness_texture  = nullptr,
    std::shared_ptr<Texture> normal_texture     = nullptr);
  ~Material();

  void use(GLuint programId);
  
private:
  std::shared_ptr<Texture> _albedo_texture;
  std::shared_ptr<Texture> _roughness_texture;
  std::shared_ptr<Texture> _R0_texture;
  std::shared_ptr<Texture> _metalness_texture;
  std::shared_ptr<Texture> _normal_texture;
};

} }