#ifndef _TEXTURELOADER_H_
#define _TEXTURELOADER_H_

#include "defines.h"

//Represents an image
class Image {
	public:
		Image(char* ps, int w, int h);
		~Image();

		/* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
		 * color of each pixel in image.  Color components range from 0 to 255.
		 * The array starts the bottom-left pixel, then moves right to the end
		 * of the row, then moves up to the next column, and so on.  This is the
		 * format in which OpenGL likes images.
		 */
		 //Array de pixels no formato R,G,B, R1,G1,B1
		 //Começa de baixo-esquerda, formato do openGL nativo
		char* pixels;
		int width;
		int height;
};

#endif

namespace texture
{
    //Le uma imagem BMP do arquivo
    extern GLuint loadTextureBMP(const char* filename);
    extern Image* loadBMP(const char* filename);
}

