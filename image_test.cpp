#include "image_test.h"
inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

Image::Image() {
}
Image::Image(const char* filename) {
	//printf("%s\n", exists_test1(filename) ? "true" : "false");
	int n;
	unsigned char* data = stbi_load(filename, &width, &height, &n, 4);
	if (data == NULL) {
		printf("ERROR LOADING IMAGE");
		return;
	}
	glGenTextures(1, &textureID);
	
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//printf("TexID: %i\nValid: %s\nError: %s\n", textureID, glIsTexture(textureID) ? "true" : "false", gluErrorString(glGetError()));

	//printf("W/H: (%d, %d)\n", width, height);
	//printf("%d %d %d %d\n",*(data+30),*(data+31),*(data+32),*(data+33));
	stbi_image_free(data);

}

Image::~Image() {
}

void Image::render(int x, int y, float angle, float scale) {
	if( textureID != 0 )
	{
		//printf("%i , %i\n", x, y);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(1.0,1.0,1.0, 1.0);
		glTranslatef( x, y, 0.0f );
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture( GL_TEXTURE_2D, textureID );
		glBegin( GL_QUADS );
				glTexCoord2f( 0.0f, 0.0f ); glVertex2f(        0.0f,         0.0f );
				glTexCoord2f( 1.0f, 0.0f ); glVertex2f( width*scale,         0.0f );
				glTexCoord2f( 1.0f, 1.0f ); glVertex2f( width*scale, height*scale );
				glTexCoord2f( 0.0f, 1.0f ); glVertex2f(        0.0f, height*scale );
		glEnd();
		//printf("TexID: %i\nValid: %s\nError: %s\n", textureID, glIsTexture(textureID) ? "true" : "false", gluErrorString(glGetError()));
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
