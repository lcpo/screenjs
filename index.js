const fs = require('fs');
const screenjs = require('./build/Release/screenjs');
const PNG = require('pngjs').PNG;

function Bitmap(img) {
  const image = {};
  image.width = img.width;
  image.height = img.height;
  if (img.image) { image.data = img.image; }
  if (img.intmap) { image.intmap = img.intmap; }
  return Object.assign({}, image, Bitmap.methods);
}
Bitmap.methods = {
  rgbaToInt(rx, gx, bx, ax) {
    const r = Math.round(rx);
    const b = Math.round(bx);
    const g = Math.round(gx);
    const a = Math.round(ax);
    const i = (r * (256 ** 3))
    + (g * (256 ** 2))
    + (b * (256 ** 1)) + (a * (256 ** 0));
    return i;
  },
  intToRGBA(i) {
    const rgba = {};
    rgba.r = Math.floor(i / (256 ** 3));
    const ra = (rgba.r * (256 ** 3));
    const rb = (rgba.g * (256 ** 2));
    rgba.g = Math.floor((i - ra) / (256 ** 2));
    rgba.b = Math.floor(((i - ra) - rb) / (256 ** 1));
    rgba.a = Math.floor(((i - ra) - rb - rb) / (256 ** 0));
    return rgba;
  },
  getBuffer() {
    const options = {
      width: this.width,
      height: this.height,
      bitDepth: 8,
      deflateLevel: 9,
      deflateStrategy: 3,
      filterType: -1,
      colorType: 6,
      inputHasAlpha: true,
    };
    const png = new PNG(options);
    png.data = new Buffer(this.data);
    return PNG.sync.write(png, options);
  },
  getBase64() {
    const data = this.getBuffer();
    const src = `data:image/png;base64,${data.toString('base64')}`;
    return src;
  },
  write(path, cb) {
    const self = this;
    const result = this.getBuffer();
    const stream = fs.createWriteStream(path);
    stream.on('open', () => {
      stream.write(result);
      stream.end();
    }).on('error', err => new Error(err));
    stream.on('finish', () => cb.call(self, null, self));
  },
  writeSync(path) {
    try {
      const result = this.getBuffer();
      fs.writeFileSync(path, result, {});
      return true;
    } catch (err) {
      throw new Error(err);
    }
  },
};
module.exports.Bitmap = Bitmap;
module.exports.Screen = screenjs;
