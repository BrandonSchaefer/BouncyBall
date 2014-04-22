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

#include "PaddleAI.h"

namespace bouncy_ball
{

namespace
{
  int const EASY   = 4;
  int const MEDIUM = 6;
  int const HARD   = 8;
  int const IMPOSS = 15;
}

PaddleAI::PaddleAI(unsigned id, unsigned ball_id)
  : Paddle(id)
  , ball_id_(ball_id)
  , top_speed_(EASY)
  , player_(false)
{
}

void PaddleAI::SetEasy()
{
  top_speed_ = EASY;
  player_ = false;
}

void PaddleAI::SetMedium()
{
  top_speed_ = MEDIUM;
  player_ = false;
}

void PaddleAI::SetHard()
{
  top_speed_ = HARD;
  player_ = false;
}

void PaddleAI::SetImpossible()
{
  top_speed_ = IMPOSS;
  player_ = false;
}

void PaddleAI::EnablePlayer()
{
  player_ = true;
}

void PaddleAI::UpdatePosition(sbe::World::Ptr const& world)
{
  if (!player_)
  {
    Entity::Ptr ball = world->GetEntity(ball_id_);

    int diff = std::abs(y() + (height() / 2) - ball->y());

    vel_y_ = diff < top_speed_ ? diff : top_speed_;

    if (y() + height() / 2 > ball->y())
      vel_y_ = -vel_y_;
  }

  Paddle::UpdatePosition(world);
}

void PaddleAI::Update(float delta_time)
{
}

void PaddleAI::Draw(sbe::GraphicsRenderer* graphics)
{
  Paddle::Draw(graphics);
}

} // namespace bouncy_ball
