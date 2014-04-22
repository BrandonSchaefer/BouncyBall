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

#ifndef BALL_H
#define BALL_H

#include <sdl_backend/Entity.h>
#include <sdl_backend/World.h>

#include <SDL2/SDL_mixer.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class Ball : public sbe::Entity
{
public:
  Ball(unsigned id, unsigned left_paddle_id, unsigned right_paddle_id);
  ~Ball();

  void UpdatePosition(sbe::World::Ptr const& world) override;
  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

  void Reset(int x, int y);

private:
  void CheckIfCollisionWithBoundry(sbe::World::Ptr const& world);
  void CheckIfCollisionWithPaddles(sbe::World::Ptr const& world);
  void CheckIfInWinningState(sbe::World::Ptr const& world);

  void EnsureBallOutside(sbe::Rect const& r, int p_vel_x, int p_vel_y);

  void PlayBounceSound();
  void PlayScoreSound();
  void PlaySound(Mix_Chunk* sound);

  void HandleBallPaddleCollision(Entity::Ptr const& paddle);

  Mix_Chunk* bounce_sound_;
  Mix_Chunk* score_sound_;

  unsigned left_padd_id_;
  unsigned right_padd_id_;
};

} // namespace bouncy_ball

#endif // BALL_H
