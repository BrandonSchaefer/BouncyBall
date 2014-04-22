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

#include "GraphicsRenderer.h"

#include <iostream>
#include <stdexcept>

namespace sdl_backend
{

GraphicsRenderer::GraphicsRenderer()
  : width_(0)
  , height_(0)
{
}

GraphicsRenderer::~GraphicsRenderer()
{
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

void GraphicsRenderer::Init(std::string title, int width, int height)
{
  width_  = width;
  height_ = height;

  InitWindow(title);
  InitRenderer();
}

void GraphicsRenderer::InitWindow(std::string title)
{
  window_ = SDL_CreateWindow(title.c_str(),
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             width_, height_, SDL_WINDOW_SHOWN);

  if (!window_)
    throw std::runtime_error("Failed to create SDL_Window");
}

void GraphicsRenderer::InitRenderer()
{
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer_)
    throw std::runtime_error("Failed to create SDL_Renderer");
}

SDL_Window* GraphicsRenderer::Window() const
{
  return window_;
}

SDL_Renderer* GraphicsRenderer::Renderer() const
{
  return renderer_;
}

int GraphicsRenderer::Width() const
{
  return width_;
}

int GraphicsRenderer::Height() const
{
  return height_;
}


void GraphicsRenderer::SetRenderColor(SDL_Color const& color)
{
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
}

} // sdl_backend
