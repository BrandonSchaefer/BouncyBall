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

#ifndef STRING_TEXTURE_H
#define STRING_TEXTURE_H

#include "Rect.h"
#include "StringTextureCreator.h"

namespace sdl_backend
{

class StringTexture
{
public:
  StringTexture(SDL_Renderer* renderer);
  ~StringTexture();

  void SetXY(int x, int y);
  void SetFontSize(int font_size);
  void SetText(std::string const& str);

  SDL_Texture* texture() const;
  Rect GetRect() const;

private:
  void UpdateTexture();

  StringTextureCreator texture_creator_;

  SDL_Renderer* renderer_;
  SDL_Texture* str_texture_;
  SDL_Color color_;
  std::string str_;
  Rect rect_;
};

} // namespace sdl_backend

#endif // STRING_TEXTURE_H
