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

#include "EntityHashTable.h"

namespace sdl_backend
{

EntityHashTable::EntityHashTable()
{
}

void EntityHashTable::add(Entity::Ptr const& entity)
{
  table_[entity->id()] = entity;
}

void EntityHashTable::remove(unsigned id)
{
  table_.erase(id);
}

Entity::Ptr EntityHashTable::get(unsigned id)
{
  if (table_.find(id) == table_.end())
    return nullptr;

  return table_[id];
}

std::unordered_map<unsigned, Entity::Ptr> const& EntityHashTable::raw_table() const
{
  return table_;
}

void EntityHashTable::clear()
{
  table_.clear();
}

} // namespace sdl_backend
