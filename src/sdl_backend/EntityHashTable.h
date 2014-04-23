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

#ifndef ENTITY_HASH_TABLE_H
#define ENTITY_HASH_TABLE_H

#include <unordered_map>

#include "Entity.h"

namespace sdl_backend
{

typedef std::pair<unsigned, Entity::Ptr> EntityPair;

class EntityHashTable
{
public:
  EntityHashTable();

  void add(Entity::Ptr const& entity);
  void remove(unsigned id);
  Entity::Ptr get(unsigned id);

  void clear();

  std::unordered_map<unsigned, Entity::Ptr> const& raw_table() const;

private:
  std::unordered_map<unsigned, Entity::Ptr> table_;
};

} // namespace sdl_backend

#endif // ENTITY_HASH_TABLE_H
