#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"
#include "player.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;




class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(1920, 1080, true)
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt

	
	player p1, p2;
	int start = 0;

	enum zustand {
		frei,
		p1_spur,
		p1,
		p2_spur,
		p2
	};

	zustand kaestle[61][33];

	void draw() override
	{
		// Notizen: Bildbereich: 1830x990 pixel 
		// Bei 30x30 Spielergröße 61x33 Spielfelder 
		// Rand: 45x45

		Gosu::Graphics::draw_rect(
			0, 0, 1920, 1080, Gosu::Color::GRAY,
			0.0
		);
		Gosu::Graphics::draw_rect(
			45, 45,	1830, 990, Gosu::Color::BLACK,
			0.0
		);



		Gosu::Graphics::draw_rect(
			p1.pos_x, p1.pos_y, 30, 30, Gosu::Color::RED,
			0.0
		);
		Gosu::Graphics::draw_rect(
			p2.pos_x, p2.pos_y, 30, 30, Gosu::Color::BLUE,
			0.0
		);
		
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		if (start == 0) {
			p1.field_to_pixel(5, 17);
			p2.field_to_pixel(56, 17);
			start = 1;

			p1.richtung = 1;
			p2.richtung = 2;

		}




		//Schalter von Player 1 abfragen
		if (input().down(Gosu::KB_D) & p1.richtung != 2) {
			p1.richtung = 1;
		}
		if (input().down(Gosu::KB_A) & p1.richtung != 1) {
			p1.richtung = 2;
		}
		if (input().down(Gosu::KB_W) & p1.richtung != 4) {
			p1.richtung = 3;
		}
		if (input().down(Gosu::KB_S) & p1.richtung != 3) {
			p1.richtung = 4;
		}
		// Schalter von Player 2 abfragen
		if (input().down(Gosu::KB_RIGHT) & p2.richtung != 2) {
			p2.richtung = 1;
		}
		if (input().down(Gosu::KB_LEFT) & p2.richtung != 1) {
			p2.richtung = 2;
		}
		if (input().down(Gosu::KB_UP) & p2.richtung != 4) {
			p2.richtung = 3;
		}
		if (input().down(Gosu::KB_DOWN) & p2.richtung != 3) {
			p2.richtung = 4;
		}
		
		if (p1.in_grid == 0) {
			p1.richtung_alt = p1.richtung;
		}

		switch (p1.richtung_alt)
		{
		case 1: p1.fahren_rechts(); break;
		case 2: p1.fahren_links(); break;
		case 3: p1.fahren_oben(); break;
		case 4: p1.fahren_unten(); break;
		}

		
		
		if (p2.in_grid == 0) {
			p2.richtung_alt = p2.richtung;
		}

		switch (p2.richtung_alt)
		{
		case 1: p2.fahren_rechts(); break;
		case 2: p2.fahren_links(); break;
		case 3: p2.fahren_oben(); break;
		case 4: p2.fahren_unten(); break;
		}
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
