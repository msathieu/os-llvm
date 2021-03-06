//===-- EPCEHFrameRegistrar.h - EPC based eh-frame registration -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// ExecutorProcessControl based eh-frame registration.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_EXECUTIONENGINE_ORC_EPCEHFRAMEREGISTRAR_H
#define LLVM_EXECUTIONENGINE_ORC_EPCEHFRAMEREGISTRAR_H

#include "llvm/ExecutionEngine/JITLink/EHFrameSupport.h"

namespace llvm {
namespace orc {

class ExecutionSession;

/// Register/Deregisters EH frames in a remote process via a
/// ExecutorProcessControl instance.
class EPCEHFrameRegistrar : public jitlink::EHFrameRegistrar {
public:
  /// Create from a ExecutorProcessControl instance alone. This will use
  /// the EPC's lookupSymbols method to find the registration/deregistration
  /// funciton addresses by name.
  static Expected<std::unique_ptr<EPCEHFrameRegistrar>>
  Create(ExecutionSession &ES);

  /// Create a EPCEHFrameRegistrar with the given ExecutorProcessControl
  /// object and registration/deregistration function addresses.
  EPCEHFrameRegistrar(ExecutionSession &ES,
                      JITTargetAddress RegisterEHFrameWrapperFnAddr,
                      JITTargetAddress DeregisterEHFRameWrapperFnAddr)
      : ES(ES), RegisterEHFrameWrapperFnAddr(RegisterEHFrameWrapperFnAddr),
        DeregisterEHFrameWrapperFnAddr(DeregisterEHFRameWrapperFnAddr) {}

  Error registerEHFrames(JITTargetAddress EHFrameSectionAddr,
                         size_t EHFrameSectionSize) override;
  Error deregisterEHFrames(JITTargetAddress EHFrameSectionAddr,
                           size_t EHFrameSectionSize) override;

private:
  ExecutionSession &ES;
  JITTargetAddress RegisterEHFrameWrapperFnAddr;
  JITTargetAddress DeregisterEHFrameWrapperFnAddr;
};

} // end namespace orc
} // end namespace llvm

#endif // LLVM_EXECUTIONENGINE_ORC_EPCEHFRAMEREGISTRAR_H
