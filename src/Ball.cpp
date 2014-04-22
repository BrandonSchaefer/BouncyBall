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

#include "config.h"

#include "Ball.h"
#include "BouncyGameData.h"

#include <sdl_backend/Color.h>

#include <iostream>

namespace bouncy_ball
{

namespace
{
  int const WIDTH  = 15;
  int const HEIGHT = 15;
  int const START_SPEED = 3;
  int const EDGE_WIDTH  = 10;
  int const MAX_SPEED   = 25;

  std::string SOUND_PATH = RESDIR"/bounce.wav";
  std::string SCORE_PATH = RESDIR"/score.wav";
}

Ball::Ball(unsigned id, unsigned left_paddle_id, unsigned right_paddle_id)
  : Entity(id)
  , bounce_sound_(Mix_LoadWAV(SOUND_PATH.c_str()))
  , score_sound_ (Mix_LoadWAV(SCORE_PATH.c_str()))
  , left_padd_id_(left_paddle_id)
  , right_padd_id_(right_paddle_id)
{
  Reset(x(), y());
}

Ball::~Ball()
{
  Mix_FreeChunk(bounce_sound_);
  Mix_FreeChunk(score_sound_);
}

void Ball::UpdatePosition(sbe::World::Ptr const& world)
{
  if (paused_)
    return;

  UpdateX(vel_x_);
  UpdateY(vel_y_);

  CheckIfCollisionWithBoundry(world);
  CheckIfCollisionWithPaddles(world);
  CheckIfInWinningState(world);
}

void Ball::CheckIfCollisionWithBoundry(sbe::World::Ptr const& world)
{
  sbe::Rect const& bound = world->Boundary();

  if (y() < bound.y() || y() + height() > bound.height())
  {
    UpdateY(-vel_y_);
    vel_y_ = -vel_y_;
    PlayBounceSound();
  }
}

void Ball::CheckIfCollisionWithPaddles(sbe::World::Ptr const& world)
{
  Entity::Ptr paddles[2];

  paddles[0] = world->GetEntity(left_padd_id_);
  paddles[1] = world->GetEntity(right_padd_id_);

  for (int i = 0; i < 2; i++)
  {
    sbe::Rect const& r = paddles[i]->rect();

    if (rect().Intersecting(r))
      HandleBallPaddleCollision(paddles[i]);
  }
}

void Ball::HandleBallPaddleCollision(Entity::Ptr const& paddle)
{
  PlayBounceSound();

  int p_vel_x = vel_x_;
  int p_vel_y = vel_y_;

  sbe::Rect const& r = paddle->rect();

  int ball_center = y() + height() / 2;
  int third_bar = r.height() / 3;
  bool flip_y = false;

  // Check if we are in the top thrid, or bottom third
  // if so, and we are moving flip the y vel
  if (ball_center < r.y() + third_bar ||
      ball_center > r.y() + third_bar*2)
  {
    if (paddle->Moving())
    {
      flip_y = true;
      vel_y_ += (vel_y_ > 0 ? 1 : -1);
    }
  }

  if (std::abs(vel_x_) < MAX_SPEED)
    vel_x_ += (vel_x_ > 0 ? 1 : -1);

  UpdateX(-vel_x_);
  vel_x_ = -vel_x_;

  if (flip_y)
  {
    UpdateX(-vel_y_);
    vel_y_ = -vel_y_;
  }

  EnsureBallOutside(r, p_vel_x, p_vel_y);
}

void Ball::EnsureBallOutside(sbe::Rect const& r, int p_vel_x, int p_vel_y)
{
  // If we are still intersecting after we collid, lets move our selfs back
  // before we collid (avoids strange behviour)
  if (rect().Intersecting(r))
  {
    UpdateX(-p_vel_x);
    UpdateY(-p_vel_y);
  }
}

void Ball::PlayScoreSound()
{
  PlaySound(score_sound_);
}

void Ball::PlayBounceSound()
{
  PlaySound(bounce_sound_);
}

void Ball::PlaySound(Mix_Chunk* sound)
{
  int channel = Mix_PlayChannel(-1, sound, 0);

  if (channel == -1)
    std::cerr << "Failed to play sound!" << std::endl;
}

void Ball::CheckIfInWinningState(sbe::World::Ptr const& world)
{
  sbe::Rect const& bound = world->Boundary();
  sbe::Rect const& left  = {bound.x(), bound.y(), EDGE_WIDTH, bound.height()};
  sbe::Rect const& right = {bound.x() + bound.width() - EDGE_WIDTH, bound.y(), EDGE_WIDTH, bound.height()};
  BouncyGameData* bouncy_data = (BouncyGameData*)world->GameData();

  if (rect().Intersecting(left))
  {
    bouncy_data->RightScored();
    PlayScoreSound();
  }
  else if (rect().Intersecting(right))
  {
    bouncy_data->LeftScored();
    PlayScoreSound();
  }
}

void Ball::Update(float delta_time)
{
}

void Ball::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = sdl_rect();
  SDL_RenderFillRect(graphics->Renderer(), &dest);
}

void Ball::Reset(int x, int y)
{
  SetRect({x, y, WIDTH, HEIGHT});

  bool up   = rand() % 2;
  bool left = rand() % 2;

  vel_x_ = (rand() % START_SPEED) + START_SPEED;
  vel_y_ = (rand() % START_SPEED) + START_SPEED;

  if (up)   vel_y_ = -vel_y_;
  if (left) vel_x_ = -vel_x_;
}

} // namespace bouncy_ball
