/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef TENSORFLOW_COMPILER_XLA_SERVICE_GPU_LLVM_TARGET_HELPER_H_
#define TENSORFLOW_COMPILER_XLA_SERVICE_GPU_LLVM_TARGET_HELPER_H_

#include <string>

#include "absl/strings/string_view.h"
#include "absl/types/span.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Triple.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/Module.h"

namespace xla {
namespace gpu {

// Enmerations to get target specific intrinsics or function calls
enum class TargetIntrinsicID {
  kShfldownf32 = 0,
  kShfldowni32,
  kThreadidx,
  kThreadidy,
  kThreadidz,
  kBlockidx,
  kBlockidy,
  kBlockidz,
  kBarrierid
};

struct TargetIntrinsics {
  llvm::Intrinsic::ID nvptx_intrinsic;
  llvm::Intrinsic::ID amdgpu_intrinsic;
};

// Emits a call to the specified target intrinsic with the given operands.
// Overloaded
// intrinsics (for example, "minnum") must include a type in overloaded_types
// for each overloaded type. Typically, overloaded intrinsics have only a single
// overloaded type.
llvm::CallInst* EmitCallToTargetIntrinsic(
    TargetIntrinsicID intrinsic_id, absl::Span<llvm::Value* const> operands,
    absl::Span<llvm::Type* const> overloaded_types, llvm::IRBuilder<>* b);

}  // namespace gpu
}  // namespace xla

#endif  // TENSORFLOW_COMPILER_XLA_SERVICE_GPU_LLVM_TARGET_HELPER_H_
