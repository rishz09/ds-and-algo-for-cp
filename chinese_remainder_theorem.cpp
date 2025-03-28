/*
https://www.youtube.com/watch?v=EHDEvFuYPRQ

Helps to find solution to a system of modulo equations

x % 4 = 3
x % 6 = 5
x % 5 = 2

need x such that all of these are satisfied
for first equation:
x = 3, 7, 11, ... (+4)

for 1st and 2nd equation, first valid number = 11
After, by how many to increment?
NOTE: It will be LCM of the moduli values, ie, LCM(4, 6) = 12

so,
x = 11, 23, 35, 47, ... (+12)

for all 3 equations, 1st valid value = 47
For increments, we can get the LCM of previous LCM and current modulus value
LCM = LCM(12, 5) = 60

So, x = 47, 107, ... (+60)

Another example:
x % 4 = 1
x % 5 = 1
x % 3 = 0
x % 7 = 3

1st:
x = 1, 5, 9, ... (+4)

2nd:
x = 1, 21, ... (+20)

3rd:
x = 21, 81, ... (+60)

4th:
Now, we know what the jump will be
It is simple LCM calculation, ie, LCM(60, 7) = 420

BUT, what will be the first valid number? That is not trivial

Here are the steps:
-> Consider the last first valid number that we had found out.
-> It is 21
-> Now, to satisfy previous 3 equations, we need to always go in steps of 60

-> See this, for 4th equation, we have to get remainder with 7
-> Get the previous first valid number and remainder with 7
-> 21 % 7 = 0, but we need 3

-> Go in jumps of 60
-> This is how it works. 
-> New remainder = (prev remainder + 60 % 7) % 7

-> We go this way, and stop when we find 3 as remainder
-> 60 % 7 = 4

-> Initially, 21 % 7 = 0
-> so, steps:
-> 0 4 1 5 2 6 3 0

-> So, we found remainder as 3 after 6 jumps
-> So, the first valid x after considering all equations = 21 + 6 * 60 = 381
-> And, jump value = 420, as found out from LCM

But what is the time complexity of this procedure?
Notice that, finding remainders like this way follows a cycle
After exactly 7 elements, we are getting a cycle
That is, we had 0 initially, and after 7 elements we are 0 again

So, it is quite evident that for a given number k, we need to k steps at max
to get the desired remainder

If remainder is not found in these k steps, no valid number exists

So, for first single equation, it is trivial, and for the rest equations we can
apply this remainder finding technique

Then, TC = O(k1 + k2 + k3 + k4 + ...)
where ki = the number to be divided with in each equation

IMPORTANT:
-> After solving the system of equations till the end, the resulting sequence of 
solutions is the solution to the equation:

x % M = R
M = LCM of all moduli
R = first valid value in the resulting sequence

For the 2nd example, it is:
x % 420 = 381
*/

#include <bits/stdc++.h>
using namespace std;

// CRT: chinese remainder theorem
void CRT(vector<int> &modulus, vector<int> &remainder)
{
    int n = modulus.size();

    int firstVal = 0, jump = 1;
    for(int i=0; i<n; i++)
    {
        int rem = firstVal % modulus[i];
        int constJump = jump % modulus[i];

        bool found = false;
        for(int j=0; j<modulus[i]; j++)
        {
            if(rem == remainder[i])
            {
                found = true;
                firstVal += j * jump;
                break;
            }

            rem = (rem + constJump) % modulus[i];
        }

        if(!found)
        {
            cout << "Not Possible" << "\n";
            break;
        }
        
        // finding LCM
        jump = (jump * modulus[i]) / __gcd(jump, modulus[i]);

        cout << "Equation " << (i + 1) << ":\n";
        cout << "First Value: " << firstVal << "\n";
        cout << "Jump: " << jump << "\n\n";
    }
}

int main()
{
    vector<int> modulus = {4, 5, 3, 7};
    vector<int> remainder = {1, 1, 0, 3};

    CRT(modulus, remainder);
    return 0;
}