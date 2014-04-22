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

#include "World.h"
#include "GraphicsRenderer.h"

namespace sdl_backend
{

World::World(Rect const& rect)
  : rect_(rect)
{
}

Rect World::Boundary() const
{
  return rect_;
}

void World::SetBoundary(Rect const& rect)
{
  rect_ = rect;
}

void World::AddEntityLayer(EntityLayer::Ptr const& entity_layer)
{
  entity_layers_.push_back(entity_layer);
}

Entity::Ptr World::GetEntity(unsigned id)
{
  for (auto& layer : entity_layers_)
  {
    Entity::Ptr entity = layer->GetEntity(id);
    if (entity)
    {
      return entity;
    }
  }

  return nullptr;
}

void World::UpdatePositions(World::Ptr const& world)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->UpdatePosition(world);
      }
    }
  }
}

void World::Update(float delta_time)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->Update(delta_time);
      }
    }
  }
}

void World::Draw(GraphicsRenderer* renderer)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->Draw(renderer);
      }
    }
  }
}

void World::EmitKeyDown(int keysym, int state, int repeat)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->key_down.emit(keysym, state, repeat);
      }
    }
  }
}

void World::EmitKeyUp(int keysym, int state, int repeat)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->key_up.emit(keysym, state, repeat);
      }
    }
  }
}

void World::EmitTextInput(std::string text)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->text_input.emit(text);
      }
    }
  }
}

void World::EmitMouseDown(int x, int y, int button, int clicks)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->mouse_down.emit(x, y, button, clicks);
      }
    }
  }
}

void World::EmitMouseUp(int x, int y, int button, int clicks)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->mouse_up.emit(x, y, button, clicks);
      }
    }
  }
}

void World::EmitMouseMove(int x, int y, int xrel, int yrel, int state)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->mouse_move.emit(x, y, xrel, yrel, state);
      }
    }
  }
}

void World::EmitMouseWheel(int x, int y)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->mouse_wheel.emit(x, y);
      }
    }
  }
}

void World::EmitFingerMotion(int x, int y, int dx, int dy)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->finger_motion.emit(x, y, dx, dy);
      }
    }
  }
}

void World::EmitFingerDown(int x, int y, int dx, int dy)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->finger_down.emit(x, y, dx, dy);
      }
    }
  }
}

void World::EmitFingerUp(int x, int y, int dx, int dy)
{
  for (auto const& layer : entity_layers_)
  {
    if (layer->Visible())
    {
      for (auto const& e : layer->hash_table())
      {
        e.second->finger_up.emit(x, y, dx, dy);
      }
    }
  }
}

void World::SetGameData(void* game_data)
{
  game_data_ = game_data;
}

void* World::GameData()
{
  return game_data_;
}

} // namespace sdl_backend
