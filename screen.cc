#include <node.h>
#include <nan.h>
#include <v8.h>
#include <vector>
#include "libs/screen.h"
#include "libs/screengrab.h"
#include "libs/MMBitmap.h"

#if defined(USE_X11)
  #include "libs/xdisplay.h"
#endif

//https://stackoverflow.com/questions/10471459/is-it-possible-to-write-a-node-js-extension-in-c-not-c
//https://stackoverflow.com/questions/20728255/could-one-write-a-native-node-js-extension-in-go-as-opposed-to-c

using namespace v8;

NAN_METHOD(getSize)
{
  //Get display size.
  MMSize displaySize = getMainDisplaySize();

  //Create our return object.
  Local<Object> obj = Nan::New<Object>();
  Nan::Set(obj, Nan::New("width").ToLocalChecked(), Nan::New<Number>(displaySize.width));
  Nan::Set(obj, Nan::New("height").ToLocalChecked(), Nan::New<Number>(displaySize.height));

  //Return our object with .width and .height.
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(getXDisplayName)
{
  #if defined(USE_X11)
  const char* display = getXDisplay();
  info.GetReturnValue().Set(Nan::New<String>(display).ToLocalChecked());
  #else
  Nan::ThrowError("getXDisplayName is only supported on Linux");
  #endif
}

NAN_METHOD(setXDisplayName)
{
  #if defined(USE_X11)
  Nan::Utf8String string(info[0]);
  setXDisplay(*string);
  info.GetReturnValue().Set(Nan::New(1));
  #else
  Nan::ThrowError("setXDisplayName is only supported on Linux");
  #endif
}

NAN_METHOD(Capture)
{
  size_t x;
  size_t y;
  size_t w;
  size_t h;

  //If user has provided screen coords, use them!
  if (info.Length() == 4)
  {
    //TODO: Make sure requested coords are within the screen bounds, or we get a seg fault.
    //     An error message is much nicer!

    x = info[0]->Int32Value();
    y = info[1]->Int32Value();
    w = info[2]->Int32Value();
    h = info[3]->Int32Value();
  }
  else
  {
    //We're getting the full screen.
    x = 0;
    y = 0;

    //Get screen size.
    MMSize displaySize = getMainDisplaySize();
    w = displaySize.width;
    h = displaySize.height;
  }

  MMBitmapRef bitmap = copyMMBitmapFromDisplayInRect(MMRectMake(x, y, w, h));

  uint32_t bufferSize = bitmap->bytewidth * bitmap->height;
  Local<Object> buffer = Nan::NewBuffer((char*)bitmap->imageBuffer, bufferSize, destroyMMBitmapBuffer, NULL).ToLocalChecked();

  Local<Object> obj = Nan::New<Object>();
  Nan::Set(obj, Nan::New("width").ToLocalChecked(), Nan::New<Number>(bitmap->width));
  Nan::Set(obj, Nan::New("height").ToLocalChecked(), Nan::New<Number>(bitmap->height));
  Nan::Set(obj, Nan::New("byteWidth").ToLocalChecked(), Nan::New<Number>(bitmap->bytewidth));
  Nan::Set(obj, Nan::New("bitsPerPixel").ToLocalChecked(), Nan::New<Number>(bitmap->bitsPerPixel));
  Nan::Set(obj, Nan::New("bytesPerPixel").ToLocalChecked(), Nan::New<Number>(bitmap->bytesPerPixel));
  Nan::Set(obj, Nan::New("image").ToLocalChecked(), buffer);

  info.GetReturnValue().Set(obj);
}



NAN_MODULE_INIT(Init)
{

  Nan::Set(target, Nan::New("getSize").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(getSize)).ToLocalChecked());

  Nan::Set(target, Nan::New("Capture").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(Capture)).ToLocalChecked());

  Nan::Set(target, Nan::New("getXDisplayName").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(getXDisplayName)).ToLocalChecked());

  Nan::Set(target, Nan::New("setXDisplayName").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(setXDisplayName)).ToLocalChecked());
}


NODE_MODULE(screen, Init);
