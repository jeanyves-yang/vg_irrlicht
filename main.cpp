#include <irrlicht.h>
#include <cstdio>
#include <iostream>

using namespace irr;
namespace iv = irr::video;
namespace is = irr::scene;
namespace ic = irr::core;

struct MyEventReceiver : IEventReceiver
{

    bool OnEvent ( const SEvent & event )
    {

        // Si l’événement est de type clavier ( KEY_INPUT )
        // et du genre pressage de touche
        // et que la touche est escape , on sort du programme
        if ( event.EventType == EET_KEY_INPUT_EVENT && event . KeyInput.PressedDown && event.KeyInput.Key == KEY_ESCAPE )
        {
         exit (0);
        }
        ic::vector3df nodePosition;
        if(node!= NULL)
        {
            nodePosition = node->getPosition();
        }
        switch(event.KeyInput.Key)
        {
            case KEY_KEY_R:
            node->setMD2Animation( irr::scene::EMAT_RUN );
            break;
        case KEY_KEY_D:
            node->setMD2Animation( irr::scene::EMAT_DEATH_FALLBACKSLOW );
            break;
        case KEY_UP:
            nodePosition.X -= 5.0f;
            break;
        case KEY_DOWN:
            nodePosition.X += 5.0f;
            break;
        case KEY_RIGHT:
            nodePosition.X += 5.0f;
            break;
        case KEY_LEFT:
            nodePosition.X += 5.0f;
            break;
        default: break;
        }
        if(node != NULL)
        {
            node->setPosition(nodePosition);
        }
        return false ;
    }
    is::IAnimatedMeshSceneNode *node = NULL;
 };

int main()
{
  // Création de la fenêtre et du système de rendu.
  MyEventReceiver receiver;
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL, ic::dimension2d <u32 >(640 , 480), 16, false, false, false, & receiver );

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();
  is::IAnimatedMesh *mesh = smgr->getMesh( "data/tris.md2" );

  receiver.node = smgr->addAnimatedMeshSceneNode( mesh );
  receiver.node->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  receiver.node->setMD2Animation( irr::scene::EMAT_CROUCH_WALK);
  receiver.node->setMaterialTexture( 0, driver->getTexture( "data/blue_texture.pcx") );
  receiver.node->setDebugDataVisible(is::EDS_NORMALS);

  is::IAnimatedMeshSceneNode *node2 = smgr->addAnimatedMeshSceneNode( mesh );
  node2->setMaterialFlag( irr::video::EMF_LIGHTING, false );
  node2->setMD2Animation( irr::scene::EMAT_CROUCH_WALK);
  node2->setMaterialTexture( 0, driver->getTexture( "data/red_texture.pcx") );
  //smgr->addCameraSceneNode( nullptr, ic::vector3df( 0, 30, -40 ), ic::vector3df( 0, 5, 0 ) );
  is::ICameraSceneNode *camera = smgr->addCameraSceneNode( receiver.node, ic::vector3df(0,0,0),ic::vector3df(0,0,5),-1, true);
  is::ISceneNodeAnimator *anim = smgr->createFlyStraightAnimator( ic::vector3df( -100 ,0 ,60 ), ic :: vector3df (100 ,0 ,60) , 3500 , true );
  node2->addAnimator( anim );

  // Ajout de l’archive qui contient entre autres un niveau complet
  device->getFileSystem()->addFileArchive("data/map-20kdm2.pk3");
  // On charge un bsp (un niveau ) en particulier :
  is::IAnimatedMesh *mesh2 = smgr->getMesh("20kdm2.bsp");
  is::ISceneNode *node3;
  node3 = smgr->addOctreeSceneNode(mesh2->getMesh(0), nullptr, -1, 1024);
  // Translation pour que nos personnages soient dans le décor
  node3->setPosition (core::vector3df(-1300, -104, -1249));
  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(150,150,150,255));


    // Dessin de la scène :x
    smgr->drawAll();
    // 
    driver->endScene();
  }
  device->drop();

  return 0;
}
