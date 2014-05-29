/*
TO DO:
spritesheets.
dundundun
*/

#include <Box2D/Box2D.h>
#include "player_object.h"
#include <glut.h>
#include "object.h"

static float ratio = 40.0f;
namespace GameEngine {
	PlayerObject::PlayerObject() {
	}
	PlayerObject::PlayerObject(SpriteSheet* _sprites, float _scale, float _x, float _y, b2World* world, int wWidth, int wHeight) {
		int _width, _height;
		b2Vec2 size = _sprites->getSequenceSize("idle");
		sprites = *_sprites;
		_width = _sprites->getSequenceSize("idle").x * _scale;
		_height = _sprites->getSequenceSize("idle").y  * _scale;
	
		scale = _scale;
	
		state = "idle";
		direction = "right";
		
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 2.0f;
		bodyDef.fixedRotation = true;
		bodyDef.position.Set(_x/ratio, _y/ratio);
		
		body = world->CreateBody(&bodyDef);
		bodyData* data = new bodyData();
		data->type = "player";
		data->object = this;
		body->SetUserData(data);
		b2DataPtr = data;
		vertices[0].Set(0,0);
		vertices[1].Set(0,_height/ratio);
		vertices[2].Set(_width/ratio, _height/ratio);
		vertices[3].Set(_width/ratio, 0);
		box.Set(vertices,4);
		
		fixtureDef.shape = &box;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 5.0f;
	
		body->CreateFixture(&fixtureDef);
		
		x = _x;
		y = _y;
	
		winWidth = wWidth;
		winHeight = wHeight;
	
		//termX = body->GetMass() * 1.5f;
	}

	void PlayerObject::update(bool up, bool down, bool left, bool right) {
		b2Vec2 linVel = body->GetLinearVelocity();
		if(up) {
			if(linVel.y == 0) {
				body->ApplyLinearImpulse( b2Vec2(0, body->GetMass() * 5), body->GetWorldCenter(), true );
			}
		}
		if(left) {
			body->ApplyLinearImpulse( b2Vec2(body->GetMass() * -0.5, 0.0 ), body->GetWorldCenter(), true );
		}
		if(right) { 
			body->ApplyLinearImpulse( b2Vec2(body->GetMass() * 0.5, 0.0 ), body->GetWorldCenter(), true );
		}
		
		b2Vec2 vel = body->GetLinearVelocity();
		if(vel.y > 1.0f) {
			state = "jump";
		}
		else {
			if(vel.y < -1.0f) {
				state = "fall";
			}
			else {
				state = "idle";
			}
		}
	
		if(vel.x > 1.0f) {
			state = "run";
			direction = "right";
		}
		if(vel.x < -1.0f) {
			state = "run";
			direction = "left";
		}
		//printf("%s %s\n", state, direction);
	}
	
	void PlayerObject::WindowResize(int wWidth, int wHeight) {
	}
	
	void PlayerObject::SetPosition(int _x, int _y) {
		bodyDef.position.Set(_x/ratio,  _y/ratio);
		body->SetTransform(b2Vec2(_x/ratio, _y/ratio), body->GetAngle());
	}
	
	void PlayerObject::resize(float _scale) { 
		scale = _scale;
		int _width, _height;
		_width = sprites.getSequenceSize("idle").x * scale;
		_height = sprites.getSequenceSize("idle").y  * scale;
		box.SetAsBox((_width/2.0)/ratio, (_height/2.0)/ratio);
	}
	
	void PlayerObject::debug() {
		printf("RECT (%d, %d, %s, %s)\n", x, y, state, direction);
	}
	
	void PlayerObject::render() { //void render(std::string sequence, int x, int y, float angle, float scale);
		x = body->GetPosition().x*ratio;
		y = body->GetPosition().y*ratio; // 
		if(direction == "right")
			sprites.render(state, x, y, body->GetAngle() * (180.0f / 3.14159265f), scale, false);
		else
			sprites.render(state, x, y, body->GetAngle() * (180.0f / 3.14159265f), scale, true);
	}
	
	void PlayerObject::_clean() {
		delete b2DataPtr;
		clean();
	}

	void PlayerObject::clean() {
		
	}

	void PlayerObject::startContact() {
	}

	void PlayerObject::endContact() {
	}
}