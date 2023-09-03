test_text.exe
Tests drawing fonts in 9 different alignments, and manipulation of that font

CONTROLS:
Scrollwheel: scale text
UP: increase vertical spacing between lines
LEFT: decrease horizontal spacing between characters
DOWN: decrease vertical spacing between lines
RIGHT: increase horizontal spacing between characters
Z: change origin point to top left corner of element
X: change origin point to top right corner of element
C: change origin point to center of element
V: change origin point to top center of element
B: change origin point to bottom center of element
N: change origin point to bottom left corner of element
M: change origin point to bottom right corner of element
,: change origin point to center left of element
.: change origin point to center right of element

TESTS:
1) NO ARGUMENTS CASE
	- EXPECTED: raylib default font
	
2) FONTFILE LOCATION CASE
	- EXPECTED: load font from provided path