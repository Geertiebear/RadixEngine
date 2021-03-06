#ifndef RADIX_COMPONENT_TRANSFORM_HPP
#define RADIX_COMPONENT_TRANSFORM_HPP

#include <radix/component/Component.hpp>
#include <radix/core/math/Vector3f.hpp>
#include <radix/core/math/Quaternion.hpp>
#include <radix/core/math/Matrix4f.hpp>

namespace radix {

class Transform : public Component {
protected:
  Vector3f position, scale;
  Quaternion orientation;

public:
  inline void privSetPosition(const Vector3f &v) {
    position = v;
  }
  inline void privSetScale(const Vector3f &v) {
    scale = v;
  }
  inline void privSetOrientation(const Quaternion &v) {
    orientation = v;
  }

  Transform(Entity &ent) :
    Component(ent), scale(1, 1, 1) {}

  const char* getName() const {
    return "Transform";
  }

  TypeId getTypeId() const {
    return Component::getTypeId<std::remove_reference<decltype(*this)>::type>();
  }

  void serialize(serine::Archiver&);

  inline const Vector3f& getPosition() const {
    return position;
  }
  void setPosition(const Vector3f&);

  inline const Vector3f& getScale() const {
    return scale;
  }
  void setScale(const Vector3f&);

  inline const Quaternion& getOrientation() const {
    return orientation;
  }
  void setOrientation(const Quaternion&);

  void applyModelMtx(Matrix4f&) const;
  void getModelMtx(Matrix4f&) const;
};

} /* namespace radix */

#endif /* RADIX_COMPONENT_TRANSFORM_HPP */
