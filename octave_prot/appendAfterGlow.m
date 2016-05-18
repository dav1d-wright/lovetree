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

function outArr = appendAfterGlow (inArr, stepIndex, afterGlowLen)
	if(afterGlowLen > 0)
		slope = 1/afterGlowLen;
		outArr = zeros(size(inArr));
		for index = 0 : afterGlowLen
			outArr(index + stepIndex - afterGlowLen) = slope * index * 0xFF;
		end
	else
		outArr = inArr;
	end
endfunction
