/*

TO DO:

KEEP TRACK OF:
- Sprite Pos in Sheet
- Which frame
- Time between next frame

YOU KNOW THE REST BRO
STAY GOLDEN

*/
#include "stb_image.h"
#include <string>
#include <vector>
#include <map>
#include <Box2D/Box2D.h>
#include <glut.h>

//#ifndef sprites
//#define sprites
#define GL_CLAMP_TO_EDGE 0x812f

class SpriteSheet {
	private:
		std::map<std::string, std::vector<std::vector<b2Vec2>>> spriteMap;
		std::map<std::string, int> frameNumber;
		std::map<std::string, float> frameTime;
		std::map<std::string, b2Vec2> frameSize;
		std::map<std::string, int> basetime;

		GLuint textureID;
	public:
		int width, height;
		SpriteSheet();
		SpriteSheet(const char* fileName);
		
		virtual ~SpriteSheet();

		void setFrameNum(std::string sequence, int frame);
		b2Vec2 getSequenceSize(std::string sequence);

		void initSequence(std::string, float frametime, float width, float height);
		void addAnimationRow(std::string, int row, int size);
		void addSequenceFrame(std::string sequence, b2Vec2 position);
		
		void renderPart(std::vector<b2Vec2> texCoords, int x, int y, float angle, float scale, b2Vec2 size);
		void render(std::string sequence, int x, int y, float angle, float scale);
		void renderFrame(std::string sequence, int frame, int x, int y, float angle, float scale);
};
//#else
//class SpriteSheet;
//#endif