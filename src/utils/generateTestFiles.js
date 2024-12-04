import fs from 'fs';
import { Readable } from 'stream';
import wav from 'wav';
import { dirname, join } from 'path';
import { fileURLToPath } from 'url';

const __filename = fileURLToPath(import.meta.url);
const __dirname = dirname(__filename);

function generateSineWave(frequency, duration, sampleRate = 44100) {
  const samples = duration * sampleRate;
  const buffer = Buffer.alloc(samples * 2); // 16-bit samples
  
  for (let i = 0; i < samples; i++) {
    const value = Math.sin(2 * Math.PI * frequency * i / sampleRate);
    const sample = Math.floor(value * 32767); // Convert to 16-bit
    buffer.writeInt16LE(sample, i * 2);
  }
  
  return buffer;
}

function createWavFile(buffer, filePath) {
  const writer = new wav.FileWriter(filePath, {
    channels: 1,
    sampleRate: 44100,
    bitDepth: 16
  });

  const readable = new Readable();
  readable._read = () => {}; // Required implementation
  readable.push(buffer);
  readable.push(null);
  
  return new Promise((resolve, reject) => {
    readable.pipe(writer);
    writer.on('finish', resolve);
    writer.on('error', reject);
  });
}

async function generateTestFiles() {
  const testDir = join(__dirname, '../../test');
  
  // Create test directory if it doesn't exist
  if (!fs.existsSync(testDir)) {
    fs.mkdirSync(testDir, { recursive: true });
  }
  
  // Generate clean sine wave
  const cleanBuffer = generateSineWave(440, 2); // 440Hz, 2 seconds
  
  // Generate processed sine wave with some modifications
  const processedBuffer = generateSineWave(440, 2);
  for (let i = 0; i < processedBuffer.length; i += 2) {
    // Add some "processing" effects
    const sample = processedBuffer.readInt16LE(i);
    const processed = Math.floor(sample * 0.8); // Reduce amplitude
    processedBuffer.writeInt16LE(processed, i);
  }
  
  // Save the files
  await Promise.all([
    createWavFile(cleanBuffer, join(testDir, 'clean.wav')),
    createWavFile(processedBuffer, join(testDir, 'processed.wav'))
  ]);
  
  console.log('Test files generated successfully');
}

generateTestFiles();