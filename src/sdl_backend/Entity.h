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

#ifndef ENTITY_H
#define ENTITY_H

#include "RenderableGeometry.h"
#include "Rect.h"

#include <sigc++/signal.h>

#include <memory>

namespace sdl_backend
{

class World;

class Entity : public RenderableGeometry
{
public:
  typedef std::shared_ptr<Entity> Ptr;

  Entity(unsigned id);

  unsigned id() const;

  bool Moving() const;

  void Pause();
  void UnPause();
  bool Paused() const;

  virtual void UpdatePosition(std::shared_ptr<World> const& world) = 0;

  // Redo signals in the Entity, possibly remove them from the mainloop
  /*           void, keysym, state, repeat */
  sigc::signal<void, int, int, int> key_down;
  sigc::signal<void, int, int, int> key_up;

  /*           void, text */
  sigc::signal<void, std::string> text_input;

  /*           void, x,   y,   button, clicks*/
  sigc::signal<void, int, int, int, int> mouse_down;
  sigc::signal<void, int, int, int, int> mouse_up;

  /*           void, x,   y,   xrel, yrel, state */
  sigc::signal<void, int, int, int, int, int> mouse_move;

  /*           void  x,   y */
  sigc::signal<void, int, int> mouse_wheel;

  /*           void  x,   y    dx   dy */
  sigc::signal<void, int, int, int, int> finger_motion;
  sigc::signal<void, int, int, int, int> finger_down;
  sigc::signal<void, int, int, int, int> finger_up;

protected:
  int vel_x_;
  int vel_y_;
  bool paused_;

private:
  unsigned id_;
};

} // namespace sdl_backend

#endif // ENTITY_H
