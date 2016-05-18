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

## Author: wright <wright@indel.ch>
## Created: 2016-05-18

function printCStyle (matrix, maxAfterGlow, numLeds, stepDelay)
	fIdCpp = fopen("../src/moveData.cpp", "w");
	
	fwrite(fIdCpp, "#include \"stdint.h\"\n");
	fwrite(fIdCpp, "#include <avr/pgmspace.h>\n");
	fwrite(fIdCpp, "#include \"moveData.h\"\n\n");

	matString = "const uint8_t g_uLightIntensityMat\n[DF_MVDATA_NUM_LEDS_PER_STRIP + DF_MVDATA_MAX_AFTERGLOW][DF_MVDATA_NUM_LEDS_PER_STRIP + DF_MVDATA_MAX_AFTERGLOW] PROGMEM = {\n";
	
	fwrite(fIdCpp, matString);

	for indexX = 1 : numLeds + maxAfterGlow
		fwrite(fIdCpp, "{");
		for indexY = 1 : numLeds + maxAfterGlow
			element = matrix(indexX, indexY);
			fwrite(fIdCpp, num2str(element));
			if(indexY ~= numLeds + maxAfterGlow)
				fwrite(fIdCpp, ", ");
			end
		end
		fwrite(fIdCpp, "},\n");
	end
	fwrite(fIdCpp, "};\n\n");
	
	arrString = "const uint8_t g_uStepDelays[DF_MVDATA_NUM_LEDS_PER_STRIP + DF_MVDATA_MAX_AFTERGLOW] PROGMEM = {";
	
	fwrite(fIdCpp, arrString);
	
	for index = 1 : numLeds + maxAfterGlow
		element = stepDelay(index);
		fwrite(fIdCpp, num2str(element));
		if(index ~= numLeds + maxAfterGlow)
			fwrite(fIdCpp, ", ");
		end
	end
	fwrite(fIdCpp, "};");
		
	fclose(fIdCpp);

end
