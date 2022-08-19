%% A*'s Algorithm
% https://www.geeksforgeeks.org/a-search-algorithm/
% https://medium.com/analytics-vidhya/a-algorithm-how-to-find-the-shortest-path-between-two-points-767c8a76376
% https://brilliant.org/wiki/a-star-search/
% https://www.redblobgames.com/pathfinding/a-star/introduction.html

function [retmap,retvisited,retsteps] = astar(mapfile,startlocation,targetlocation)

    %list of squares we checked to find the nearest path    open list (queue)
    %list that we have decided and will not change again close list(retsteps) &
    %retvisted
    queue  = {startlocation};
    mapSize = size(mapfile);
    retmap = mapfile;
    retsteps = {};
    retvisited = ones(mapSize);
    Hscore = zeros(mapSize);
    Fscore = zeros(mapSize);
    Gscore = zeros(mapSize);
    prevFscore = 2000;
    currentGcost = 0;
    stepNum = 0;

    %add startloaction to closed list.
    %current location = startlocation
    %add all open location next to current location to open list
    visiting = [-1,-1]; % just for initalisation purposes
    checkifAtEnd = 0;
    while (checkifAtEnd ~= 1)
        
        % Find node with lowest Fscore to visit
        for i = 1:length(queue)
            location = queue{1,i};
            Frow = location(1);
            Fcols = location(2);
            nodeFscore = Fscore(Frow,Fcols);

            % check if node has the lowest Fscore
            if nodeFscore < prevFscore
                smallestFNode = location;
                index = i;
                prevFscore = nodeFscore;
            end
        end
            
        % visit smallest Fscore node and remove from queue
        visiting = smallestFNode;
        stepNum = stepNum + 1;
        prevFscore = 5000; % reset checking previous F node value
        retsteps = append(retsteps,visiting); %add to closed list
        retvisited(visiting) = 0; % place step on visited map
        placestep(visiting,stepNum);
        queue = removeElement(queue,index);
        
         %checks if location of node is at end
        checkifAtEnd =(targetlocation(1) == visiting(1)) && (targetlocation(2) == visiting(2));

        % determine neighbours of visiting node and caluclate Fscore
         ycurrent = visiting(1);
         xcurrent = visiting(2);    
         % Neighbours are S, N, E, W from current location
         neighbours = {[ycurrent+1,xcurrent ],[ycurrent-1,xcurrent ],[ycurrent,xcurrent+1],[ycurrent,xcurrent-1]};
         
         % check if neighbour is not in closed list (retsteps --> ie visted array)
         % and not in open list (queue) and is not a wall
        for j = 1: length(neighbours)
            adjacentpos = neighbours{1,j};
            rows = adjacentpos(1);
            cols = adjacentpos(2);
            newFscore = 0;
            if (rows > 0 && cols >0 && retmap(rows,cols) ~= 1 && retvisited(rows,cols) ~= 0) % not a wall and has not been visited
                % check if open list (queue) does not contain current
                % adjacent position
                if(contains(queue,adjacentpos) == false)
                    queue = append(queue,adjacentpos);
                    
                    % calculate Fscore
                    Gscore = calculateGScore(Gscore,adjacentpos,currentGcost);
                    Hscore = calculateHScore(Hscore,adjacentpos, targetlocation);
                    Fscore(rows,cols) = Gscore(rows,cols) + Hscore(rows,cols);
                
                else % if it is already in open list update fscore if needed
                    oldFscore = Fscore(rows,cols);
                    Gscore = calculateGScore(Gscore,adjacentpos,currentGcost);
                    Hscore = calculateHScore(Hscore,adjacentpos, targetlocation);
                    newFscore = Gscore(rows,cols) + Hscore(rows,cols);
                    
                    if( newFscore < oldFscore)
                        Fscore(rows,cols) = newFscore;
                    end
                    
                end
            end
        end
        

    
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
    Hmaps = Hmap;
    Hmaps(xloc,yloc) = abs(xloc-target(1)) + abs(yloc-target(2));
end

%% calculating G score
function [Gmaps] = calculateGScore(Gmap,currentpos,currentcost)
        Gmaps = Gmap;
        xloc = currentpos(1);
        yloc = currentpos(2);
        Gmaps(xloc,yloc) = currentcost +1;
end

function [doesContain] = contains(cellarray, target)
    doesContain = false;
    for i = 1:length(cellarray)
        pos = cellarray{1,i};
        if (pos == target)
            doesContain = true;
            break
        end
    end
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
