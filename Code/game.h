
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
#include "player.h"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;
#include "Enemy.h"
#include <ctime>
#include <SFML/Audio.hpp>



class Game
{
public:
   
Sprite background; //Game background sprite
Texture bg_texture;
Texture Ptex;
Texture t;

Player* p; //player 
// add other game attributes
//Invader* enemy;
Enemy* alpha[5];
AddOn* AddOns[4];
Enemy* monster;
Enemy* Dragon;

Sprite Lives; // to display lives
Texture lives_tex;
Font font;
Text text_Score;
Text text_GameOver;
Music music;






Game()
{
    srand(time(NULL));
    lives_tex.loadFromFile("img/PNG/UI/playerLife1_red.png");
    Lives.setTexture(lives_tex);
    Lives.setScale(0.75, 0.75);
    Lives.setPosition(300, 300);

    
    
    music.openFromFile("SkyFire (Title Screen).ogg");
    music.play();
    music.setVolume(10); 
    
   // enemy = new alpha(100,100, "img/enemy_1.png",3);
   // monster = new Monster(350,100,"img/monster",25,2,0);
    monster = nullptr;
    Dragon = nullptr;
    for (int i = 0; i < 5; ++i)
    {
        alpha[i] = new Invader(100*i + 130, 100, "img/enemy_1.png", 3,5, rand() %-5+0);
    }
    for (int i = 0; i < 4; ++i)
    {
        AddOns[i] = nullptr;
    }
    

    
 
p=new Player("img/player_ship.png");
//Ptex.loadFromFile("img/player_ship.png");


//t.loadFromFile("img/LeftShip.png");

bg_texture.loadFromFile("img/background.jpg");


background.setTexture(bg_texture);
background.setScale(2, 1.5);

font.loadFromFile("Fonts/Sugar Quota.ttf");
text_Score.setFont(font);

text_Score.setPosition(620, 0);
text_Score.setFillColor(Color::Magenta);
text_Score.setCharacterSize(30);
text_Score.setStyle(Text::Bold);

text_GameOver.setFont(font);

text_GameOver.setPosition(200, 300);
text_GameOver.setFillColor(Color::Red);
text_GameOver.setCharacterSize(90);
text_GameOver.setStyle(Text::Bold);
text_GameOver.setString("Game Over");


}
void start_game()
{
    
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    float timer=0;
    bool Gamma = false; // after 2nd wave gamma enemies will start to show up
    bool MONSTER = false; // indicating if monster is on screen or not
    bool DRAGON = false; // indicating if dragon is on screen or not
    int MonsterSpawn= -1; // random number to see if monster should spawn or not
    int DragonSpawn = -1; // random number for dragon spawn
    float fire_time = 0; // to note player fire time
    float SpawnTime = 0; //to note enemy spawn time
    int Enemy_count = 5; // no. of enemies remaining 
    float temp;
    bool player_alive = true;
    int EnemyWave = 1; // which enemy wave/round it is
    float InvaderFireTime = 0;
    float collisionTime = 0; // it takes for a bullet to go through ship, hence to avoid calling function multiple times with one hit.
    
    float AddOnSpawnTime = 0; // to note how much time it will take to spawn fire addON
    float fireAddOnTime = 0; // to note how much time Fire add on will last
    float PowerUPTime = 0;
    float DangerSpawnTime = 0; // to note spawn time for danger blocks
    float extraLifeTime = 0; // to note spawn time of extra lives
    float PowerUPSpawnTime = 0;
    bool Pause = false;
    bool FIRE = false; //if fire addON is active or not
    bool POWER = false; // if POWER ADDON IS ACTIVE OR NOT
    float respawnTime=0; //when ship gets hit, to note how much time it will respawn
    int coin; //to randomize which addOn will spawn
    int bullets = 7;
    float enemyX, enemyY; //coordinates for enemies
    float MX, MY; // coordinates for MONSTER
    bool MonsterLASER = false;
    bool DragonFlame = false; //
    bool LockON = false; // Monster locks on player to shoot laserr
    float flameRotation = 0;
    FloatRect rect1;
    int SCORE = 0; // scoring
    
    
    while (window.isOpen())
    {
       
        
        float time = clock.getElapsedTime().asSeconds(); 
        clock.restart();
        timer += time;  
        fire_time += time ;
        InvaderFireTime += time;
        collisionTime += time;
        
        fireAddOnTime += time;
        PowerUPTime += time;
        respawnTime += time;
        AddOnSpawnTime += time;
        PowerUPSpawnTime += time;
        extraLifeTime += time;
        DangerSpawnTime += time;
        
     
        
      //  SpawnTime += time;
        //cout<<time<<endl; 
 	Event e;
        while (window.pollEvent(e))
        {  
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close(); //close the game    
            if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::P)
                {
                    Pause = !Pause; // toggle pause state
                }
            }
        }
          
	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
            p->move("l");    // Player will move to left
	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            p->move("r");  //player will move to right
	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
            p->move("u");    //playet will move upwards
	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            p->move("d");  //player will move downwards
       


    text_Score.setString("Score: " + to_string(SCORE));
    
    //music
    if (music.getStatus() == sf::SoundSource::Stopped) {
        // Music has finished playing
        music.openFromFile("SkyFire (Title Screen).ogg");
        music.play();
        
    }


    //pausing game
    if (Pause)
    {
        sleep(sf::milliseconds(50));
        time = 0;
        
    }

    //setting alphabomb speed to 0.25
    for (int i = 0; i < 5; ++i)
    {
        if (alpha[i] != nullptr && alpha[i]->getBomb() != nullptr)
        {
            alpha[i]->getBomb()->bullet_speed = 0.25;
        }
    }

    //firing bullets by pressing space
    if (player_alive)
    {
        if (fire_time >= 0.4) // firing bullets
        {
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                p->fire();
                fire_time = 0;

            }

        }
    }

    //player getting hit by alpha bombs
    for (int i = 0; i < 5; ++i) // player getting hit by enemy bomb
    {
        if (alpha[i] != nullptr)
        {
            if (alpha[i]->getBomb() != nullptr)
            {
                if (collisionTime > 0.4)
                {
                     if(p->Collision(alpha[i]->getBomb()->bullet_spr.getPosition().x, alpha[i]->getBomb()->bullet_spr.getPosition().y,34))
                     {
                       //  cout << "Player GOT HIT" << endl;
                         collisionTime = 0;
                         alpha[i]->destroy_bomb();
                         if (p->addon == nullptr || p->addon->type == "fire")
                         {
                             
                             p->lives--;

                             player_alive = false;
                             respawnTime = 0;
                         }
                         
                         
                         
                     }
                }
            }
        }
    }

    //setting player to default location after it gets shot
    if (!player_alive)
    {
        p->sprite.setPosition(340, 700);
    }

    //game over
    

    //respawing ship after getting hit 
    if (respawnTime > 3 && p->lives >0)
    {
        player_alive = true;
        
    }


    //hitting alphas with bullets
    for (int i = 0; i < 5; ++i) // hitting enemies with bullets
    {
        if (alpha[i] != nullptr)
        {
                
            if (p->b != nullptr)
            {
                if (alpha[i]->Collision(p->b->bullet_spr.getPosition().x, p->b->bullet_spr.getPosition().y,45))
                {
                 //   cout << "Enemy " << i << "Got HIT" << endl;
                    alpha[i]->hp -= p->b->damage;
                            
                    
                    if (FIRE != true)
                    {
                        delete p->b;
                        p->b = nullptr;
                    }
                    if (alpha[i]->Destroy())
                    {
                        if (alpha[i]->fireRate == 5) // alpha invader
                        {
                            SCORE += 10;
                        }
                        else if (alpha[i]->fireRate == 3) // beta invader
                        {
                            SCORE += 20;
                        }
                        else //gamma invader
                        {
                            SCORE += 30;
                        }
                   //     cout << "Score: " << SCORE << endl;
                        Enemy_count--;
                        delete alpha[i];
                        alpha[i] = nullptr;
                    }
                }
            }
                
        }
    }


    //hitting enemies with spreadShot powerUP
    for (int j = 0; j < 7; ++j)
    {
        if (p->powerBullets[j] != nullptr)
        {
            for (int i = 0; i < 5; ++i)
            {
                if (alpha[i] != nullptr)
                {
                    if (alpha[i]->Collision(p->powerBullets[j]->bullet_spr.getPosition().x, p->powerBullets[j]->bullet_spr.getPosition().y,45))
                    {
                        
                        // delete p->powerBullets[j];
                        // p->powerBullets[j] = nullptr;
                        p->powerBullets[j]->bullet_spr.setPosition(-1000, 100*j);
                        
                        
                       // cout << "Enemy " << i << "Got HIT" << endl;
                        alpha[i]->hp -= 1;
                        if (alpha[i]->Destroy())
                        {
                            if (alpha[i]->fireRate == 5) // alpha invader
                            {
                                SCORE += 10;
                            }
                            else if (alpha[i]->fireRate == 3) // beta invader
                            {
                                SCORE += 20;
                            }
                            else //gamma invader
                            {
                                SCORE += 30;
                            }
                        //    cout << "Score: " << SCORE << endl;
                            Enemy_count--;
                            delete alpha[i];
                            alpha[i] = nullptr;
                        }
                        
                    }
                }
            }
        }
    }


    //movement of enemies
    for (int i = 0; i < 5; ++i)
    {
        if (alpha[i] != nullptr)
        { 
            alpha[i]->Move();
        }
    }
 




    //Colliding with alphas, and destroying player
    for (int i = 0; i < 5; ++i)
    {
        if (alpha[i] != nullptr)
        {
            if (p->Collision(alpha[i]->enemy_spr.getPosition().x + alpha[i]->enemy_spr.getGlobalBounds().width/2, alpha[i]->enemy_spr.getPosition().y + alpha[i]->enemy_spr.getGlobalBounds().height/2 , 69))
            {
                p->lives--;
                respawnTime = 0;
                player_alive = false;
            }
        }
    }

    

    //alphas droping bombs 5sec interval
    if (player_alive)
    {
        for (int i = 0; i < 5; ++i) // enemies firing 
        {

            if (alpha[i] == nullptr)
            {
                continue;
            }
            //alpha[i]->fireRate += time;
           // cout << alpha[i] << endl;
           // InvaderFireTime += time;
            alpha[i]->reloadTime += time;
            if (alpha[i]->reloadTime > alpha[i]->fireRate)
            {
                alpha[i]->Attack();
                //alpha[i]->fireRate = 0;
                alpha[i]->reloadTime = 0;

            }
        }
    }

    //spawning more Enemies
   // EnemyWave = 2;
    if (Enemy_count == 0 && MONSTER == false) // no enemies spawn if monster is on screen
    {
      //  MonsterSpawn = rand() % 5;
        if (EnemyWave < 1)
        {
            SpawnTime += time;
            // cout << SpawnTime << endl;

            

            if (SpawnTime > 4)
            {
                for (int i = 0; i < 5; ++i)
                {
                    alpha[i] = new Invader(100 * i + 130, 100, "img/enemy_1.png", 3, 5,rand()%-5+0);
                }
                SpawnTime = 0;
                Enemy_count = 5;
                if(!Gamma)
                    EnemyWave++;
                else
                {
                    EnemyWave = rand() % 3;
                    MonsterSpawn = rand() % 5; // 1/4 chance of spawning monster after 2nd round
                    DragonSpawn = rand() % 6; // 1/5 chance of spawning dragon
                }
            }
        }

        else if(EnemyWave == 1)
        {
            SpawnTime += time;

            if (SpawnTime > 4)
            {
                for (int i = 0; i < 5; ++i)
                {
                    alpha[i] = new Invader(100 * i + 130, 100, "img/enemy_2.png", 4, 3, rand() % -5 + 0);
                    alpha[i]->enemy_spr.setScale(0.7, 0.7);
                }
                SpawnTime = 0;
                Enemy_count = 5;
                EnemyWave = rand() % 3;
                Gamma = true;
                MonsterSpawn = rand() % 5;
                DragonSpawn = rand() % 6;
                
            }
        }

        else if (EnemyWave == 2)
        {
            SpawnTime += time;

            if (SpawnTime > 4)
            {
                for (int i = 0; i < 5; ++i)
                {
                    alpha[i] = new Invader(100 * i + 130, 100, "img/enemy_3.png", 5, 2, rand() % -5 + 0);
                    alpha[i]->enemy_spr.setScale(0.55, 0.55);
                }
                SpawnTime = 0;
                Enemy_count = 5;
                EnemyWave = rand() % 3;
                MonsterSpawn = rand() % 5; 
                DragonSpawn = rand() % 6;
                
            }
        }
        
    } 


    //Spawning MONSTER
   // MonsterSpawn = 1;
    if (MonsterSpawn == 1 && MONSTER == false && Enemy_count ==0 && DRAGON == false)
    {
        SpawnTime += time;
        if(SpawnTime > 3)
        {
            monster = new Monster(237, 45, "img/monster.png", 60, 2, 0);
            monster->enemy_spr.setScale(0.2, 0.2);
            MONSTER = true;
            MX = monster->x;
            MY = monster->y;
         //   cout << "ASDASD" << endl;
            Enemy_count = 1;
            SpawnTime = 0;
            MonsterSpawn = -1;
        }
      
        
    }

    //Spawning Dragon
   // DragonSpawn = 1;
    if (DragonSpawn == 1 && DRAGON == false && Enemy_count == 0)
    {
        SpawnTime += time;
        if (SpawnTime > 1)
        {
            Dragon = new dragon(200, -100, "img/dragon.png", 65, 4, 0);
           // Dragon->enemy_spr.setScale(0.2, 0.2);
            DRAGON = true;
         
         //   cout << "DRAGON SPAWNED" << endl;
            Enemy_count = 1;
            SpawnTime = 0;
            DragonSpawn = -1;
        }
    }



    if (DRAGON)
    {
        Dragon->reloadTime += time;
        if (DragonFlame)
        {
            rect1 = Dragon->getBomb()->bullet_spr.getGlobalBounds();
   
            if (Dragon->reloadTime > Dragon->fireRate)
            {
                Dragon->destroy_bomb();
                delete Dragon;
                Dragon = nullptr;
                DRAGON = false;
                DragonFlame = false;
                flameRotation = 0;
                Enemy_count--;
                SCORE += 50;
            }
            else if(rect1.intersects(p->sprite.getGlobalBounds()) && player_alive && (p->addon == nullptr || p->addon->type == "fire"))
            {
                //cout << "got hit lmao" << endl;
                player_alive = false;
                respawnTime = -2;
                p->lives--;
            }
            else if (Dragon->x < p->sprite.getPosition().x-140)
            {
                flameRotation -= 0.005;
                Dragon->getBomb()->bullet_spr.setRotation(flameRotation);
            }
            else if (Dragon->x > p->sprite.getPosition().x-140)
            {
                //cout << "YEE";
                flameRotation += 0.005;
                Dragon->getBomb()->bullet_spr.setRotation(flameRotation);
            }
 
        }
        else if(Dragon != nullptr)
        {
            if (Dragon->fireRate < Dragon->reloadTime)
            {
                Dragon->Attack();
                rect1 = Dragon->getBomb()->bullet_spr.getGlobalBounds();
                rect1.width += 50;
                rect1.height *= 16;
                DragonFlame = true;
                Dragon->reloadTime = 0;
            }
        }
    }

   


    
    if (MONSTER == true)
    {
        //if locked on monster charges for 2sec then shoots
        if (LockON == true)
        {
            monster->reloadTime += time;
        }
        
        //updating x coordinates of monster
        if (monster->enemy_spr.getPosition().x + monster->enemy_spr.getGlobalBounds().width / 2 < p->sprite.getPosition().x+30 && player_alive)
        {
            MX += 0.03;
         
        }
        else if(monster->enemy_spr.getPosition().x + monster->enemy_spr.getGlobalBounds().width / 2 > p->sprite.getPosition().x + 30 && player_alive)
        {
            MX -= 0.03;
            
        }

        //locking on player and if player inside laser gets hit
        if(monster->enemy_spr.getPosition().x + monster->enemy_spr.getGlobalBounds().width / 2 - p->sprite.getPosition().x - 30 < 40 && monster->enemy_spr.getPosition().x + monster->enemy_spr.getGlobalBounds().width / 2 - p->sprite.getPosition().x - 30 > -40 && player_alive)
        {
           // cout << "pew " << endl;
            LockON = true; // getting ship in sight
            if (MonsterLASER )
            {
                if (p->addon == nullptr || p->addon->type == "fire")
                {
                    p->lives--;
                    respawnTime = 0;
                    player_alive = false;
                }
            }
            

        }

        //shooting laser
        if (LockON &&monster->fireRate < monster->reloadTime && monster->getBomb() == nullptr && player_alive)
        {
            monster->Attack();
            
            //   monster->reloadTime = 0;
            MonsterLASER = true;
           // LockON = false;
        }

        //moving monster laser sprite
        if (MonsterLASER)
        {
            monster->getBomb()->bullet_spr.setPosition(MX+110, MY + 80);
            
        }

        //moving monster sprite
        if (player_alive)
        {
            monster->enemy_spr.setPosition(MX, MY);
        }
        //  cout << MX << endl;



        //colliding with monster
        if (p->Collision(monster->enemy_spr.getPosition().x + monster->enemy_spr.getGlobalBounds().width / 2, monster->enemy_spr.getPosition().y + monster->enemy_spr.getGlobalBounds().height / 2, 170))
        {
            player_alive = false;
            respawnTime = 0;
            p->lives--;
        }


        //hitting monster with bullets
        if (p->b != nullptr)
        {
            if (monster->Collision(p->b->bullet_spr.getPosition().x, p->b->bullet_spr.getPosition().y, 120))
            {
            //    cout << "Monster " << "Got HIT" << endl;
                monster->hp -= p->b->damage;

                delete p->b;
                p->b = nullptr;

                if (monster->Destroy())
                {
                    SCORE += 40;
                  //  cout << "Score: " << SCORE << endl;
                    Enemy_count--;
                    delete monster;
                    monster = nullptr;
                    MONSTER = false;
                    MonsterLASER = false;
                }
            }
        }

        //hitting monster with spreadShot
        for (int j = 0; j < 7; ++j)
        {
            if (p->powerBullets[j] != nullptr)
            {
                if (monster != nullptr)
                {
                    if (monster->Collision(p->powerBullets[j]->bullet_spr.getPosition().x, p->powerBullets[j]->bullet_spr.getPosition().y, 120))
                    {

                        // delete p->powerBullets[j];
                        // p->powerBullets[j] = nullptr;
                        p->powerBullets[j]->bullet_spr.setPosition(-1000, 100 * j);


                       // cout << "Monster " <<  "Got HIT" << endl;
                        monster->hp -= 1;
                        if (monster->Destroy())
                        {
                            SCORE += 40;
                  //          cout << "Score: " << SCORE << endl;
                            Enemy_count--;
                            delete monster;
                            monster = nullptr;
                            MONSTER = false;
                            MonsterLASER = false;
                        }

                    }
                }
            }
        }



        
    }

    if (MonsterLASER && monster->reloadTime > monster->fireRate + 3) // fires laser for 5 seconds
    {
    //    cout << "GONESBFASIFBASFUIASBUFASBFASUIFO" << endl;
        monster->destroy_bomb();
        MonsterLASER = false;
        monster->reloadTime = 0;
        LockON = false;
    }
    


    //spawning AddOns
    if (player_alive)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (AddOns[i] == nullptr && FIRE == false && POWER == false)
            {
                coin = rand() % 5; // to randomize the spawn of items
            
                
                if (coin == 1 && AddOnSpawnTime >15)
                {
                    AddOns[i] = new Fire(rand() % 600 + 80, 250);
                    AddOnSpawnTime = 0;
                }
                else if(coin == 2 && DangerSpawnTime > 10)
                {
                    AddOns[i] = new Danger(rand() % 600 + 80, 250);
                    DangerSpawnTime = 0;
                }
                else if(coin == 3 && extraLifeTime > 25)
                {
                    AddOns[i] = new ExtraLive(rand() % 600 + 80, 250);
                    extraLifeTime = 0;
                }
                else if (coin == 4 && PowerUPSpawnTime > 20)
                {
                    AddOns[i] = new PowerUP(rand() % 600 + 80, 250);
                    PowerUPSpawnTime = 0;
                }
                

            }
        }
    }

    //items falling/deleting
    for (int i = 0; i < 4; ++i)
    {
        if (AddOns[i] != nullptr)
        {
            AddOns[i]->Fall();
            if (AddOns[i]->y > 780 && FIRE == false && POWER == false)
            {
                if (AddOns[i]->type == "danger")
                {
                    SCORE += 5;
                 //   cout << "Score: " << SCORE << endl;
                }
                delete AddOns[i];
                AddOns[i] = nullptr;
                
            }
        }
    }

  
    
 

    //Collecting AddOns
    if (player_alive)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (AddOns[i] != nullptr)
            {

                if (p->Collision(AddOns[i]->Icon_spr.getPosition().x, AddOns[i]->Icon_spr.getPosition().y, 34))
                {

                    if (AddOns[i]->type == "fire" && POWER == false)
                    {
                        fireAddOnTime = 0;

                        p->setAddOn(AddOns[i]);
                        AddOns[i]->x = 780; // when collected item item disapears
                        FIRE = true;


                    }
                    else if (AddOns[i]->type == "danger")
                    {
                        if (POWER == true)
                        {
                            delete AddOns[i];
                            AddOns[i] = nullptr;
                        }
                        else
                        {
                            p->lives--;
                            respawnTime = 0;

                            player_alive = false;
                        }


                    }
                    else if (AddOns[i]->type == "lives")
                    {
                        p->lives++;
                        AddOns[i]->x = 880; // when collected item item disapears
                    }
                    else if (AddOns[i]->type == "power" && FIRE == false)
                    {
                        PowerUPTime = 0;
                        p->setAddOn(AddOns[i]);
                        AddOns[i]->x = 780;
                        POWER = true;
                    }

                }
            }
        }
    }

    //turning addOn off
    if (fireAddOnTime > 5 && PowerUPTime > 5)
    {
        p->setAddOn(nullptr);
    }
    

    //p->setAddOn(nullptr);
    //turning fire and power off
    if (FIRE == true && fireAddOnTime > 5) // after use of fire, item gets deleted
    {

        for (int i = 0; i < 4; ++i)
        {
            if (AddOns[i] != nullptr)
            {
                if (AddOns[i]->type == "fire")
                {
                    delete AddOns[i];
                    AddOns[i] = nullptr;
                }
            }
        }
        FIRE = false;
            
    }
    else if(POWER == true && PowerUPTime > 5) // after use of POWER, item gets deleted
    {

        for (int i = 0; i < 4; ++i)
        {
            if (AddOns[i] != nullptr)
            {
                if (AddOns[i]->type == "power")
                {
                    delete AddOns[i];
                    AddOns[i] = nullptr;
                }
            }
        }
        POWER = false;

    }

    
    

    


    
    
	////////////////////////////////////////////////
	/////  Call your functions here            ////
	//////////////////////////////////////////////
   
    //wrap around map
    p->wrapAround();
    
    
    

	window.clear(Color::Black); //clears the screen
	window.draw(background);  // setting background
    
    //drawing player
    if (player_alive)
    {
        window.draw(p->sprite);   // setting player on screen
    }
    

    //drawing alphas
    for (int i = 0; i < 5; ++i)
    {
        if (alpha[i] == nullptr)
        {
            continue;
        }
        window.draw(alpha[i]->enemy_spr);
    }

    //drawing MONSTER and monster laser
    if (monster != nullptr)
    {
        window.draw(monster->enemy_spr);
        if (monster->getBomb() != nullptr)
        {
            window.draw(monster->getBomb()->bullet_spr);
        }

    }

    //drawing dragon
    if (Dragon != nullptr)
    {
        window.draw(Dragon->enemy_spr);
        if (Dragon->getBomb() != nullptr)
        {
            window.draw(Dragon->getBomb()->bullet_spr);
        }
    }
   

    //drawing player bullets, moving and deleting them
    if (p->b != nullptr)
    {
        p->b->move();
        window.draw(p->b->bullet_spr);
        p->Bullet_recycle();
    }
    

    //drawing alphas bombs, moving and deleting them
    for (int i = 0; i < 5; ++i)
    {
        if (alpha[i] != nullptr)
        {
            if (alpha[i]->getBomb() != nullptr)
            {
                alpha[i]->getBomb()->move();
                window.draw(alpha[i]->getBomb()->bullet_spr);
                alpha[i]->Bomb_recycle();
            }

        }
    }
    
    //drawing AddOns
    for (int i = 0; i < 4; ++i)
    {
        if (AddOns[i] != nullptr)
        {
            window.draw(AddOns[i]->Icon_spr);
        }
    }

    
    //drawing LIVES
    for (int i = 0; i < p->lives; ++i)
    {
        Lives.setScale(1, 1);
        Lives.setPosition(38 * i + 20, 20);
        window.draw(Lives);
    }
    
    //drawing powerUP BUllets
    for (int i = 0; i < 7; ++i)
    {
        if (p->powerBullets[i] != nullptr)
        {
            p->powerBullets[i]->move();
            window.draw(p->powerBullets[i]->bullet_spr);
            p->Bullet_recycle();
        }
    }

    //drawing shield PowerUP
    if (p->addon != nullptr && p->addon->type != "fire")
    {
        p->shield.setPosition(p->sprite.getPosition().x - 36, p->sprite.getPosition().y-5);
        window.draw(p->shield);
    }
    
    //displaying Score
    window.draw(text_Score);

    if (p->lives <= 0)
    {
        player_alive = false;
        window.draw(text_GameOver);
        // cout << "YOU DIED" << endl;//////////////////////////////////////////////////////////////////////////////////
    }

    if (!Pause)
    {
        window.display();  //Displying all the sprites
    }
    }


}


};

