#pragma once

#include <jni.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <pthread.h>

class GlRenderer
{
private:
  bool _isRunning;

  //{@ egl
  EGLConfig  _eglConfig;
  EGLContext _eglContext;
  EGLSurface _eglSurface;
  EGLDisplay _eglDisplay;

  EGLContext _eglSharedContext;
  //}@ egl


  //{@ threading
  void RunMainThread();
  void RunUpdateThread();

  static void * _runMainThread(void * thiz);
  static void * _runUpdateThread(void * thiz);

  pthread_attr_t _attrs;
  pthread_t _mainThread;
  pthread_t _updateThread;

  pthread_cond_t _cond;
  pthread_mutex_t _mutex;
  //}@ threading

  //{@ openGl
  GLuint _bufferId;
  GLuint _programId;
  GLuint _vao;
  //}@

public:
  int width;
  int height;
  bool doLogUpdate;
  bool doLogDraw;
  bool doUpdate;

  GlRenderer()
    : _isRunning(false),
      _eglConfig(NULL),
      _eglContext(EGL_NO_CONTEXT),
      _eglSurface(EGL_NO_SURFACE),
      _eglDisplay(EGL_NO_DISPLAY),
      _eglSharedContext(EGL_NO_CONTEXT),
      _mainThread(0),
      _updateThread(0),
      _bufferId(0),
      _programId(0),
      _vao(0),
      width(400),
      height(400),
      doLogUpdate(false),
      doLogDraw(false),
      doUpdate(false)
    {}

  ~GlRenderer()
  {
    Stop();
  }

  void Start();
  void Stop();
  void SetUpEgl(EGLConfig  eglConfig,  EGLContext eglContext,
                EGLSurface eglSurface, EGLDisplay eglDisplay);

  void Init();
  void Draw();
  void Update();

  GLuint LoadShader(const char * shaderSrc, GLenum type);
  void   LinkProgram();
};
