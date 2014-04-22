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

#ifndef BUTTON_H
#define BUTTON_H

#include <sdl_backend/Entity.h>
#include <sdl_backend/StringTexture.h>
#include <sdl_backend/World.h>

namespace sbe = sdl_backend;

namespace bouncy_ball
{

class Button : public sbe::Entity
{
public:
  Button(unsigned id, SDL_Renderer* renderer);

  void UpdatePosition(sbe::World::Ptr const& world) override;
  void Update(float delta_time) override;
  void Draw(sbe::GraphicsRenderer* graphics) override;

  void SetFontSize(int font_size);
  void SetText(std::string const& message);

  void Hightlight();
  void UnHightlight();

  sigc::signal<void> clicked;

private:
  void UpdateStringTexture();
  
  sbe::StringTexture message_;
  int border_size_;
  bool mouse_over_;
  bool highlight_;
};

} // namespace bouncy_ball

#endif // BUTTON_H
