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

using namespace v8;

NAN_METHOD(getSize) {
  MMSize displaySize = getMainDisplaySize();
  Local<Object> obj = Nan::New<Object>();
  Nan::Set(obj, Nan::New("width").ToLocalChecked(), Nan::New<Number>(displaySize.width));
  Nan::Set(obj, Nan::New("height").ToLocalChecked(), Nan::New<Number>(displaySize.height));
  info.GetReturnValue().Set(obj);
}

NAN_METHOD(Capture) {
  size_t x;
  size_t y;
  size_t w;
  size_t h;

  if (info.Length() == 4) {
    x = info[0]->Int32Value();
    y = info[1]->Int32Value();
    w = info[2]->Int32Value();
    h = info[3]->Int32Value();
  } else {
    x = 0;
    y = 0;
    MMSize displaySize = getMainDisplaySize();
    w = displaySize.width;
    h = displaySize.height;
  }
  MMBitmapRef bitmap = copyMMBitmapFromDisplayInRect(MMRectMake(x, y, w, h));
  unsigned int red = 0;
  unsigned int blue = 0;
    unsigned int green = 0;
  unsigned int alpha = 0;
  unsigned int rgbaint = 0;
  size_t n = 0;

//  int32_t rx = 0;
//  int32_t ry = 0;
//  int32_t idx = 0;


unsigned int* intmapc = (unsigned int*)malloc((bitmap->height * bitmap->width ) * sizeof(unsigned int) );
uint32_t size = bitmap->width * bitmap->height;
v8::Isolate* isolate = v8::Isolate::GetCurrent();
Local<Uint32Array> intmap = Uint32Array::New(ArrayBuffer::New(isolate,intmapc, size),0,size);


 for (unsigned int i = 0; i < (size * 4); i += 4) { // BGR to RGB
     bitmap->imageBuffer[i + 3] = 255; //no alpha
     red = bitmap->imageBuffer[i];
     blue = bitmap->imageBuffer[i + 2];
     bitmap->imageBuffer[i] = blue;
     bitmap->imageBuffer[i + 2] = red;
     
      red =   bitmap->imageBuffer[i];
      green = bitmap->imageBuffer[i + 1];
      blue =  bitmap->imageBuffer[i + 2];
      alpha = bitmap->imageBuffer[i + 3];
      rgbaint = 0;
      rgbaint = (red * std::pow(256, 3)) + (green * std::pow(256, 2)) + (blue * std::pow(256, 1)) + (alpha * std::pow(256, 0));
      intmapc[n] = rgbaint; 
	  n += 1;

    
/*   
    idx = ((bitmap->width * ry) + rx) << 2;
    if (rx <= bitmap->width) { rx += 1; }
    if ((rx >= bitmap->width) && (ry <= bitmap->height)) { ry += 1; }
    if (ry >= bitmap->height) {break;}
	if (rx >= bitmap->width) {rx = 0;}
*/ 
  }

  uint32_t bufferSize = bitmap->bytewidth * bitmap->height;
  Local<Object> buffer = Nan::NewBuffer((char*)bitmap->imageBuffer, bufferSize, destroyMMBitmapBuffer, NULL).ToLocalChecked();

  Local<Object> obj = Nan::New<Object>();
  Nan::Set(obj, Nan::New("width").ToLocalChecked(), Nan::New<Number>(bitmap->width));
  Nan::Set(obj, Nan::New("height").ToLocalChecked(), Nan::New<Number>(bitmap->height));
  Nan::Set(obj, Nan::New("byteWidth").ToLocalChecked(), Nan::New<Number>(bitmap->bytewidth));
  Nan::Set(obj, Nan::New("bitsPerPixel").ToLocalChecked(), Nan::New<Number>(bitmap->bitsPerPixel));
  Nan::Set(obj, Nan::New("bytesPerPixel").ToLocalChecked(), Nan::New<Number>(bitmap->bytesPerPixel));
  Nan::Set(obj, Nan::New("image").ToLocalChecked(), buffer);
  Nan::Set(obj, Nan::New("intmap").ToLocalChecked(), intmap);

  info.GetReturnValue().Set(obj);
}


NAN_METHOD(CaptureGetIntMap){
  size_t x;
  size_t y;
  size_t w;
  size_t h;

  if (info.Length() == 4) {
    x = info[0]->Int32Value();
    y = info[1]->Int32Value();
    w = info[2]->Int32Value();
    h = info[3]->Int32Value();
  } else {
    x = 0;
    y = 0;
    MMSize displaySize = getMainDisplaySize();
    w = displaySize.width;
    h = displaySize.height;
  }
  MMBitmapRef bitmap = copyMMBitmapFromDisplayInRect(MMRectMake(x, y, w, h));
  unsigned int red = 0;
  unsigned int blue = 0;
  unsigned int green = 0;
  unsigned int alpha = 0;
  unsigned int rgbaint = 0;
  size_t n = 0;

unsigned int* intmap = (unsigned int*)malloc((bitmap->height * bitmap->width ) * sizeof(unsigned int) );
uint32_t bufferSize = bitmap->width * bitmap->height;
v8::Isolate* isolate = v8::Isolate::GetCurrent();
Local<Uint32Array> buffer = Uint32Array::New(ArrayBuffer::New(isolate,intmap, bufferSize),0,bufferSize);

 for (unsigned int i = 0; i < (bufferSize * 4); i += 4) { // BGR to RGB
     bitmap->imageBuffer[i + 3] = 255; //no alpha
     red = bitmap->imageBuffer[i];
     blue = bitmap->imageBuffer[i + 2];
     bitmap->imageBuffer[i] = blue;
     bitmap->imageBuffer[i + 2] = red;
      red =   bitmap->imageBuffer[i];
      green = bitmap->imageBuffer[i + 1];
      blue =  bitmap->imageBuffer[i + 2];
      alpha = bitmap->imageBuffer[i + 3];
      rgbaint = 0;
      rgbaint = (red * std::pow(256, 3)) + (green * std::pow(256, 2)) + (blue * std::pow(256, 1)) + (alpha * std::pow(256, 0));
      intmap[n] = rgbaint; 
	  n += 1;
   
  }
  Local<Object> obj = Nan::New<Object>();
  Nan::Set(obj, Nan::New("width").ToLocalChecked(), Nan::New<Number>(bitmap->width));
  Nan::Set(obj, Nan::New("height").ToLocalChecked(), Nan::New<Number>(bitmap->height));
  Nan::Set(obj, Nan::New("byteWidth").ToLocalChecked(), Nan::New<Number>(bitmap->bytewidth));
  Nan::Set(obj, Nan::New("bitsPerPixel").ToLocalChecked(), Nan::New<Number>(bitmap->bitsPerPixel));
  Nan::Set(obj, Nan::New("bytesPerPixel").ToLocalChecked(), Nan::New<Number>(bitmap->bytesPerPixel));
  Nan::Set(obj, Nan::New("intmap").ToLocalChecked(), buffer);
  info.GetReturnValue().Set(obj);
}


NAN_METHOD(CaptureGetImage) {
  size_t x;
  size_t y;
  size_t w;
  size_t h;

  if (info.Length() == 4) {
    x = info[0]->Int32Value();
    y = info[1]->Int32Value();
    w = info[2]->Int32Value();
    h = info[3]->Int32Value();
  } else {
    x = 0;
    y = 0;
    MMSize displaySize = getMainDisplaySize();
    w = displaySize.width;
    h = displaySize.height;
  }
  MMBitmapRef bitmap = copyMMBitmapFromDisplayInRect(MMRectMake(x, y, w, h));
  unsigned int red = 0;
  unsigned int blue = 0;
 for (unsigned int i = 0; i < (bitmap->width * bitmap->height * 4); i += 4) { // BGR to RGB
     bitmap->imageBuffer[i + 3] = 255; //no alpha
     red = bitmap->imageBuffer[i];
     blue = bitmap->imageBuffer[i + 2];
     bitmap->imageBuffer[i] = blue;
     bitmap->imageBuffer[i + 2] = red;
  
  }
  size_t bufferSize = bitmap->bytewidth * bitmap->height;
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

  Nan::Set(target, Nan::New("CaptureGetIntMap").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(CaptureGetIntMap)).ToLocalChecked());
    
      Nan::Set(target, Nan::New("CaptureGetImage").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(CaptureGetImage)).ToLocalChecked());
}

NODE_MODULE(screen, Init);
