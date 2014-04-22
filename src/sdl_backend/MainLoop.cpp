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
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "MainLoop.h"
#include "SDLTimer.h"

#include <sys/time.h>
#include <iostream>

#include <stdexcept>

namespace sdl_backend
{

namespace
{
  int const FRAMES_PER_SECOND = 60;
  float const ONE_SECOND      = 1000.0f;
}

MainLoop::MainLoop(std::string title, int width, int height)
  : world_(std::make_shared<World>(Rect(0, 0, width, height)))
{
  try
  {
    InitSDL();
    graphics_.Init(title, width, height);
  }
  catch (std::runtime_error const& e)
  {
    std::cerr << "Caught runtime error: " << e.what() << std::endl;
  }
}

MainLoop::~MainLoop()
{
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void MainLoop::InitSDL() const
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    throw std::runtime_error("Failed to INIT SDL");

  if (IMG_Init(IMG_INIT_PNG) < 0)
    throw std::runtime_error("Failed to INIT IMG");

  if (TTF_Init() < 0)
    throw std::runtime_error("Failed to INIT TTF");

  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16SYS;
  int audio_channels = 2;
  int audio_buffers = 4096;

  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    throw std::runtime_error("Failed to INIT audio/mixer");
}

SDL_Renderer* MainLoop::Renderer() const
{
  return graphics_.Renderer();
}

SDL_Window* MainLoop::Window() const
{
  return graphics_.Window();
}

World::Ptr MainLoop::world() const
{
  return world_;
}

bool MainLoop::EmitEventSignals()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_KEYDOWN:
        world_->EmitKeyDown(event.key.keysym.sym, event.key.state, event.key.repeat);
        break;
      case SDL_KEYUP:
        world_->EmitKeyUp(event.key.keysym.sym, event.key.state, event.key.repeat);
        break;
      case SDL_TEXTINPUT:
        world_->EmitTextInput(event.text.text);
        break;
      case SDL_MOUSEBUTTONDOWN:
        world_->EmitMouseDown(event.button.x, event.button.y,
                        event.button.button, event.button.clicks);
        break;
      case SDL_MOUSEBUTTONUP:
        world_->EmitMouseUp(event.button.x, event.button.y,
                              event.button.button, event.button.clicks);
        break;
      case SDL_MOUSEMOTION:
        world_->EmitMouseMove(event.motion.x, event.motion.y,
                              event.motion.xrel, event.motion.yrel, event.motion.state);
        break;
      case SDL_MOUSEWHEEL:
        world_->EmitMouseWheel(event.wheel.x, event.wheel.y);
        break;
      case SDL_FINGERMOTION:
        world_->EmitFingerMotion(event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy);
        break;
      case SDL_FINGERDOWN:
        world_->EmitFingerDown(event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy);
        break;
      case SDL_FINGERUP:
        world_->EmitFingerUp(event.tfinger.x, event.tfinger.y, event.tfinger.dx, event.tfinger.dy);
        break;
      case SDL_QUIT:
        return false;
      default:
        break;
    }
  }

  return true;
}

void MainLoop::EmitDrawSignal()
{
  SDL_RenderClear(graphics_.Renderer());
  world_->Draw(&graphics_);
  SDL_RenderPresent(graphics_.Renderer());
}

void MainLoop::EmitUpdateSignal(float delta_time)
{
  world_->UpdatePositions(world_);
  world_->Update(delta_time);
}

void MainLoop::StartMainLoop()
{
  float delta_time = 0.0f;
  bool done = false;
  SDLTimer fps;

  while (!done)
  {
    fps.start();

    if (!EmitEventSignals())
      done = true;

    EmitUpdateSignal(delta_time);
    EmitDrawSignal();

    if (fps.ticks() < ONE_SECOND / FRAMES_PER_SECOND)
      SDL_Delay((ONE_SECOND / FRAMES_PER_SECOND) - fps.ticks());

    delta_time = fps.ticks() / ONE_SECOND;
  }
}

} // sdl_backend
