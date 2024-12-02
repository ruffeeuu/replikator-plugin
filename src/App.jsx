import React from 'react';
import AudioAnalyzer from './components/AudioAnalyzer';
import styled from 'styled-components';

const AppContainer = styled.div`
  display: flex;
  flex-direction: column;
  align-items: center;
  min-height: 100vh;
  padding: 40px 20px;
  background: #141520;
`;

function App() {
  return (
    <AppContainer>
      <AudioAnalyzer />
    </AppContainer>
  );
}

export default App;