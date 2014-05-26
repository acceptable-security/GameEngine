#include <fstream>
#include <string.h>
#include "level.h"

std::string get_file_contents(const char *filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	return "";
}


namespace GameEngine {
	void loadLevel(const char* file, World* world, int windowWidth, int windowHeight) {
		Json::Value root;
		Json::Reader reader;

		std::string contents = get_file_contents(file);
		const char* more = contents.c_str();
		
		bool parsingSuccessful = reader.parse(more, root);
		if(parsingSuccessful) {
			const Json::Value spawnPoint = root["spawn-point"];
			
			int spawn_x = spawnPoint[(Json::Value::ArrayIndex)0].asInt();
			int spawn_y = spawnPoint[(Json::Value::ArrayIndex)1].asInt();
				
			b2Vec2 spawnpoint(spawn_x, spawn_y);
				
			const char* background = root.get("background-image", "none.png").asCString();
			const char* name = root.get("name", "Unnamed Level").asCString();
				
			const Json::Value objects = root["objects"];
			Json::Value obj;
			
			int x;
			int y;
			float scale;
			
			std::string filename;
			std::string type;
			
			for(unsigned int i=0;i<objects.size();i++) {
				obj = objects[(Json::Value::ArrayIndex)i];
					
				x = obj["position"][(Json::Value::ArrayIndex)0].asInt();
				y = obj["position"][(Json::Value::ArrayIndex)1].asInt();
					
				scale = obj.get("scale", 1.0).asDouble();
				
				filename = obj.get("image", "none.png").asString();
				type = obj.get("type", "static").asString();

				if(type == "static") {
					world->addObject(new StaticObject(filename.c_str(), scale, b2Vec2(x,y), world->getWorld(), windowWidth, windowHeight));
				}
				else {
					if(type == "dynamic") {
						world->addObject(new DynamicObject(filename.c_str(), scale, b2Vec2(x,y), world->getWorld(), windowWidth, windowHeight));
					}
					else {
						printf("**ERROR: Invalid object type: %s", type);
					}
				}
			}
		}
		else {
			printf("**ERROR: Unable to load file %s\n", file);
		}
	}

	void loadSpriteSheet(const char* file, World* world) {
		Json::Value root;
		Json::Reader reader;

		std::string contents = get_file_contents(file);
		const char* more = contents.c_str();
		
		bool parsingSuccessful = reader.parse(more, root);
		if(parsingSuccessful) {
			SpriteSheet* sprite = world->initSpriteSheet(root.get("name","none").asString(), root.get("image_file","none.png").asString().c_str());
			
			Json::Value::Members animations = root["animations"].getMemberNames();
			Json::Value anim;
			const char* animationname;
			for(unsigned int i=0; i<animations.size();i++) {
				animationname = animations[i].c_str();
				anim = root["animations"][animationname];
				sprite->initSequence(animationname, anim["time"].asDouble(), anim["size"][(Json::Value::ArrayIndex)0].asInt(), anim["size"][(Json::Value::ArrayIndex)1].asInt());
				if(!anim.isMember("positions")) {
					sprite->addAnimationRow(animationname, anim["row"].asInt(), anim["count"].asInt());
				}
				else {
					for(unsigned int j=0; j<anim["positions"].size();j++) {
						sprite->addSequenceFrame(animationname, b2Vec2(anim["positions"][j][(Json::Value::ArrayIndex)0].asInt(),anim["positions"][j][(Json::Value::ArrayIndex)1].asInt()));
					}
				}
			}
		}
		else {
			printf("**ERROR: Unable to load file %s\n", file);
		}
	}
}