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

#ifndef RECT_H
#define RECT_H

#include <SDL2/SDL.h>

#include "Point.h"
#include "Size.h"

namespace sdl_backend
{

class Rect
{
public:
  Rect();
  Rect(int x, int y, int w, int h);
  Rect(Point const& p, int w, int h);
  Rect(int x, int y, Size const& size);
  Rect(Point const& p, Size const& size);

  SDL_Rect sdl_rect() const;
  
  void SetX(int x);
  void SetY(int y);
  void SetWidth(int width);
  void SetHeight(int height);

  int x() const;
  int y() const;
  int width() const;
  int height() const;

  bool Intersecting(Rect const& rect) const;
  bool PointInside(Point const& point) const;

private:
  int x_;
  int y_;
  int w_;
  int h_;
};

} // namespace sdl_backend

#endif // RECT_H
