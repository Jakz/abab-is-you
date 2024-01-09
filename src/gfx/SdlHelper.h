#pragma once

#include "Common.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

#include <cstdint>
#include <cstdio>
#include <cassert>

using u32 = uint32_t;

class Director
{
public:
  virtual void render() = 0;
  virtual void handle(const events::KeyEvent& event) = 0;
  virtual void handle(const events::MouseEvent& event) = 0;
  virtual size2d_t windowSize() const = 0;
};

class SDL
{
protected:
  Director* _director;

  SDL_Window* _window;
  SDL_Renderer* _renderer;

  bool willQuit;
  u32 ticks;
  float _lastFrameTicks;

  u32 frameRate;
  float ticksPerFrame;


public:
  SDL(Director* director) : _director(director), _window(nullptr), _renderer(nullptr), willQuit(false), ticks(0)
  {
    setFrameRate(60);
  }

  void setFrameRate(u32 frameRate)
  {
    this->frameRate = frameRate;
    this->ticksPerFrame = 1000 / (float)frameRate;
  }

  float lastFrameTicks() const { return _lastFrameTicks; }

  bool init();
  void deinit();
  void capFPS();

  void loop();
  void handleEvents();

  size2d_t getWindowSize()
  {
    int w, h;
    SDL_GetWindowSize(_window, &w, &h);
    return { w, h };
  }

  void exit() { willQuit = true; }

  void blit(const Texture* texture, const rect_t& src, int dx, int dy);
  void blit(const Texture* texture, const rect_t& src, const rect_t& dest);

  void blit(const Texture* texture, int sx, int sy, int w, int h, int dx, int dy);
  void blit(const Texture* texture, int sx, int sy, int w, int h, int dx, int dy, int dw, int dh);
  void blit(const Texture* texture, int dx, int dy);
  void blit(const Texture* texture, color_t color, const rect_t& src, const rect_t& dest);

  void drawRect(int x, int y, int w, int h, color_t color);
  void fillRect(int x, int y, int w, int h, color_t color);
  void line(int x1, int y1, int x2, int y2, color_t color);
  void clear(color_t color);

  void fillRect(const rect_t& rect, color_t color) { fillRect(rect.x, rect.y, rect.w, rect.h, color); }
  void drawRect(const rect_t& rect, color_t color) { drawRect(rect.x, rect.y, rect.w, rect.h, color); }

  void blit(const Surface* src, const rect_t* srcRect, const Surface* dest, const rect_t* destRect);

  Texture* loadImage(const path& path);
  Texture* buildTexture(const Surface& surface);
  Surface loadImageAsSurface(const path& path);
  Surface generateSurface(size2d_t size);

  SDL_Window* window() { return _window; }
  SDL_Renderer* renderer() { return _renderer; }
};
