#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "miniRT.h"


void	write_color(int file, t_vec3 *pixel_color)
{
	double r = pixel_color->x; 
	double g = pixel_color->y; 
	double b = pixel_color->z;
	int rbyte = (int)(255.999 * r);
	int gbyte = (int)(255.999 * g);
	int bbyte = (int)(255.999 * b);
	char pixel[16];
	int len = sprintf(pixel, "%d %d %d\n", rbyte, gbyte, bbyte);
	write(file, pixel, len);
}

int main(void)
{
	int i;
	int j;
	int image_height;
	int image_width;
	int file;
	int aspect_ratio = 16 / 9;

	file = open("image.ppm", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1) {
		write(2, "Error opening file\n", 19);
		return (1);
	}
	image_width = 400;
	// Calculate the image height, and ensure that it's at least 1.
	image_height = image_width / aspect_ratio;
	if (image_height < 1)
	{
		image_height = 1;
	}
	// Viewport widths less than one are ok since they are real valued.
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)(image_width)/image_height);

	write(file, "P3\n", 3);
	write(file, "256 256\n", 8);
	write(file, "255\n", 4);
	i = 0;
	while (i < image_height)
	{
		j = 0;
		while (j < image_width)
		{
			t_vec3 pixel_color = {(double)(i)/(image_width-1), (double)(j)/(image_height-1), 0};
			write_color(file, &pixel_color);
			j++;
		}
		i++;
	}
	close(file);
	return (0);
}
