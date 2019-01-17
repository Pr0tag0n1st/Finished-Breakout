#include <stdio.h>
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
using namespace std;

bool Collision(int b1x, int b1y, int b2x, int b2y);

class brick {
public:
	void initBrick(int x, int y, int w, int h);
	void draw();
	bool IsDead();
	void killBrick();
	bool Collision(int b1x, int b1y);
	void Brick();

private:
	int Xpos;
	int Ypos;
	int width;
	int height;
	bool dead;
	int Color;
};


int main()
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *paddle = NULL;
	ALLEGRO_BITMAP *ball = NULL;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_FONT *font = NULL;
	//here's the bouncer's x and y coordinates on the screen
	float paddle_x = 30;
	float paddle_y = 30;
	float FPS = 60;
	int deadbricks = 0;
	int lives = 3;

	float ball_x = 90;
	float ball_y = 90;
	float ball_dx = -4.0, ball_dy = 4.0;


	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	timer = al_create_timer(1 / FPS);
	display = al_create_display(640, 480);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	bool key[2] = { false, false, };
	bool redraw = true;
	bool doexit = false;
	al_install_keyboard();
	timer = al_create_timer(1/FPS);
	display = al_create_display(640, 480);
	font = al_create_builtin_font();
	ball = al_create_bitmap(32, 32);
	al_set_target_bitmap(ball);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	paddle = al_create_bitmap(180, 32);
	al_set_target_bitmap(paddle);
	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	brick joe;
	joe.initBrick(20, 365, 50, 30);

	brick slimshady;
	slimshady.initBrick(80, 365, 50, 30);

	brick hater;
	hater.initBrick(140, 365, 50, 30);

	brick halo;
	halo.initBrick(200, 365, 50, 30);

	brick jim;
	jim.initBrick(260, 365, 50, 30);

	brick coral;
	coral.initBrick(320, 365, 50, 30);

	brick marlin;
	marlin.initBrick(380, 365, 50, 30);

	brick nemo;
	nemo.initBrick(440, 365, 50, 30);

	brick dory;
	dory.initBrick(500, 365, 50, 30);

	brick carl;
	carl.initBrick(560, 365, 50, 30);

	brick russel;
	russel.initBrick(40, 400, 50, 30);

	brick dug;
	dug.initBrick(100, 400, 50, 30);

	brick kevin;
	kevin.initBrick(160, 400, 50, 30);

	brick walle;
	walle.initBrick(220, 400, 50, 30);

	brick eve;
	eve.initBrick(280, 400, 50, 30);

	brick dash;
	dash.initBrick(340, 400, 50, 30);

	brick elastagirl;
	elastagirl.initBrick(400, 400, 50, 30);

	brick violet;
	violet.initBrick(460, 400, 50, 30);

	brick bob;
	bob.initBrick(520, 400, 50, 30);

	brick frozone;
	frozone.initBrick(20, 435, 50, 30);

	brick syndrome;
	syndrome.initBrick(80, 435, 50, 30);

	brick killa;
	killa.initBrick(140, 435, 50, 30);

	brick outcast;
	outcast.initBrick(200, 435, 50, 30);

	brick billybob;
	billybob.initBrick(260, 435, 50, 30);

	brick carmando;
	carmando.initBrick(320, 435, 50, 30);

	brick mike;
	mike.initBrick(380, 435, 50, 30);

	brick sully;
	sully.initBrick(440, 435, 50, 30);

	brick randal;
	randal.initBrick(500, 435, 50, 30);

	brick boo;
	boo.initBrick(560, 435, 50, 30);
	//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
	//OR the mouse closing the display
	while (!doexit && lives != 0 && deadbricks !=29)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the movement algorithm

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			//if the left button is pressed AND we're still right of the left wall
			//move the box left by 4 pixels
			if (key[0] && paddle_x >= 0) {
				paddle_x -= 9.0;
			}

			//if the right button is pressed AND we're still left of the right wall
			//move the box right by 4 pixels
			if (key[1] && paddle_x <= 640 - 180) {
				paddle_x += 9.0;

			}

			if (ball_x < 0 || ball_x > 640 - 32) {
				ball_dx = -ball_dx;
			}


			if (ball_y < 0) {
				lives--;
				ball_dy = -ball_dy;
			}
			if (ball_y > 480 - 32) {
				ball_dy = -ball_dy;
			}


			//really important code!
			//move the box in a diagonal
			ball_x += ball_dx;
			ball_y += ball_dy;
	
			if (Collision(paddle_x, paddle_y, ball_x, ball_y) == 1)
				ball_dy = -ball_dy;

			//brick collision
			if ((joe.Collision(ball_x, ball_y) == 1) && (joe.IsDead() != 1)) {
				ball_dy = -ball_dy;
				joe.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((billybob.Collision(ball_x, ball_y) == 1) && (billybob.IsDead() != 1)) {
				ball_dy = -ball_dy;
				billybob.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((carmando.Collision(ball_x, ball_y) == 1) && (carmando.IsDead() != 1)) {
				ball_dy = -ball_dy;
				carmando.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((slimshady.Collision(ball_x, ball_y) == 1) && (slimshady.IsDead() != 1)) {
				ball_dy = -ball_dy;
				slimshady.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((outcast.Collision(ball_x, ball_y) == 1) && (outcast.IsDead() != 1)) {
				ball_dy = -ball_dy;
				outcast.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((killa.Collision(ball_x, ball_y) == 1) && (killa.IsDead() != 1)) {
				ball_dy = -ball_dy;
				killa.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((hater.Collision(ball_x, ball_y) == 1) && (hater.IsDead() != 1)) {
				ball_dy = -ball_dy;
				hater.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((halo.Collision(ball_x, ball_y) == 1) && (halo.IsDead() != 1)) {
				ball_dy = -ball_dy;
				halo.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((jim.Collision(ball_x, ball_y) == 1) && (jim.IsDead() != 1)) {
				ball_dy = -ball_dy;
				jim.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((coral.Collision(ball_x, ball_y) == 1) && (coral.IsDead() != 1)) {
				ball_dy = -ball_dy;
				coral.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((marlin.Collision(ball_x, ball_y) == 1) && (marlin.IsDead() != 1)) {
				ball_dy = -ball_dy;
				marlin.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((nemo.Collision(ball_x, ball_y) == 1) && (nemo.IsDead() != 1)) {
				ball_dy = -ball_dy;
				nemo.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((dory.Collision(ball_x, ball_y) == 1) && (dory.IsDead() != 1)) {
				ball_dy = -ball_dy;
				dory.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((carl.Collision(ball_x, ball_y) == 1) && (carl.IsDead() != 1)) {
				ball_dy = -ball_dy;
				carl.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((russel.Collision(ball_x, ball_y) == 1) && (russel.IsDead() != 1)) {
				ball_dy = -ball_dy;
				russel.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((dug.Collision(ball_x, ball_y) == 1) && (dug.IsDead() != 1)) {
				ball_dy = -ball_dy;
				dug.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((kevin.Collision(ball_x, ball_y) == 1) && (kevin.IsDead() != 1)) {
				ball_dy = -ball_dy;
				kevin.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((walle.Collision(ball_x, ball_y) == 1) && (walle.IsDead() != 1)) {
				ball_dy = -ball_dy;
				walle.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((eve.Collision(ball_x, ball_y) == 1) && (eve.IsDead() != 1)) {
				ball_dy = -ball_dy;
				eve.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((dash.Collision(ball_x, ball_y) == 1) && (dash.IsDead() != 1)) {
				ball_dy = -ball_dy;
				dash.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((elastagirl.Collision(ball_x, ball_y) == 1) && (elastagirl.IsDead() != 1)) {
				ball_dy = -ball_dy;
				elastagirl.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((violet.Collision(ball_x, ball_y) == 1) && (violet.IsDead() != 1)) {
				ball_dy = -ball_dy;
				violet.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((bob.Collision(ball_x, ball_y) == 1) && (bob.IsDead() != 1)) {
				ball_dy = -ball_dy;
				bob.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((frozone.Collision(ball_x, ball_y) == 1) && (frozone.IsDead() != 1)) {
				ball_dy = -ball_dy;
				frozone.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((syndrome.Collision(ball_x, ball_y) == 1) && (syndrome.IsDead() != 1)) {
				ball_dy = -ball_dy;
				syndrome.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((mike.Collision(ball_x, ball_y) == 1) && (mike.IsDead() != 1)) {
				ball_dy = -ball_dy;
				mike.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((sully.Collision(ball_x, ball_y) == 1) && (sully.IsDead() != 1)) {
				ball_dy = -ball_dy;
				sully.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((randal.Collision(ball_x, ball_y) == 1) && (randal.IsDead() != 1)) {
				ball_dy = -ball_dy;
				randal.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}

			if ((boo.Collision(ball_x, ball_y) == 1) && (boo.IsDead() != 1)) {
				ball_dy = -ball_dy;
				boo.killBrick();
				deadbricks++;
				//Wacky sound effect goes here
			}
			redraw = true;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//here's the algorithm that turns key presses into events
		//a "key down" event is when a key is pushed
		//while a "key up" event is when a key is released

		//has something been pressed on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

			//"keycode" holds all the different keys on the keyboard
			switch (ev.keyboard.keycode) {

				//if the left key has been pressed
			case ALLEGRO_KEY_LEFT:
				key[0] = true;
				break;

				//if the right key has been pressed
			case ALLEGRO_KEY_RIGHT:
				key[1] = true;
				break;

			}
		}
		//has something been released on the keyboard?
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {

			case ALLEGRO_KEY_LEFT:
				key[0] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[1] = false;
				break;



				//kill the program if someone presses escape
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;

			}

		}
		//if the clock ticked but no other events happened, don't bother redrawing
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			
			//paint black over the old screen, so the old square dissapears
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//the algorithm above just changes the x and y coordinates
			//here's where the bitmap is actually drawn somewhere else
			al_draw_bitmap(paddle, paddle_x, paddle_y, 0);
			al_draw_bitmap(ball, ball_x, ball_y, 0);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 320, 20, 0, "LIVES: %d", lives);

			if (joe.IsDead() == false)
				joe.draw();
			if (billybob.IsDead() == false)
				billybob.draw();
			if (carmando.IsDead() == false)
				carmando.draw();
			if (slimshady.IsDead() == false)
				slimshady.draw();
			if (outcast.IsDead() == false)
				outcast.draw();
			if (killa.IsDead() == false)
				killa.draw();
			if (hater.IsDead() == false)
				hater.draw();
			if (halo.IsDead() == false)
				halo.draw();
			if (jim.IsDead() == false)
				jim.draw();
			if (coral.IsDead() == false)
				coral.draw();
			if (marlin.IsDead() == false)
				marlin.draw();
			if (nemo.IsDead() == false)
				nemo.draw();
			if (dory.IsDead() == false)
				dory.draw();
			if (carl.IsDead() == false)
				carl.draw();
			if (russel.IsDead() == false)
				russel.draw();
			if (dug.IsDead() == false)
				dug.draw();
			if (kevin.IsDead() == false)
				kevin.draw();
			if (walle.IsDead() == false)
				walle.draw();
			if (eve.IsDead() == false)
				eve.draw();
			if (dash.IsDead() == false)
				dash.draw();
			if (elastagirl.IsDead() == false)
				elastagirl.draw();
			if (violet.IsDead() == false)
				violet.draw();
			if (bob.IsDead() == false)
				bob.draw();
			if (frozone.IsDead() == false)
				frozone.draw();
			if (syndrome.IsDead() == false)
				syndrome.draw();
			if (mike.IsDead() == false)
				mike.draw();
			if (sully.IsDead() == false)
				sully.draw();
			if (randal.IsDead() == false)
				randal.draw();
			if (boo.IsDead() == false)
				boo.draw();


			al_flip_display();

		}
	}//end game loop
	if (lives == 0) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(font, al_map_rgb(255, 255, 255), 320, 240, 0, "YOU LOSE!  BRICKS HIT: %s", deadbricks);
		al_flip_display();
				al_rest(3.0);
		al_destroy_bitmap(paddle);
		al_destroy_bitmap(ball);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
	}
	if (deadbricks == 29) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_textf(font, al_map_rgb(255, 255, 255), 320, 240, 0, "YOU WIN!  REMAINING LIVES: %s", lives);
		al_flip_display();
		al_rest(3.0);
		al_destroy_bitmap(paddle);
		al_destroy_bitmap(ball);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
	}

	al_destroy_bitmap(paddle);
	al_destroy_bitmap(ball);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;

}
bool Collision(int b1x, int b1y, int b2x, int b2y) {

	if ((b1x + 180 < b2x) ||
		(b1x > b2x + 25) ||
		(b1y > b2y + 25) ||
		(b1y + 32 < b2y)

		)

		return 0;
	else {
		return 1;
	}
}

void brick::initBrick(int x, int y, int w, int h) {
	Xpos = x;
	Ypos = y;
	width = w;
	height = h;
	dead = false;


}
void	brick::draw() {
	al_draw_filled_rectangle(Xpos, Ypos, Xpos + width, Ypos + height, al_map_rgb(255, 0, 255));
}
bool brick::IsDead() {
	return dead;
}
void brick::killBrick() {
	dead = true;
}


bool brick::Collision(int b1x, int b1y) {

	if ((b1x + 32 < Xpos) ||
		(b1x > Xpos + 50) ||
		(b1y > Ypos + 30) ||
		(b1y + 32 < Ypos)

		)

		return 0;
	else {
		return 1;
	}
}
void brick::Brick() {

}