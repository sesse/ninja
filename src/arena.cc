// Copyright 2024 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "arena.h"

#include <algorithm>

char* Arena::AllocSlowPath(size_t num_bytes)
{
  size_t to_allocate = std::max(next_size_, num_bytes);

  Block new_block;
  new_block.mem.reset(new char[to_allocate]);

  char *ret = new_block.mem.get();
  cur_ptr_ = new_block.mem.get() + num_bytes;
  cur_end_ = new_block.mem.get() + to_allocate;

  blocks.push_back(std::move(new_block));
  next_size_ += next_size_ / 2;

  return ret;
}

