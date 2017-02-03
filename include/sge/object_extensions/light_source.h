#pragma once

#include "sge/core/object_3d.h"
#include "sge/core/new_mesh.h"
#include "sge/core/camera.h"

#include <vector>
  
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace sge { namespace core {

class DeferredShadingRenderer;

class PointLightSource : public Object3D
{
public:
  PointLightSource(glm::vec3 color, float radiant_flux);
  ~PointLightSource() {};
  virtual void submit(DeferredShadingRenderer& renderer) override;
  virtual void render(const PerspectiveCamera& camera);

  void setRadiantFlux(float radiant_flux);
  void setColor(glm::vec3 color);
private:
  void renderQuad(const PerspectiveCamera& camera);
  void renderSphere(const PerspectiveCamera& camera);
  void setupLightSourceUniforms(const PerspectiveCamera& camera);

  std::shared_ptr<NewMesh> _quad_mesh;
  std::shared_ptr<NewMesh> _sphere_mesh;

  float _sphere_scale;

  glm::vec3 _color;
  float     _radiant_flux;
};

class DirectionalLightSource : public Object3D
{
public:
  DirectionalLightSource(glm::vec3 color, float radiance);
  ~DirectionalLightSource() {};
  virtual void submit(DeferredShadingRenderer& renderer) override;
  virtual void render(const PerspectiveCamera& camera);

  void setRadiance(float radiance);
  void setColor(glm::vec3 color);
private:
  void setupLightSourceUniforms(const PerspectiveCamera& camera);

  std::shared_ptr<NewMesh> _quad_mesh;
  
  glm::vec3 _color;
  float     _radiance;
};

} }