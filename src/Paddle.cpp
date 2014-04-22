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

#include "Paddle.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/GraphicsRenderer.h>

namespace bouncy_ball
{

namespace
{
  int const WIDTH  = 10;
  int const HEIGHT = 70;
  int const SPEED  = 3;
}

Paddle::Paddle(unsigned id)
  : Entity(id)
  , keysym_up_(-1)
  , keysym_down_(-1)
  , up_key_down_(false)
  , down_key_down_(false)
  , events_enabled_(true)
  , speed_increse_(0)
{
  SetWidth(WIDTH);
  SetHeight(HEIGHT);

  finger_down.connect([this] (int x, int y, int dx, int dy) {
    if (!paused_ && events_enabled_ && input_boundary_.PointInside({x, y}))
      SetY(y - height() / 2);
  });
}

void Paddle::SetInputBoundary(sbe::Rect const& rect)
{
  input_boundary_ = rect;
}

void Paddle::HandleKeyDown(int keysym, int state, int repeat)
{
  if (!repeat)
  {
    if (keysym == keysym_up_)
    {
      vel_y_ += -SPEED;
      up_key_down_ = true;
    }
    else if (keysym == keysym_down_)
    {
      vel_y_ += SPEED;
      down_key_down_ = true;
    }
  }
}

void Paddle::HandleKeyUp(int keysym, int state, int repeat)
{
  if (keysym == keysym_up_)
  {
    vel_y_ = 0;
    up_key_down_   = false;
  }
  else if (keysym == keysym_down_)
  {
    vel_y_ = 0;
    down_key_down_ = false;
  }
}

void Paddle::EnableKeyEvents(int keysym_up, int keysym_down)
{
  if (keysym_up_ == -1)
  {
    key_down.connect(sigc::mem_fun(this, &Paddle::HandleKeyDown));
    key_up.connect  (sigc::mem_fun(this, &Paddle::HandleKeyUp));
    keysym_up_   = keysym_up;
    keysym_down_ = keysym_down;
  }
}

void Paddle::UpdatePosition(sbe::World::Ptr const& world)
{
  if (paused_)
    return;

  sbe::Rect const& bound = world->Boundary();

  UpdateVelocity();
  UpdateY(vel_y_);
  HandleCollision(bound);
}

void Paddle::UpdateVelocity()
{
  if (up_key_down_ || down_key_down_)
  {
    if (down_key_down_)
      vel_y_ += speed_increse_;

    if (up_key_down_)
      vel_y_ -= speed_increse_;

    speed_increse_ = (speed_increse_ + 1) % 2;
  }
}

void Paddle::HandleCollision(sbe::Rect const& bound)
{
  // if we collid with top/bottom make sure we do the diff
  // of the remaining space (otherwise it looks ugly!)
  if (y() < bound.y())
  {
    int diff = y() - bound.y();
    UpdateY(-diff);
  }
  else if (y() + height() > bound.height())
  {
    int diff = y() + height() - bound.height();
    UpdateY(-diff);
  }
}

void Paddle::Update(float delta_time)
{
}

void Paddle::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = sdl_rect();
  SDL_RenderFillRect(graphics->Renderer(), &dest);
}

void Paddle::Reset()
{
  vel_x_ = 0;
  vel_y_ = 0;

  up_key_down_   = false;
  down_key_down_ = false;
}

void Paddle::EnableEvents()
{
  events_enabled_ = true;
}

void Paddle::DisableEvents()
{
  events_enabled_ = false;
}

} // namespace bouncy_ball
