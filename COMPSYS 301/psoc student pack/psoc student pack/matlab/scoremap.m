
%this function gives a value to each node a set distance away from the
%target loc regardless of wall size or not.

function [map] = scoremap(mapScore,finishlocation)
x=mapScore;
mapsize = size(x);


for xloc = 1: mapsize(1)
    for yloc = 1:mapsize(2)
        
        x(xloc,yloc) = abs(xloc-finishlocation(1)) + abs(yloc-finishlocation(2));
        
        
        
    end
end

map = x; %returns output
end