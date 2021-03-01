//===--- DeclareNearUsageCheck.h - clang-tidy -------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_READABILITY_DECLARENEARUSAGECHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_READABILITY_DECLARENEARUSAGECHECK_H

#include "../ClangTidyCheck.h"

#include <map>

namespace clang {
namespace tidy {
namespace readability {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/readability-declare-near-usage.html
class DeclareNearUsageCheck : public ClangTidyCheck {
public:
  DeclareNearUsageCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
  void onEndOfTranslationUnit() override;

private:
  struct Usage {
    Usage() = default;
    Usage(unsigned declare, unsigned use)
        : declareLine{declare}, useLine{use} {}
    unsigned declareLine = 0;
    unsigned useLine = 0;
  };

  std::map<const ValueDecl *, Usage> NearestUsageToDeclaration;
};

} // namespace readability
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_READABILITY_DECLARENEARUSAGECHECK_H
