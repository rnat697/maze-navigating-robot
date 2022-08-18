%% Dijkstra's Algorithm
% https://brilliant.org/wiki/dijkstras-short-path-finder/ --> explaination
% https://www.programiz.com/dsa/dijkstra-algorithm --> pseudocode
% https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/

% assume distances between each vertex is 1
function [retmap,retvisited,retsteps] = dfs(mapfile,startlocation,targetlocation)
    % for each vertex v in a map
        % distance[v]  = infinite
        % previous[v] = null
        % if vertex is not in the set S, add v to priority queue Q
    % distances[S] <- 0
    % while Q is not empty
        % U <- extract min from q
        % for each unvisited neighbour V of U
            % temp distance <- distance[u]+ edge_weight(u,v)
            % if temp distance < distance[u]
                % distance[V] <- temp distance
                % previous[V] <-- U
         % return distance[], prev[]
    

  % assume distances between each vertex is 1
  weight = ones(size(mapfile));
  distance = empty(size(mapfile));
  previous = empty(size(mapfile));
  [rows,cols] = size(mapfile);
  visiting = startlocation;
  queue = {};

  % set source node distance (start location) to 0  
   distance(startlocaiton(1),startlocation(2)) = 0;

   % load each element in distance array to an large value (infinity) and
   % load each element in prev array to null
   for i=1: rows
       for j = 1:cols
           vertex = [i,j];
           if(vertex ~= startlocation) 
                distance(i,j) = 500;
                previous(i,j) = null;
           end
           queue = append(queue,vertex);
           
       end
   end

    while(~isempty(queue))
        retsteps = visiting;
    
    end

  




    


end


function placestep(position,i)
    % This function will plot a insert yellow rectangle and also print a number in this rectangle. Use with plotmap/viewmap. 
    position = [16-position(1) position(2)];
    position=[position(2)+0.1 position(1)+0.1];
    rectangle('Position',[position,0.8,0.8],'FaceColor','y');
    c=sprintf('%d',i);
    text(position(1)+0.2,position(2)+0.2,c,'FontSize',10);
end

function [updatedStack] = append(stack,node)
    updatedStack = stack;
    updatedStack{length(stack)+1} = node;

end