import fs from 'fs';
import wav from 'wav';

class AudioLoader {
  static loadFile(path) {
    return new Promise((resolve, reject) => {
      const reader = new wav.Reader();
      const buffers = [];

      reader.on('data', buffer => buffers.push(buffer));
      reader.on('end', () => {
        const audioBuffer = Buffer.concat(buffers);
        const floatArray = new Float32Array(audioBuffer.length / 2);
        
        // Convert buffer to float32 array
        for (let i = 0; i < audioBuffer.length; i += 2) {
          const sample = audioBuffer.readInt16LE(i);
          floatArray[i / 2] = sample / 32768.0; // Normalize to [-1, 1]
        }
        
        resolve(floatArray);
      });
      reader.on('error', reject);

      fs.createReadStream(path).pipe(reader);
    });
  }
}

export default AudioLoader;