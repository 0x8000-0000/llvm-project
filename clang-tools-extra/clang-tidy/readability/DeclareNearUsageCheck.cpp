//===--- DeclareNearUsageCheck.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DeclareNearUsageCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

#include <utility>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace readability {

void DeclareNearUsageCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(declRefExpr().bind("reference"), this);
}

void DeclareNearUsageCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedRef = Result.Nodes.getNodeAs<DeclRefExpr>("reference");

  const auto *Decl = MatchedRef->getDecl();

  if (!Decl)
    return;

  if (!isa<VarDecl>(Decl))
     return;

  auto &SourceManager = Result.SourceManager;

  const auto declareLine =
      SourceManager->getPresumedLoc(Decl->getLocation()).getLine();
  const auto useLine =
      SourceManager->getPresumedLoc(MatchedRef->getLocation()).getLine();

  auto iter = NearestUsageToDeclaration.find(Decl);
  if (iter == NearestUsageToDeclaration.end()) {
    NearestUsageToDeclaration[Decl] = Usage{declareLine, useLine};
  } else {
    if (iter->second.useLine > useLine) {
      iter->second.useLine = useLine;
    }
  }
}

void DeclareNearUsageCheck::onEndOfTranslationUnit() {
  for (const auto& iter : NearestUsageToDeclaration) {
     const ValueDecl *Decl = iter.first;

    if (iter.second.useLine > (iter.second.declareLine + 3)) {
      diag(Decl->getLocation(),
           "variable %0 declared here is first used on line %1")
          << iter.first << iter.second.useLine;
    }
  }
}

} // namespace readability
} // namespace tidy
} // namespace clang
