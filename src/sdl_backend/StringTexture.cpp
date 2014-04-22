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

#include "Color.h"
#include "StringTexture.h"

namespace sdl_backend
{

namespace
{
  int const FONT_SIZE = 50;
}

StringTexture::StringTexture(SDL_Renderer* renderer)
  : texture_creator_(FONT_SIZE)
  , renderer_(renderer)
  , str_texture_(nullptr)
  , color_(color::WHITE)
  , str_("")
{
}

StringTexture::~StringTexture()
{
  SDL_DestroyTexture(str_texture_);
}

void StringTexture::SetXY(int x, int y)
{
  rect_.SetX(x);
  rect_.SetY(y);
}

SDL_Texture* StringTexture::texture() const
{
  return str_texture_;
}

Rect StringTexture::GetRect() const
{
  return rect_;
}

void StringTexture::SetFontSize(int font_size)
{
  texture_creator_.SetFontSize(font_size);
  UpdateTexture();
}

void StringTexture::SetText(std::string const& str)
{
  str_ = str;
  UpdateTexture();
}

void StringTexture::UpdateTexture()
{
  Size const& size = texture_creator_.GetMessageSize(str_);
  rect_.SetWidth(size.width);
  rect_.SetHeight(size.height);

  StringTextureData data = {str_, color_};
  str_texture_ = texture_creator_.CreateTextureFromString(renderer_, data);
}

} // namespace sdl_backend
