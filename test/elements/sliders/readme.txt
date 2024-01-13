test_sliders.exe
tests 3 different slider classes: Slider Base Class, Cursorer Inherited Class, and NotchedCursorer.

CONTROLS:
CLICK + DRAG: change value of slider
ANGLE: change angle of sliders
ALIGN: change alignment of slide/cursor
MULTIPLIER: changes the rate of increase of the sliders values

TESTS:
LEFT ALIGNMENT: all Slider values should be positive (assuming positive multiplier).

CENTER ALIGNMENT: Slider value should be positive (assuming positive multiplier), and Cursorer values should be positive past the centerpoint, and negative behind the centerpoint (assuming positive multiplier).

RIGHT ALIGNMENT: Slider value should be positive (assuming positive multiplier), and Cursorer values should be negative (assuming positive multiplier).
