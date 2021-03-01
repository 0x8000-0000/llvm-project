// RUN: %check_clang_tidy %s readability-declare-near-usage %t

void f1()
{
   int i;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable 'i' declared here is first used on line [[@LINE+8]] [readability-declare-near-usage]

   int j;

   int k;

   int p;

   i = 5;
}

void setFarAway()
{
   int i = 5;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable 'i' declared here is first used on line [[@LINE+5]] [readability-declare-near-usage]

   int k;
   k = 3;

   i = 4;
}

void producer(int& val);

void consumer(int val);

void produceFarAway()
{
   int a = 5;
// CHECK-MESSAGES: :[[@LINE-1]]:8: warning: variable 'a' declared here is first used on line [[@LINE+5]] [readability-declare-near-usage]

   int k;
   k = 3;

   producer(a);
}

void produceNear()
{
   int b = 5;
   producer(b);

   b = 7;
}

#if 0
void badUseInDifferentScope()
{
   int q;

   for (int r = 0; r < 42; ++r)
   {
      int s = 5;

      q = s + 2;

      consumer(q);
   }
}

void goodUseInDifferentScope()
{
   int q = 7;

   for (int r = 0; r < 42; ++r)
   {
      int s = 5;

      q += s;
   }

   consumer(q);
}

void goodUseAtADistance()
{
   int a = 1;
   int b = 2;
   int c = 3;
   int d = 4;
   int e = 5;
   int f = a + b + c + d + e;
}
#endif
