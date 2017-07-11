# screenjs
>Very small, Very fast, cross-platform library, to create a screenshot
screenjs supports Mac, Windows, and Linux(X11).

### What is created for?
For one project, I needed to make screenshots very quickly, and save them in an array of numbers (intmap), also it was necessary to sometimes save screenshots to the PNG file ...

## Contents
- [Installation](#installation)
- [API](#api)
- [Examples](#examples)
- [License](#license)

## Installation:

#### For Windows:
```
MinGW or other GCC
```

#### For Mac OS X:
    Xcode Command Line Tools

##### For Ubuntu:
```yml
sudo apt-get install gcc libc6-dev
sudo apt-get install libx11-dev
sudo apt-get install xorg-dev

```

### After all this:
`npm install screenjs --save` or  `npm install -g screenjs --save` (from global)

## API:

#### Import:

```js
const Screen = require('screenjs').Screen; // The object responsible for the screenshots
const Bitmap = require('screenjs').Bitmap; // Additional functionality, saving to file, or base64, etc.
```

### Methods:

```js
Screen.getSize();
// Will return { width: 1366, height: 768 };

```


```js
Screen.Capture();
/* Will return
{ width: 1366,
  height: 768,
  byteWidth: 5464,
  bitsPerPixel: 32,
  bytesPerPixel: 4,
  image: <Buffer ... >,
  intmap: Uint32Array [...] };
*/
```

```js
Screen.Capture(x, y, width, height);
// Screen.Capture(10, 15, 100, 100);
/* Will return
{ width: 100,
  height: 100,
  byteWidth: 400,
  bitsPerPixel: 32,
  bytesPerPixel: 4,
  image: <Buffer ... >,
  intmap: Uint32Array [...] };
*/
```

```js
Screen.CaptureGetIntMap();
/* Will return
{ width: 1366,
  height: 768,
  byteWidth: 5464,
  bitsPerPixel: 32,
  bytesPerPixel: 4,
  intmap: Uint32Array [...] };
*/
```

```js
Screen.CaptureGetIntMap(x, y, width, height);
// Screen.CaptureGetIntMap(10, 15, 100, 100);
/* Will return
{ width: 100,
  height: 100,
  byteWidth: 400,
  bitsPerPixel: 32,
  bytesPerPixel: 4,
  intmap: Uint32Array [...] };
*/
```


```js
Screen.CaptureGetImage();
/* Will return
{ width: 1366,
  height: 768,
  byteWidth: 5464,
  bitsPerPixel: 32,
  bytesPerPixel: 4,
  image: <Buffer ... > };
*/
```


```js
Screen.CaptureGetImage(x, y, width, height);
// Screen.CaptureGetImage(10, 15, 100, 100);
/* Will return
{ width: 100,
  height: 100,
  byteWidth: 400,
  bitsPerPixel: 32,
  bytesPerPixel: 4,
  image: <Buffer ... > };
*/
```


```js
Bitmap(img);
// return js bitmap object
```


```js
Bitmap.rgbaToInt(red, green, blue, alpha);
// return number
```


```js
Bitmap.intToRGBA(num);
// return rgba object
```

```js
Bitmap.getBuffer();
// return buffer PNG image
```

```js
Bitmap.getBase64();
// return base64 string (data:image/png;base64,...etc.)
```

```js
Bitmap.write(pathFile, callback);
// save from file Async
```


```js
Bitmap.writeSync(pathFile);
// save from file Sync
```


## Examples:

```js
const Screen = require('screenjs').Screen;
const Bitmap = require('screenjs').Bitmap;

const pic = Screen.Capture(); // It will work very quickly
console.log(pic); // And this will work slowly
const image = Bitmap(pic); // It will work very quickly
console.log(image); // And this will work slowly
```

```js
const Screen = require('screenjs').Screen;
const Bitmap = require('screenjs').Bitmap;

const pic = Screen.CaptureGetImage(); // It will work very quickly
const image = Bitmap(pic); // It will work very quickly
image.writeSync('test.png'); //And this will work very slowly
```

```js
const Screen = require('screenjs').Screen;

const pic = Screen.CaptureGetIntMap(); // It will work very quickly
console.log(image.intmap.length); //It will work very quickly
```

## License:
MIT
