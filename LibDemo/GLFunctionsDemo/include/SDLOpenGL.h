#ifndef SDLOPENGL_H__
#define SDLOPENGL_H__
#include <SDL.h>
#include <string>

/// \author Jon Macey
/// Modified by Kate Edge to include Maths Library
/// \version 1.0
/// \date 13/3/17 \n

class SDLOpenGL
{
  public :
    SDLOpenGL(const std::string &_name, int _x, int _y, int _width, int _height);

    void makeCurrent() { SDL_GL_MakeCurrent(m_window,m_glContext);}
    void swapWindow() { SDL_GL_SwapWindow(m_window); }

    void pollEvent(SDL_Event &_event);


  private :
    /// @brief width of screen
    int m_width;
    /// @brief height of screen
    int m_height;
    // xpos of window
    int m_x;
    // ypos of window
    int m_y;
    // name of window
    std::string m_name;

    void init();

    SDL_GLContext m_glContext;
    void createGLContext();

    void ErrorExit(const std::string &_msg) const;

    SDL_Window *m_window;

};

#endif
