import React, { useState, useRef } from 'react';
import styled from 'styled-components';
import { FiUpload, FiPlay, FiPause, FiActivity, FiSave, FiVolume2 } from 'react-icons/fi';
import WaveSurfer from 'wavesurfer.js';
import { VolumeControl } from './VolumeControl';
import { WaveformDisplay } from './WaveformDisplay';
import { AnalysisResults } from './AnalysisResults';
import { StyledButton, StyledContainer, StyledTitle, StyledControls, StyledControlGroup } from './styles';

const AudioAnalyzer = () => {
  const [cleanAudio, setCleanAudio] = useState(null);
  const [processedAudio, setProcessedAudio] = useState(null);
  const [analyzing, setAnalyzing] = useState(false);
  const [progress, setProgress] = useState(0);
  const [results, setResults] = useState(null);
  const [cleanVolume, setCleanVolume] = useState(0);
  const [processedVolume, setProcessedVolume] = useState(0);
  
  const cleanWaveformRef = useRef(null);
  const processedWaveformRef = useRef(null);
  const cleanInputRef = useRef(null);
  const processedInputRef = useRef(null);
  const cleanWavesurferRef = useRef(null);
  const processedWavesurferRef = useRef(null);

  const handleFileUpload = (event, type) => {
    const file = event.target.files[0];
    if (file) {
      const reader = new FileReader();
      reader.onload = (e) => {
        if (type === 'clean') {
          setCleanAudio(e.target.result);
          initWaveform(e.target.result, cleanWaveformRef.current, 'clean');
        } else {
          setProcessedAudio(e.target.result);
          initWaveform(e.target.result, processedWaveformRef.current, 'processed');
        }
      };
      reader.readAsArrayBuffer(file);
    }
  };

  const initWaveform = (audioData, container, type) => {
    const wavesurfer = WaveSurfer.create({
      container,
      waveColor: '#4CAF50',
      progressColor: '#1976D2',
      cursorColor: '#E6E8FF',
      height: 80,
      normalize: true,
      plugins: []
    });

    wavesurfer.loadBlob(new Blob([audioData]));

    if (type === 'clean') {
      if (cleanWavesurferRef.current) {
        cleanWavesurferRef.current.destroy();
      }
      cleanWavesurferRef.current = wavesurfer;
    } else {
      if (processedWavesurferRef.current) {
        processedWavesurferRef.current.destroy();
      }
      processedWavesurferRef.current = wavesurfer;
    }
  };

  const handleVolumeChange = (value, type) => {
    if (type === 'clean') {
      setCleanVolume(value[0]);
      if (cleanWavesurferRef.current) {
        cleanWavesurferRef.current.setVolume(value[0] / 100);
      }
    } else {
      setProcessedVolume(value[0]);
      if (processedWavesurferRef.current) {
        processedWavesurferRef.current.setVolume(value[0] / 100);
      }
    }
  };

  const startAnalysis = async () => {
    if (!cleanAudio || !processedAudio) return;

    setAnalyzing(true);
    setProgress(0);

    const interval = setInterval(() => {
      setProgress((prev) => {
        if (prev >= 100) {
          clearInterval(interval);
          return 100;
        }
        return prev + 1;
      });
    }, 50);

    try {
      setTimeout(() => {
        clearInterval(interval);
        setAnalyzing(false);
        setProgress(100);
        setResults({
          eq: [
            { freq: '100Hz', gain: '+2dB' },
            { freq: '1kHz', gain: '-3dB' },
            { freq: '10kHz', gain: '+1dB' },
          ],
          dynamics: {
            threshold: '-18dB',
            ratio: '2:1',
            attack: '10ms',
            release: '100ms',
          },
          transients: {
            attack: '+2dB',
            sustain: '-1dB',
          },
        });
      }, 5000);
    } catch (error) {
      console.error('Analysis failed:', error);
      clearInterval(interval);
      setAnalyzing(false);
      setProgress(0);
    }
  };

  return (
    <StyledContainer>
      <StyledTitle>Audio Analysis</StyledTitle>
      
      <StyledControls>
        <StyledControlGroup>
          <WaveformDisplay
            ref={cleanWaveformRef}
            label="Clean Audio"
            volume={cleanVolume}
            onVolumeChange={(value) => handleVolumeChange(value, 'clean')}
          />
          <input
            type="file"
            accept=".wav"
            onChange={(e) => handleFileUpload(e, 'clean')}
            ref={cleanInputRef}
            style={{ display: 'none' }}
          />
          <StyledButton onClick={() => cleanInputRef.current.click()}>
            <FiUpload />
            Load Clean Audio
          </StyledButton>
        </StyledControlGroup>

        <StyledControlGroup>
          <WaveformDisplay
            ref={processedWaveformRef}
            label="Processed Audio"
            volume={processedVolume}
            onVolumeChange={(value) => handleVolumeChange(value, 'processed')}
          />
          <input
            type="file"
            accept=".wav"
            onChange={(e) => handleFileUpload(e, 'processed')}
            ref={processedInputRef}
            style={{ display: 'none' }}
          />
          <StyledButton onClick={() => processedInputRef.current.click()}>
            <FiUpload />
            Load Processed Audio
          </StyledButton>
        </StyledControlGroup>
      </StyledControls>

      <StyledButton
        onClick={startAnalysis}
        disabled={!cleanAudio || !processedAudio || analyzing}
        style={{ width: '100%' }}
      >
        <FiActivity />
        {analyzing ? 'Analyzing...' : 'Start Analysis'}
      </StyledButton>

      <AnalysisResults
        analyzing={analyzing}
        progress={progress}
        results={results}
      />
    </StyledContainer>
  );
};

export default AudioAnalyzer;