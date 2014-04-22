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

#include "Entity.h"

namespace sdl_backend
{

Entity::Entity(unsigned id)
  : vel_x_(0)
  , vel_y_(0)
  , paused_(false)
  , id_(id)
{
}

void Entity::Pause()
{
  paused_ = true;
}

void Entity::UnPause()
{
  paused_ = false;
}

bool Entity::Paused() const
{
  return paused_;
}

unsigned Entity::id() const
{
  return id_;
}

bool Entity::Moving() const
{
  return (vel_x_ != 0 || vel_y_ != 0);
}

} // namespace sdl_backend
