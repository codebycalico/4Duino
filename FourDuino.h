#ifndef FOURDUINO_h
#define FOURDUINO_h

#include <Arduino.h>
#include "SoftwareSerial.h"

#include "OLEDUtil.h"
#include "Color.h"
#include "SerialContainers.h"

//
// Settings
//

#define OLED_HARDWARE_SERIAL_DEFAULT    Serial // Mega can also use Serial1, Serial2, Serial3
#define OLED_BAUD_DEFAULT			    28800 // 38400+ causes problems with ReadSector using SoftwareSerial
#define OLED_INIT_RETRIES               10 // How many times to try initializing before failing
#define OLED_INIT_DELAY_MS			    1000 // How long to wait for the display to power up
#define OLED_RESET_DELAY_MS			    20 // How long to hold reset pin low
#define OLED_RESPONSE_RETRY_DELAY_US    17 // 17.3: Approximate amount of time for one bit at 57600
#define OLED_RESPONSE_RETRIES           30000 // 60000: About one second at 17 microseconds per retry
#define OLED_SD_SECTOR_READ_DELAY_MS    0 // Slow SD cards might want to increase this to prevent underflow
#define OLED_SD_WIPE_MAX_SECTORS        0xFFFFFFFF // Dunno how big these things get, really.

//
// General constants
//

#define OLED_ACK					0x06
#define OLED_NAK					0x15
#define OLED_NORESPONSE				0x00

#define OLED_PRM_NA					0x00
#define OLED_PRM_BOOL_FALSE			0x00
#define OLED_PRM_BOOL_TRUE			0x01

//
// Base system commands
//

#define OLED_CMD_BAUD_AUTO			0x55
#define OLED_CMD_INFO				0x56
#define OLED_CMD_CLEAR_SCREEN		0x45
#define OLED_CMD_CTLFUNC			0x59
#define OLED_CMD_SLEEP				0x5A
#define OLED_CMD_INPUT_STATUS		0x4A
#define OLED_CMD_INPUT_STATUS_WAIT	0x6A
#define	OLED_CMD_SOUND				0x4E
#define OLED_CMD_TUNE				0x6E

#define OLED_PRM_CTLFUNC_NA			0x00
#define OLED_PRM_CTLFUNC_POWER		0x01
#define OLED_PRM_CTLFUNC_CONTRAST	0x02
#define OLED_PRM_CTLFUNC_LOWPOWER	0x03
#define OLED_PRM_CTLFUNC_POWER_OFF	0x00
#define OLED_PRM_CTLFUNC_POWER_ON	0x01
#define OLED_PRM_CTLFUNC_LOWPOWER_SHUTDOWN	0x00
#define OLED_PRM_CTLFUNC_LOWPOWER_POWERUP	0x01
#define OLED_PRM_SLEEP_SD_OFF		0x80
#define OLED_PRM_SLEEP_WAKE_JOY		0x02
#define OLED_PRM_SLEEP_WAKE_SERIAL	0x01

#define OLED_DEVICETYPE_OLED		0x00
#define OLED_DEVICETYPE_LCD			0x01
#define OLED_DEVICETYPE_VGA			0x02

#define OLED_RES_64					0x64
#define OLED_RES_96					0x96
#define OLED_RES_128				0x28
#define OLED_RES_160				0x60
#define OLED_RES_176				0x76
#define OLED_RES_220				0x22
#define OLED_RES_320				0x32

//
// Graphics commands
//

#define OLED_CMD_READ_PIXEL			0x52
#define OLED_CMD_DRAW_PIXEL			0x50
#define OLED_CMD_DRAW_LINE			0x4C
#define OLED_CMD_DRAW_RECTANGLE		0x72
#define OLED_CMD_DRAW_TRIANGLE		0x47
#define OLED_CMD_DRAW_POLYGON		0x67
#define OLED_CMD_DRAW_CIRCLE		0x43
#define OLED_CMD_DRAW_IMAGE			0x49
#define OLED_CMD_ADD_USER_BITMAP	0x41
#define OLED_CMD_DRAW_USER_BITMAP	0x44
#define OLED_CMD_SET_BACKGROUND		0x4B
#define OLED_CMD_REPLACE_BACKGROUND	0x42
#define OLED_CMD_REPLACE_COLOR		0x6B
#define OLED_CMD_SET_PEN_SIZE		0x70
#define OLED_CMD_SCREEN_COPY_PASTE	0x63

#define OLED_PRM_DRAW_IMAGE_8BIT	0x08
#define OLED_PRM_DRAW_IMAGE_16BIT	0x10
#define OLED_PRM_SET_PEN_SIZE_FILL	0x00
#define OLED_PRM_SET_PEN_SIZE_EMPTY	0x01

//
// Text commands
//

#define OLED_CMD_SET_FONT			0x46
#define OLED_CMD_SET_FONT_OPACITY	0x4F
#define OLED_CMD_DRAW_STRING_TEXT	0x73
#define OLED_CMD_DRAW_STRING_GFX	0x53
#define OLED_CMD_DRAW_STRING_BUTTON	0x62
#define OLED_CMD_DRAW_CHAR_TEXT		0x54 // I don't really see the point.
#define OLED_CMD_DRAW_CHAR_GFX		0x74 // Not bothering.

#define OLED_PRM_BUTTON_DOWN        0x00
#define OLED_PRM_BUTTON_UP          0x01

#define OLED_FONT_SMALL				0x00
#define OLED_FONT_MEDIUM			0x01
#define OLED_FONT_LARGE				0x02
#define OLED_FONT_SIZE_NOT_SET		0xFF
#define OLED_FONT_TRANSPARENT		0x00
#define OLED_FONT_OPAQUE			0x01
#define OLED_FONT_OPACITY_NOT_SET	0xFF
#define OLED_FONT_COLOR_DEFAULT		COLOR_WHITE
#define OLED_FONT_PROPORTIONAL		0x10
#define OLED_FONT_NONPROPORTIONAL	0x00
#define OLED_FONT_PROPORTIONAL_NOT_SET	0xFF
#define OLED_BUTTON_COLOR_DEFAULT       COLOR_SLATEGRAY
#define OLED_BUTTON_FONT_COLOR_DEFAULT  COLOR_SILVER

//
// SD Card commands
//

#define OLED_CMD_EXTENDED_SD            0x40
#define OLED_CMD_SD_INITIALIZE_CARD     0x69
#define OLED_CMD_SD_SET_ADDRESS_POINTER 0x41
#define OLED_CMD_SD_READ_BYTE           0x72
#define OLED_CMD_SD_WRITE_BYTE          0x77
#define OLED_CMD_SD_READ_SECTOR_BLOCK   0x52
#define OLED_CMD_SD_WRITE_SECTOR_BLOCK  0x57
#define OLED_CMD_SD_WRITE_SCREENSHOT    0x43
#define OLED_CMD_SD_DISPLAY_IMAGE       0x49
#define OLED_CMD_SD_DISPLAY_OBJECT      0x4F
#define OLED_CMD_SD_DISPLAY_VIDEO       0x56
#define OLED_CMD_SD_RUN_4DSL_SCRIPT     0x50

#define OLED_SD_SECTOR_SIZE             512
#define OLED_SD_READ_STRING_BUFFER_LENGTH   32
// Decrease this to apply an artificial limit on string length.
// Arduino only has 2KB SRAM anyway, so reducing this may be outright necessary...
#define OLED_SD_READ_STRING_MAX_LENGTH  2048



class OLED
{
public:
    OLED(uint8_t pinReset, HardwareSerial serial,
        uint32_t baudRate = OLED_BAUD_DEFAULT, uint16_t initDelay = OLED_INIT_DELAY_MS);
    OLED(uint8_t pinReset, SoftwareSerial serial,
        uint32_t baudRate = OLED_BAUD_DEFAULT, uint16_t initDelay = OLED_INIT_DELAY_MS);
    ~OLED();
    
    void SerialBegin(uint32_t baudRate);
    void Write(uint8_t value);
    void Write(uint8_t numValues, uint8_t value1, ...);
    void WriteShort(uint16_t value);
    void WriteShort(uint8_t numValues, uint16_t value1, ...);
    void WriteLong(uint32_t value);
    void WriteLong(uint8_t numValues, uint32_t value1, ...);
    void WriteText(char* text);
    void WriteString(String text);
    
    bool GetResponse(uint8_t& result);
    bool GetResponseShort(uint16_t& result);
    bool GetAck();

    bool Init();
    void Reset();

    // General
    bool GetDeviceInfo(bool displayOnScreen);
    String GetDeviceType();
    uint8_t GetDeviceWidth();
    uint8_t GetDeviceHeight();
    uint8_t GetHardwareRevision();
    uint8_t GetFirmwareRevision();
    bool Clear();
    bool SetPower(bool on);
    bool On();
    bool Off();
    bool SetContrast(uint8_t value);
    bool LowPowerShutdown();
    bool LowPowerPowerUp();
    bool TurnOffSD();
    bool WakeOnJoystick();
    bool WakeOnSerial();
    // TODO
    bool Joystick();
    bool JoystickWait();
    bool Sound(uint16_t note, uint16_t duration);
    bool Tune(uint8_t length, uint16_t note, uint16_t duration = 0);

    // Graphics
    bool ReadPixel(uint8_t x, uint8_t y, uint16_t& resultShort);
    bool ReadPixel(uint8_t x, uint8_t y, Color& resultColor);
    bool DrawPixel(uint8_t x, uint8_t y, uint16_t color);
    bool DrawPixel(uint8_t x, uint8_t y, Color color);
    bool DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);
    bool DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color);
    bool DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t color);
    bool DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Color color);
    bool DrawRectangleWH(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);
    bool DrawRectangleWH(uint8_t x, uint8_t y, uint8_t width, uint8_t height, Color color);
    bool DrawProgressBar(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
        uint8_t progressPercent, uint16_t foreColor, uint16_t backColor);
    bool DrawProgressBar(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
        uint8_t progressPercent, Color foreColor, Color backColor);
    bool DrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3,
        uint16_t color);
    bool DrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3,
        Color color);
    bool DrawPolygonV(uint16_t color, uint8_t numVertices, uint8_t x1, uint8_t y1, va_list ap);
    bool DrawPolygon(uint16_t color, uint8_t numVertices, uint8_t x1, uint8_t y1, ...);
    bool DrawPolygon(Color color, uint8_t numVertices, uint8_t x1, uint8_t y1, ...);
    bool DrawPolygon(uint16_t color, uint8_t numVertices, uint8_t vertices[][2]);
    bool DrawPolygon(Color color, uint8_t numVertices, uint8_t vertices[][2]);
    bool DrawCircle(uint8_t x, uint8_t y, uint8_t radius, uint16_t color);
    bool DrawCircle(uint8_t x, uint8_t y, uint8_t radius, Color color);
    bool AddUserBitmap(uint8_t char_index,
        uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4,
        uint8_t data5, uint8_t data6, uint8_t data7, uint8_t data8);
    bool DrawUserBitmap(uint8_t charIndex, uint8_t x, uint8_t y, uint16_t color);
    bool DrawUserBitmap(uint8_t charIndex, uint8_t x, uint8_t y, Color color);
    bool SetFill(bool fillShapes);
    bool ScreenCopyPaste(uint8_t xs, uint8_t ys, uint8_t xd, uint8_t yd,
        uint8_t sourceWidth, uint8_t sourceHeight);
    bool SetBackground(uint16_t color);
    bool SetBackground(Color color);
    bool ReplaceBackground(uint16_t color);
    bool ReplaceBackground(Color color);
    // TODO
    bool DrawImage8Bit(uint8_t x, uint8_t y, uint8_t imageWidth, uint8_t imageHeight,
        uint8_t pixel1, ...);
    bool DrawImage16Bit(uint8_t x, uint8_t y, uint8_t imageWidth, uint8_t imageHeight,
        uint16_t pixel1, ...);

    // Text
    bool SetFont(uint8_t fontSize);
    bool SetFontOpacity(bool opaque);
    void SetButtonOpacity(bool opaque);
    void SetFontProportional(bool proportional);
    void SetFontColor(uint16_t color);
    void SetFontColor(Color color);
    void SetButtonColor(uint16_t color);
    void SetButtonColor(Color color);
    void SetButtonFontColor(uint16_t color);
    void SetButtonFontColor(Color color);
    bool DrawText(uint8_t col, uint8_t row, String text, uint16_t color,
        uint8_t fontSize = OLED_FONT_SIZE_NOT_SET, uint8_t opacity = OLED_FONT_OPACITY_NOT_SET,
        uint8_t proportional = OLED_FONT_PROPORTIONAL_NOT_SET);
    bool DrawText(uint8_t col, uint8_t row, String text, Color color,
        uint8_t fontSize = OLED_FONT_SIZE_NOT_SET, uint8_t opacity = OLED_FONT_OPACITY_NOT_SET,
        uint8_t proportional = OLED_FONT_PROPORTIONAL_NOT_SET);
    bool DrawText(uint8_t col, uint8_t row, String text);
    bool DrawTextGraphic(uint8_t x, uint8_t y, String text,
        uint8_t width, uint8_t height, uint16_t color,
        uint8_t fontSize = OLED_FONT_SIZE_NOT_SET, uint8_t opacity = OLED_FONT_OPACITY_NOT_SET,
        uint8_t proportional = OLED_FONT_PROPORTIONAL_NOT_SET);
    bool DrawTextGraphic(uint8_t x, uint8_t y, String text,
        uint8_t width, uint8_t height, Color color,
        uint8_t fontSize = OLED_FONT_SIZE_NOT_SET, uint8_t opacity = OLED_FONT_OPACITY_NOT_SET,
        uint8_t proportional = OLED_FONT_PROPORTIONAL_NOT_SET);
    bool DrawTextGraphic(uint8_t x, uint8_t y, String text, uint8_t width, uint8_t height);
    bool DrawTextGraphic(uint8_t x, uint8_t y, String text);
    bool DrawTextButton(uint8_t x, uint8_t y, String text,
        uint8_t width, uint8_t height, bool pressed, uint16_t fontColor, uint16_t buttonColor,
        uint8_t fontSize = OLED_FONT_SIZE_NOT_SET, uint8_t opacity = OLED_FONT_OPACITY_NOT_SET,
        uint8_t proportional = OLED_FONT_PROPORTIONAL_NOT_SET);
    bool DrawTextButton(uint8_t x, uint8_t y, String text,
        uint8_t width, uint8_t height, bool pressed, Color fontColor, Color buttonColor,
        uint8_t fontSize = OLED_FONT_SIZE_NOT_SET, uint8_t opacity = OLED_FONT_OPACITY_NOT_SET,
        uint8_t proportional = OLED_FONT_PROPORTIONAL_NOT_SET);
    bool DrawTextButton(uint8_t x, uint8_t y, String text, uint8_t width, uint8_t height,
        bool pressed);

    // SD Card
    bool SDInitialize();
    bool SDSetAddressPointer(uint32_t address);
    bool SDRead(uint8_t &data);
    bool SDReadShort(uint16_t &data);
    bool SDReadLong(uint32_t &data);
    bool SDReadString(String &data);

    bool SDWrite(uint8_t data);
    bool SDWrite(uint16_t numValues, uint8_t *values);
    bool SDWrite(uint16_t numValues, uint8_t value1, ...);
    bool SDWriteShort(uint16_t data);
    bool SDWriteShort(uint16_t numValues, uint16_t *values);
    bool SDWriteShort(uint16_t numValues, uint16_t value1, ...);
    bool SDWriteLong(uint32_t data);
    bool SDWriteLong(uint16_t numValues, uint32_t *values);
    bool SDWriteLong(uint16_t numValues, uint32_t value1, ...);
    bool SDWriteText(char* text);
    bool SDWriteString(String data);

    bool SDReadSector(uint32_t sectorAddress, uint8_t *data);
    bool SDReadSector(uint32_t sectorAddress, uint8_t *data, uint16_t &bytesRead);
    bool SDWriteSector(uint32_t sectorAddress, uint8_t *data);
    bool SDWipeSector(uint32_t sectorAddress, uint8_t wipeData = 0x00);
    bool SDWipeSectors(uint32_t sectorAddress, uint32_t numSectors,
        uint32_t &sectorsWiped, bool displayProgress = false, uint8_t wipeData = 0x00);
    uint32_t SDWipeCard(uint8_t wipeData);
    
    bool SDWriteScreen(uint32_t sectorAddress);
    bool SDWriteScreen(uint32_t sectorAddress,
        uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    bool SDDrawScreen(uint32_t sectorAddress);
    bool SDDrawImage(uint32_t sectorAddress,
        uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    bool SDRunCommand(uint32_t address);
    bool SDPlayVideo(uint8_t x, uint8_t y, uint8_t width, uint8_t height,
        uint8_t delayMs, uint16_t frameCount, uint32_t sectorAddress);
    bool SDRunScript(uint32_t address);

private:
    String ConvertDeviceType(uint8_t deviceTypeResponse);
    uint16_t ConvertResolution(uint8_t resolutionResponse);

    uint8_t *heapptr, *stackptr;
    uint16_t CheckMemory();

    uint8_t _pinReset;
    uint16_t _initDelay;
    uint32_t _baudRate;
    
    SerialContainer *_serial;

    String _deviceType;
    uint8_t _hardwareRevision;
    uint8_t _firmwareRevision;
    uint16_t _deviceWidth;
    uint16_t _deviceHeight;

    uint16_t _buttonColor;
    uint16_t _buttonFontColor;
    uint16_t _fontColor;
    uint8_t _fontSize;
    bool _fontOpacity;
    bool _buttonOpacity;
    bool _fontProportional;

    bool charIndexList[32];
};

#endif
