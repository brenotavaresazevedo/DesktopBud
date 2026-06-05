#include "raylib.h"
#include <vector>
#include <string>
#include <iostream>
void screenCanvasInit(){
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_MOUSE_PASSTHROUGH | FLAG_WINDOW_RESIZABLE|FLAG_WINDOW_UNDECORATED);
	InitWindow(500,500,"");
	MaximizeWindow();
};
class AnimatedSprite{
	private:
	int animacaoAtual = 0;
	float spriteCounter = 0;
	int spriteAtual = 0;
	public:
	bool paused = false;
	bool unused = false;
	struct spriteTable{
		std::string name;
		std::vector<Texture2D> anim;
		float maxTimer;
	};
	float x = 0.0f;
	float y = 0.0f;
	float size = 1.0f;
	float rotation = 0;
	float velocityX = 0;
	float velocityY = 0;
	std::vector<spriteTable> sprites;
	void addAnimation(std::string nome,float fps){
		sprites.push_back({nome , {},fps});
	}
	void addSprite(std::string nome, std::string path){
		for(int i=0;i<sprites.size();i++){
			if(sprites[i].name==nome){
				sprites[i].anim.push_back(LoadTexture(path.c_str()));
				break;
			}
		}
	}
	void setFPS(float fps,std::string animation){
		for(int i=0;i<sprites.size();i++){
			if(sprites[i].name==animation){
				sprites[i].maxTimer = fps;
				break;
			}
		}
	}
	void update(){
		if(spriteCounter>=sprites[animacaoAtual].maxTimer){
			spriteCounter = 0;
			if(sprites[animacaoAtual].anim.size()>0){
				if(sprites[animacaoAtual].anim.size() <= spriteAtual){
					spriteAtual = 0;
					spriteCounter = 0.0f;
				}
				else{
					if(paused==false){
						spriteAtual += 1;
					}
				}
			}
		}
		else{
			spriteCounter += GetFrameTime();
		}
		if(sprites[animacaoAtual].anim.size()<=spriteAtual){
			spriteAtual = 0;
			spriteCounter = 0;
		}
		else{
			DrawTextureEx(sprites[animacaoAtual].anim[spriteAtual],(Vector2){x,y},rotation,size,WHITE);
		}
		x += velocityX * GetFrameTime();
		y += velocityY * GetFrameTime();
	}
	void setAnimation(std::string nome){
		for(int i=0;i<sprites.size();i++){
			if(sprites[i].name==nome){
				if(sprites[i].anim.size()-1<spriteAtual){
					spriteAtual = 0;
					spriteCounter = 0.0f;
				}
				else{
					;
				}
				animacaoAtual = i;
				break;
			}
		}
	}
	void unload(){
		for(int i=0;i<sprites.size();i++){
			for(int k=0;k<sprites[i].anim.size();k++){
				if(sprites[i].anim[k].id==0){
					;
				}
				else{
					UnloadTexture(sprites[i].anim[k]);
				}
			}
		}
		unused = true;
	}
	void eraseAnimation(std::string nome){
		for(int i=0;i<sprites.size();i++){
			if(sprites[i].name==nome){
				for(int k=0;k<sprites[i].anim.size();k++){
					if(sprites[i].anim[k].id!=0){
						UnloadTexture(sprites[i].anim[k]);
					}
					else{
						;
					}
				}
				sprites.erase(sprites.begin() + i);
				break;
			}
		}
	}
	bool animationFinished(){
		if(spriteAtual>=sprites[animacaoAtual].anim.size()-1){
			return true;
		}
		return false;
	}
	void setFrame(int indice){
		if(indice>=sprites[animacaoAtual].anim.size()){
			;
		}
		else{
			spriteAtual = indice;
		}
	}
	int getAnimationSize(){
		return sprites[animacaoAtual].anim.size();
	}
	std::string getCurrentAnimation(){
		return sprites[animacaoAtual].name;
	}
	void setAnimationFPS(std::string nome, float fps){
		for(int i=0;i<sprites.size();i++){
			if(sprites[i].name==nome){
				sprites[i].maxTimer = fps;
				break;
			}
		}
	}
	float getAnimationFPS(std::string animation){
		for(int i=0;i<sprites.size();i++){
			if(sprites[i].name==animation){
				return sprites[i].maxTimer;
			}
		}
		return 0.0;
	}
};
class Sprite{
	public:
	float x;
	float y;
	float size = 1.0f;
	float rotation = 0;
	Texture2D tex;
	void setTexture(std::string path){
		tex = LoadTexture(path.c_str());
	}
	void update(){
		DrawTextureEx(tex,(Vector2){x,y},rotation,size,WHITE);
	}
	void unload(){
		UnloadTexture(tex);
	}
};
class CollideBox{
	private:
	AnimatedSprite* collide = nullptr;
	bool canUse = false;
	std::vector<Rectangle> collisors;
	Rectangle collidedCollisor;
	Rectangle collideBox;
	public:
	bool debugMode = false;
	float x;
	float y;
	float sizeX;
	float sizeY;
	bool isOnFloor(){
		if(collisors.size()>0){
			if(collideBox.y+collideBox.height>=collidedCollisor.y && collideBox.y+collideBox.height<=collidedCollisor.y+collidedCollisor.height/2){
				return true;
			}
		}
		return false;
	}
	bool isOnWall(std::string direction){
		if(collisors.size()>0){
			if(direction=="left"){
				if(collideBox.x<collidedCollisor.x+collidedCollisor.width){
					return true;
				}
			}
			else if(direction=="right"){
				if(collideBox.x + collideBox.width > collidedCollisor.x){
					return true;
				}
			}
		}
		return false;
	}
	bool collided(){
		if(collisors.size()>0){
			if(collideBox.x<collidedCollisor.x+collidedCollisor.width && collideBox.x + collideBox.width > collidedCollisor.x && collideBox.y < collidedCollisor.y + collidedCollisor.height && collideBox.y+collideBox.height>collidedCollisor.y){
				return true;
			}
		}
		return false;
	}
	bool isOnCelling(){
		if(collisors.size()>0){
			if(collideBox.y<=collidedCollisor.y+collidedCollisor.height && collideBox.y+collideBox.height>collidedCollisor.y+collidedCollisor.height/2){
				return true;
			}
		}
		return false;
	}
	void update(){
		if(canUse==true){
			if(collide->unused==true){
				collide = nullptr;
				canUse = false;
			}
			else{
				collideBox.x = collide->x;
				collideBox.y = collide->y;
			}
		}
		else{
			return;
		}
		for(int i=0;i<collisors.size();i++){
			if(collideBox.x<collisors[i].x+collisors[i].width && collideBox.x + collideBox.width > collisors[i].x && collideBox.y < collisors[i].y + collisors[i].height && collideBox.y+collideBox.height>collisors[i].y){
				collidedCollisor = collisors[i];
			}
		}
		if(debugMode==true){
			DrawRectangle(collideBox.x,collideBox.y,collideBox.width,collideBox.height,BLUE);
			for(int i=0;i<collisors.size();i++){
				DrawRectangle(collisors[i].x,collisors[i].y,collisors[i].width,collisors[i].height,RED);
			}
		}
		collideBox.width = sizeX;
		collideBox.height = sizeY;
	}
	void makeCollideObject(AnimatedSprite& spr){
		collide = &spr;
		canUse = true;
	}
	void addCollisor(Rectangle coll){
		collisors.push_back(coll);
	}
	void eraseCollisor(Rectangle rect){
		for(int i=0;i<collisors.size();i++){
			if(collisors[i].x==rect.x && collisors[i].y==rect.y && collisors[i].width==rect.width && collisors[i].height==rect.height){
				collisors.erase(collisors.begin() + i);
				break;
			}
		}
	}
};


