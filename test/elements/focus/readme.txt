test_hover.exe
Launching with different arguments should display different shapes in the top left, center, and right. As well as dead center, and bottom left, center, and right

CONTROLS:
Scroll Up: rotate 1 degree clockwise around origin point
Scroll Down: rotate 1 degree counter-clockwise around origin point
Button: flickers red for a single frame when clicked
Hoverable: turns red when hovered
Toggle: turns red when clicked, and returns to white when clicked again
Trigger: holds red as long as mouse button is down on it
Slider: Like Trigger, but with another rectangle that scales to the length of the mouse
CheckBox: turns red and displays text when clicked
Cursorer: Like trigger, but a smaller shape follows the mouse cursor

TESTS:
1) NO ARGUMENTS CASE
	- EXPECTED: circle top left, line top center, square top right. Triangle in the center and Square in the bottom left, with an octagon in the bottom center, and another circle in the bottom right.
	
2) "circle" CASE
	- EXPECTED: Circles in all positions
	
3) "ellipse" CASE
	- EXPECTED: Circles along the top and center, double thick ellipses along the bottom
	
4) "line" CASE
	- EXPECTED: Lines in all positions
	
5) "tri" CASE
	- EXPECTED: Triangles in all positions
	
6) "triangle" CASE
	- EXPECTED: regular triangles along top and center, double thick triangles along the bottom
	
7) "square" CASE
	- EXPECTED: squares in all positions
	
8) "rectangle" CASE
	- EXPECTED: squares along top and center, rectangles along bottom
	
9) "poly" CASE
	- EXPECTED: 5 sided polygon in the top left, 6 sided polygon top center, and 7 sided polygon on the top right. Octagon dead center, with 9, 10, and 11 sided polygons along the bottom
	
10) "polygon" CASE
	- EXPECTED: Same as "poly" case but the polygons along the bottom are doubly thick