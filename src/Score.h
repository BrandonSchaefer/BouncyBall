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

#ifndef SCORE_H
#define SCORE_H

#include <sdl_backend/Entity.h>
#include <sdl_backend/StringTexture.h>
#include <sdl_backend/World.h>

#include <SDL2/SDL.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class Score : public sbe::Entity
{
public:
  Score(unsigned id, SDL_Renderer* renderer);

  void UpdatePosition(sbe::World::Ptr const& world);
  void Update(float delta_time);
  void Draw(sbe::GraphicsRenderer* graphics);

  void Increment();
  void Reset();

  int GetScore();

private:
  sbe::StringTexture score_texture_;
  int score_;

};

} // namespace bouncy_ball

#endif // SCORE_H
