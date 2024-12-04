import React from 'react';
import styled from 'styled-components';
import { FiSave } from 'react-icons/fi';
import * as Progress from '@radix-ui/react-progress';
import { StyledButton } from './styles';

const ProgressBar = styled(Progress.Root)`
  position: relative;
  overflow: hidden;
  background: #1A1C2A;
  border-radius: 99999px;
  width: 100%;
  height: 12px;
  margin: 10px 0;
`;

const ProgressIndicator = styled(Progress.Indicator)`
  background-color: #4CAF50;
  width: 100%;
  height: 100%;
  transition: transform 660ms cubic-bezier(0.65, 0, 0.35, 1);
`;

const ResultsContainer = styled.div`
  background: #1A1C2A;
  border-radius: 8px;
  padding: 20px;
  color: #E6E8FF;
  font-family: 'Monaco', monospace;
  white-space: pre-wrap;
  max-height: 300px;
  overflow-y: auto;
`;

export const AnalysisResults = ({ analyzing, progress, results }) => {
  const handleSave = () => {
    const dataStr = JSON.stringify(results, null, 2);
    const blob = new Blob([dataStr], { type: 'application/json' });
    const url = URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'processing-profile.json';
    a.click();
    URL.revokeObjectURL(url);
  };

  return (
    <>
      {analyzing && (
        <ProgressBar value={progress}>
          <ProgressIndicator
            style={{ transform: `translateX(-${100 - progress}%)` }}
          />
        </ProgressBar>
      )}

      {results && (
        <>
          <ResultsContainer>
            {JSON.stringify(results, null, 2)}
          </ResultsContainer>
          <StyledButton onClick={handleSave} style={{ marginTop: '20px' }}>
            <FiSave />
            Save Processing Profile
          </StyledButton>
        </>
      )}
    </>
  );
};