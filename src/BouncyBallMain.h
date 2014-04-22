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

#ifndef BOUNCY_BALL_MAIN_H
#define BOUNCY_BALL_MAIN_H

#include "Ball.h"
#include "BouncyGameData.h"
#include "LosingScreen.h"
#include "Paddle.h"
#include "PaddleAI.h"
#include "PauseMenu.h"
#include "Score.h"
#include "TitleScreen.h"

#include <sdl_backend/Entity.h>
#include <sdl_backend/EntityLayer.h>
#include <sdl_backend/MainLoop.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class BouncyBallMain : public sbe::Entity
{
public:
  typedef std::shared_ptr<BouncyBallMain> Ptr;

  BouncyBallMain(unsigned id, sbe::MainLoop const& main_loop);

  void UpdatePosition(sbe::World::Ptr const& world) override;
  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

private:
  void ResetGame();
  void StartGame();
  void SetupGame();

  void OnKeyUp(int keysym, int state, int repeat);

  void HideEntities();
  void ShowEntities();

  void ResetBall();

  void CheckIfWinning();

  sbe::MainLoop main_loop_;
  SDL_Texture* background_;
  BouncyGameData bouncy_data_;
  TitleScreen title_screen_;
  LosingScreen losing_screen_;
  PauseMenu pause_menu_;

  std::shared_ptr<Ball> ball_;
  std::shared_ptr<Score> left_;
  std::shared_ptr<Score> right_;
  std::shared_ptr<Paddle> left_paddle_;
  std::shared_ptr<PaddleAI> right_paddle_;

  sbe::EntityLayer::Ptr game_layer_;

  bool game_started_;
  bool losing_;
};

} // namespace bouncy_ball

#endif // BOUNCY_BALL_MAIN_H
