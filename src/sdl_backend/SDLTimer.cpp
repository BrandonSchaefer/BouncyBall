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

#include "SDLTimer.h"

#include <SDL2/SDL.h>

namespace sdl_backend
{

SDLTimer::SDLTimer()
  : start_ticks_(0)
  , paused_ticks_(0)
  , started_(false)
  , paused_(false)
{
}

void SDLTimer::start()
{
  start_ticks_  = SDL_GetTicks();
  paused_ticks_ = 0;
  started_ = true;
  paused_  = false;
}

void SDLTimer::stop()
{
  start_ticks_  = 0;
  paused_ticks_ = 0;
  started_ = false;
  paused_  = false;
}

void SDLTimer::pause()
{
  if (started_ && !paused_)
  {
    paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_ticks_;
    start_ticks_  = 0;
  }
}

void SDLTimer::unpause()
{
  if (started_ && paused_)
  {
    paused_ = false;
    start_ticks_  = SDL_GetTicks() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

unsigned SDLTimer::ticks() const
{
  unsigned ticks = 0;

  if (started_)
  {
    if (paused_)
    {
      ticks = paused_ticks_;
    }
    else
    {
      ticks = SDL_GetTicks() - start_ticks_;
    }
  }

  return ticks;
}

bool SDLTimer::started() const
{
  return started_;
}

bool SDLTimer::paused() const
{
  return paused_;
}

} // namespace sdl_backend
