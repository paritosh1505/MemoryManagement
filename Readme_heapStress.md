**For heap stress**

1.Allocate N (e.g., 10–20) blocks of random sizes (1–256 bytes).

2.Fill each block with a known pattern (e.g., index number).

3.Randomly free half of them.

4.Reallocate new blocks for the freed ones (reuse pointers correctly).

5.Finally, free all remaining memory cleanly.

6.Program must pass:
