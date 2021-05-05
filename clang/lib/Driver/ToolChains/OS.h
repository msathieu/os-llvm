//===--- OS.h - OS ToolChain Implementations ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
// Modified by MSathieu

#pragma once
#include "Gnu.h"

namespace clang {
namespace driver {
namespace tools {
namespace os {
class LLVM_LIBRARY_VISIBILITY Linker : public Tool {
public:
  Linker(const ToolChain &TC) : Tool("os::Linker", "linker", TC) {}
  bool hasIntegratedCPP() const override { return false; }
  bool isLinkJob() const override { return true; }
  void ConstructJob(Compilation &C, const JobAction &JA,
                    const InputInfo &Output, const InputInfoList &Inputs,
                    const llvm::opt::ArgList &TCArgs,
                    const char *LinkingOutput) const override;
};
} // namespace os
} // namespace tools
namespace toolchains {
class LLVM_LIBRARY_VISIBILITY MyOS : public Generic_ELF {
public:
  MyOS(const Driver &D, const llvm::Triple &Triple,
       const llvm::opt::ArgList &Args);
  bool HasNativeLLVMSupport() const override { return true; }
  LangOptions::StackProtectorMode
  GetDefaultStackProtectorLevel(bool KernelOrKext) const override {
    return LangOptions::SSPStrong;
  }
  void
  AddClangSystemIncludeArgs(const llvm::opt::ArgList &DriverArgs,
                            llvm::opt::ArgStringList &CC1Args) const override;
  const char *getDefaultLinker() const override { return "ld.lld"; }

protected:
  Tool *buildLinker() const override;
};
} // end namespace toolchains
} // end namespace driver
} // end namespace clang
