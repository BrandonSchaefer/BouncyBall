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

#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "Button.h"

#include <sdl_backend/EntityLayer.h>
#include <sdl_backend/RenderableGeometry.h>
#include <sdl_backend/Rect.h>
#include <sdl_backend/StringTexture.h>

#include <memory>
#include <sigc++/signal.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class TitleScreen : public sbe::RenderableGeometry
{
public:
  TitleScreen(SDL_Renderer* renderer, sbe::World::Ptr const& world);

  void Update(float delta_time);
  void Draw(sbe::GraphicsRenderer* graphics);

  void Hide();
  void Show();

  void SetEasy();
  void SetMedium();
  void SetHard();

  sigc::signal<void> start_clicked;

  sigc::signal<void> two_player_clicked;
  sigc::signal<void> easy_clicked;
  sigc::signal<void> medium_clicked;
  sigc::signal<void> hard_clicked;
  sigc::signal<void> exit_clicked;

private:
  void UnHightlightAll();
  void EasyClicked();
  void MediumClicked();
  void HardClicked();

  std::shared_ptr<Button> one_player_;
  std::shared_ptr<Button> two_player_;

  std::shared_ptr<Button> easy_button_;
  std::shared_ptr<Button> medium_button_;
  std::shared_ptr<Button> hard_button_;

  std::shared_ptr<Button> exit_;

  sbe::EntityLayer::Ptr main_menu_layer_;
  sbe::StringTexture game_title_;
};

} // namespace bouncy_ball

#endif // TITLE_SCREEN_H
