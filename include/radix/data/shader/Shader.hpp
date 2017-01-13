#ifndef RADIX_SHADER_HPP
#define RADIX_SHADER_HPP

#include <string>
#include <map>

namespace radix {

class Shader {
public:
  enum Type {
    Vertex,
    Fragment,
    Geometry
  };

  Shader(unsigned int handle) : handle(handle) { }
  void bind() const;
  void release() const;

  unsigned int handle;

  int uni(const std::string&);
  int att(const std::string&);
private:

  std::map<std::string, int> locationMap;
};

} /* namespace radix */

#endif /* RADIX_SHADER_HPP */
