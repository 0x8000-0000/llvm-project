//===--- VariableLengthCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "VariableLengthCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace readability {

void VariableLengthCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      varDecl(hasParent(declStmt(hasParent(forStmt())))).bind("loopVar"), this);
  Finder->addMatcher(varDecl(unless(hasParent(declStmt(hasParent(forStmt())))))
                         .bind("standaloneVar"),
                     this);
}

void VariableLengthCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *StandaloneVar = Result.Nodes.getNodeAs<VarDecl>("standaloneVar");
  if (StandaloneVar) {
    if (!StandaloneVar->getIdentifier() || StandaloneVar->getName().size() > 2)
      return;

    diag(StandaloneVar->getLocation(), "variable name %0 is too short")
        << StandaloneVar;
  }

  const auto *LoopVar = Result.Nodes.getNodeAs<VarDecl>("loopVar");
  if (LoopVar) {
    if (!LoopVar->getIdentifier() || LoopVar->getName().size() > 1)
      return;

    diag(LoopVar->getLocation(), "loop variable name %0 is too short")
        << LoopVar;
  }
}

} // namespace readability
} // namespace tidy
} // namespace clang
