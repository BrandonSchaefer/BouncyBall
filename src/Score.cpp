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

#include "Score.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/StringTextureData.h>

namespace bouncy_ball
{

namespace
{
  int const FONT_SIZE = 50;
}

Score::Score(unsigned id, SDL_Renderer* renderer)
  : Entity(id)
  , score_texture_(renderer)
  , score_(0)
{
  score_texture_.SetFontSize(FONT_SIZE);
  score_texture_.SetText(std::to_string(score_));

  sbe::Rect const& str_size = score_texture_.GetRect();
  SetWidth(str_size.width());
  SetHeight(str_size.height());
}

void Score::UpdatePosition(sbe::World::Ptr const& world)
{
}

void Score::Update(float delta_time)
{
}

void Score::Draw(sbe::GraphicsRenderer* graphics)
{
  SDL_Rect dest = sdl_rect();
  SDL_RenderCopy(graphics->Renderer(), score_texture_.texture(), nullptr, &dest);
}

void Score::Increment()
{
  score_++;
  score_texture_.SetText(std::to_string(score_));
}

void Score::Reset()
{
  score_ = 0;
  score_texture_.SetText(std::to_string(score_));
}

int Score::GetScore()
{
  return score_;
}

} // namespace bouncy_ball
