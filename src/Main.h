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

#ifndef MAIN_H
#define MAIN_H

#include "BouncyBallMain.h"

#include <sdl_backend/EntityLayer.h>

namespace bouncy_ball
{

class Main
{
public:
  Main();

private:
  sbe::MainLoop main_loop_;
  BouncyBallMain::Ptr bouncy_main_;
  sbe::EntityLayer::Ptr main_layer_;
};

} // namespace bouncy_ball

#endif // MAIN_H
