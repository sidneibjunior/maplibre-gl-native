# Build (on Linux)
- install mingw: `sudo apt install mingw-w64`
- create a folder `~/applications/mingw-install`
- download the required libraries and extract them under `~/applications/mingw-install`:
  - `libcurl`: https://curl.se/windows/
  - `libicu`: https://packages.msys2.org/package/mingw-w64-x86_64-icu
  - `libjpeg`: https://packages.msys2.org/package/mingw-w64-x86_64-libjpeg-turbo
  - `libpng`: https://packages.msys2.org/package/mingw-w64-x86_64-libpng
  <!-- - `X11`: `sudo apt install xorg-dev` -->
  - `glut mingw`: https://www.transmissionzero.co.uk/software/freeglut-devel/
  - `glew`: https://packages.msys2.org/package/mingw-w64-x86_64-glew
  - `opengl`: `sudo apt-get install libgl1-mesa-dev`
