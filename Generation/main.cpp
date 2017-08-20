#include <kvs/HydrogenVolumeData>
#include <kvs/StructuredVolumeObject>
#include <kvs/PointObject>
#include <kvs/CellByCellMetropolisSampling>
#include <kvs/TransferFunction>
#include <kvs/Vector3>
#include <kvs/OpenMP>
#include "Input.h"
#include "Logger.h"
#include "Timer.h"

typedef kvs::StructuredVolumeObject Volume;
typedef kvs::PointObject Point;

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

int main( int argc, char** argv )
{
    Timer timer;
    Logger logger;

    Input input( argc, argv );
    if ( !input.parse() ) { return 1; }

    Volume* volume = Create( input, timer );
    Point* point = Generate( input, timer, volume );
    delete point;

    timer.print( logger() << "PROCESSING TIMES" << std::endl );

    return 0;
}
