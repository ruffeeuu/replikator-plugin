import React from 'react';
import styled from 'styled-components';
import { VolumeControl } from './VolumeControl';

const WaveformContainer = styled.div`
  background: #1A1C2A;
  border-radius: 8px;
  padding: 20px;
  margin-bottom: 20px;
`;

const WaveformLabel = styled.div`
  color: #E6E8FF;
  margin-bottom: 10px;
  font-size: 0.9rem;
  opacity: 0.8;
`;

export const WaveformDisplay = React.forwardRef(({ label, volume, onVolumeChange }, ref) => {
  return (
    <WaveformContainer>
      <WaveformLabel>{label}</WaveformLabel>
      <div ref={ref} />
      <VolumeControl
        value={volume}
        onChange={onVolumeChange}
      />
    </WaveformContainer>
  );
});