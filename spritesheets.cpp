#include "spritesheets.h"
inline bool exists_test1 (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}

SpriteSheet::SpriteSheet() {
}


SpriteSheet::SpriteSheet(const char* filename) {
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//printf("TexID: %i\nValid: %s\nError: %s\n", textureID, glIsTexture(textureID) ? "true" : "false", gluErrorString(glGetError()));

	//printf("W/H: (%d, %d)\n", width, height);
	//printf("%d %d %d %d\n",*(data+30),*(data+31),*(data+32),*(data+33));
	stbi_image_free(data);

}

SpriteSheet::~SpriteSheet() {
	printf("BALLS\n");
	//glDeleteTextures(1, &textureID);
}

void SpriteSheet::initSequence(std::string sequence, float frametime, float width, float height) {
	frameNumber[sequence] = 0;
	frameTime[sequence] = frametime;
	frameSize[sequence] = b2Vec2(width, height);
}

void SpriteSheet::addAnimationRow(std::string sequence, int row, int size) {
	int y = row;
	for(int i = 0;i < size; i++) {
		addSequenceFrame(sequence, b2Vec2(i * frameSize[sequence].x, y));
	}
}

void SpriteSheet::setFrameNum(std::string sequence, int frame) {
	frameNumber[sequence] = frame % spriteMap[sequence].size();
}

b2Vec2 SpriteSheet::getSequenceSize(std::string sequence) {
	return frameSize[sequence];
}

void SpriteSheet::addSequenceFrame(std::string sequence, b2Vec2 position) {
	float a2 = frameSize[sequence].x / width;
	float b2 = frameSize[sequence].y / height;
	
	float c2 = position.x / width;
	float d2 = position.y / height;

	/*b2Vec2 A = b2Vec2(c2, d2);
	b2Vec2 B = b2Vec2(c2, d2 + b2);
	b2Vec2 C = b2Vec2(c2 + a2, d2 + b2);
	b2Vec2 D = b2Vec2(c2 + a2, d2);*/

	b2Vec2 D = b2Vec2((position.x/frameSize[sequence].x)*a2,(position.y)*b2);
	b2Vec2 B = b2Vec2(D.x + a2, D.y + b2);
	b2Vec2 A = b2Vec2(D.x, B.y);
	b2Vec2 C = b2Vec2(B.x, D.y);

	std::vector<b2Vec2> corners;
	corners.push_back(A);
	corners.push_back(B);
	corners.push_back(C);
	corners.push_back(D);
	spriteMap[sequence].push_back(corners);
}

void SpriteSheet::renderPart(std::vector<b2Vec2> texCoords, int x, int y, float angle, float scale, b2Vec2 size, bool flip) {
	if( textureID != 0 )
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(1.0,1.0,1.0, 1.0);
		glTranslatef( x, y, 0.0f );
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture( GL_TEXTURE_2D, textureID );
		glBegin( GL_QUADS ); 
		if(!flip) {
			glTexCoord2f( texCoords[0].x, texCoords[0].y ); glVertex2f(         0.0f,         0.0f );
			glTexCoord2f( texCoords[1].x, texCoords[1].y ); glVertex2f( size.x*scale,         0.0f );
			glTexCoord2f( texCoords[2].x, texCoords[2].y ); glVertex2f( size.x*scale, size.y*scale );
			glTexCoord2f( texCoords[3].x, texCoords[3].y ); glVertex2f(         0.0f, size.y*scale );
			glEnd();
		}
		else {
			float tex = 1.0f - texCoords[0].x;
			glTexCoord2f( texCoords[1].x, texCoords[1].y ); glVertex2f(         0.0f,         0.0f );
			glTexCoord2f( texCoords[0].x, texCoords[0].y ); glVertex2f( size.x*scale,         0.0f );
			glTexCoord2f( texCoords[3].x, texCoords[3].y ); glVertex2f( size.x*scale, size.y*scale );
			glTexCoord2f( texCoords[2].x, texCoords[2].y ); glVertex2f(         0.0f, size.y*scale );
			glEnd();	
		}
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();
	}
}

void SpriteSheet::renderFrame(std::string animation, int frame, int x, int y, float angle, float scale, bool flip) {
	if(frame < spriteMap[animation].size())
		renderPart(spriteMap[animation][frame], x, y, angle, scale, frameSize[animation], flip);
}

void SpriteSheet::render(std::string animation, int x, int y, float angle, float scale, bool flip) {
	int size = spriteMap[animation].size();

	int curr = frameNumber[animation];
	int time = glutGet(GLUT_ELAPSED_TIME);
	if ((time - basetime[animation]) > frameTime[animation])
	{
		frameNumber[animation] += 1;
		curr += 1;
		if(curr > size - 1) {
			curr = 0;
			frameNumber[animation] = 0;
		}
		basetime[animation] = time;
	}
	renderPart(spriteMap[animation][curr], x, y, angle, scale, frameSize[animation], flip);
}