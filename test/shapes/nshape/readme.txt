test_shapes.exe
Launching with different arguments should display different shapes in the top left, center, and right. As well as dead center, and bottom left, center, and right

CONTROLS:
Left Mouse Button: rotate 1 degree clockwise around origin point
Right Mouse Button: rotate 1 degree counter-clockwise around origin point

TESTS:
1) NO ARGUMENTS CASE
	- EXPECTED: line top left, triangle top center, rectangle top right. ellipse in the center and Square in the bottom left, with an octagon in the bottom center, and a circle in the bottom right
	
2) "circle" CASE
	- EXPECTED: Circles in all positions
	
3) "ellipse" CASE
	- EXPECTED: Circles along the top and center, double thick ellipses along the bottom
	
4) "line" CASE
	- EXPECTED: Lines in all positions
	
5) "tri" CASE
	- EXPECTED: Evenly proportioned triangles in all positions
	
6) "triangle" CASE
	- EXPECTED: Wide triangles in all positions
	
7) "square" CASE
	- EXPECTED: squares in all positions
	
8) "rectangle" CASE
	- EXPECTED: squares along top and center, rectangles along bottom
	
9) "poly" CASE
	- EXPECTED: 5 sided polygon in the top left, 6 sided polygon top center, and 7 sided polygon on the top right. Octagon dead center, with 9, 10, and 11 sided polygons along the bottom
	
10) "polygon" CASE
	- EXPECTED: Same as "poly" case but the polygons are not as tall