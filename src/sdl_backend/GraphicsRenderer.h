// -*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/*
 * Copyright (C) 2014 Brandon Schaefer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
 */

#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include "StringTextureCreator.h"
#include "StringTextureData.h"

#include <SDL2/SDL.h>

#include <string>

namespace sdl_backend
{

class GraphicsRenderer
{
public:
  GraphicsRenderer();
  ~GraphicsRenderer();

  void Init(std::string title, int width, int height);

  SDL_Window*   Window()   const;
  SDL_Renderer* Renderer() const;

  int Width() const;
  int Height() const;

  void SetRenderColor(SDL_Color const& color);

private:
  void InitWindow(std::string title);
  void InitRenderer();

  int width_;
  int height_;

  SDL_Window*   window_;
  SDL_Renderer* renderer_;
};

} // sdl_backend

#endif // GRAPHICS_RENDERER_H
