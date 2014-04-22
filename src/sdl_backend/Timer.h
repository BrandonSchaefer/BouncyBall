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

#ifndef ANIMATION_H
#define ANIMATION_H

#include <sigc++/signal.h>

namespace sdl_backend
{

class Timer
{
public:
  Timer(float duration, int ticks);

  void Start();
  void Stop();
  void Restart();
  bool IsRunning() const;

  void Tick(float delta_time);

  sigc::signal<void> update;
  sigc::signal<void> done;
private:
  float duration_;
  float tick_speed_;
  float total_;
  float current_;

  bool running_;
};

} // namespace sdl_backend

#endif // ANIMATION_H
