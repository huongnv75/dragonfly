// Copyright 2022, Roman Gershman.  All rights reserved.
// See LICENSE for licensing terms.
//

#pragma once

#include <absl/strings/ascii.h>
#include <absl/types/span.h>

#include <string_view>
#include <vector>
#include "facade/facade_types.h"

namespace dfly {

enum class ListDir : uint8_t { LEFT, RIGHT };


using DbIndex = uint16_t;
using ShardId = uint16_t;
using TxId = uint64_t;
using TxClock = uint64_t;

using facade::MutableSlice;
using facade::CmdArgList;
using facade::CmdArgVec;
using facade::ArgS;

using ArgSlice = absl::Span<const std::string_view>;

constexpr DbIndex kInvalidDbId = DbIndex(-1);
constexpr ShardId kInvalidSid = ShardId(-1);
constexpr DbIndex kMaxDbId = 1024;  // Reasonable starting point.

class CommandId;
class Transaction;
class EngineShard;

struct KeyLockArgs {
  DbIndex db_index;
  ArgSlice args;
  unsigned key_step;
};

// Describes key indices.
struct KeyIndex {
  unsigned start;
  unsigned end;  // does not include this index (open limit).
  unsigned step; // 1 for commands like mget. 2 for commands like mset.
};

struct OpArgs {
  EngineShard* shard;
  DbIndex db_ind;
};

inline void ToUpper(const MutableSlice* val) {
  for (auto& c : *val) {
    c = absl::ascii_toupper(c);
  }
}

inline void ToLower(const MutableSlice* val) {
  for (auto& c : *val) {
    c = absl::ascii_tolower(c);
  }
}

}  // namespace dfly