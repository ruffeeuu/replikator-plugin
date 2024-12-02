class DynamicsAnalyzer {
  static analyze(clean, processed) {
    const cleanStats = this.calculateSignalStats(clean);
    const processedStats = this.calculateSignalStats(processed);

    return {
      compressionRatio: this.calculateCompressionRatio(cleanStats, processedStats),
      threshold: this.estimateThreshold(clean, processed),
      attack: this.calculateAttackTime(clean, processed),
      release: this.calculateReleaseTime(clean, processed)
    };
  }

  static calculateSignalStats(buffer, windowSize = 1024) {
    const stats = {
      rms: 0,
      peak: 0,
      crest: 0
    };

    for (let i = 0; i < buffer.length; i += windowSize) {
      const chunk = buffer.slice(i, Math.min(i + windowSize, buffer.length));
      const chunkStats = this.analyzeChunk(chunk);
      stats.rms += chunkStats.rms;
      stats.peak = Math.max(stats.peak, chunkStats.peak);
    }

    stats.rms = Math.sqrt(stats.rms / Math.ceil(buffer.length / windowSize));
    stats.crest = stats.peak / stats.rms;

    return stats;
  }

  static analyzeChunk(chunk) {
    let sumSquares = 0;
    let peak = 0;

    for (const sample of chunk) {
      const abs = Math.abs(sample);
      sumSquares += sample * sample;
      peak = Math.max(peak, abs);
    }

    return {
      rms: Math.sqrt(sumSquares / chunk.length),
      peak
    };
  }

  static estimateThreshold(clean, processed) {
    const windowSize = 1024;
    let maxRatio = 0;
    let threshold = -Infinity;

    for (let i = 0; i < clean.length; i += windowSize) {
      const cleanChunk = clean.slice(i, i + windowSize);
      const processedChunk = processed.slice(i, i + windowSize);
      
      const cleanPeak = Math.max(...cleanChunk.map(Math.abs));
      const processedPeak = Math.max(...processedChunk.map(Math.abs));
      
      const ratio = cleanPeak > 0 ? processedPeak / cleanPeak : 1;
      
      if (ratio < 1 && ratio > maxRatio) {
        maxRatio = ratio;
        threshold = cleanPeak;
      }
    }

    return threshold === -Infinity ? -60 : 20 * Math.log10(threshold);
  }

  static calculateAttackTime(clean, processed) {
    const sampleRate = 44100;
    const windowSize = 128;
    let maxAttackDiff = 0;

    for (let i = windowSize; i < clean.length - windowSize; i++) {
      const cleanDiff = Math.abs(clean[i]) - Math.abs(clean[i - 1]);
      const procDiff = Math.abs(processed[i]) - Math.abs(processed[i - 1]);
      
      if (cleanDiff > 0.1) { // Transient detection threshold
        const attackDiff = Math.abs(cleanDiff - procDiff);
        maxAttackDiff = Math.max(maxAttackDiff, attackDiff);
      }
    }

    return Math.min(100, Math.max(1, (maxAttackDiff * 1000) / sampleRate));
  }

  static calculateReleaseTime(clean, processed) {
    const sampleRate = 44100;
    const windowSize = 1024;
    let maxReleaseDiff = 0;

    for (let i = windowSize; i < clean.length - windowSize; i += windowSize) {
      const cleanEnv = this.calculateEnvelope(clean.slice(i - windowSize, i + windowSize));
      const procEnv = this.calculateEnvelope(processed.slice(i - windowSize, i + windowSize));
      
      const releaseDiff = Math.abs(cleanEnv.decay - procEnv.decay);
      maxReleaseDiff = Math.max(maxReleaseDiff, releaseDiff);
    }

    return Math.min(2000, Math.max(50, (maxReleaseDiff * 1000) / sampleRate));
  }

  static calculateEnvelope(buffer) {
    const attack = buffer.slice(0, buffer.length / 2);
    const release = buffer.slice(buffer.length / 2);
    
    return {
      attack: Math.max(...attack.map(Math.abs)),
      decay: Math.max(...release.map(Math.abs))
    };
  }
}

export default DynamicsAnalyzer;