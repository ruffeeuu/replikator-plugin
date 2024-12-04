import styled from 'styled-components';

export const StyledContainer = styled.div`
  background: linear-gradient(180deg, #2A2D3E 0%, #1F2232 100%);
  border-radius: 12px;
  padding: 20px;
  width: 900px;
  box-shadow: 0 10px 20px rgba(0, 0, 0, 0.3);
`;

export const StyledTitle = styled.h2`
  color: #E6E8FF;
  margin: 0 0 20px 0;
  font-size: 1.5rem;
`;

export const StyledControls = styled.div`
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 20px;
  margin-bottom: 20px;
`;

export const StyledControlGroup = styled.div`
  display: flex;
  flex-direction: column;
  gap: 10px;
`;

export const StyledButton = styled.button`
  background: #3B4058;
  border: none;
  border-radius: 6px;
  padding: 12px 20px;
  color: #E6E8FF;
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 8px;
  cursor: pointer;
  transition: all 0.2s;
  font-size: 0.9rem;

  &:hover {
    background: #4B5068;
  }

  &:disabled {
    opacity: 0.5;
    cursor: not-allowed;
  }
`;