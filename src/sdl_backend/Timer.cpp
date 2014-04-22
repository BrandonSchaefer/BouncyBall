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

#include "Timer.h"

#include <stdio.h>

namespace sdl_backend
{

Timer::Timer(float duration, int ticks)
  : duration_(duration)
  , tick_speed_(duration / ticks)
  , total_(0.0f)
  , current_(0.0f)
  , running_(false)
{
}

void Timer::Start()
{
  total_ = 0.0f;
  current_ = 0.0f;
  running_ = true;
}

void Timer::Stop()
{
  running_ = false;
}

void Timer::Restart()
{
  Start();
}

bool Timer::IsRunning() const
{
  return running_;
}

void Timer::Tick(float delta_time)
{
  if (running_)
  {
    total_ += delta_time;

    current_ += delta_time;
    if (current_ >= tick_speed_)
    {
      update.emit();
      current_ = 0.0f;
    }

    if (total_ >= duration_)
    {
      running_ = false;
      update.emit();
      done.emit();
    }
  }
}

} // namespace sdl_backend
