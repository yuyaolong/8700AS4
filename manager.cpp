#include <iostream>
#include <string>
#include <iomanip>
#include "vector2f.h"
#include "gamedata.h"
#include "manager.h"
#include "twowaysprite.h"
#include "vessel.h"
#include "explotion.h"


Manager::~Manager() { 
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
    std::vector<World*>::const_iterator wPtr = worlds.begin();
    std::vector<Scaledsprite *>::const_iterator ePtr = enemys.begin();
  while ( ptr != sprites.end() ) {
    delete (*ptr);
    ++ptr;
  }
    while (wPtr != worlds.end() ) {
        delete (*wPtr);
        ++wPtr;
    }
    while (ePtr != enemys.end() ) {
        delete (*ePtr);
        ++ePtr;
    }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  viewport( Viewport::getInstance() ),
    worlds(),
  sprites(),
  currentSprite(),
  enemys(),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") ),
    eachSpritsNumbe(),
    hud("hud"),
    health("health")
{
     if (SDL_Init(SDL_INIT_VIDEO) != 0) {
         throw string("Unable to initialize SDL: ");
     }
    SDL_WM_SetCaption(title.c_str(), NULL);
    atexit(SDL_Quit);

    
    worlds.push_back(new World("back1"));
    worlds.push_back(new World("back2"));
    worlds.push_back(new World("back3"));
    worlds.push_back(new World("back4"));
    std::sort(worlds.begin(), worlds.end(), FactorCompare());
        eachSpritsNumbe.push_back(Gamedata::getInstance().getXmlInt("Enemy/number"));
    eachSpritsNumbe.push_back(Gamedata::getInstance().getXmlInt("Vessel1/number"));
    eachSpritsNumbe.push_back(Gamedata::getInstance().getXmlInt("Explotion/number"));
  	
    
        gundam = new Player("Gundam");
        gundam -> setStatus(STAND);
        sprites.push_back(gundam);
        
    
    
    enemys.reserve(eachSpritsNumbe[0]);
    for (int i = 0; i< eachSpritsNumbe[0]; i++) {
        enemys.push_back( new Scaledsprite("Enemy"));
    }
    std::sort(enemys.begin(),enemys.end(),SpriteCompareLess());
    std::cout<<"Painter scaled sprites\n";
    for (int i = 0; i< eachSpritsNumbe[0]; i++) {
        std::cout<<enemys[i]->getScale()<<"\n";
    }
  
    for (int i=0; i< eachSpritsNumbe[1]; i++) {
        sprites.push_back( new Vessel("Vessel1") );
    }
    

    for (int i=0; i< eachSpritsNumbe[2]; i++) {
        sprites.push_back( new Explotion("Explotion") );
    }

    currentSprite = sprites.begin();
    viewport.setObjectToTrack(*currentSprite);
}




void Manager::draw() const {
  //world.draw();
    for (unsigned int i=0; i<worlds.size(); i++) {
        worlds[i]->draw();
    }
    for (unsigned int i=0; i<enemys.size(); i++) {
        enemys[i]->draw();
    }
  clock.draw();
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->draw();
    ++ptr;
  }
  io.printMessageAt(title, 650, 450);
    hud.draw();
    health.draw();
  viewport.draw();
    
    
  SDL_Flip(screen);
}

// Move this to IOManager
// void Manager::makeFrame() {
//   std::stringstream strm;
//   strm << "frames/" << username<< '.' 
//        << std::setfill('0') << std::setw(4) 
//        << frameCount++ << ".bmp";
//   std::string filename( strm.str() );
//   std::cout << "Making frame: " << filename << std::endl;
//   SDL_SaveBMP(screen, filename.c_str());
// }

void Manager::switchSprite() {
    static int whichKindSprite = 0;
    whichKindSprite++;
    for (int k=0; k<eachSpritsNumbe[whichKindSprite%(Gamedata::getInstance().getXmlInt("spritesKinds"))]; ++k) {
         currentSprite++;
    }
 
  if ( currentSprite == sprites.end() ) {
    currentSprite = sprites.begin();
  }
  viewport.setObjectToTrack(*currentSprite);
}

void Manager::update() {
  clock.update();
  Uint32 ticks = clock.getTicksSinceLastFrame();
    for (unsigned int i=0; i<enemys.size(); i++) {
        enemys[i]->update(ticks);
    }
  std::list<Drawable*>::const_iterator ptr = sprites.begin();
  while ( ptr != sprites.end() ) {
    (*ptr)->update(ticks);
    ++ptr;
  }
  if ( makeVideo && frameCount < frameMax ) {
    io.makeFrame(frameCount);
  }
    for (unsigned int i=0; i<worlds.size(); i++) {
        worlds[i]->update();
    }
    hud.update(ticks);
    health.update(ticks);
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;
  bool done = false;
  clock.start();
  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
       
        if (event.type == SDL_KEYUP) {
            gundam->setStatus(STAND);
        }
        
      if(event.type == SDL_KEYDOWN) {
          
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_s]) {
          clock.toggleSloMo();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
          if (keystate[SDLK_F1]) {
              hud.toggle();
          }
          
      }
        
        if(keystate[SDLK_LEFT])
        {
            gundam->setStatus(MOVELEFT);
            
        }
        if(keystate[SDLK_RIGHT])
        {
            gundam->setStatus(MOVERIGHT);
        }
        if(keystate[SDLK_DOWN])
        {
            gundam->setStatus(MOVEDOWN);
        }
        if(keystate[SDLK_UP])
        {
            gundam->setStatus(MOVEUP);
        }
        
        if(keystate[SDLK_RIGHT] && keystate[SDLK_LEFT])
        {
            gundam->setStatus(STAND);
        }
        if(keystate[SDLK_UP] && keystate[SDLK_DOWN])
        {
            gundam->setStatus(STAND);
        }

    }

    update();
    draw();
    
  }
}
