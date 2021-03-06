#pragma once

#include "elk/core/object_3d.h"
#include "elk/core/mesh.h"
#include "elk/core/camera.h"

#include <vector>
  
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace elk { namespace core {

class Renderer;

class PointLightSource : public Object3D
{
public:
  PointLightSource(glm::vec3 color, float radiant_flux);
  ~PointLightSource() {};
  virtual void submit(Renderer& renderer) override;
  virtual void update(double dt) override;
  void render(const UsefulRenderData& render_data);

  void setRadiantFlux(float radiant_flux);
  void setColor(glm::vec3 color);
private:
  void renderQuad(const UsefulRenderData& render_data);
  void renderSphere(const UsefulRenderData& render_data);
  void setupLightSourceUniforms(const UsefulRenderData& render_data);

  std::shared_ptr<Mesh> _quad_mesh;
  std::shared_ptr<Mesh> _sphere_mesh;

  float _sphere_scale;

  glm::vec3 _color;
  float     _radiant_flux;
};

class DirectionalLightSource : public Object3D
{
public:
  DirectionalLightSource(glm::vec3 color, float radiance);
  ~DirectionalLightSource() {};
  virtual void submit(Renderer& renderer) override;
  virtual void update(double dt) override;
  void render(const UsefulRenderData& render_data);

  void setRadiance(float radiance);
  void setColor(glm::vec3 color);
private:
  void setupLightSourceUniforms(const UsefulRenderData& render_data);

  std::shared_ptr<Mesh> _quad_mesh;
  
  glm::vec3 _color;
  float     _radiance;
};

} }
