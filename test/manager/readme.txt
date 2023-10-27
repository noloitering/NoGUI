test_manager.exe
Tests all features of a Page with visuals. Columns represent keys/tags, and rows represent elements

CONTROLS:
DEL: delete all elements

TESTS:
1) CLICK EXISTING ELEMENT
	- EXPECTED: popup appears asking if you want to delete element. Can cancel, delete, or clear all elements with the same tag
	
2) CLICK ROW +
	- EXPECTED: adds an element to the row with the same tag
	
3) CLICK COLUMN +
	- EXPECTED: popup appears asking you to enter a new tag for the column. Repeated tags and "+" are not allowed. Can cancel. If valid tag is submitted an element is added