class TransientsAnalyzer {
  static analyze(clean, processed) {
    return {
      attack: TransientsAnalyzer.analyzeTransientModification(clean, processed, 'attack'),
      sustain: TransientsAnalyzer.analyzeTransientModification(clean, processed, 'sustain')
    };
  }

  static analyzeTransientModification(clean, processed, phase) {
    const cleanEnvelope = TransientsAnalyzer.extractEnvelope(clean);
    const processedEnvelope = TransientsAnalyzer.extractEnvelope(processed);
    
    return phase === 'attack' 
      ? TransientsAnalyzer.compareAttacks(cleanEnvelope, processedEnvelope)
      : TransientsAnalyzer.compareSustains(cleanEnvelope, processedEnvelope);
  }

  static extractEnvelope(buffer) {
    const windowSize = 128;
    const envelope = new Float32Array(Math.ceil(buffer.length / windowSize));
    
    for (let i = 0; i < envelope.length; i++) {
      const start = i * windowSize;
      const end = Math.min(start + windowSize, buffer.length);
      envelope[i] = Math.max(...buffer.slice(start, end).map(Math.abs));
    }
    
    return envelope;
  }

  static compareAttacks(cleanEnv, processedEnv) {
    const attackTime = 50;
    const cleanAttack = cleanEnv.slice(0, attackTime);
    const processedAttack = processedEnv.slice(0, attackTime);
    
    return processedAttack.reduce((sum, val, i) => sum + val - cleanAttack[i], 0) / attackTime;
  }

  static compareSustains(cleanEnv, processedEnv) {
    const sustainStart = 50;
    const cleanSustain = cleanEnv.slice(sustainStart);
    const processedSustain = processedEnv.slice(sustainStart);
    
    return processedSustain.reduce((sum, val, i) => sum + val - cleanSustain[i], 0) / cleanSustain.length;
  }
}

export default TransientsAnalyzer;