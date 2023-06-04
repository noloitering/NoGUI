test_imgs.exe
Tests the 4 different ways of displaying images (NONE, FIT, CUT, SCROLL) and manipulation of those images.

CONTROLS:
Spacebar: change display mode
Scrollwheel: scale image
Left Mouse Button: rotate 1 degree clockwise around origin point
Right Mouse Button: rotate 1 degree counter-clockwise around origin point

TESTS:
1) "NONE" CASE
	- EXPECTED: Texture displayed as is centered on each element
	
2) "FIT" CASE
	- EXPECTED: Texture fit to exact dimensions as each respective element. Cannot scale
	
3) "CUT" CASE
	- EXPECTED: Texture takes shape of element, and will not exceed boundaries of that element. Scaling past the boundary will result in a zoom
	
4) "SCROLL" CASE
	- EXPECTED: 