%% A*'s Algorithm

function [retmap,retvisited,retsteps] = astar(mapfile,startlocation,targetlocation)

%list of squares we checked to find the nearest path        open list
%list that we have decided and will not change again        close list

%add startloaction to closed list.
%current location = startlocation
%add all open location next to current location to open list

%path Score
%G is the estimated cost from path a to the square, (increases as u move
%add 1 for each frame travelled.
%away)
%h is a heuristic movement cost as we travel awayu from the square
%F = G+h checked when travelling


%determine neighbours and add all to open list after calculating its score
%visit lowest score F and call it W
% remove W from open and add to closed list.
% for each square T in w's walkable neighbor path
%if T is in closed list.ignore
% if t is in open list add and compute score






end

%% Placing steps on map
function placestep(position,i)
    % This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
    position = [16-position(1) position(2)];
    position=[position(2)+0.1 position(1)+0.1];
    rectangle('Position',[position,0.8,0.8],'FaceColor','y');
    c=sprintf('%d',i);
    text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end
