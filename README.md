# Sand-physics

I had reviewed the original contents of the python based emulator and realized how slow it performed with iterations exceeding 100. Since every frame performs twice of O(n^2) operations, It performed slower and slower as the cell size was increased.


I opted to fix for faster and quicker iterations, but instead I decided to re write the entire simulator in c++. Not only does performance nearly double in efficiency, but I also implemented only two iterations per frame. That way the difference in speed is much more noticable. I am not familar with c++, so the code is primitive, and I most likely will make some small provisions in the future.
