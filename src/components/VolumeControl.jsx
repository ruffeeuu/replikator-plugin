import React from 'react';
import styled from 'styled-components';
import { FiVolume2 } from 'react-icons/fi';
import * as Slider from '@radix-ui/react-slider';

const VolumeWrapper = styled.div`
  display: flex;
  align-items: center;
  gap: 10px;
  color: #E6E8FF;
  margin-top: 10px;
`;

const SliderRoot = styled(Slider.Root)`
  position: relative;
  display: flex;
  align-items: center;
  width: 200px;
  height: 20px;
`;

const SliderTrack = styled(Slider.Track)`
  background-color: #1A1C2A;
  position: relative;
  flex-grow: 1;
  height: 3px;
  border-radius: 9999px;
`;

const SliderRange = styled(Slider.Range)`
  position: absolute;
  background-color: #4CAF50;
  height: 100%;
  border-radius: 9999px;
`;

const SliderThumb = styled(Slider.Thumb)`
  display: block;
  width: 16px;
  height: 16px;
  background-color: #E6E8FF;
  border-radius: 50%;
  cursor: pointer;
  
  &:hover {
    background-color: #4CAF50;
  }
`;

export const VolumeControl = ({ value, onChange }) => {
  return (
    <VolumeWrapper>
      <FiVolume2 />
      <SliderRoot
        value={[value]}
        max={100}
        step={1}
        onValueChange={onChange}
      >
        <SliderTrack>
          <SliderRange />
        </SliderTrack>
        <SliderThumb />
      </SliderRoot>
      <span>{value}%</span>
    </VolumeWrapper>
  );
};