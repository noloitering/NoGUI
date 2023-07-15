test_imgs.exe
Tests the 4 different ways of displaying images (NONE, FIT, CUT, SCROLL) and manipulation of those images.


CONTROLS:
Spacebar: change display mode
Scrollwheel: scale image
W: Scale image up y direction
A: Scale image down x direction
S: Scale image down y direction
D: Scale image up x direction
Left Mouse Button: rotate 1 degree clockwise around origin point
Right Mouse Button: rotate 1 degree counter-clockwise around origin point
Q: toggle texture scrolling
E: toggle texture scrolling
ENTER: toggle texture scrolling
UP: scroll up
LEFT: scroll left
DOWN: scroll down
RIGHT: scroll right

TESTS:
1) "NONE" CASE
	- EXPECTED: Texture displayed as is centered on each element
	
2) "FIT" CASE
	- EXPECTED: Texture fit to exact dimensions as each respective element. Cannot scale
	
3) "CUT" CASE
	- EXPECTED: Texture takes shape of element, and will not exceed boundaries of that element. Scaling past the boundary will result in a zoom