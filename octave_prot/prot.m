## Copyright (C) 2016 wright
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## Author: wright <david.wright@bluewin.ch>
## Created: 2016-05-18

# 4 LED strips with 30 LEDs/m are divided by 3 --> 12 LED strips of 5/3m length each
virtStripsPerRealStrip = 2;
numLeds = 30 * 5/virtStripsPerRealStrip;
maxAfterGlow = 55;
afterGlow = floor(linspace(2, maxAfterGlow, numLeds + maxAfterGlow));
afterGlow(1) = 0;
afterGlow(2) = 1;
stepDelay = floor(linspace(100, 20, numLeds + maxAfterGlow));

stepMatrix = zeros(numLeds + maxAfterGlow, numLeds + maxAfterGlow);
stepMatrix(1,1) = 0xFF;
#filterSize = 3;
#filterMatrix = ones(filterSize)./(filterSize^2);


# First only shift the leading pixel. This should result in a diagonal matrix.
for stepIndex = 1 : numLeds + maxAfterGlow
	stepMatrix(stepIndex + 1, :) = arrshift(stepMatrix(stepIndex, :) , 1);
end

# then append the afterglow
for stepIndex = 1 : numLeds + maxAfterGlow
	stepMatrix(stepIndex, :) = appendAfterGlow(stepMatrix(stepIndex, :), stepIndex, afterGlow(stepIndex));
end

# filter the matrix
#stepMatrix = convn(stepMatrix, filterMatrix, "same");
#maxStepMatrix = max(max(stepMatrix));
#stepMatrix = stepMatrix ./ maxStepMatrix * 255;

weightMatrix = stepMatrix > 0;
stepMatrix = stepMatrix - (10 .* (rand(size(stepMatrix)) - 0.5) .* (weightMatrix));
stepMatrix(stepMatrix < 0) = 0;
stepMatrix(stepMatrix > 255) = 255;
stepMatrix = round(stepMatrix);
printCStyle(stepMatrix, maxAfterGlow, numLeds, stepDelay);



