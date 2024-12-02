import SpectralAnalyzer from './utils/fft.js';
import AudioLoader from './utils/audioLoader.js';
import DynamicsAnalyzer from './analyzers/dynamicsAnalyzer.js';
import TransientsAnalyzer from './analyzers/transientsAnalyzer.js';

class AudioAnalyzer {
  constructor() {
    this.spectralAnalyzer = new SpectralAnalyzer(2048);
  }

  async analyzeSpectralDifferences(cleanPath, processedPath) {
    const [cleanBuffer, processedBuffer] = await Promise.all([
      AudioLoader.loadFile(cleanPath),
      AudioLoader.loadFile(processedPath)
    ]);

    const differences = {
      spectral: this.calculateSpectralDifferences(cleanBuffer, processedBuffer),
      dynamics: DynamicsAnalyzer.analyze(cleanBuffer, processedBuffer),
      transients: TransientsAnalyzer.analyze(cleanBuffer, processedBuffer)
    };

    return this.generateProcessingProfile(differences);
  }

  calculateSpectralDifferences(clean, processed) {
    const cleanSpectrum = this.spectralAnalyzer.getAverageSpectrum(clean);
    const processedSpectrum = this.spectralAnalyzer.getAverageSpectrum(processed);
    
    return {
      eqCurve: this.calculateEQCurve(cleanSpectrum, processedSpectrum),
      harmonicContent: this.analyzeHarmonics(cleanSpectrum, processedSpectrum)
    };
  }

  calculateEQCurve(cleanSpectrum, processedSpectrum) {
    return processedSpectrum.map((val, i) => ({
      frequency: this.binToFrequency(i),
      gain: val / (cleanSpectrum[i] || 1e-6)
    }));
  }

  binToFrequency(bin) {
    const sampleRate = 44100;
    return (bin * sampleRate) / (this.spectralAnalyzer.fftSize * 2);
  }

  analyzeHarmonics(cleanSpectrum, processedSpectrum) {
    return processedSpectrum.map((val, i) => ({
      harmonic: i + 1,
      amplitude: val / (cleanSpectrum[i] || 1e-6)
    }));
  }

  generateProcessingProfile(differences) {
    const profile = {
      version: '1.0',
      eq: this.convertToEQBands(differences.spectral.eqCurve),
      dynamics: differences.dynamics,
      transients: differences.transients,
      harmonics: differences.spectral.harmonicContent
    };

    return JSON.stringify(profile, null, 2);
  }

  convertToEQBands(eqCurve) {
    const bands = [20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000];
    return bands.map(freq => ({
      frequency: freq,
      gain: this.interpolateEQGain(freq, eqCurve)
    }));
  }

  interpolateEQGain(freq, eqCurve) {
    const nearest = eqCurve.reduce((prev, curr) => 
      Math.abs(curr.frequency - freq) < Math.abs(prev.frequency - freq) ? curr : prev
    );
    return nearest.gain;
  }
}

export default AudioAnalyzer;