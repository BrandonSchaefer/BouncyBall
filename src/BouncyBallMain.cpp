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

#include <SDL2/SDL_image.h>

#include "config.h"
#include "BouncyBallMain.h"

#include <sdl_backend/EntityCreator.h>

namespace bouncy_ball
{

namespace
{
  std::string const BACKGROUND_PATH = RESDIR"/background.png";
  int const WIN                = 10;
}

BouncyBallMain::BouncyBallMain(unsigned id, sbe::MainLoop const& main_loop)
  : Entity(id)
  , main_loop_(main_loop)
  , background_(IMG_LoadTexture(main_loop_.Renderer(), BACKGROUND_PATH.c_str()))
  , title_screen_(main_loop_.Renderer(), main_loop_.world())
  , losing_screen_(main_loop_.Renderer(), main_loop_.world())
  , pause_menu_(main_loop_.Renderer(), main_loop_.world())
  , game_layer_(std::make_shared<sbe::EntityLayer>())
  , game_started_(false)
  , losing_(false)
{
  key_up.connect(sigc::mem_fun(this, &BouncyBallMain::OnKeyUp));
  main_loop_.world()->SetGameData((void*)&bouncy_data_);

  bouncy_data_.left_scored.connect([this] {
    left_->Increment();
    CheckIfWinning();
  });

  bouncy_data_.right_scored.connect([this] {
    right_->Increment();
    CheckIfWinning();
  });

  title_screen_.start_clicked.connect([this] {
    StartGame();
  });

  title_screen_.two_player_clicked.connect([this] {
    right_paddle_->EnablePlayer();
    right_paddle_->EnableEvents();
  });

  title_screen_.easy_clicked.connect([this] {
      right_paddle_->SetEasy();
  });

  title_screen_.medium_clicked.connect([this] {
      right_paddle_->SetMedium();
  });

  title_screen_.hard_clicked.connect([this] {
      right_paddle_->SetHard();
  });

  title_screen_.exit_clicked.connect([this] {
    // FIXME exit better then this...
    exit(0);
  });

  losing_screen_.play_again.connect([this] {
    losing_screen_.Hide();
    StartGame();
    losing_ = false;
  });

  losing_screen_.main_menu.connect([this] {
    losing_screen_.Hide();
    ResetGame();
    losing_ = false;
  });

  pause_menu_.resume_clicked.connect([this] {
    pause_menu_.Hide();
    game_layer_->UnPause();
  });

  pause_menu_.main_menu_clicked.connect([this] {
    pause_menu_.Hide();
    game_layer_->UnPause();
    ResetGame();
  });

  pause_menu_.restart_clicked.connect([this] {
    pause_menu_.Hide();
    game_layer_->UnPause();
    StartGame();
  });

  pause_menu_.exit_clicked.connect([this] {
    // FIXME exit better then this...
    exit(0);
  });

  sbe::Rect const& bound = main_loop_.world()->Boundary();
  sbe::Rect new_bound = {0, 10, bound.width(), bound.height() - 10};
  main_loop_.world()->SetBoundary(new_bound);

  SetupGame();

  title_screen_.SetMedium();

  game_layer_->Hide();
  losing_screen_.Hide();
  pause_menu_.Hide();

  main_loop_.world()->AddEntityLayer(game_layer_);
}

void BouncyBallMain::ResetGame()
{
  title_screen_.Show();
  title_screen_.SetMedium();
  right_paddle_->DisableEvents();
  HideEntities();
}

void BouncyBallMain::StartGame()
{
  sbe::Rect const& bound = main_loop_.world()->Boundary();

  title_screen_.Hide();
  ShowEntities();

  left_paddle_->SetX(30);
  left_paddle_->SetY(bound.width() / 3);
  left_paddle_->Reset();

  right_paddle_->SetX(bound.width() - 30 - right_paddle_->width());
  right_paddle_->SetY(bound.height() / 2);
  right_paddle_->Reset();

  left_->Reset();
  right_->Reset();

  ResetBall();
}

void BouncyBallMain::ShowEntities()
{
  game_layer_->Show();
  game_started_ = true;
}

void BouncyBallMain::HideEntities()
{
  game_layer_->Hide();
  game_started_ = false;
}

void BouncyBallMain::SetupGame()
{
  sbe::EntityCreator ec;
  sbe::Rect const& bound = main_loop_.world()->Boundary();

  unsigned ball_id       = ec.GetUniqueId();
  unsigned left_padd_id  = ec.GetUniqueId();
  unsigned right_padd_id = ec.GetUniqueId();

  int half_width = bound.width() / 2;

  sbe::Rect left_boundary = {bound.x(), bound.y(), half_width, bound.height()};
  left_paddle_ = std::make_shared<Paddle>(left_padd_id);
  left_paddle_->EnableKeyEvents(SDLK_w, SDLK_s);
  left_paddle_->SetInputBoundary(left_boundary);

  sbe::Rect right_boundary = {bound.x() + half_width, bound.y(), half_width, bound.height()};
  right_paddle_ = std::make_shared<PaddleAI>(right_padd_id, ball_id);
  right_paddle_->EnableKeyEvents(SDLK_UP, SDLK_DOWN);
  right_paddle_->SetInputBoundary(right_boundary);
  right_paddle_->DisableEvents();

  ball_ = std::make_shared<Ball>(ball_id, left_padd_id, right_padd_id);
  ResetBall();

  right_ = std::make_shared<Score>(ec.GetUniqueId(), main_loop_.Renderer());
  right_->SetX(bound.width() / 2 + 20);
  right_->SetY(20);

  left_ = std::make_shared<Score>(ec.GetUniqueId(), main_loop_.Renderer());
  left_->SetX(bound.width() / 2 - 50);
  left_->SetY(20);

  game_layer_->AddEntity(left_);
  game_layer_->AddEntity(right_);
  game_layer_->AddEntity(left_paddle_);
  game_layer_->AddEntity(right_paddle_);
  game_layer_->AddEntity(ball_);
}

void BouncyBallMain::ResetBall()
{
  sbe::Rect const& bound = main_loop_.world()->Boundary();
  ball_->Reset(bound.width() / 2 - 50, bound.height() / 2);
}

void BouncyBallMain::CheckIfWinning()
{
  bool win = false;
  if (left_->GetScore() >= WIN)
  {
    losing_screen_.SetPlayer1Wins();
    win = true;
  }
  else if (right_->GetScore() >= WIN)
  {
    losing_screen_.SetPlayer2Wins();
    win = true;
  }

  ResetBall();

  if (win)
  {
    HideEntities();
    losing_screen_.Show();
    losing_ = true;
  }
}

void BouncyBallMain::OnKeyUp(int keysym, int state, int repeat)
{
  if (keysym == SDLK_ESCAPE && game_started_)
  {
    if (game_layer_->Paused())
    {
      pause_menu_.Hide();
      game_layer_->UnPause();
    }
    else
    {
      pause_menu_.Show();
      game_layer_->Pause();
    }
  }
}

void BouncyBallMain::UpdatePosition(sbe::World::Ptr const& world)
{
}

void BouncyBallMain::Update(float delta_time)
{
}

void BouncyBallMain::Draw(sbe::GraphicsRenderer* graphics)
{
  if (game_started_)
  {
    SDL_Rect dest = {0, 0, graphics->Width(), graphics->Height()};
    SDL_RenderCopy(graphics->Renderer(), background_, nullptr, &dest);

    if (game_layer_->Paused())
      pause_menu_.Draw(graphics);
  }
  else
  {
    if (!losing_)
      title_screen_.Draw(graphics);
    else
      losing_screen_.Draw(graphics);
  }
}

} // namespace bouncy_ball
