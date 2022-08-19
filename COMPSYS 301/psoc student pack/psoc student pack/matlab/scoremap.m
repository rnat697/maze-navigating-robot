
%this function gives a value to each node a set distance away from the
%target loc regardless of wall size or not.



function [map] = scoremap(ogmap, target,start)
% Using Manhattan Distance because we are only allowed to move up,down,
% left, right. see: https://www.geeksforgeeks.org/a-search-algorithm/]

    mapsize = size(ogmap);
    Hmap = zeros(mapsize);
    %Gmap = zeros(mapsize);
    %Fmap = zeros(mapsize);

    for xloc = 1: mapsize(1)
        for yloc = 1:mapsize(2)
            %Gmap(xloc,yloc) = abs(xloc-start(1))+ abs(yloc-start(2));
            %if(ogmap(xloc,yloc) ~= 1)
                Hmap(xloc,yloc) = abs(xloc-target(1)) + abs(yloc-target(2));
                 %Fmap(xloc,yloc) = Gmap(xloc,yloc)+ Hmap(xloc,yloc);
            %end

            
            
            
        end
    end
    map = Hmap;

end


% function [map] = scoremap(mapScore,finishlocation)
% x=mapScore;
% mapsize = size(x);
% 
% 
% for xloc = 1: mapsize(1)
%     for yloc = 1:mapsize(2)
%         
%         x(xloc,yloc) = abs(xloc-finishlocation(1)) + abs(yloc-finishlocation(2));
%         
%         
%         
%     end
% end
% 
% map = x; %returns output
% end