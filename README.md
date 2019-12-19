This project is a wireframe mesh '3d' object renderer. It takes text files such as those in the test_maps file, in which the there are numbers placed around a board which correspond to the locations y value (height). The project can be compiled using make, and run using ./fdf [map_text_file]. Or for example './fdf test_maps/extra/t1.fdf'. Currently only works on MacOS.

Controls:

	-arrow keys for movement
	-WASD to increase the height and lean the object
	-'[' and ']' to zoom
	-'+' and '-' to pan the viewpoint
	-'r' to reset the parameters
	-'1' - '3' to change view types (wireframe, small points, large points)
	-'4' to randomize colors based on height

To Do:

	-add linux support
	-true 3d rendering
	-better -custom controlled RGB based- color selection
	-smooth color gradients between points
	-implementation of Wu's line algorithm for anti-aliasing

![FdF Screenshot](https://cdn.discordapp.com/attachments/613478885174018084/650516404071694416/unknown.png)

![FdF Screenshot 2](https://media.discordapp.net/attachments/613478885174018084/628491975263387667/unknown.png)
