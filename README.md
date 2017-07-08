# screenjs
>Very small, Very fast, cross-platform library, to create a screenshot
screenjs supports Mac, Windows, and Linux(X11).

### What is created for?
For one project, I needed to make screenshots very quickly, and save them in an array of numbers (intmap), also it was necessary to sometimes save screenshots to the PNG file ...

## Contents
- [Installation](#installation)
- [API](#API)
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
Screen.getSize()
```
return CPP bitmap object


```js
Screen.Capture()
```
return CPP bitmap object


```js
Screen.Capture(x, y, width, height)
```
return CPP bitmap object


```js
Screen.CaptureGetIntMap()
```
return CPP bitmap object


```js
Screen.CaptureGetIntMap(x, y, width, height)
```
return CPP bitmap object


```js
Screen.CaptureGetImage()
```
return CPP bitmap object


```js
Screen.CaptureGetImage(x, y, width, height)
```
return CPP bitmap object


```js
Bitmap(img)
```
return js bitmap object


```js
Bitmap.rgbaToInt(red, green, blue, alpha)
```
return number


```js
Bitmap.intToRGBA(num)
```
return rgba object

```js
Bitmap.[prototype].getBuffer()
```
return buffer PNG image

```js
Bitmap.[prototype].getBase64()
```
return base64 string (data:image/png;base64,...etc.)

```js
Bitmap.[prototype].write(pathFile, callback)
```
save from file Async


```js
Bitmap.[prototype].writeSync(pathFile)
```
save from file Sync

## Examples:

```js
const Screen = require('screenjs').Screen;
const Bitmap = require('screenjs').Bitmap;

const pic = Screen.Capture(); // It will work very quickly
console.log(pic); // And this will work slowly
const image = new Bitmap(pic); // It will work very quickly
console.log(image); // And this will work slowly
```

```js
const Screen = require('screenjs').Screen;
const Bitmap = require('screenjs').Bitmap;

const pic = Screen.CaptureGetImage(); // It will work very quickly
const image = new Bitmap(pic); // It will work very quickly
image.writeSync('test.png'); //And this will work very slowly
```

```js
const Screen = require('screenjs').Screen;

const pic = Screen.CaptureGetIntMap(); // It will work very quickly
console.log(image.intmap.length); //It will work very quickly
```

## License:
MIT
