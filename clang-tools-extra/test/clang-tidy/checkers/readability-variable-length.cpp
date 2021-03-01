// RUN: %check_clang_tidy %s readability-variable-length %t \
// RUN: -config='{CheckOptions: \
// RUN:  [{key: readability-variable-length.IgnoredVariableNames, value: "^[xy]$"}]}' \
// RUN: --

struct myexcept
{
   int val;
};

struct simpleexcept
{
   int other;
};

void doIt();

void tooShortVariableNames(int z)
// CHECK-MESSAGES: :[[@LINE-1]]:32: warning: parameter name 'z' is too short, expected at least 3 characters [readability-variable-length]
{
   int i = 5;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable name 'i' is too short, expected at least 3 characters [readability-variable-length]

   int jj = z;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable name 'jj' is too short, expected at least 3 characters [readability-variable-length]

   for (int m = 0; m < 5; ++ m)
// CHECK-MESSAGES: :[[@LINE-1]]:13: warning: loop variable name 'm' is too short, expected at least 2 characters [readability-variable-length]
   {
      doIt();
   }

   try
   {
      doIt();
   }
   catch (const myexcept& x)
// CHECK-MESSAGES: :[[@LINE-1]]:27: warning: exception variable name 'x' is too short, expected at least 2 characters [readability-variable-length]
   {
      doIt();
   }
}

void longEnoughVariableNames(int n) // argument 'n' ignored by configuration
{
   int var = 5;

   for (int i = 0; i < 42; ++ i) // 'i' is default allowed, for historical reasons
   {
      doIt();
   }

   for (int kk = 0; kk < 42; ++ kk)
   {
      doIt();
   }

   try
   {
      doIt();
   }
   catch (const simpleexcept& e) // ignored via default configuration
   {
      doIt();
   }
   catch (const myexcept& ex)
   {
      doIt();
   }

   int x = 5;  // ignored by configuration
}
