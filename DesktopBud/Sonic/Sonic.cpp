#include <vector>
#include "../nodesHeader.hpp"
#include "raylib.h"
#include <iostream>
struct player{
	AnimatedSprite sonic;
	bool isDashing = false;
	bool spinDash = false;
	bool jump = true;
	bool tookDamage = false;
	float referencePos;
	std::string direction = "right";
	float spinDashVelocityForce = 0;
	CollideBox colBox;
	player(){
		screenCanvasInit();
		sonic.addAnimation("walking>",0.2f);
		sonic.addSprite("walking>","./costume1.png");
		sonic.addSprite("walking>","./costume2.png");
		sonic.addSprite("walking>","./costume3.png");
		sonic.addSprite("walking>","./costume4.png");
		sonic.addSprite("walking>","./costume5.png");
		sonic.addSprite("walking>","./costume6(2).png");
		sonic.addSprite("walking>","./costume7(2).png");
		sonic.addSprite("walking>","./costume8.png");
		sonic.addAnimation("<walking",0.2f);
		sonic.addSprite("<walking","./costume1(1).png");
		sonic.addSprite("<walking","./costume2(1).png");
		sonic.addSprite("<walking","./costume3(1).png");
		sonic.addSprite("<walking","./costume4(1).png");
		sonic.addSprite("<walking","./costume5(1).png");
		sonic.addSprite("<walking","./costume6(3).png");
		sonic.addSprite("<walking","./costume7(1).png");
		sonic.addSprite("<walking","./costume8(1).png");
		sonic.addAnimation("idle>",0.4f);
		sonic.addSprite("idle>","./costume6.png");
		sonic.addAnimation("<idle",0.4f);
		sonic.addSprite("<idle","./costume6(1).png");
		sonic.addAnimation("running>",0.1f);
		sonic.addSprite("running>","./costume1(2).png");
		sonic.addSprite("running>","./costume3(2).png");
		sonic.addSprite("running>","./costume4(2).png");
		sonic.addAnimation("<running",0.1f);
		sonic.addSprite("<running","./costume1(3).png");
		sonic.addSprite("<running","./costume2(3).png");
		sonic.addSprite("<running","./costume3(3).png");
		sonic.addSprite("<running","./costume4(3).png");
		sonic.addAnimation("brake>",1.0f);
		sonic.addSprite("brake>","./costume1(9).png");
		sonic.addAnimation("<brake",1.0f);
		sonic.addSprite("<brake","./costume1(10).png");
		sonic.addAnimation("down>",0.3f);
		sonic.addSprite("down>","./costume8(2).png");
		sonic.addSprite("down>","./costume10.png");
		sonic.addAnimation("<down",0.3f);
		sonic.addSprite("<down","./costume8(3).png");
		sonic.addSprite("<down","./costume10(1).png");
		sonic.addAnimation("jump>",0.2f);
		sonic.addSprite("jump>","./costume1(4).png");
		sonic.addSprite("jump>","./costume5(2).png");
		sonic.addSprite("jump>","./costume2(4).png");
		sonic.addSprite("jump>","./costume5(2).png");
		sonic.addSprite("jump>","./costume3(4).png");
		sonic.addSprite("jump>","./costume5(2).png");
		sonic.addSprite("jump>","./costume4(4).png");
		sonic.addSprite("jump>","./costume5(2).png");
		sonic.addAnimation("<jump",0.2f);
		sonic.addSprite("<jump","./costume1(5).png");
		sonic.addSprite("<jump","./costume5(3).png");
		sonic.addSprite("<jump","./costume3(5).png");
		sonic.addSprite("<jump","./costume5(3).png");
		sonic.addSprite("<jump","./costume4(5).png");
		sonic.addSprite("<jump","./costume5(3).png");
		sonic.addAnimation("spindash>",0.2f);
		sonic.addSprite("spindash>","./costume1(10) (1).png");
		sonic.addSprite("spindash>","./costume2(8).png");
		sonic.addSprite("spindash>","./costume3(8).png");
		sonic.addSprite("spindash>","./costume4(6).png");
		sonic.addSprite("spindash>","./costume5(4).png");
		sonic.addSprite("spindash>","./costume6(4).png");
		sonic.addAnimation("<spindash",0.2f);
		sonic.addSprite("<spindash","./costume1(11).png");
		sonic.addSprite("<spindash","./costume2(12).png");
		sonic.addSprite("<spindash","./costume3(9).png");
		sonic.addSprite("<spindash","./costume4(7).png");
		sonic.addSprite("<spindash","./costume5(5).png");
		sonic.addSprite("<spindash","./costume6(7).png");
		sonic.x = 100;
		sonic.y = 100;
		referencePos = sonic.y;
	};
};
player Sonic;
int main(){
	Sonic.colBox.addCollisor({100,450,50,50});
	Sonic.colBox.makeCollideObject(Sonic.sonic);
	Sonic.colBox.sizeX = 50;
	Sonic.colBox.sizeY = 75;
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLANK);
		Sonic.referencePos += Sonic.sonic.velocityY * GetFrameTime();
		float spinDashFps = 0;
		Sonic.sonic.update();
		Sonic.colBox.update();
		if(Sonic.colBox.isOnWall("left") && Sonic.colBox.collided() && !Sonic.colBox.isOnFloor()){
			Sonic.sonic.x -= 10;
			Sonic.sonic.velocityX = -10;
			std::cout << "teste" << std::endl;
		}
		if(Sonic.colBox.isOnWall("right") && Sonic.colBox.collided() && !Sonic.colBox.isOnFloor()){
			Sonic.sonic.x += 10;
			Sonic.sonic.velocityX = 10;
		}
		if(Sonic.colBox.isOnCelling() && Sonic.colBox.collided()){
			Sonic.sonic.velocityY = 100;
		}
		if(Sonic.sonic.y>(float)GetScreenHeight()-80 || Sonic.colBox.isOnFloor() && Sonic.colBox.collided() && !Sonic.colBox.isOnCelling()){
			Sonic.sonic.velocityY = 0;
			if(IsKeyDown(KEY_SPACE) && !IsKeyDown(KEY_DOWN)){
				Sonic.sonic.velocityY = -800;
				Sonic.jump = true;
			}
			else{
				Sonic.jump = false;
			}
			if(IsKeyDown(KEY_DOWN) || Sonic.isDashing==true || Sonic.spinDash==true){
				Sonic.sonic.y = Sonic.referencePos+25;
			}
			else{
				Sonic.sonic.y = Sonic.referencePos;
			}
			if(Sonic.isDashing==true){
				if(Sonic.direction=="left"){
					Sonic.sonic.setAnimation("<jump");
				}
				else{
					Sonic.sonic.setAnimation("jump>");
				}
				if(Sonic.sonic.velocityX==0){
					Sonic.isDashing = false;
				}
			}
			if(Sonic.spinDash==true){
				if(Sonic.direction=="right")
					Sonic.sonic.setAnimation("spindash>");
				else
					Sonic.sonic.setAnimation("<spindash");
			}
		}
		else{
			Sonic.sonic.velocityY += 1.4;
			if(Sonic.jump==true){
				if(Sonic.direction=="right")
					Sonic.sonic.setAnimation("jump>");
				else if(Sonic.direction=="left")
					Sonic.sonic.setAnimation("<jump");
			}
		}
		if(Sonic.sonic.velocityX>=1 || Sonic.sonic.velocityX<=1 && Sonic.jump==false){
			if(IsKeyPressed(KEY_DOWN)){
				Sonic.isDashing = true;
			}
		}
		if(Sonic.sonic.velocityX==0 && Sonic.jump==false){
			if(IsKeyDown(KEY_DOWN)){
				if(IsKeyPressed(KEY_SPACE)){
					Sonic.spinDash = true;
					if(Sonic.direction=="right")
						Sonic.spinDashVelocityForce += 200;
					else if(Sonic.direction=="left")
						Sonic.spinDashVelocityForce -= 200;
					if(Sonic.sonic.getAnimationFPS(Sonic.sonic.getCurrentAnimation())>0) Sonic.sonic.setAnimationFPS(Sonic.sonic.getCurrentAnimation(),Sonic.sonic.getAnimationFPS(Sonic.sonic.getCurrentAnimation())-0.05);
				}
			}
			if(IsKeyReleased(KEY_DOWN) && Sonic.spinDash==true){
				Sonic.isDashing = true;
				Sonic.spinDash = false;
				Sonic.sonic.velocityX = Sonic.spinDashVelocityForce;
				Sonic.spinDashVelocityForce = 0;
				Sonic.sonic.setAnimationFPS(Sonic.sonic.getCurrentAnimation(),0.2);
			}
		}
		if(Sonic.sonic.velocityY>=1000){
			Sonic.sonic.velocityY = 1000;
		}
		if(Sonic.sonic.velocityX<-1000){
			Sonic.sonic.velocityX = -1000;
		}
		if(Sonic.sonic.velocityX>1000){
			Sonic.sonic.velocityX = 1000;
		}
		if(Sonic.sonic.velocityX>1 && Sonic.jump==false && Sonic.isDashing==false && Sonic.spinDash==false){
			if(!IsKeyDown(KEY_LEFT)){
				if(Sonic.sonic.velocityX<750){
					Sonic.sonic.setAnimation("walking>");
				}
				else if(Sonic.sonic.velocityX>=750){
					Sonic.sonic.setAnimation("running>");
				}
			}
			else{
				Sonic.sonic.setAnimation("brake>");
			}
			Sonic.direction = "right";
		}
		else if(Sonic.sonic.velocityX<-1 && Sonic.jump==false && Sonic.isDashing==false && Sonic.spinDash==false){
			if(!IsKeyDown(KEY_RIGHT)){
				if(Sonic.sonic.velocityX>-750){
					Sonic.sonic.setAnimation("<walking");
				}
				else if(Sonic.sonic.velocityX<=-750){
					Sonic.sonic.setAnimation("<running");
				}
			}
			else{
				Sonic.sonic.setAnimation("<brake");
			}
			Sonic.direction = "left";
		}
		else{
			if(!IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && Sonic.jump==false && Sonic.isDashing==false && Sonic.spinDash==false){
				if(Sonic.direction=="left"){
					Sonic.sonic.setAnimation("<idle");
				}
				else{
					Sonic.sonic.setAnimation("idle>");
				}
			}
		}
		if(IsKeyDown(KEY_RIGHT) && Sonic.isDashing==false && Sonic.spinDash==false && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)){
			Sonic.sonic.velocityX += 1;
		}
		else if(IsKeyDown(KEY_LEFT) && Sonic.isDashing==false && Sonic.spinDash==false && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)){
			Sonic.sonic.velocityX -= 1;
		}
		else{
			if(Sonic.sonic.velocityX>1){
				Sonic.sonic.velocityX -= 1;
			}
			else if(Sonic.sonic.velocityX<-1){
				Sonic.sonic.velocityX += 1;
			}
			else{
				Sonic.sonic.velocityX = 0;
			}
		}
		if(Sonic.sonic.velocityX==0 && Sonic.jump==false && Sonic.spinDash==false && Sonic.isDashing==false){
			if(Sonic.direction=="right"){
				if(IsKeyDown(KEY_DOWN)){
					Sonic.sonic.setAnimation("down>");
					if(Sonic.sonic.animationFinished()){
						Sonic.sonic.paused = true;
					}
				}
				else{
					Sonic.sonic.paused = false;
				}
			}
			else if(Sonic.direction=="left"){
				if(IsKeyDown(KEY_DOWN)){
					Sonic.sonic.setAnimation("<down");
					if(Sonic.sonic.animationFinished()){
						Sonic.sonic.paused = true;
					}
				}
				else{
					Sonic.sonic.paused = false;
				}
			}
		}
		else{
			Sonic.sonic.paused = false;
		}
		EndDrawing();
	}
	Sonic.sonic.unload();
	CloseWindow();
	return 0;
}
