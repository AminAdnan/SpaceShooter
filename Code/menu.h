
#include "game.h"
class Menu{
public:
    sf::RenderWindow mWindow;
    sf::Font mFont;
    sf::Text mTitle;
    sf::RectangleShape mButton1;
    sf::RectangleShape mButton2;

    //Sprite background; //Game background sprite
    //Texture bg_texture;
    // 
//add menu attributes here
Menu()
{
  

    /*
    bg_texture.loadFromFile("img/background.jpg");
    background.setTexture(bg_texture);
    background.setScale(2, 1.5);
//constructors body*/
}





void display_menu()

{
    /*
    RenderWindow window(VideoMode(500, 500), title);
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game                        	    
        }
    }*/
    
    Game g; 
//display menu screen here

// add functionality of all the menu options here

//if Start game option is chosen 
    
    g.start_game();



}


};
