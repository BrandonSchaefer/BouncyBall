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

#include "RenderableGeometry.h"

namespace sdl_backend
{

RenderableGeometry::RenderableGeometry()
  : rect_({0, 0, 0, 0})
{
}

RenderableGeometry::RenderableGeometry(Rect const& rect)
  : rect_(rect)
{
}

void RenderableGeometry::SetRect(Rect const& rect)
{
  rect_ = rect;
}

void RenderableGeometry::SetX(int x)
{
  rect_.SetX(x);
}

void RenderableGeometry::SetY(int y)
{
  rect_.SetY(y);
}

void RenderableGeometry::UpdateX(int x)
{
  rect_.SetX(rect_.x() + x);
}

void RenderableGeometry::UpdateY(int y)
{
  rect_.SetY(rect_.y() + y);
}

void RenderableGeometry::SetWidth(int width)
{
  rect_.SetWidth(width);
}

void RenderableGeometry::SetHeight(int height)
{
  rect_.SetHeight(height);
}

int RenderableGeometry::x() const
{
  return rect_.x();
}

int RenderableGeometry::y() const
{
  return rect_.y();
}

int RenderableGeometry::width() const
{
  return rect_.width();
}

int RenderableGeometry::height() const
{
  return rect_.height();
}

Rect RenderableGeometry::rect() const
{
  return rect_;
}

SDL_Rect RenderableGeometry::sdl_rect() const
{
  return rect_.sdl_rect();
}

} // namespace sdl_backend
