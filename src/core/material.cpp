#include "sge/core/material.h"

#include "sge/core/create_texture.h"
#include "sge/core/texture_unit.h"

namespace sge { namespace core {

Material::Material(
  std::shared_ptr<Texture> albedo_texture,
  std::shared_ptr<Texture> roughness_texture,
  std::shared_ptr<Texture> R0_texture,
  std::shared_ptr<Texture> metalness_texture,
  std::shared_ptr<Texture> normal_texture)
{
  _albedo_texture     = albedo_texture    ? albedo_texture    : CreateTexture::white(2,2);
  _roughness_texture  = roughness_texture ? roughness_texture : CreateTexture::white(2,2);
  _R0_texture         = R0_texture        ? R0_texture        : CreateTexture::white(2,2);
  _metalness_texture  = metalness_texture ? metalness_texture : CreateTexture::black(2,2);
  _normal_texture     = normal_texture    ? normal_texture    : CreateTexture::black(2,2);

  _albedo_texture->upload();
  _roughness_texture->upload();
  _R0_texture->upload();
  _metalness_texture->upload();
  _normal_texture->upload();
}

Material::~Material()
{
  
}

void Material::use(GLuint programId)
{
  TextureUnit
    tex_unit_albedo,
    tex_unit_roughness,
    tex_unit_R0,
    tex_unit_metalness,
    tex_unit_normal;
  
  // Activate tex units and bind them to corresponding textures
  tex_unit_albedo.activate();
  _albedo_texture->bind();
  tex_unit_roughness.activate();
  _roughness_texture->bind();
  tex_unit_R0.activate();
  _R0_texture->bind();
  tex_unit_metalness.activate();
  _metalness_texture->bind();
  tex_unit_normal.activate();
  _normal_texture->bind();

  glUniform1i(glGetUniformLocation(programId, "albedo_texture"),    tex_unit_albedo);
  glUniform1i(glGetUniformLocation(programId, "roughness_texture"), tex_unit_roughness);
  glUniform1i(glGetUniformLocation(programId, "R0_texture"),        tex_unit_R0);
  glUniform1i(glGetUniformLocation(programId, "metalness_texture"), tex_unit_metalness);
  glUniform1i(glGetUniformLocation(programId, "normal_texture"),    tex_unit_normal);
}

} }
