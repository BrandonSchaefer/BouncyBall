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

#include "Rect.h"

namespace sdl_backend
{

Rect::Rect()
  : x_(0)
  , y_(0)
  , w_(0)
  , h_(0)
{
}

Rect::Rect(int x, int y, int w, int h)
  : x_(x)
  , y_(y)
  , w_(w)
  , h_(h)
{
}

Rect::Rect(Point const& p, int w, int h)
  : x_(p.x)
  , y_(p.y)
  , w_(w)
  , h_(h)
{
}

Rect::Rect(int x, int y, Size const& size)
  : x_(x)
  , y_(y)
  , w_(size.width)
  , h_(size.height)
{
}

Rect::Rect(Point const& p, Size const& size)
  : x_(p.x)
  , y_(p.y)
  , w_(size.width)
  , h_(size.height)
{
}

SDL_Rect Rect::sdl_rect() const
{
  return {x_, y_, w_, h_};
}

void Rect::SetX(int x)
{
  x_ = x;
}

void Rect::SetY(int y)
{
  y_ = y;
}

void Rect::SetWidth(int width)
{
  w_ = width;
}

void Rect::SetHeight(int height)
{
  h_ = height;
}


int Rect::x() const
{
  return x_;
}

int Rect::y() const
{
  return y_;
}

int Rect::width() const
{
  return w_;
}

int Rect::height() const
{
  return h_;
}

bool Rect::Intersecting(Rect const& rect) const
{
  if (!((rect.x() > x() + width()) ||
        (rect.x() + rect.width() < x()) ||
        (rect.y() > y() + height()) ||
        (rect.y() + rect.height() < y())))
  {
    return true;
  }

  return false;
}

bool Rect::PointInside(Point const& point) const
{
  if (point.x >= x() && point.x <= x() + width() &&
      point.y >= y() && point.y <= y() + height())
  {
    return true;
  }

  return false;
}

} // namespace sdl_backend
