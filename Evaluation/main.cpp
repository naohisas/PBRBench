#include <kvs/ColorImage>
#include <kvs/Vector3>
#include <kvs/RGBColor>
#include <cmath>
#include <iostream>


int main( int argc, char** argv )
{
    kvs::ColorImage image1( argv[1] );
    kvs::ColorImage image2( argv[2] );

    kvs::Real32 sum = 0.0f;
    for ( size_t index = 0; index < image1.numberOfPixels(); index++ )
    {
        const kvs::Vec3 p1 = image1.pixel( index ).toVec3();
        const kvs::Vec3 p2 = image2.pixel( index ).toVec3();
        const kvs::Real32 length = ( p2 - p1 ).length();
        sum += length * length;
    }

    const kvs::Real32 mse = sum / ( 3.0f * image1.numberOfPixels() );
    const kvs::Real32 psnr = 10.0f * std::log10( 1.0 / mse );
    std::cout << "MSE: " << mse << std::endl;
    std::cout << "PSNR: " << psnr << std::endl;

    return 0;
}
