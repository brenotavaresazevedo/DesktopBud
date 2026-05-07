#include "raylib.h"
#include <vector>
#include <string>
void screenCanvasInit(){
	SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_MOUSE_PASSTHROUGH | FLAG_WINDOW_RESIZABLE|FLAG_WINDOW_UNDECORATED);
	InitWindow(500,500,"");
	MaximizeWindow();
};
class AnimatedSprite{
	private:
	int animacaoAtual = 0;
	float spriteCounter = 0;
	float spriteAtual = 0;
	public:
	bool paused = false;
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


