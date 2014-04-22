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

#include "StringTextureCreator.h"

namespace sdl_backend
{

// FIXME Make this easier to change...
std::string const FONT_PATH = "/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-B.ttf";

StringTextureCreator::StringTextureCreator(int font_size)
  : font_(TTF_OpenFont(FONT_PATH.c_str(), font_size))
{
}

StringTextureCreator::~StringTextureCreator()
{
  //TTF_CloseFont(font_);
}

void StringTextureCreator::SetFontSize(int size)
{
  TTF_CloseFont(font_);
  font_ = TTF_OpenFont(FONT_PATH.c_str(), size);
}

SDL_Texture* StringTextureCreator::CreateTextureFromString(SDL_Renderer* renderer,
                                                           StringTextureData const& data) const
{
  SDL_Surface* surface;
  SDL_Texture* texture;

  surface = TTF_RenderText_Blended(font_, data.message.c_str(), data.color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  return texture;
}

Size StringTextureCreator::GetMessageSize(std::string const& str) const
{
  int w, h;
  TTF_SizeText(font_, str.c_str(), &w, &h);

  return {w, h};
}

} // namespace sdl_backend
