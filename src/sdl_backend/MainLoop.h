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

#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "GraphicsRenderer.h"
#include "World.h"

#include <string>

namespace sdl_backend
{

class MainLoop
{
public:
  MainLoop(std::string title, int width, int height);
  ~MainLoop();

  void StartMainLoop();

  SDL_Renderer* Renderer() const;
  SDL_Window*   Window() const;

  World::Ptr world() const;

private:
  void InitSDL() const;

  bool EmitEventSignals();
  void EmitDrawSignal();
  void EmitUpdateSignal(float delta_time);

  GraphicsRenderer graphics_;
  World::Ptr world_;
};

} // sdl_backend

#endif // MAIN_LOOP_H
