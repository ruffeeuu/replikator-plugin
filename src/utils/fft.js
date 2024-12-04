import { FFT } from 'ml-fft';

class SpectralAnalyzer {
  constructor(fftSize = 2048) {
    this.fftSize = fftSize;
    this.fft = new FFT(fftSize);
  }

  getAverageSpectrum(buffer) {
    const numSegments = Math.floor(buffer.length / this.fftSize);
    const spectrum = new Float32Array(this.fftSize / 2);
    const window = this.getHannWindow();

    for (let i = 0; i < numSegments; i++) {
      const segment = new Float32Array(this.fftSize);
      const start = i * this.fftSize;
      
      // Apply Hann window and copy segment
      for (let j = 0; j < this.fftSize; j++) {
        if (start + j < buffer.length) {
          segment[j] = buffer[start + j] * window[j];
        }
      }
      
      const fftResult = this.fft.createComplexArray();
      this.fft.realTransform(fftResult, segment);
      
      // Calculate magnitude spectrum
      for (let j = 0; j < this.fftSize / 2; j++) {
        const real = fftResult[2 * j];
        const imag = fftResult[2 * j + 1];
        spectrum[j] += Math.sqrt(real * real + imag * imag);
      }
    }

    // Average and convert to dB
    return spectrum.map(val => {
      const averaged = val / numSegments;
      return 20 * Math.log10(averaged + 1e-6);
    });
  }

  getHannWindow() {
    const window = new Float32Array(this.fftSize);
    for (let i = 0; i < this.fftSize; i++) {
      window[i] = 0.5 * (1 - Math.cos((2 * Math.PI * i) / (this.fftSize - 1)));
    }
    return window;
  }

  binToFrequency(bin, sampleRate = 44100) {
    return (bin * sampleRate) / this.fftSize;
  }

  frequencyToBin(freq, sampleRate = 44100) {
    return Math.round((freq * this.fftSize) / sampleRate);
  }
}

export default SpectralAnalyzer;