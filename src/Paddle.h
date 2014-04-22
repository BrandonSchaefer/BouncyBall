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

#ifndef PADDLE_H
#define PADDLE_H

#include <sdl_backend/Entity.h>
#include <sdl_backend/World.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class Paddle : public sbe::Entity
{
public:
  Paddle(unsigned id);

  void HandleKeyDown(int keysym, int state, int repeat);
  void HandleKeyUp(int keysym, int state, int repeat);

  void EnableKeyEvents(int keysym_up, int keysym_down);

  virtual void UpdatePosition(sbe::World::Ptr const& world) override;
  virtual void Update(float delta_time) override;
  virtual void Draw(sbe::GraphicsRenderer* graphics) override;

  void Reset();

  void SetInputBoundary(sbe::Rect const& rect);

  void EnableEvents();
  void DisableEvents();

private:
  void UpdateVelocity();
  void HandleCollision(sbe::Rect const& bound);

  sbe::Rect input_boundary_;

  int keysym_up_;
  int keysym_down_;
  bool up_key_down_;
  bool down_key_down_;
  bool events_enabled_;
  int speed_increse_;
};

} // namespace bouncy_ball

#endif // PADDLE_H
