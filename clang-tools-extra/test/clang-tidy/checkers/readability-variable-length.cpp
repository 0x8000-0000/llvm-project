// RUN: %check_clang_tidy %s readability-variable-length %t

void f()
{
   int i = 5;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable name 'i' is too short [readability-variable-length]
   int jj = 6;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable name 'jj' is too short [readability-variable-length]
   int var = 5;
}

void g()
{
   for (int m = 0; m < 5; ++ m)
// CHECK-MESSAGES: :[[@LINE-1]]:13: warning: loop variable name 'm' is too short [readability-variable-length]
   {
      f();
   }

   for (int kk = 0; kk < 42; ++ kk)
   {
      f();
   }
}
