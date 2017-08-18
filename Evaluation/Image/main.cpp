#include <kvs/glut/Application>
#include <kvs/glut/Screen>
#include <kvs/HydrogenVolumeData>
#include <kvs/StructuredVolumeObject>
#include <kvs/RayCastingRenderer>
#include <kvs/ColorImage>
#include <kvs/Camera>
#include "Input.h"
#include "Logger.h"
#include "Timer.h"

typedef kvs::glut::Application Application;
typedef kvs::glut::Screen Screen;
typedef kvs::StructuredVolumeObject Volume;
typedef kvs::ColorImage Image;

Volume* Create( Input& input, Timer& timer )
{
    const kvs::Vec3u dims = kvs::Vec3u::All( input.dims );

    timer.start();
    Volume* volume = new kvs::HydrogenVolumeData( dims );
    timer.stop();
    timer.stamp( "Create" );

    return volume;
}

Image Render( Input& input, Timer& timer, Screen& screen, Volume* volume )
{
    kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();
    screen.registerObject( volume, renderer );
    screen.create();
    screen.hide();
    screen.paintEvent();

    timer.start();
    screen.paintEvent();
    timer.stop();
    timer.stamp( "Render" );

    return screen.scene()->camera()->snapshot();
}

int main( int argc, char** argv )
{
    Application app( argc, argv );
    Screen screen( &app );

    Timer timer;
    Logger logger;

    Input input( argc, argv );
    if ( !input.parse() ) { return 1; }

    Volume* volume = Create( input, timer );
    volume->print( logger() << std::endl << "INPUT VOLUME DATA" << std::endl );

    Image image = Render( input, timer, screen, volume );
    image.write( "result.bmp" );

    timer.print( logger() << std::endl << "PROCESSING TIMES" << std::endl );

    app.quit();
    return 0;
}
