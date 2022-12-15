#include <core.h>
#include <logger.h>
#include <filelogger.h>
#include <util/FileStream.h>
#include <util/memory.h>
#include <util/hotloader.h>
#include <window/window.h>
#include <window/input.h>

void runExamples();

int main() {
    CoreInit();
    runExamples();
    return 0;
}

void MemoryLeakTrackerExample();
void LoggerExample();
void FileLoggerExample();
void StringExample();
void FileExample();
void SerializerExample();
void HotLoaderExample();
void BinaryBufferExample();
void WindowAndInputExample();

void runExamples()
{
    MemoryLeakTrackerExample();
    LoggerExample();
    FileLoggerExample();
    StringExample();
    FileExample();
    SerializerExample();
    HotLoaderExample();
    BinaryBufferExample();
    WindowAndInputExample();
}

void MemoryLeakTrackerExample()
{
    MemoryEnableTracking(true);
    char* buffer = (char*)Malloc(8);
    MemZero(buffer, 8);
    Free(buffer);

    int* i = (int*)MemReg(new int[1]);
    MemoryPrintStack();
    delete (int*)MemDeReg(i);
}

void LoggerExample()
{
    LOG_INFO({C_HiLi("log", Gray, 0),
              C_HiLi("%i", Red, 0)},"This is a log %i", 0);
    LOG_WARNING({C_HiLi("log", Gray, 0),
                 C_HiLi("%i", Red, 0)},"This is a log %i", 1);
    LOG_ERROR({C_HiLi("log", Gray, 0),
               C_HiLi("%i", Red, 0)},"This is a log %i", 2);
    LOG_ASSERT(true, {C_HiLi("log", Gray,0),
                       C_HiLi("%i", Red, 0)}, "This is a log %i", 3);
}

void FileLoggerExample()
{
    LOG_INFO_FILE("../fileout/log.txt", "this is a file log %i", 0);
    LOG_WARNING_FILE("../fileout/log.txt", "this is a file log %i", 1)
    LOG_ERROR_FILE("../fileout/log.txt", "this is a file log %i", 2)
    LOG_ASSERT_FILE(true, "../fileout/log.txt", "this is a file log %i", 3)
}

void StringExample()
{
    String string("I am a string");
    string.add(". I was added later");

    string.replaceWith("added later", "replaced");

    auto tokens = string.tokenize(' ');
    for(const String& str : tokens)
    {
        printf("%s\n", str.c_str());
    }
}

void FileExample()
{
    FS::File write("../fileout/writeFile.txt", FILE_CRT);
    write.addString("string");
    write.addF32(4.2f);
    write.write();

    FS::File load("../fileout/writeFile.txt", FILE_READ);
    String string = load.getString();
    f32 f = load.getFloat();

    LOG_INFO({C_HiLi("%s", Blue, 0),
              C_HiLi("%f", Blue, 0)}, "String: '%s'\nF32: '%f'", string.c_str(), f);
}

void SerializerExample()
{
    FS::Serializer s("../fileout/serializer.txt");
    s.addNewNode("i/am/a/new/node");
    s.addDataToNode("i", "1");
    s.addDataToNode("i/am", "2");
    s.addDataToNode("i/am/a", "3");
    s.addDataToNode("i/am/a/new", "4");
    s.addDataToNode("i/am/a/new/node", "5");
    s.write();

    FS::Serializer s2("../fileout/serializer.txt");
    s2.load();
    int ir1 = s2.getI32FromNode("i");
    int ir2 = s2.getI32FromNode("i/am");
    int ir3 = s2.getI32FromNode("i/am/a");
    int ir4 = s2.getI32FromNode("i/am/a/new");
    int ir5 = s2.getI32FromNode("i/am/a/new/node");
}

void HotLoaderExample()
{
    HotLoader::AddFileToWatch("../fileout/log.txt");
    while(!HotLoader::IsModified("../fileout/log.txt"))
    {
        //depending on when the code is executed
        //9000 new lines can be written to the file because the HotLoader measures in seconds
        LOG_INFO_FILE("../fileout/log.txt", "I will trigger the HotLoader example");
        HotLoader::CheckFiles();
    }
    auto file = HotLoader::GetFile("../fileout/log.txt");
    HotLoader::RemoveFileToWatch("../fileout/log.txt");
}

void BinaryBufferExample()
{
    BinaryBuffer buffer(128);
    buffer.add("This is a String");
    buffer.add((i32)1234);
    buffer.add(4.2f);
    buffer.add(42.42);

    String str = buffer.getString();
    i32 i = buffer.getI32();
    f32 f = buffer.getF32();
    f64 d = buffer.getF64();

    LOG_INFO({C_HiLi("%s", Blue, 0),
              C_HiLi("%i", Blue, 0),
              C_HiLi("%f", Blue, 0),
              C_HiLi("%f", Blue, 1)}, "String: '%s'\nI32: '%i'\nF32: '%f'\nF64: '%f'", str.c_str(), i, f, d);
}

void WindowAndInputExampleSetSettings()
{
    Input::SetSetting(Input::CollectKeyCallback, true);
    Input::SetSetting(Input::CollectCharacterCallback, true);
    Input::SetSetting(Input::CollectCursorPositionCallback, true);
    Input::SetSetting(Input::CollectCursorEnterCallback, true);
    Input::SetSetting(Input::CollectMouseButtonCallback, true);
    Input::SetSetting(Input::CollectScrollCallback, true);
    Input::SetSetting(Input::CollectDropCallback, true);
    Input::SetSetting(Input::CollectCharModsCallback, true);
    Input::SetSetting(Input::CollectFramebufferSizeCallback, true);
    Input::SetSetting(Input::CollectJoystickCallback, true);
    Input::SetSetting(Input::CollectMonitorCallback, true);
    Input::SetSetting(Input::CollectWindowContentScaleCallback, true);
    Input::SetSetting(Input::CollectWindowCloseCallback, true);
    Input::SetSetting(Input::CollectWindowFocusCallback, true);
    Input::SetSetting(Input::CollectWindowMaximizeCallback, true);
    Input::SetSetting(Input::CollectWindowPosCallback, true);
    Input::SetSetting(Input::CollectWindowRefreshCallback, true);
    Input::SetSetting(Input::CollectWindowSizeCallback, true);
    Input::SetSetting(Input::CollectWindowIconifyCallback, true);
    Input::SetSetting(Input::LoadDropedFiles, true);
}

void WindowAndInputExample()
{
    Window::Init();
    Window::Window win = Window::WindowBuilder
            .setSize(400, 300)
            .setRGBBufferSize(8, 8, 8)
            .setOpacity(1.0f)
            .setRefreshRate(60)
            .centerWindowOnScreen()
            .setStandardCursor(Window::CrosshairCursor)
            .setSettingsFileName("window.node")
            .build("playground");
    win.init();

    WindowAndInputExampleSetSettings();

    while(win.isWindowValid())
    {
        if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            win.close();
        }
        if (Input::IsScrollUp())
        {
            LOG_INFO({}, "scroll up!");
        }
        if (Input::IsScrollDown())
        {
            LOG_INFO({}, "scroll down!");
        }
        if(Input::IsKeyPressed(GLFW_KEY_W))
        {
            LOG_INFO({}, "You pressed W!");
        }
        if(Input::IsKeyReleased(GLFW_KEY_W))
        {
            LOG_INFO({}, "You released W!");
        }
        if(Input::WasWindowMoved())
        {
            LOG_INFO({}, "Window was Moved!");
        }

        //do stuff

        win.swapBuffers();
        Input::Update();
        Window::pollEvents();
    }
    win.clear();
}