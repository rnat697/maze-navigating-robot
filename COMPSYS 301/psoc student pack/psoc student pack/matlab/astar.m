%% A*'s Algorithm
% https://www.geeksforgeeks.org/a-search-algorithm/
% https://medium.com/analytics-vidhya/a-algorithm-how-to-find-the-shortest-path-between-two-points-767c8a76376
% https://brilliant.org/wiki/a-star-search/

function [retmap,retvisited,retsteps] = astar(mapfile,startlocation,targetlocation)

    %list of squares we checked to find the nearest path    open list (queue)
    %list that we have decided and will not change again close list(retsteps) &
    %retvisted
    queue  = {startlocation};
    mapSize = size(mapfile);
    retvisited = ones(mapeSize);
    Hscoremap = calculateFscore(mapfile,targetlocation);
    Fscore = zeros(mapSize);
    Gscore = zeros(mapSize);
    prevFscore = 2000;
    %add startloaction to closed list.
    %current location = startlocation
    %add all open location next to current location to open list
    visiting = [-1,-1]; % just for initalisation purposes
    while (visiting ~= targetlocation)
        
        % Find node with lowest Fscore to visit
        for i = 1:length(queue)
            location = queue(1,i)
            nodeFscore = Fscore(location);
            if nodeFscore < prevFscore
                smallestFNode = location;
                index = [i];
                prevFscore = nodeFscore;
            end
        end
    
        % visit smallest Fscore node and remove from queue
        visiting = smallestFNode;
        retsteps = append(retsteps,visiting); %add to closed list
        retvisited(visiting) = 0; % place step on visited map
        queue = removeElement(queue,index);

        % determine neighbours of visiting node and caluclate Fscore
        
    
    end
        
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


%% calculating H score
function [Hmaps] = calculateHScore(Hmap,current, target)
% Using Manhattan Distance because we are only allowed to move up,down,
% left, right. see: https://www.geeksforgeeks.org/a-search-algorithm/]
    xloc = current(1);
    yloc = current(2);
    Hmap(xloc,yloc) = abs(xloc-target(1)) + abs(yloc-target(2));
end

%% calculating G score
function [Gmaps] = calculateGScore(Gmap,current,source)
    
end


%% removes an element in the array
function[array]= removeElement(poparray,index)
% Input index has to be a integer
    array = poparray;
    array(index)= [];

end
%% Appends to end of stack
function [updatedStack] = append(stack,node)
    updatedStack = stack;
    updatedStack{length(stack)+1} = node;

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
