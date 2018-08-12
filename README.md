## Compiling:
Compile with VS2015 (libs for VS2015 from: https://github.com/guaxiao/renderer.gua/tree/master/platform/win/SDL-1.2.15/vs2015-x86, there are problems with the original libs in SDL site).
Check that the "Libs" folder in the solution folder, otherwise SDL includes and libs will be missing and the build will fail.
The dlls of SDL are in the "Libs/SDL-1.2.15/dll" folder
## Code:
Followed "Google C++ Style Guide" (excluding "#pragma once" and maybe more)
	
## Graphics:
The tiles (Resources/breakout_tiles.png and also folder Bricks/) (and more) from here: https://opengameart.org/content/breakout-graphics-no-shadow

## License:
The code under the GPL v3, also some of the resources that are not taken from the tiles, 
all other content under other licenses as described earlier in this README or on the sites corresponds to that files (such as SDL libs).
