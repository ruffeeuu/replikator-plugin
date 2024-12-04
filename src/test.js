import AudioAnalyzer from './analyzer.js';
import { writeFileSync } from 'fs';
import { fileURLToPath } from 'url';
import { dirname, join } from 'path';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

async function runTest() {
  const analyzer = new AudioAnalyzer();
  
  try {
    const profile = await analyzer.analyzeSpectralDifferences(
      join(__dirname, '../test/clean.wav'),
      join(__dirname, '../test/processed.wav')
    );
    
    console.log('Processing profile generated:');
    console.log(profile);
    
    writeFileSync(
      join(__dirname, '../processing-profile.json'),
      profile,
      'utf8'
    );
    
  } catch (error) {
    console.error('Error during analysis:', error);
    process.exit(1);
  }
}

runTest();