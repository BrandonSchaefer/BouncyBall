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

#ifndef PADDLE_A_I_H
#define PADDLE_A_I_H

#include "Paddle.h"

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class PaddleAI : public Paddle
{
public:
  PaddleAI(unsigned id, unsigned ball_id);

  void UpdatePosition(sbe::World::Ptr const& world) override;
  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

  void SetEasy();
  void SetMedium();
  void SetHard();
  void SetImpossible();

  // FIXME BAD BAD BAD :(
  void EnablePlayer();

private:
  int ball_id_;
  int top_speed_;
  bool player_;
};

} // namespace bouncy_ball

#endif // PADDLE_A_I_H
