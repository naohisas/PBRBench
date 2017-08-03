#include <KVS.osmesa/Lib/Screen.h>
#include <kvs/HydrogenVolumeData>
#include <kvs/StructuredVolumeObject>
#include <kvs/PointObject>
#include <kvs/CellByCellMetropolisSampling>
#include <kvs/ParticleBasedRenderer>
#include <kvs/TransferFunction>
#include <kvs/Vector3>
#include <kvs/ColorImage>
#include <cmath>
#include "Input.h"
#include "Logger.h"
#include "Timer.h"

typedef kvs::osmesa::Screen Screen;
typedef kvs::StructuredVolumeObject Volume;
typedef kvs::PointObject Point;
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

Point* Generate( Input& input, Timer& timer, Volume* volume )
{
    const size_t repeats = input.repeats;
    const float step = 0.5f;
    const kvs::TransferFunction tfunc( 256 );

    timer.start();
    Point* point = new kvs::CellByCellMetropolisSampling( volume, repeats, step, tfunc );
    timer.stop();
    timer.stamp( "Generate" );

    delete volume;
    return point;
}

Image Render( Input& input, Timer& timer, Screen& screen, Point* point )
{
    kvs::ParticleBasedRenderer* renderer = new kvs::ParticleBasedRenderer();
    renderer->setSubpixelLevel( std::sqrt( input.repeats ) );
    screen.registerObject( point, renderer );
    screen.draw();

    timer.start();
    screen.draw();
    timer.stop();
    timer.stamp( "Render" );

    return screen.capture();
}

int main( int argc, char** argv )
{
    Screen screen;

    Timer timer;
    Logger logger( "result.log" );

    Input input( argc, argv );
    if ( !input.parse() ) { return 1; }
    input.print( logger() << "INPUT PARAMETERS" << std::endl );

    Volume* volume = Create( input, timer );
    volume->print( logger() << std::endl << "INPUT VOLUME DATA" << std::endl );

    Point* point = Generate( input, timer, volume );
    point->print( logger() << std::endl << "GENERATED PARTICLES" << std::endl );

    Image image = Render( input, timer, screen, point );
    image.write( "result.bmp" );

    timer.print( logger() << std::endl << "PROCESSING TIMES" << std::endl );

    return 0;
}
