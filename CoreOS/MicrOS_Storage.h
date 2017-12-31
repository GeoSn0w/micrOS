//Declarations for storage media (sda1) for micrOS by GeoSn0w (@FCE365)

Sd2Card MicroSD;
SdVolume sda1;
const int chipSelect = 10;
bool check_sda(){
    if (!MicroSD.init(SPI_HALF_SPEED, chipSelect)) {
        return false;
    } else {
        return true;
    }
}
