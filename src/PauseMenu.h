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

#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Button.h"

#include <sdl_backend/EntityLayer.h>
#include <sdl_backend/World.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class PauseMenu
{
public:
  PauseMenu(SDL_Renderer* renderer, sbe::World::Ptr const& world);

  void Show();
  void Hide();

  sigc::signal<void> resume_clicked;
  sigc::signal<void> main_menu_clicked;
  sigc::signal<void> restart_clicked;
  sigc::signal<void> exit_clicked;

  void Draw(sbe::GraphicsRenderer* graphics);

private:
  std::shared_ptr<Button> resume_;
  std::shared_ptr<Button> main_menu_;
  std::shared_ptr<Button> restart_;
  std::shared_ptr<Button> exit_;

  sbe::EntityLayer::Ptr pause_menu_layer_;
  sbe::Rect border_rect_;
};

} // namespace bouncy_ball

#endif // PAUSE_MENU_H
