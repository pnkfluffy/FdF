This project is a wireframe mesh '3d' object renderer. It takes text files
such as those in the test_maps file, in which the there are numbers placed
around a board which correspond to the locations y value (height). The project
can be compiled using make, and run using ./fdf [map_text_file]. Or for example
'./fdf test_maps/extra/t1.fdf'.

Controls:
	-arrow keys for movement
	-WASD to increase the height and lean the object
	-'[' and ']' to zoom
	-'+' and '-' to pan the viewpoint
	-'r' to reset the parameters
	-'1' - '3' to change view types (wireframe, small points, large points)
	-'4' to randomize colors based on height

To Do:
	-true 3d rendering (not spoofed 3d)
	-better -custom controlled RGB based- color selection
	-implementation of Wu's line algorithm for anti-aliasing