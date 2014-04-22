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

#include "PauseMenu.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/EntityCreator.h>

namespace bouncy_ball
{

namespace
{
  std::string RESUME    = "Resume";
  std::string MAIN_MENU = "Main Menu";
  std::string RESTART   = "Restart";
  std::string EXIT      = "Exit Game";

  int const BUTTON_WIDTH   = 200;
  int const BUTTON_HEIGHT  =  40;
  int const BUTTON_OFFSET  =  20;
  int const BACK_OFFSET    =   5;
  int const BUTTON_COUNT   =   4;
}

PauseMenu::PauseMenu(SDL_Renderer* renderer, sbe::World::Ptr const& world)
  : pause_menu_layer_(std::make_shared<sbe::EntityLayer>())
{
  sbe::Rect const& bound = world->Boundary();
  int start_x = bound.width() / 2 - BUTTON_WIDTH / 2;
  int start_y = bound.height() / 4;
  int button_offset = BUTTON_HEIGHT + BUTTON_OFFSET;

  border_rect_ = {start_x - (BACK_OFFSET*2 + BUTTON_OFFSET),
                  start_y - (BACK_OFFSET*2 + BUTTON_OFFSET),
                 (BUTTON_WIDTH + BUTTON_OFFSET * 3),
                 (BUTTON_HEIGHT * BUTTON_COUNT + BUTTON_OFFSET * (BUTTON_COUNT+2))};

  sbe::EntityCreator ec;

  resume_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  resume_->SetRect({start_x, start_y, BUTTON_WIDTH, BUTTON_HEIGHT});
  resume_->SetText(RESUME);
  resume_->clicked.connect([this] { resume_clicked.emit(); });

  main_menu_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  main_menu_->SetRect({start_x, start_y + button_offset, BUTTON_WIDTH, BUTTON_HEIGHT});
  main_menu_->SetText(MAIN_MENU);
  main_menu_->clicked.connect([this] { main_menu_clicked.emit(); });

  restart_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  restart_->SetRect({start_x, start_y + button_offset*2, BUTTON_WIDTH, BUTTON_HEIGHT});
  restart_->SetText(RESTART);
  restart_->clicked.connect([this] { restart_clicked.emit(); });

  exit_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  exit_->SetRect({start_x, start_y + button_offset*3, BUTTON_WIDTH, BUTTON_HEIGHT});
  exit_->SetText(EXIT);
  exit_->clicked.connect([this] { exit_clicked.emit(); });

  pause_menu_layer_->AddEntity(resume_);
  pause_menu_layer_->AddEntity(main_menu_);
  pause_menu_layer_->AddEntity(restart_);
  pause_menu_layer_->AddEntity(exit_);

  world->AddEntityLayer(pause_menu_layer_);
}

void PauseMenu::Show()
{
  pause_menu_layer_->Show();
}

void PauseMenu::Hide()
{
  pause_menu_layer_->Hide();
}

void PauseMenu::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = border_rect_.sdl_rect();
  SDL_RenderFillRect(graphics->Renderer(), &dest);

  graphics->SetRenderColor(sbe::color::BLACK);
  dest = {dest.x + BACK_OFFSET, dest.y + BACK_OFFSET, dest.w - BACK_OFFSET*2, dest.h - BACK_OFFSET*2};
  SDL_RenderFillRect(graphics->Renderer(), &dest);
}

} // namespace bouncy_ball
