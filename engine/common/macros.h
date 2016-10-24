#ifndef BELLUM_MACROS_H
#define BELLUM_MACROS_H

#define DELETE_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName& copy) = delete; \
  TypeName operator=(const TypeName& copy) = delete

#define DEFINE_EXCEPTION(Name, What) \
  class Name : public std::exception { \
  private: std::string msg_; \
  public: \
  Name() : msg_(What) {} \
  Name(const std::string& msg) : msg_(msg) {  } \
  const char* what() const throw() override { \
      return msg_.c_str(); \
  } \
  }

#endif

#define GL_CHECK() \
  { GLenum err = glGetError(); \
  if (err != GL_NO_ERROR) { \
    std::cerr << "OpenGL error '" << err << "', at " << __FILE__ << ":" << __LINE__ << std::endl;\
    std::exit(1); \
  } }
