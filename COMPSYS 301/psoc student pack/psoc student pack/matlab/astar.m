%% A*'s Algorithm
% see astar explaination.txt for further detail

function [retmap,retvisited,retsteps] = astar(mapfile,startlocation,targetlocation)

    %list of squares we checked to find the nearest path    open list (queue)
    %list that we have decided and will not change again close list(visitedlist & retvisted)
    queue  = {startlocation}; % list of squares we checked to find the nearest path (open list)
    mapSize = size(mapfile);
    retmap = mapfile;
    retsteps = {};
    visitedList = {}; % list that we have decided and will not change again (closed list)
    retvisited = ones(mapSize); % map of visited nodes where 1 = not visited, 0 = visited
    parents = {}; % map of parent locations (ie: the neighbouring nodes have "parent" nodes --> parent nodes is the current node)
    
    % maps of H, G and F scores
    Hscore = zeros(mapSize);
    Fscore = zeros(mapSize);
    Gscore = zeros(mapSize);
    
    prevFscore = 2000;
    currentGcost = 0;
    stepNum = 0;
    visiting = [-1,-1]; % just for initalisation purposes
    checkifAtEnd = 0;


    while (checkifAtEnd ~= 1) % ends when we found target location
        
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
        prevFscore = 5000; % reset to checking previous F node value for next iteration
        visitedList= append(visitedList,visiting); %add to closed list
        retvisited(visiting(1),visiting(2)) = 0; % place visited on visited map
        queue = removeElement(queue,index);

        %checks if location of node is at end
        checkifAtEnd =(targetlocation(1) == visiting(1)) && (targetlocation(2) == visiting(2));
        
       
        % determine neighbours of visiting node and caluclate Fscore
         ycurrent = visiting(1);
         xcurrent = visiting(2); 

         % Neighbours are S, N,E, W from the current location
         neighbours = {[ycurrent+1,xcurrent],[ycurrent-1,xcurrent ],[ycurrent,xcurrent+1],[ycurrent,xcurrent-1]};
         
         % calculate Fscore if neighbour is not in closed list (visitedList --> ie visted array)
         % and not in open list (queue) and is not a wall
        for j = 1: length(neighbours)
            adjacentpos = neighbours{1,j};
            rows = adjacentpos(1);
            cols = adjacentpos(2);
            newFscore = 0;
            currentGcost = Gscore(ycurrent,xcurrent);
            if (rows > 0 && cols >0 && retmap(rows,cols) ~= 1 && retvisited(rows,cols) ~= 0) % not a wall and has not been visited
                
                % check if open list (queue) does not contain current neighbouring position
                if(contains(queue,adjacentpos) == false)
                    queue = append(queue,adjacentpos);
                    
                    % calculate Fscore, Gscore and Hscore
                    % Fscore = Gscore + Hscore
                    Gscore = calculateGScore(Gscore,adjacentpos,currentGcost);
                    Hscore = calculateHScore(Hscore,adjacentpos, targetlocation);
                    Fscore(rows,cols) = Gscore(rows,cols) + Hscore(rows,cols);
                    
                    parents{rows,cols} = [ycurrent,xcurrent]; % add parent for the neighbouring node
                
                else % if it is already in open list update fscore if needed and update parent
                    oldFscore = Fscore(rows,cols);
                    Gscore = calculateGScore(Gscore,adjacentpos,currentGcost);
                    Hscore = calculateHScore(Hscore,adjacentpos, targetlocation);
                    newFscore = Gscore(rows,cols) + Hscore(rows,cols);
                  
                    % check if new Fscore is smaller than old Fscore
                    if(newFscore < oldFscore)
                        Fscore(rows,cols) = newFscore;
                        parents{rows,cols} = [ycurrent,xcurrent]; % update parent node of neighbour to current node
                    end
                    
                end
            end
        end
    end

    % Finds the actual shortest path by going in the reverse direction and looking at
    % a neighbour's parent location. eg: target location is [1,18], the
    % parent of that point is [2,18] so we go to [2,18] and find it's parents
    % until we get to the start node.
    % Starts from target node and get the paths back to start node
    
    currentNode = targetlocation;
    parentNode = [-1,-1]; % initialised parent node
    reversedPath = {};
    checkStart = 0;
    reversedPath = append(reversedPath,currentNode); % add target to reversed path list
    
    while(checkStart ~= 1)
        parentNode = parents{currentNode(1),currentNode(2)}; % find parent node associated with current node
        reversedPath = append(reversedPath,parentNode); % add to reversed path list
        currentNode = parentNode; % for next iteration
        checkStart = (currentNode(1) == startlocation(1) && currentNode(2)== startlocation(2));
    end
    retsteps = flip(reversedPath); % flips order of elements to make a path to go from start to target. 
    

    % display path on map
    for k = 1:length(retsteps)
        placestep(retsteps{k},k);
    end
end


%% calculating H score
% H score is the estimated cost of movement from start point to target and
% ignores walls.
% //Previously used Manhattan Distance [Hmaps(xloc,yloc)=abs(xloc-target(1)) + abs(yloc-target(2));)]//
% Using Euclidean Distance (supposed to be used for when we can move in any
% direction but it seems to give a more accurate cost which in turn will
% generate a more accurate shortest path) We have tried use Manhattan Distance
% since its best used for only moving left, right,up and down but it did
% not give an accurate shortest path in some situations.
% Eclidian Distance --> H = square root ((currentx - targetx)^2 + (currenty-targety)^2)
% See: https://www.geeksforgeeks.org/a-search-algorithm/]
function [Hmaps] = calculateHScore(Hmap,current, target)
    xloc = current(1);
    yloc = current(2);
    Hmaps = Hmap;
    Hmaps(xloc,yloc) = sqrt((xloc-target(1))^2 + (yloc-target(2))^2);
    
    
end

%% calculating G score
% G score is the movement score from the start point to current point. We
% add to the current cost by one each time we move away from start point.
function [Gmaps] = calculateGScore(Gmap,currentpos,currentcost)
        Gmaps = Gmap;
        xloc = currentpos(1);
        yloc = currentpos(2);
        Gmaps(xloc,yloc) = currentcost +1;
end

%% Checks if array contains a location
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

%% removes an specified element in the array
function[array]= removeElement(poparray,index)
    array = poparray;
    % Input index has to be a integer
        array(index)= [];
    

end
%% Appends to end of array
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
