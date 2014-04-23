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

#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"
#include "EntityHashTable.h"
#include "EntityLayer.h"
#include "Rect.h"

#include <memory>
#include <vector>

namespace sdl_backend
{

class World
{
public:
  typedef std::shared_ptr<World> Ptr;

  World(Rect const& rect);

  Rect Boundary() const;
  void SetBoundary(Rect const& rect);

  void AddEntityLayer(EntityLayer::Ptr const& entity_layer);
  Entity::Ptr GetEntity(unsigned id);
  void RemoveEntity(unsigned id);

  void UpdatePositions(World::Ptr const& world);
  void Update(float delta_time);
  void Draw(GraphicsRenderer* renderer);

  void EmitKeyDown(int keysym, int state, int repeat);
  void EmitKeyUp(int keysym, int state, int repeat);

  void EmitTextInput(std::string text);

  void EmitMouseDown(int x, int y, int button, int clicks);
  void EmitMouseUp(int x, int y, int button, int clicks);

  void EmitMouseMove(int x, int y, int xrel, int yrel, int state);

  void EmitMouseWheel(int x, int y);

  void EmitFingerMotion(int x, int y, int dx, int dy);
  void EmitFingerDown(int x, int y, int dx, int dy);
  void EmitFingerUp(int x, int y, int dx, int dy);

  void SetGameData(void* game_data);
  void* GameData();

private:

  template <typename FUNC>
  void EmitSignal(FUNC func)
  {
    for (auto const& layer : entity_layers_)
      if (layer->Visible())
        for_each(layer->hash_table().begin(), layer->hash_table().end(), func);
  }

  std::vector<EntityLayer::Ptr> entity_layers_;
  void* game_data_;
  Rect rect_;
};

} // namespace sdl_backend

#endif // WORLD_H
