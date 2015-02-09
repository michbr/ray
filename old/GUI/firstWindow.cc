//#include <CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

using namespace CEGUI;



CEGUI::OpenGLRenderer& myRenderer = CEGUI::OpenGLRenderer::bootstrapSystem();





WindowManager& wmgr = WindowManager::getSingleton();
Window* myRoot = wmgr.createWindow( "DefaultWindow", "root" );
System::getSingleton().getDefaultGUIContext().setRootWindow( myRoot );
myRoot->addChild( fWnd );
// position a quarter of the way in from the top-left of parent.
fWnd->setPosition( UVector2( UDim( 0.25f, 0.0f ), UDim( 0.25f, 0.0f ) ) );
// set size to be half the size of the parent
fWnd->setSize( USize( UDim( 0.5f, 0.0f ), UDim( 0.5f, 0.0f ) ) );
fWnd->setText( "Hello World!" );

