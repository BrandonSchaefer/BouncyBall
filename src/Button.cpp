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

#include "Button.h"

#include <sdl_backend/Color.h>

namespace bouncy_ball
{

namespace
{
  int const BORDER_SIZE = 5;
  int const FONT_SIZE   = 50;
}

Button::Button(unsigned id, SDL_Renderer* renderer)
  : Entity(id)
  , message_(renderer)
  , border_size_(BORDER_SIZE)
  , mouse_over_(false)
  , highlight_(false)
{
  message_.SetFontSize(FONT_SIZE);

  mouse_up.connect([this] (int x, int y, int button, int clicks) {
    if (rect().PointInside({x, y}))
      clicked.emit();
  });

  mouse_move.connect([this] (int x, int y, int dx, int dy, int button) {
    if (rect().PointInside({x, y}))
      mouse_over_ = true;
    else
      mouse_over_ = false;
  });
}

void Button::SetFontSize(int font_size)
{
  message_.SetFontSize(font_size);
}

void Button::SetText(std::string const& message)
{
  message_.SetText(message);
}

void Button::Hightlight()
{
  highlight_ = true;
}

void Button::UnHightlight()
{
  highlight_ = false;
}

void Button::UpdatePosition(sbe::World::Ptr const& world)
{
}

void Button::Update(float delta_time)
{
}

void Button::Draw(sbe::GraphicsRenderer* graphics)
{
  SDL_Rect dest = sdl_rect();
  SDL_Rect white_bord = dest;
  white_bord.x -= border_size_;
  white_bord.y -= border_size_;
  white_bord.w += border_size_ * 2;
  white_bord.h += border_size_ * 2;

  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_RenderFillRect(graphics->Renderer(), &white_bord);

  if (mouse_over_ || highlight_)
    graphics->SetRenderColor(sbe::color::GREY);
  else
    graphics->SetRenderColor(sbe::color::BLACK);

  SDL_RenderFillRect(graphics->Renderer(), &dest);

  SDL_RenderCopy(graphics->Renderer(), message_.texture(), nullptr, &dest);
}

} // namespace bouncy_ball
