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

#ifndef ENTITY_LAYER_H
#define ENTITY_LAYER_H

#include "Entity.h"
#include "EntityHashTable.h"

#include <memory>

namespace sdl_backend
{

class EntityLayer
{
public:
  typedef std::shared_ptr<EntityLayer> Ptr;

  EntityLayer();

  void AddEntity(Entity::Ptr const& entity);
  void RemoveEntity(unsigned id);
  Entity::Ptr GetEntity(unsigned id);

  void Pause();
  void UnPause();

  void Show();
  void Hide();

  bool Paused() const;
  bool Visible() const;

  std::unordered_map<unsigned, Entity::Ptr> const& hash_table() const;

private:
  EntityHashTable hash_table_;

  bool paused_;
  bool visible_;

};

} // namespace sdl_backend

#endif // ENTITY_LAYER_H
