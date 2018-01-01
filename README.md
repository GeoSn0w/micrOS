# micrOS
An Arduino Mega Operating System With TFT TouchScreen and Micro SD Card Support.

<p>This is an operating system I have written from scratch for Arduino Mega. It is optimized to work with MCUFriend's 3.5 inch TFT TouchScreen shield and I am currently working to support the SIM900 GSM Shield for SIM Card Support. Tests on this shield and the OS have been conclusive, but I still have to fix stuff here and there, therefore I am not releasing the BaseBand (GSM Shield) code for it yet. It should, however, boot without that with a small kernel patch, refer to patches.</p>

<p><b>What is this tho?</b></p>
Well, an Operating System. I don't want to include it in the same category as Linux, macOS, and Windows because it isn't. It is very basic because Arduino Mega in itself is very basic. With 16 Mhz of CPU clock, 8KB of SRAM and an EEPROM of 4KB, this is not exactly the rig to run an OS at all.</p>

<p><b>Why you made this contraption then?</b></p>
To push the limits of the Arduino board and to work on a nice project that has barely ever been touched before.
I should make myself clear here that I don't expect someone to go ahead and use this OS on an Arduino as a daily device (lol).</p>

<p><b>Project Status:</b><p>
<p>This is a work in progress. For the moment I am focusing on building the Desktop UI (com.geosn0w.switchboard). The 3.5-inch TouchScreen from MCUFRIEND is not the best, nor the easiest to code because most decent UTFT and UTouchScreen libraries and forks are not compatible with it (or only partially), but I like it better this way since harder = more things to learn.
The UI is an original one, I did not inspire it from a different product (if anything, from the flip phones of early 2007?). It is not the most astonishing UI in the universe, but I assume for an Arduino Mega with such limited hardware and no Graphics Processing Unit whatsoever, it is pretty decent, considering that is CPU driven, and Atmel Atmega2560 is barely a CPU.
</p>

<p>I am currently working actively on this project so features will be added. The reason I uploaded the source code in such an alpha stage is that some people were curious, especially when it comes to the TouchScreen and the graphics.</p>
