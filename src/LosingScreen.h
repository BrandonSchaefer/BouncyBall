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

#ifndef LOSING_SCREEN_H
#define LOSING_SCREEN_H

#include "Button.h"

#include <sdl_backend/EntityLayer.h>
#include <sdl_backend/RenderableGeometry.h>
#include <sdl_backend/StringTexture.h>

#include <memory>
#include <sigc++/signal.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class LosingScreen : public sbe::RenderableGeometry
{
public:
  LosingScreen(SDL_Renderer* renderer, sbe::World::Ptr const& world);

  void Update(float delta_time);
  void Draw(sbe::GraphicsRenderer* graphics);

  void Show();
  void Hide();

  void SetPlayer1Wins();
  void SetPlayer2Wins();

  sigc::signal<void> play_again;
  sigc::signal<void> main_menu;

private:
  void UpdateTexture();

  std::shared_ptr<Button> play_again_;
  std::shared_ptr<Button> main_menu_;

  sbe::EntityLayer::Ptr losing_menu_layer_;
  sbe::StringTexture losing_message_;
};

} // namespace bouncy_ball

#endif // LOSING_SCREEN_H
