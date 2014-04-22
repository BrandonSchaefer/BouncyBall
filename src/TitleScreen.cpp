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

#include "TitleScreen.h"

#include <sdl_backend/Color.h>
#include <sdl_backend/EntityCreator.h>

namespace bouncy_ball
{

namespace
{
  std::string const GAME_TITLE = "Bouncy Ball!";
  std::string const ONE_PLAYER = "One Player";
  std::string const TWO_PLAYER = "Two Player";
  std::string const EXIT       = "Exit Game";
  std::string const EASY       = "Easy";
  std::string const MEDIUM     = "Medium";
  std::string const HARD       = "Hard";

  int const BACK_OFFSET   =  10;
  int const GAME_OFFSET   =  75;
  int const FONT_SIZE     =  75;
  int const BUTTON_WIDTH  = 250;
  int const BUTTON_HEIGHT =  40;
  int const BUTTON_OFFSET =  20;
}

TitleScreen::TitleScreen(SDL_Renderer* renderer, sbe::World::Ptr const& world)
  : main_menu_layer_(std::make_shared<sbe::EntityLayer>())
  , game_title_(renderer)
{
  sbe::Rect const& bound = world->Boundary();

  int start_x = bound.width() / 2;
  int start_y = bound.height() / 3;

  sbe::EntityCreator ec;

  game_title_.SetFontSize(FONT_SIZE);
  game_title_.SetText(GAME_TITLE);

  sbe::Rect const& size = game_title_.GetRect();
  game_title_.SetXY(start_x - size.width() / 2, start_y - GAME_OFFSET);
  start_y += GAME_OFFSET;

  // FIXME Pretty messy... but it works i guess... :(
  one_player_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  one_player_->SetText(ONE_PLAYER);
  one_player_->SetRect({start_x - BUTTON_WIDTH / 2, start_y, BUTTON_WIDTH, BUTTON_HEIGHT});
  one_player_->clicked.connect([this] { start_clicked.emit(); });

  easy_button_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  easy_button_->SetText(EASY);
  easy_button_->SetRect({start_x - BUTTON_WIDTH / 2 - BUTTON_OFFSET,
                         start_y + BUTTON_HEIGHT + BUTTON_OFFSET,
                         BUTTON_WIDTH / 3, BUTTON_HEIGHT});
  easy_button_->clicked.connect(sigc::mem_fun(this, &TitleScreen::EasyClicked));

  medium_button_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  medium_button_->SetFontSize(45);
  medium_button_->SetText(MEDIUM);
  medium_button_->SetRect({start_x - BUTTON_WIDTH / 2 + easy_button_->width(),
                           start_y + BUTTON_HEIGHT + BUTTON_OFFSET,
                           BUTTON_WIDTH / 3, BUTTON_HEIGHT});
  medium_button_->clicked.connect(sigc::mem_fun(this, &TitleScreen::MediumClicked));

  hard_button_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  hard_button_->SetText(HARD);
  hard_button_->SetRect({start_x - BUTTON_WIDTH / 2 + easy_button_->width()*2 + BUTTON_OFFSET*1,
                         start_y + BUTTON_HEIGHT + BUTTON_OFFSET,
                         BUTTON_WIDTH / 3, BUTTON_HEIGHT});
  hard_button_->clicked.connect(sigc::mem_fun(this, &TitleScreen::HardClicked));

  two_player_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  two_player_->SetText(TWO_PLAYER);
  two_player_->SetRect({start_x - BUTTON_WIDTH / 2, start_y + BUTTON_HEIGHT*2 + BUTTON_OFFSET*2, BUTTON_WIDTH, BUTTON_HEIGHT});
  two_player_->clicked.connect([this] { two_player_clicked.emit(); start_clicked.emit(); });

  exit_ = std::make_shared<Button>(ec.GetUniqueId(), renderer);
  exit_->SetText(EXIT);
  exit_->SetRect({start_x - BUTTON_WIDTH / 2, start_y + (BUTTON_HEIGHT + BUTTON_OFFSET)*3, BUTTON_WIDTH, BUTTON_HEIGHT});
  exit_->clicked.connect([this] { exit_clicked.emit(); });

  main_menu_layer_->AddEntity(one_player_);
  main_menu_layer_->AddEntity(two_player_);
  main_menu_layer_->AddEntity(easy_button_);
  main_menu_layer_->AddEntity(medium_button_);
  main_menu_layer_->AddEntity(hard_button_);
  main_menu_layer_->AddEntity(exit_);

  world->AddEntityLayer(main_menu_layer_);
}

void TitleScreen::SetEasy()
{
  EasyClicked();
}

void TitleScreen::SetMedium()
{
  MediumClicked();
}

void TitleScreen::SetHard()
{
  HardClicked();
}

void TitleScreen::EasyClicked()
{
  UnHightlightAll();
  easy_button_->Hightlight();
  easy_clicked.emit();
}

void TitleScreen::MediumClicked()
{
  UnHightlightAll();
  medium_button_->Hightlight();
  medium_clicked.emit();
}

void TitleScreen::HardClicked()
{
  UnHightlightAll();
  hard_button_->Hightlight();
  hard_clicked.emit();
}

void TitleScreen::UnHightlightAll()
{
  easy_button_->UnHightlight();
  medium_button_->UnHightlight();
  hard_button_->UnHightlight();
}

void TitleScreen::Hide()
{
  main_menu_layer_->Hide();
}

void TitleScreen::Show()
{
  main_menu_layer_->Show();
}

void TitleScreen::Update(float delta_time)
{
}

void TitleScreen::Draw(sbe::GraphicsRenderer* graphics)
{
  graphics->SetRenderColor(sbe::color::WHITE);
  SDL_Rect dest = {0, 0, graphics->Width(), graphics->Height()};
  SDL_RenderFillRect(graphics->Renderer(), &dest);

  graphics->SetRenderColor(sbe::color::BLACK);
  dest = {0, BACK_OFFSET, graphics->Width(), graphics->Height() - BACK_OFFSET*2};
  SDL_RenderFillRect(graphics->Renderer(), &dest);

  dest = game_title_.GetRect().sdl_rect();
  SDL_RenderCopy(graphics->Renderer(), game_title_.texture(), nullptr, &dest);
}

} // namespace bouncy_ball
