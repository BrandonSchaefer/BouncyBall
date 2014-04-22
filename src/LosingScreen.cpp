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

#include "LosingScreen.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/EntityCreator.h>

namespace bouncy_ball
{

namespace
{
  std::string PLAYER_1_WINS = "Player One Wins";
  std::string PLAYER_2_WINS = "Player Two Wins";
  std::string PLAY_AGAIN = "Play Again";
  std::string MAIN_MENU  = "Main Menu";

  int const BUTTON_WIDTH   = 250;
  int const BACK_OFFSET    =  10;
  int const FONT_SIZE      =  70;
  int const BUTTON_HEIGHT  =  40;
  int const BUTTON_OFFSET  =  20;
  int const MESSAGE_OFFSET =  50;
}

LosingScreen::LosingScreen(SDL_Renderer* renderer, sbe::World::Ptr const& world)
  : losing_menu_layer_(std::make_shared<sbe::EntityLayer>())
  , losing_message_(renderer)
{
  sbe::Rect const& bound = world->Boundary();
  int start_x = bound.width() / 2;
  int start_y = bound.height() / 3;

  losing_message_.SetFontSize(FONT_SIZE);
  losing_message_.SetText(PLAYER_1_WINS);

  sbe::Rect const& size = losing_message_.GetRect();
  losing_message_.SetXY(start_x - size.width() / 2, start_y - MESSAGE_OFFSET);

  sbe::EntityCreator ec;

  start_x -= BUTTON_WIDTH / 2;

  play_again_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  play_again_->SetText(PLAY_AGAIN);
  play_again_->SetRect({start_x,
                        start_y + size.height() + BUTTON_OFFSET,
                        BUTTON_WIDTH, BUTTON_HEIGHT});
  play_again_->clicked.connect([this] { play_again.emit(); });

  main_menu_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  main_menu_->SetText(MAIN_MENU);
  main_menu_->SetRect({start_x,
                       play_again_->y() + play_again_->height() + BUTTON_OFFSET,
                       BUTTON_WIDTH, BUTTON_HEIGHT});
  main_menu_->clicked.connect([this] { main_menu.emit(); });

  losing_menu_layer_->AddEntity(play_again_);
  losing_menu_layer_->AddEntity(main_menu_);

  world->AddEntityLayer(losing_menu_layer_);
}

void LosingScreen::SetPlayer1Wins()
{
  losing_message_.SetText(PLAYER_1_WINS);
}

void LosingScreen::SetPlayer2Wins()
{
  losing_message_.SetText(PLAYER_2_WINS);
}

void LosingScreen::Update(float delta_time)
{
}

void LosingScreen::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = {0, 0, graphics->Width(), graphics->Height()};
  SDL_RenderFillRect(graphics->Renderer(), &dest);

  graphics->SetRenderColor(sbe::color::BLACK);
  dest = {0, BACK_OFFSET, graphics->Width(), graphics->Height() - BACK_OFFSET*2};
  SDL_RenderFillRect(graphics->Renderer(), &dest);

  dest = losing_message_.GetRect().sdl_rect();
  SDL_RenderCopy(graphics->Renderer(), losing_message_.texture(), nullptr, &dest);
}

void LosingScreen::Show()
{
  losing_menu_layer_->Show();
}

void LosingScreen::Hide()
{
  losing_menu_layer_->Hide();
}

} // namespace bouncy_ball
