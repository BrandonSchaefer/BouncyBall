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

#ifndef RENDERABLE_GEOMETRY_H
#define RENDERABLE_GEOMETRY_H

#include "Renderable.h"
#include "Rect.h"

#include <SDL2/SDL.h>

namespace sdl_backend
{

class RenderableGeometry : public Renderable
{
public:
  RenderableGeometry();
  RenderableGeometry(Rect const& rect);

  void SetRect(Rect const& rect);

  void SetX(int x);
  void SetY(int y);
  void UpdateX(int x);
  void UpdateY(int y);

  void SetWidth(int width);
  void SetHeight(int height);

  int x() const;
  int y() const;
  int width() const;
  int height() const;

  Rect rect() const;
  SDL_Rect sdl_rect() const;

private:
  Rect rect_;

};

} // namespace sdl_backend

#endif // RENDERABLE_GEOMETRY_H
